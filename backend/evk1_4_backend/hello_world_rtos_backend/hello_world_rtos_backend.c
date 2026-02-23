/** @file  evk1_4_backend.c
 *  @brief Implement hello-world-rtos facade prototype functions.
 *
 *  @copyright Copyright (C) 2024 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "evk.h"
#include "hello_world_rtos_facade.h"
#include "tinyusb_freertos.h"

/* CONSTANTS ******************************************************************/
#define DELAY_MS_SHORT_PERIOD       100
#define DELAY_MS_LONG_PERIOD        250
#define LED_BLINK_REPEAT_PAIRING    2
#define LED_BLINK_REPEAT_NOT_PAIRED 4
#define BUTTON_IRQ_PRIORITY         15

/* Button press timings. */
#define SHORT_PRESS_TIME_MS            250
#define LONG_PRESS_TIME_MS             3000

#define DELAY_MS_LONG_PERIOD           250
#define DELAY_MS_SHORT_PERIOD          100
#define LED_BLINK_REPEAT               2

#define USER_RESPONSE_DELAY_MS         1000
#define LED_BLINK_CERTIFICATION_MODE_1 1

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
static void (*button_app_callback)(void);

/* PRIVATE FUNCTION PROTOTYPES ************************************************/
static void led_all_toggle(void);
static void led_all_off(void);
static void led1_blink(uint8_t blink_count);
static void handle_button_state(button_handle_t *button_handle, void (*short_press_button_callback)(void),
                                void (*long_press_button_callback)(void));
static void initialize_button_gpio(void);
static void button_isr(void);

/* PUBLIC FUNCTIONS ***********************************************************/
void facade_board_init(void)
{
    evk_cfg_t evk_cfg = {
        .freq = CLK_169_98MHZ,
        .vdd = VDD_3V3,
    };
    evk_init(&evk_cfg);

    initialize_button_gpio();

    tinyusb_freertos_task_setup();
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

void facade_set_button_event_callback(void (*button_event_callback)(void))
{
    button_app_callback = button_event_callback;
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
    uint16_t delay_ms = DELAY_MS_LONG_PERIOD;
    uint8_t repeat = LED_BLINK_REPEAT_PAIRING;

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
    uint8_t repeat = LED_BLINK_REPEAT_NOT_PAIRED;

    led_all_off();

    for (uint8_t i = 0; i < repeat; i++) {
        evk_timer_delay_ms(delay_ms);
        led_all_toggle();
    }
}

void facade_notify_pairing_successful(void)
{
    uint16_t delay_ms = DELAY_MS_SHORT_PERIOD;

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

/* PRIVATE FUNCTIONS **********************************************************/
/** @brief Button interrupt service routine.
 */
static void button_isr(void)
{
    if (button_app_callback != NULL) {
        button_app_callback();
    }
}

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

facade_certification_mode_t facade_get_certification_mode(void)
{
    /* If button 2 is pressed at board startup, the application enters in a certification selection mode. */
    if (evk_read_btn_state(BTN2)) {
        led1_blink(LED_BLINK_CERTIFICATION_MODE_1);
        evk_timer_delay_ms(USER_RESPONSE_DELAY_MS);

        return FACADE_CERTIF_HELLO_WORLD_RTOS;
    }

    /* If button 2 is not pressed, the application runs normally without entering any certification mode. */
    return FACADE_CERTIF_NONE;
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
        } else if (button_handle->active && !button_handle->handled &&
                   ((current_time - button_handle->press_start_time) >= LONG_PRESS_TIME_MS)) {
            /* Button has been held long enough. */
            if (long_press_button_callback != NULL) {
                long_press_button_callback();
            }
        }
        /* Reset button state. */
        button_handle->active = false;
        button_handle->handled = false;
    }
}

static void initialize_button_gpio(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = BTN0_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BTN0_PORT, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, BUTTON_IRQ_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* Configure button callback. */
    evk_set_but0_irq_callback(button_isr);
}
