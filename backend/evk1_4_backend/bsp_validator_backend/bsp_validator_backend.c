/** @file  bsp_validator_backend.c
 *  @brief Implement BSP validator facade prototype functions.
 *
 *  @copyright Copyright (C) 2024 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "bsp_validator_facade.h"
#include "evk.h"

/* CONSTANTS ******************************************************************/
#define LOG_UART_TIMEOUT_MS 1000

/* PUBLIC FUNCTIONS ***********************************************************/
void facade_bsp_init(void)
{
    evk_cfg_t evk_cfg = {
        .freq = CLK_169_98MHZ,
        .vdd = VDD_3V3,
    };
    evk_init(&evk_cfg);
}

void facade_uart_init(void)
{
    return;
}

void facade_time_delay(uint32_t ms)
{
    evk_timer_delay_ms(ms);
}

void facade_log_io(char *string)
{
    evk_uart_debug_write_blocking((uint8_t *)string, strlen(string), LOG_UART_TIMEOUT_MS);
}

void facade_context_switch_trigger(void)
{
    evk_radio_callback_context_switch();
}

void facade_set_context_switch_handler(void (*callback)(void))
{
    evk_set_pendsv_callback(callback);
}
