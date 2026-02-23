/** @file  evk_flash.c
 *  @brief This module is composed of all functionalities related to the MCU's flash memory.
 *
 *  @copyright Copyright (C) 2020-2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "evk_flash.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_flash_ex.h"

/* PRIVATE FUNCTION PROTOTYPES ************************************************/
static void memory_get_erase_info(uint32_t address, FLASH_EraseInitTypeDef *erase_info);
static evk_flash_error_t memory_verify_status(HAL_StatusTypeDef status);

/* PUBLIC FUNCTIONS ***********************************************************/
evk_flash_error_t evk_flash_prog(uint32_t address, const void *buffer, uint32_t size)
{
    HAL_StatusTypeDef status = 0;
    uint64_t *pdata = (uint64_t *)buffer;

    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
        return memory_verify_status(status);
    }

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS);
    while (size > 0) {
        if (size >= sizeof(uint64_t)) {
            /* Write the data as 8-byte chunks */
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, *pdata);
            if (status != HAL_OK) {
                return memory_verify_status(status);
            }

            /* Next write address is 8 bytes further */
            address += sizeof(uint64_t);
            /* Decrement remaining number of bytes to write by 8 */
            size -= sizeof(uint64_t);
            /* Jump to next 8 bytes to write */
            pdata++;
            continue;
        }
        /* Less than 8 bytes to write */
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, *pdata);
        if (status != HAL_OK) {
            return memory_verify_status(status);
        }

        size = 0;
    }
    status = HAL_FLASH_Lock();
    if (status != HAL_OK) {
        return memory_verify_status(status);
    }

    return EVK_FLASH_ERR_NONE;
}

evk_flash_error_t evk_flash_erase(uint32_t address)
{
    FLASH_EraseInitTypeDef erase_init = {0};
    uint32_t page_error = 0;
    HAL_StatusTypeDef status = {0};

    memory_get_erase_info(address, &erase_init);

    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
        return memory_verify_status(status);
    }

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS);
    status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    if (status != HAL_OK) {
        return memory_verify_status(status);
    }

    status = HAL_FLASH_Lock();
    if (status != HAL_OK) {
        return memory_verify_status(status);
    }

    return EVK_FLASH_ERR_NONE;
}

/* PRIVATE FUNCTIONS **********************************************************/
/** @brief Get erase info from address.
 *
 *  @param[in] address     Flash address.
 *  @param[in] erase_info  Fash erase information.
 */
static void memory_get_erase_info(uint32_t address, FLASH_EraseInitTypeDef *erase_info)
{
    /* Only use 1 page for user data. */
    erase_info->NbPages = 1;
    erase_info->TypeErase = FLASH_TYPEERASE_PAGES;

    if (address < (FLASH_BASE + FLASH_BANK_SIZE)) {
        erase_info->Banks = FLASH_BANK_1;
        erase_info->Page = (address - FLASH_BASE) / FLASH_PAGE_SIZE;
    } else {
        erase_info->Banks = FLASH_BANK_2;
        erase_info->Page = (address - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
    }
}

/** @brief Get the status from STM32 HAL and translate to error status.
 *
 *  @param[in] status  Status from STM32 HAL.
 *  @return The resulting EVK memory error status.
 */
static evk_flash_error_t memory_verify_status(HAL_StatusTypeDef status)
{
    evk_flash_error_t err = EVK_FLASH_ERR_NONE;

    switch (status) {
    case HAL_OK:
        err = EVK_FLASH_ERR_NONE;
        break;
    case HAL_ERROR:
        err = EVK_FLASH_ERR;
        break;
    case HAL_BUSY:
        err = EVK_FLASH_ERR_BUSY;
        break;
    case HAL_TIMEOUT:
        err = EVK_FLASH_ERR_TIMEOUT;
        break;
    default:
        err = EVK_FLASH_ERR_UNKNOWN;
        break;
    }

    return err;
}
