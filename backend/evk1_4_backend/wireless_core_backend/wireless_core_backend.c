/** @file  evk1_4_backend.c
 *  @brief Implement swc_hal_facade facade prototype functions.
 *
 *  @copyright Copyright (C) 2024 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "evk.h"
#include "swc_hal_facade.h"

/* PUBLIC FUNCTIONS ***********************************************************/
/* Context Switching and Interrupt Management */
void swc_hal_radio_1_context_switch(void)
{
    evk_radio_context_switch();
}

void swc_hal_set_radio_1_irq_callback(void (*callback)(void))
{
    evk_set_radio_irq_callback(callback);
}

void swc_hal_set_radio_1_dma_rx_callback(void (*callback)(void))
{
    evk_set_radio_dma_rx_callback(callback);
}

void swc_hal_radio_1_disable_irq_it(void)
{
    evk_radio_disable_irq_it();
}

void swc_hal_radio_1_enable_irq_it(void)
{
    evk_radio_enable_irq_it();
}

void swc_hal_radio_1_disable_dma_irq_it(void)
{
    evk_radio_disable_dma_irq_it();
}

void swc_hal_radio_1_enable_dma_irq_it(void)
{
    evk_radio_enable_dma_irq_it();
}

/* GPIO Controls for Radios */
bool swc_hal_radio_1_read_irq_pin(void)
{
    return evk_radio_read_irq_pin();
}

void swc_hal_radio_1_set_reset_pin(void)
{
    evk_radio_set_reset_pin();
}

void swc_hal_radio_1_reset_reset_pin(void)
{
    evk_radio_reset_reset_pin();
}

/* SPI Communication */
void swc_hal_radio_1_spi_set_cs(void)
{
    evk_radio_spi_set_cs();
}

void swc_hal_radio_1_spi_reset_cs(void)
{
    evk_radio_spi_reset_cs();
}

void swc_hal_radio_1_spi_transfer_full_duplex_blocking(uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
    evk_radio_spi_transfer_full_duplex_blocking(tx_data, rx_data, size);
}

void swc_hal_radio_1_spi_transfer_full_duplex_non_blocking(uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
    evk_radio_spi_transfer_full_duplex_non_blocking(tx_data, rx_data, size);
}

bool swc_hal_radio_1_is_spi_busy(void)
{
    return evk_radio_is_spi_busy();
}

/* Timer and Delay Management */
uint64_t swc_hal_get_tick_free_running_timer(void)
{
    return evk_timer_free_running_ms_get_tick_count();
}

uint32_t swc_hal_get_free_running_timer_frequency_hz(void)
{
    return evk_timer_free_running_ms_get_tick_frequency();
}
