/** @file  evk1.4_backend.c
 *  @brief Implement audio unidrectional facade prototype functions.
 *
 *  @copyright Copyright (C) 2024 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "audio_bidirectional_facade.h"
#include "evk.h"
#include "max98091.h"
#include "tinyusb_baremetal.h"

/* CONSTANTS ******************************************************************/
#define TIMER_SELECTION_AUDIO_PROCESS_MAIN_CHANNEL    EVK_TIMER_SELECTION_TIMER15
#define TIMER_SELECTION_AUDIO_PROCESS_BACK_CHANNEL    EVK_TIMER_SELECTION_TIMER20
#define TIMER_SELECTION_DATA                          EVK_TIMER_SELECTION_TIMER3

#define IRQ_PRIORITY_TIMER_AUDIO_PROCESS_MAIN_CHANNEL 13
#define IRQ_PRIORITY_TIMER_AUDIO_PROCESS_BACK_CHANNEL 14
#define IRQ_PRIORITY_TIMER_DATA                       15

#define DELAY_MS_LONG_PERIOD                          250
#define DELAY_MS_SHORT_PERIOD                         100
#define LED_BLINK_REPEAT                              2

#define USER_RESPONSE_DELAY_MS                        1000
#define LED_BLINK_CERTIFICATION_MODE_1                1
#define LED_BLINK_CERTIFICATION_MODE_2                2
#define LED_BLINK_CERTIFICATION_MODE_3                3

/* Button press timings. */
#define SHORT_PRESS_TIME_MS 250
#define LONG_PRESS_TIME_MS  3000

/* TYPES **********************************************************************/
/** @brief Structure tracking a button's state, press start time, and whether it is currently held and handled.
 */
typedef struct button_handle {
    evk_btn_t button_id;
    uint32_t press_start_time;
    bool active;
    bool handled;
} button_handle_t;

/* PRIVATE GLOBALS ************************************************************/
static max98091_i2c_hal_t codec_hal = {
    .i2c_addr = MAX98091A_I2C_ADDR,
    .read = evk_audio_i2c_read_byte_blocking,
    .write = evk_audio_i2c_write_byte_blocking,
};

/* PRIVATE FUNCTION PROTOTYPES ************************************************/
static void led_all_toggle(void);
static void led1_blink(uint8_t blink_count);
static void handle_button_state(button_handle_t *button_handle, void (*short_press_button_callback)(void),
                                void (*long_press_button_callback)(void));

/* PUBLIC FUNCTIONS ***********************************************************/
void facade_context_switch_trigger(void)
{
    evk_radio_callback_context_switch();
}

void facade_set_context_switch_handler(void (*callback)(void))
{
    evk_set_pendsv_callback(callback);
}

void facade_board_init(void)
{
    evk_cfg_t evk_cfg = {
        .freq = CLK_169_98MHZ,
        .vdd = VDD_3V3,
    };
    evk_init(&evk_cfg);

    /* Initialize the Codec's I2C interface. */
    evk_audio_i2c_init();

    tinyusb_baremetal_setup();
}

void facade_audio_coord_init(void)
{
    evk_sai_config_t sai_config = {
        /* SAI communicating from the codec to the CPU; the Coordinator sends stereo. */
        .rx_sai_mono_stereo = EVK_SAI_MODE_STEREO,
        /* SAI communicating from the CPU to the codec; the Coordinator receives mono. */
        .tx_sai_mono_stereo = EVK_SAI_MODE_MONO,
        .sai_bit_depth = EVK_SAI_BIT_DEPTH_24BITS,
    };

    /* Reset codec before initializing the SAI. */
    max98091_reset_codec(&codec_hal);
    evk_timer_delay_ms(1);

    evk_audio_sai_configuration(&sai_config);

    max98091_codec_cfg_t cfg = {
        .sampling_rate = MAX98091_AUDIO_48KHZ,
        .word_size = MAX98091_AUDIO_24BITS,
        .record_enabled = true,
        .playback_enabled = true,
        .record_filter_enabled = false,
        .playback_filter_enabled = false,
    };
    max98091_init(&codec_hal, &cfg);
}

