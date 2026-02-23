/** @file  evk_flash.h
 *  @brief This module is composed of all functionalities related to the MCU's flash memory.
 *
 *  @copyright Copyright (C) 2020-2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef EVK_FLASH_H_
#define EVK_FLASH_H_

/* INCLUDES *******************************************************************/
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CONSTANTS ******************************************************************/
/* Current __COUNTER__ value. */
enum {
    EVK_FLASH_COUNTER_BASE = __COUNTER__
};

/* MACROS *********************************************************************/
/** @brief Create a local counter macro.
 */
#define EVK_FLASH_COUNTER (__COUNTER__ - EVK_FLASH_COUNTER_BASE)

/** @brief Automatically increase error count each time invoked. Starts at -(0 + 1) = -1.
 */
#define EVK_FLASH_GENERATE_ERR_CODE (-(EVK_FLASH_COUNTER + 1))

/* TYPES **********************************************************************/
/** @brief Flash error status.
 */
typedef enum evk_flash_error {
    /*! No error was detected. */
    EVK_FLASH_ERR_NONE = 0,
    /*! Write flash error. */
    EVK_FLASH_ERR = EVK_FLASH_GENERATE_ERR_CODE,
    /*! Flash is busy. */
    EVK_FLASH_ERR_BUSY = EVK_FLASH_GENERATE_ERR_CODE,
    /*! Flash write/read timeout. */
    EVK_FLASH_ERR_TIMEOUT = EVK_FLASH_GENERATE_ERR_CODE,
    /*! Flash function argument error. */
    EVK_FLASH_ERR_ARGUMENT = EVK_FLASH_GENERATE_ERR_CODE,
    /*! There is an unknown error occurring. */
    EVK_FLASH_ERR_UNKNOWN = EVK_FLASH_GENERATE_ERR_CODE,
} evk_flash_error_t;

/* PUBLIC FUNCTION PROTOTYPES *************************************************/
/** @brief Program a region in a block of the MCU's flash memory.
 *
 *  The block must be previously erased.
 *
 *  @param[in] address  Flash memory address to write.
 *  @param[in] buffer   Buffer to write.
 *  @param[in] size     Size of the buffer.
 *  @return The EVK error code.
 */
evk_flash_error_t evk_flash_prog(uint32_t address, const void *buffer, uint32_t size);

/** @brief Erase a memory block of the MCU's flash memory.
 *
 *  The state of an erased block is undefined. A block must be erased before being programmed.
 *
 *  @param[in] address  The address of the flash memory.
 *  @return The EVK error code.
 */
evk_flash_error_t evk_flash_erase(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif /* EVK_FLASH_H_ */
