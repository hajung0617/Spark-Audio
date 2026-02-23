/** @file  evk1_4_backend.c
 *  @brief Implement datalink facade prototype functions.
 *
 *  @copyright Copyright (C) 2024 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "datalink_facade.h"
#include "evk.h"
#include "tinyusb_baremetal.h"

/* CONSTANTS ******************************************************************/
#define IRQ_PRIORITY_TMER_PACKET_GENERATION 8
#define TIMER_SELECTION_PACKET_GENERATION   EVK_TIMER_SELECTION_TIMER8

#define DELAY_MS_LONG_PERIOD                250
#define DELAY_MS_SHORT_PERIOD               100
#define LED_BLINK_REPEAT                    2

#define USER_RESPONSE_DELAY_MS              1000
#define LED_BLINK_CERTIFICATION_MODE_1      1
#define LED_BLINK_CERTIFICATION_MODE_2      2

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

/* PRIVATE FUNCTION PROTOTYPES ************************************************/
static void led_all_toggle(void);
static void led_all_off(void);
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

void facade_packet_generation_set_timer_callback(void (*irq_callback)(void))
{
    evk_it_set_timer8_callback(irq_callback);
}

void facade_packet_generation_timer_init(uint32_t timeslot)
{
    evk_timer_cfg_t timer_config = {
        .timer_selection = TIMER_SELECTION_PACKET_GENERATION,
        .time_base = EVK_TIMER_TIME_BASE_MICROSECOND,
        .time_period = timeslot / 2,
        .irq_priority = IRQ_PRIORITY_TMER_PACKET_GENERATION,
    };
    evk_timer_init(timer_config);
}

void facade_packet_generation_timer_start(void)
{
    evk_timer_start(TIMER_SELECTION_PACKET_GENERATION);
}

void facade_packet_generation_timer_stop(void)
{
    evk_timer_stop(TIMER_SELECTION_PACKET_GENERATION);
}

void facade_board_init(void)
{
    evk_cfg_t evk_cfg = {
        .freq = CLK_169_98MHZ,
        .vdd = VDD_3V3,
    };
    evk_init(&evk_cfg);

    tinyusb_baremetal_setup();
}

facade_certification_mode_t facade_get_certification_mode(void)
{
    /* If button 2 is pressed at board startup, the application enters in a certification selection mode. */
    if (evk_read_btn_state(BTN2)) {
        led1_blink(LED_BLINK_CERTIFICATION_MODE_1);
        evk_timer_delay_ms(USER_RESPONSE_DELAY_MS);

        return FACADE_CERTIF_DATALINK;
    }

    /* If button 2 is not pressed, the application runs normally without entering any certification mode. */
    return FACADE_CERTIF_NONE;
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

    handle_button_state(&btn1_handle, button2_callback, button1_callback);
    handle_button_state(&btn2_handle, button4_callback, button3_callback);
}

void facade_tx_conn_status(void)
{
    evk_led_toggle(LED0);
}

void facade_rx_conn_status(void)
{
    evk_led_toggle(LED1);
}

void facade_delay(uint32_t ms_delay)
{
    evk_timer_delay_ms(ms_delay);
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

void facade_notify_enter_pairing(void)
{
    uint16_t delay_ms = 250;
    uint8_t repeat = 2;

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
    uint16_t delay_ms = 250;
    uint8_t repeat = 4;

    led_all_off();

    for (uint8_t i = 0; i < repeat; i++) {
        evk_timer_delay_ms(delay_ms);
        led_all_toggle();
    }
}

void facade_notify_pairing_successful(void)
{
    uint16_t delay_ms = 100;

    led_all_off();
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

/* PRIVATE FUNCTIONS **********************************************************/
/** @brief Toggle all LEDs.
 */
static void led_all_toggle(void)
{
    evk_led_toggle(LED0);
    evk_led_toggle(LED1);
    evk_led_toggle(LED2);
}

/** @brief Turn off all LEDs.
 */
static void led_all_off(void)
{
    evk_led_off(LED0);
    evk_led_off(LED1);
    evk_led_off(LED2);
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