void facade_audio_node_init(void)
{
    evk_sai_config_t sai_config = {
        /* SAI communicating from the codec to the CPU; the Node sends mono. */
        .rx_sai_mono_stereo = EVK_SAI_MODE_MONO,
        /* SAI communicating from the CPU to the codec; the Node receives stereo. */
        .tx_sai_mono_stereo = EVK_SAI_MODE_STEREO,
        .sai_bit_depth = EVK_SAI_BIT_DEPTH_24BITS,
    };

    /* Reset codec before initializing the SAI. */
    max98091_reset_codec(&codec_hal);
    evk_timer_delay_ms(1);

    evk_audio_sai_configuration(&sai_config);

    max98091_codec_cfg_t cfg = {
        .sampling_rate = MAX98091_AUDIO_48KHZ,
        .word_size = MAX98091_AUDIO_24BITS,
        .record_enabled = true,
        .playback_enabled = true,
        .record_filter_enabled = false,
        .playback_filter_enabled = false,
    };
    max98091_init(&codec_hal, &cfg);
}

void facade_audio_deinit(void)
{
    evk_audio_sai_deinit();
    max98091_reset_codec(&codec_hal);
}

void facade_set_sai_complete_callback(void (*tx_callback)(void), void (*rx_callback)(void))
{
    evk_audio_set_sai_tx_dma_cplt_callback((irq_callback)tx_callback);
    evk_audio_set_sai_rx_dma_cplt_callback((irq_callback)rx_callback);
}

facade_certification_mode_t facade_get_certification_mode(void)
{
    if (!evk_read_btn_state(BTN2)) {
        /* If button 2 is not pressed, the application runs normally without entering any certification mode. */
        return FACADE_CERTIF_NONE;
    }

    /* If button 2 is pressed at board startup, the application enters in a certification selection mode. */
    led1_blink(LED_BLINK_CERTIFICATION_MODE_1);
    evk_timer_delay_ms(USER_RESPONSE_DELAY_MS);

    if (!evk_read_btn_state(BTN2)) {
        /* Button held for less than 1 delay period.
         * -> Entering in audio 24 bit certification mode.
         */
        return FACADE_CERTIF_AUDIO_24_BIT;
    }

    led1_blink(LED_BLINK_CERTIFICATION_MODE_2);
    evk_timer_delay_ms(USER_RESPONSE_DELAY_MS);

    if (!evk_read_btn_state(BTN2)) {
        /* Button held for less than 2 delay periods.
         * -> Entering in audio ADPCM certification mode.
         */
        return FACADE_CERTIF_AUDIO_ADPCM;
    }

    /* Button held for more than 2 delay periods.
     * -> Entering in data certification mode.
     */
    led1_blink(LED_BLINK_CERTIFICATION_MODE_3);
    return FACADE_CERTIF_DATA;
}

void facade_button_handling(void (*button1_callback)(void), void (*button2_callback)(void),
                            void (*button3_callback)(void), void (*button4_callback)(void))
{
    static button_handle_t btn1_handle = {
        .button_id = BTN1,
    };
    static button_handle_t btn2_handle = {
        .button_id = BTN2,
    };

    handle_button_state(&btn1_handle, button3_callback, button1_callback);
    handle_button_state(&btn2_handle, button4_callback, button2_callback);
}

void facade_tx_audio_conn_status(void)
{
    evk_led_toggle(LED0);
}

void facade_tx_data_conn_status(void)
{
}

void facade_rx_audio_conn_status(void)
{
    evk_led_toggle(LED0);
}

void facade_rx_data_conn_status(void)
{
}

void facade_fallback_status(bool on)
{
    if (on) {
        evk_led_on(LED1);
    } else {
        evk_led_off(LED1);
    }
}

