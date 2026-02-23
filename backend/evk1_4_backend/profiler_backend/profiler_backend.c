/** @file  profiler_backend.c
 *  @brief Implement Profiler facade prototype functions.
 *
 *  @copyright Copyright (C) 2025 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include <string.h>
#include "evk.h"
#include "profiler_facade.h"

/* CONSTANTS ******************************************************************/
#define IRQ_PRIORITY_TMER_PACKET_GENERATION (PRIO_PENDSV_IRQ + 1)
#define TIMER_SELECTION_PACKET_GENERATION   EVK_TIMER_SELECTION_TIMER8
#define SEC_TO_US                           ((double)1e6)

/* CONSTANTS ******************************************************************/
#define LOG_UART_TIMEOUT_MS 1000

/* PRIVATE GLOBALS ************************************************************/
static uint32_t timestamp_begin;

/* PUBLIC FUNCTIONS ***********************************************************/
void facade_board_init(void)
{
    evk_cfg_t evk_cfg = {
        .freq = CLK_169_98MHZ,
        .vdd = VDD_3V3,
    };
    evk_init(&evk_cfg);
}

void facade_delay(uint32_t ms_delay)
{
    evk_timer_delay_ms(ms_delay);
}

void facade_log_init(void)
{
    /* The UART is already initialized in the evk_init function. */
    return;
}

void facade_log_write(char *string)
{
    evk_uart_debug_write_blocking((uint8_t *)string, strlen(string), LOG_UART_TIMEOUT_MS);
}

void facade_log_error_string(char *string)
{
    /* Turn OFF LEDs to show nothing is happening. */
    facade_led_all_off();

    /* Set to highest priority. */
    HAL_NVIC_SetPriority(NVIC_USB_LP_IRQ, 0, 0);
    facade_log_write(string);
}

void facade_context_switch_trigger(void)
{
    evk_radio_callback_context_switch();
}

void facade_set_context_switch_handler(void (*callback)(void))
{
    evk_set_pendsv_callback(callback);
}

void facade_packet_generation_timer_init(uint32_t period)
{
    evk_timer_cfg_t timer_config = {
        .timer_selection = TIMER_SELECTION_PACKET_GENERATION,
        .time_base = EVK_TIMER_TIME_BASE_MICROSECOND,
        .time_period = period,
        .irq_priority = IRQ_PRIORITY_TMER_PACKET_GENERATION,
    };
    evk_timer_init(timer_config);
}

void facade_packet_generation_set_timer_callback(void (*irq_callback)(void))
{
    evk_it_set_timer8_callback(irq_callback);
}

void facade_packet_generation_timer_start(void)
{
    evk_timer_start(TIMER_SELECTION_PACKET_GENERATION);
}

void facade_packet_generation_timer_stop(void)
{
    evk_timer_stop(TIMER_SELECTION_PACKET_GENERATION);
}

void facade_profiler_init(void)
{
    evk_profiler_init();
}

void facade_profiler_start(uint32_t *timestamp_start_handle)
{
    if (timestamp_start_handle == NULL) {
        timestamp_begin = evk_profiler_get_cycle_count();
        return;
    }

    *timestamp_start_handle = evk_profiler_get_cycle_count();
}

uint32_t facade_profiler_stop(uint32_t *timestamp_start_handle)
{
    uint32_t timestamp_end = evk_profiler_get_cycle_count();

    if (timestamp_start_handle == NULL) {
        return timestamp_end - timestamp_begin;
    }

    return timestamp_end - *timestamp_start_handle;
}

double facade_profiler_get_elapsed_us(uint32_t cycle_count)
{
    double clk_freq = (double)evk_get_system_clock_freq();

    return ((double)cycle_count / clk_freq) * SEC_TO_US;
}

void facade_tx_conn_status(void)
{
    evk_led_toggle(LED0);
}

void facade_rx_conn_status(void)
{
    evk_led_toggle(LED1);
}

void facade_led_all_off(void)
{
    evk_led_off(LED0);
    evk_led_off(LED1);
    evk_led_off(LED2);
}
