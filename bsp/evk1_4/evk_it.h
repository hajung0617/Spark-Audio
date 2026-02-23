/** @file  evk_it.h
 *  @brief This module controls interrupt related features.
 *
 *  @copyright Copyright (C) 2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef EVK_IT_H_
#define EVK_IT_H_

/* INCLUDES *******************************************************************/
#include "evk_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PUBLIC FUNCTION PROTOTYPES *************************************************/
/** @brief This functions sets the function callback for the every interrupt.
 *
 *  @param[in] callback  Common callback function pointer.
 */
void evk_it_set_common_callback(void (*callback)(void));

/** @brief This function sets the function callback for USB detection interrupt.
 *
 *  @param[in] callback  USB Detect callback function pointer.
 */
void evk_set_usb_detect_callback(void (*callback)(void));

/** @brief This function sets the function callback for the radio pin interrupt.
 *
 *  @param[in] callback  External interrupt callback function pointer.
 */
void evk_set_radio_irq_callback(void (*callback)(void));

/** @brief This function sets the function callback for the button 0 pin interrupt.
 *
 *  @param[in] callback  External interrupt callback function pointer.
 */
void evk_set_but0_irq_callback(void (*callback)(void));

/** @brief This function sets the function callback for the button 1 pin interrupt.
 *
 *  @param[in] callback  External interrupt callback function pointer.
 */
void evk_set_but1_irq_callback(void (*callback)(void));

/** @brief This function sets the function callback for the DMA_RX ISR.
 *
 *  @param[in] callback  External interrupt callback function pointer.
 */
void evk_set_radio_dma_rx_callback(void (*callback)(void));

/** @brief This function sets the function callback for the pendsv.
 *
 *  @param[in] callback  External interrupt callback function pointer.
 */
void evk_set_pendsv_callback(void (*callback)(void));

/** @brief Set USB IRQ callback.
 *
 *  @param[in] callback  USB IRQ callback.
 */
void evk_set_usb_irq_callback(void (*callback)(void));

/** @brief Set Timer 1 interrupt callback.
 *
 *  @param[in] callback  Timer 1 callback.
 */
void evk_it_set_timer1_callback(void (*callback)(void));

/** @brief Set Timer 2 interrupt callback.
 *
 *  @param[in] callback  Timer 2 callback.
 */
void evk_it_set_timer2_callback(void (*callback)(void));

/** @brief Set Timer 3 interrupt callback.
 *
 *  @param[in] callback  Timer 3 callback.
 */
void evk_it_set_timer3_callback(void (*callback)(void));

/** @brief Set Timer 4 interrupt callback.
 *
 *  @param[in] callback  Timer 4 callback.
 */
void evk_it_set_timer4_callback(void (*callback)(void));

/** @brief Set Timer 5 interrupt callback.
 *
 *  @param[in] callback  Timer 5 callback.
 */
void evk_it_set_timer5_callback(void (*callback)(void));

/** @brief Set Timer 6 interrupt callback.
 *
 *  @param[in] callback  Timer 6 callback.
 */
void evk_it_set_timer6_callback(void (*callback)(void));

/** @brief Set Timer 7 interrupt callback.
 *
 *  @param[in] callback  Timer 7 callback.
 */
void evk_it_set_timer7_callback(void (*callback)(void));

/** @brief Set Timer 8 interrupt callback.
 *
 *  @param[in] callback  Timer 8 callback.
 */
void evk_it_set_timer8_callback(void (*callback)(void));

/** @brief Set Timer 15 interrupt callback.
 *
 *  @param[in] callback  Timer 15 callback.
 */
void evk_it_set_timer15_callback(void (*callback)(void));

/** @brief Set Timer 16 interrupt callback.
 *
 *  @param[in] callback  Timer 16 callback.
 */
void evk_it_set_timer16_callback(void (*callback)(void));

/** @brief Set Timer 17 interrupt callback.
 *
 *  @param[in] callback  Timer 17 callback.
 */
void evk_it_set_timer17_callback(void (*callback)(void));

/** @brief Set Timer 20 interrupt callback.
 *
 *  @param[in] callback  Timer 20 callback.
 */
void evk_it_set_timer20_callback(void (*callback)(void));

/** @brief Disable IRQ Interrupts.
 */
void evk_enter_critical(void);

/** @brief Enable IRQ Interrupts.
 */
void evk_exit_critical(void);

/** @brief Error handle used by STM32 HAL.
 */
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* EVK_IT_H_ */