void facade_audio_process_main_channel_timer_init(void (*callback)(void))
{
    evk_timer_cfg_t timer_config = {
        .timer_selection = TIMER_SELECTION_AUDIO_PROCESS_MAIN_CHANNEL,
        /* Initialize timer base value to 1 second. */
        .time_base = EVK_TIMER_TIME_BASE_MILLISECOND,
        .time_period = 1000,
        .irq_priority = IRQ_PRIORITY_TIMER_AUDIO_PROCESS_MAIN_CHANNEL,
    };
    evk_timer_init(timer_config);
    evk_it_set_timer15_callback(callback);
}

void facade_audio_process_back_channel_timer_init(void (*callback)(void))
{
    evk_timer_cfg_t timer_config = {
        .timer_selection = TIMER_SELECTION_AUDIO_PROCESS_BACK_CHANNEL,
        /* Initialize timer base value to 1 second. */
        .time_base = EVK_TIMER_TIME_BASE_MILLISECOND,
        .time_period = 1000,
        .irq_priority = IRQ_PRIORITY_TIMER_AUDIO_PROCESS_BACK_CHANNEL,
    };
    evk_timer_init(timer_config);
    evk_it_set_timer20_callback(callback);
}

void facade_audio_process_main_channel_timer_start(void)
{
    evk_timer_start(TIMER_SELECTION_AUDIO_PROCESS_MAIN_CHANNEL);
}

void facade_audio_process_main_channel_timer_trigger(void)
{
    evk_timer_generate_event(TIMER_SELECTION_AUDIO_PROCESS_MAIN_CHANNEL);
}

void facade_audio_process_back_channel_timer_trigger(void)
{
    evk_timer_generate_event(TIMER_SELECTION_AUDIO_PROCESS_BACK_CHANNEL);
}

void facade_audio_process_back_channel_timer_start(void)
{
    evk_timer_start(TIMER_SELECTION_AUDIO_PROCESS_BACK_CHANNEL);
}

void facade_audio_process_main_channel_timer_stop(void)
{
    evk_timer_stop(TIMER_SELECTION_AUDIO_PROCESS_MAIN_CHANNEL);
}

void facade_audio_process_back_channel_timer_stop(void)
{
    evk_timer_stop(TIMER_SELECTION_AUDIO_PROCESS_BACK_CHANNEL);
}

void facade_data_timer_init(uint32_t period_ms)
{
    evk_timer_cfg_t timer_cfg = {
        .timer_selection = TIMER_SELECTION_DATA,
        .time_base = EVK_TIMER_TIME_BASE_MILLISECOND,
        .time_period = period_ms,
        .irq_priority = IRQ_PRIORITY_TIMER_DATA,
    };
    evk_timer_init(timer_cfg);
}

void facade_data_timer_set_callback(void (*callback)(void))
{
    evk_it_set_timer3_callback(callback);
}

void facade_data_timer_start(void)
{
    evk_timer_start(TIMER_SELECTION_DATA);
}

void facade_data_timer_stop(void)
{
    evk_timer_stop(TIMER_SELECTION_DATA);
}

void facade_print_string(char *string)
{
    if (tud_cdc_connected()) {
        tud_cdc_write_str(string);
        tud_cdc_write_flush();
    }
}

void facade_print_error_string(char *string)
{
    /* Turn OFF LEDs to show nothing is happening. */
    facade_led_all_off();

    /* Set to highest priority. */
    HAL_NVIC_SetPriority(NVIC_USB_LP_IRQ, 0, 0);
    facade_print_string(string);
}

void facade_empty_payload_received_status(void)
{
    evk_led_off(LED2);
}

void facade_payload_received_status(void)
{
    evk_led_on(LED2);
}

