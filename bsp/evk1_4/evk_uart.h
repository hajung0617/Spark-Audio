/** @file  evk_uart.h
 *  @brief This module controls UART features of SPARK EVK board.
 *
 *  @copyright Copyright (C) 2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef EVK_UART_H_
#define EVK_UART_H_

/* INCLUDES *******************************************************************/
#include "evk_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PUBLIC FUNCTION PROTOTYPES *************************************************/
/** @brief Initialize the UART bus connected to the expansion board.
 */
void evk_exp_uart_init(void);

/** @brief Initialize the low power UART bus connected to the expansion board.
 */
void evk_exp_lpuart_init(void);

/** @brief Update the configuration of the low power UART, useful when clock changes.
 */
void evk_exp_lpuart_update_config(void);

/** @brief Read data on the LPUART which is on the expansion board.
 *
 *  @param[in] data        Data buffer to write.
 *  @param[in] size        Size of the data to write.
 *  @param[in] timeout_ms  The amount of milliseconds before timeout.
 */
void evk_uart_debug_read_blocking(uint8_t *data, uint16_t size, uint32_t timeout_ms);

/** @brief Write data on the debug UART.
 *
 *  @param[in] data        Data buffer to write.
 *  @param[in] size        Size of the data to write.
 *  @param[in] timeout_ms  The amount of milliseconds before timeout.
 */
void evk_uart_debug_write_blocking(uint8_t *data, uint16_t size, uint32_t timeout_ms);

/** @brief Write data on the debug UART in non blocking mode.
 *
 *  @param[in] data  Data buffer to write.
 *  @param[in] size  Size of the data to write.
 */
void evk_uart_debug_write_non_blocking(uint8_t *data, uint16_t size);

/** @brief Read byte on the debug UART in non blocking mode.
 *
 *  @param[in] data  Data byte to write.
 */
void evk_uart_debug_read_byte_non_blocking(uint8_t *data);

/** @brief Set the debug LPUART TX callback.
 *
 *  @param[in] callback  Pointer to the LPUART TX callback.
 */
void evk_uart_debug_set_tx_callback(void (*callback)(void));

/** @brief Set the debug LPUART RX callback.
 *
 *  @param[in] callback  Pointer to the LPUART RX callback.
 */
void evk_uart_debug_set_rx_callback(void (*callback)(void));

/** @brief Disable debug UART DMA RX interrupt.
 */
void evk_uart_debug_dma_rx_enter_critical(void);

/** @brief Enable debug UART DMA RX interrupt.
 */
void evk_uart_debug_dma_rx_exit_critical(void);

/** @brief Stop debug UART receive with DMA peripheral.
 */
void evk_uart_debug_stop_read_non_blocking(void);

/** @brief Set the expansion UART RX callback.
 *
 *  @param[in] callback  Pointer to the UART RX callback.
 */
void evk_uart_exp_set_rx_callback(void (*callback)(void));

/** @brief Set the expansion UART TX callback.
 *
 *  @param[in] callback  Pointer to the UART TX callback.
 */
void evk_uart_exp_set_tx_callback(void (*callback)(void));

/** @brief Write data on the expansion UART in non blocking interrupt mode.
 *
 *  @param[in] data  Data buffer to write.
 *  @param[in] size  Size of the data to write.
 */
void evk_uart_exp_write_non_blocking_interrupt(uint8_t *data, uint16_t size);

/** @brief Read data from the expansion UART in non blocking interrupt mode.
 *
 *  @param[in] data  Data buffer to read.
 *  @param[in] size  Size of the data to read.
 */
void evk_uart_exp_read_non_blocking_interrupt(uint8_t *data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* EVK_UART_H_ */
