/** @file  sr1000/swc_def.h
 *  @brief SPARK Wireless Core definitions.
 *
 *  @copyright Copyright (C) 2022 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
               Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef SWC_DEF_H_
#define SWC_DEF_H_

/* INCLUDES *******************************************************************/
#include <stdbool.h>

/* TYPES **********************************************************************/
/** @brief Node's Role.
 */
typedef enum swc_role {
    /*! Node acts as the Coordinator */
    SWC_ROLE_COORDINATOR,
    /*! Node has no special function */
    SWC_ROLE_NODE
} swc_role_t;

/** @brief Node's Sleep Level.
 */
typedef enum swc_sleep_level {
    /*! Idle sleep level */
    SWC_SLEEP_IDLE,
    /*! Shallow sleep level */
    SWC_SLEEP_SHALLOW,
    /*! Deep sleep level */
    SWC_SLEEP_DEEP
} swc_sleep_level_t;

/** @brief Radio's Interrupt Request Polarity.
 */
typedef enum swc_irq_polarity {
    /*! Interrupt pin active in low state */
    SWC_IRQ_ACTIVE_LOW,
    /*! Interrupt pin active in high state */
    SWC_IRQ_ACTIVE_HIGH
} swc_irq_polarity_t;

/** @brief Radio's SPI mode.
 */
typedef enum swc_spi_mode {
    /*! SPI timings are standard */
    SWC_SPI_STANDARD,
    /*! SPI timings are optimized for high capacitive load on the bus */
    SWC_SPI_FAST
} swc_spi_mode_t;

/** @brief Connection's Modulation.
 */
typedef enum swc_modulation {
    /*! Inverted on-off keying */
    SWC_MOD_IOOK,
    /*! 2-bit pulse position modulation */
    SWC_MOD_2BITPPM
} swc_modulation_t;

/** @brief Connection's Forward Error Correction Ratio.
 */
typedef enum swc_fec_ratio {
    /*! FEC ratio 1.00 */
    SWC_FEC_1_0_0,
    /*! FEC ratio 1.33 */
    SWC_FEC_1_3_3,
    /*! FEC ratio 1.66 */
    SWC_FEC_1_6_6,
    /*! FEC ratio 2.00 */
    SWC_FEC_2_0_0,
} swc_fec_ratio_t;

/** @brief Clear Channel Assessment Fail Action.
 */
typedef enum swc_cca_fail_action {
    /*! Force transmission */
    SWC_CCA_FORCE_TX,
    /*! Abort transmission */
    SWC_CCA_ABORT_TX
} swc_cca_fail_action_t;

/** @brief Wireless core events.
 */
typedef enum swc_event {
    /*! No event */
    SWC_EVENT_NONE,
    /*! The connection is established between nodes */
    SWC_EVENT_CONNECT,
    /*! The connection is broken between nodes */
    SWC_EVENT_DISCONNECT,
    /*! An error occured on the wireless core */
    SWC_EVENT_ERROR
} swc_event_t;

/** @brief Concurrency modes.
 */
typedef enum swc_concurrency_mode {
    /*! Concurrency mode for high performance MCU */
    SWC_CONCURRENCY_MODE_HIGH_PERFORMANCE,
    /*! Concurrency mode for low performance MCU */
    SWC_CONCURRENCY_MODE_LOW_PERFORMANCE
} swc_concurrency_mode_t;

#endif /* SWC_DEF_H_ */