void facade_notify_enter_pairing(void)
{
    uint16_t delay_ms = DELAY_MS_LONG_PERIOD;
    uint8_t repeat = LED_BLINK_REPEAT;

    evk_led_off(LED0);

    for (uint8_t i = 0; i < repeat; i++) {
        evk_timer_delay_ms(delay_ms);
        evk_led_on(LED0);
        evk_timer_delay_ms(delay_ms);
        evk_led_off(LED0);
    }
}

void facade_notify_not_paired(void)
{
    uint16_t delay_ms = DELAY_MS_LONG_PERIOD;

    facade_led_all_off();

    for (uint8_t i = 0; i < LED_BLINK_REPEAT * LED_BLINK_REPEAT; i++) {
        evk_timer_delay_ms(delay_ms);
        led_all_toggle();
    }
}

void facade_notify_pairing_successful(void)
{
    uint16_t delay_ms = DELAY_MS_SHORT_PERIOD;

    facade_led_all_off();
    evk_timer_delay_ms(delay_ms);
    evk_led_on(LED0);
    evk_timer_delay_ms(delay_ms);
    evk_led_on(LED1);
    evk_timer_delay_ms(delay_ms);
    evk_led_on(LED2);
    evk_timer_delay_ms(delay_ms);
    evk_led_off(LED2);
    evk_timer_delay_ms(delay_ms);
    evk_led_off(LED1);
    evk_timer_delay_ms(delay_ms);
    evk_led_off(LED0);
}

void facade_led_all_off(void)
{
    evk_led_off(LED0);
    evk_led_off(LED1);
    evk_led_off(LED2);
}

uint32_t facade_get_tick_ms(void)
{
    return evk_timer_free_running_ms_get_tick_count();
}

bool facade_read_button_state(void)
{
    return evk_read_btn_state(BTN2);
}

/* PRIVATE FUNCTIONS **********************************************************/
/** @brief Toggle all LEDs.
 */
static void led_all_toggle(void)
{
    evk_led_toggle(LED0);
    evk_led_toggle(LED1);
    evk_led_toggle(LED2);
}

/** @brief Blinks the LED 1 a specified number of times.
 *
 *  @param[in] blink_count  The number of times to blink the LED.
 */
static void led1_blink(uint8_t blink_count)
{
    evk_led_off(LED1);
    for (int i = 0; i < blink_count * LED_BLINK_REPEAT; i++) {
        evk_led_toggle(LED1);
        evk_timer_delay_ms(DELAY_MS_LONG_PERIOD);
    }
}

/** @brief Manages the state of a button, detecting presses and triggering a callback on a long press.
 *
 *  @param[in] button_handle                Pointer to the button state structure.
 *  @param[in] short_press_button_callback  Function to call when a short press is detected.
 *  @param[in] long_press_button_callback   Function to call when a long press is detected.
 */
static void handle_button_state(button_handle_t *button_handle, void (*short_press_button_callback)(void),
                                void (*long_press_button_callback)(void))
{
    uint32_t current_time = evk_timer_get_ms_tick();

    if (evk_read_btn_state(button_handle->button_id)) {
        if (!button_handle->active) {
            /* Button is pressed, start timing for long press. */
            button_handle->press_start_time = current_time;
            button_handle->active = true;
            /* Reset the handled flag on a new press. */
            button_handle->handled = false;
        } else if (!button_handle->handled && (current_time - button_handle->press_start_time >= LONG_PRESS_TIME_MS)) {
            /* Mark as handled so the callback doesn’t trigger again. */
            button_handle->handled = true;
            /* Button has been held long enough. */
            if (long_press_button_callback != NULL) {
                long_press_button_callback();
            }
        }
    } else {
        /* Button is released. */
        if (button_handle->active && ((current_time - button_handle->press_start_time) <= SHORT_PRESS_TIME_MS)) {
            if (short_press_button_callback != NULL) {
                short_press_button_callback();
            }
        }
        /* Reset button state. */
        button_handle->active = false;
        button_handle->handled = false;
    }
}
