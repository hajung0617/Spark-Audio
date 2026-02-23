/** @file  sr_pwr_up.h
 *  @brief SR1000 power up sequence.
 *
 *  @copyright Copyright (C) 2023 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is confidential and proprietary.
 *  @author    SPARK FW Team.
 */
#ifndef SR_PWR_UP_H_
#define SR_PWR_UP_H_

/* INCLUDES *******************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "sr_def.h"

#ifdef __cplusplus
extern "C" {
#endif
/* PUBLIC FUNCTION PROTOTYPES *************************************************/
/** @brief Power up radio.
 *
 *  @param[in] radio     Radio's instance.
 *  @param[in] reset     Reset_flag.
 *  @param[in] err       Pointer to the error code.
 */
static inline void sr_pwr_up(radio_t *radio, bool reset, sr_phy_error_t *err)
{
    uint32_t default_sfd_value = 0;
    uint8_t byte_count = 4;
    uint32_t expected_sfd_value = (REG8_SFD_31_24_DEFAULT << 24) | (REG8_SFD_23_16_DEFAULT << 16) |
                                  (REG8_SFD_15_8_DEFAULT << 8) | (REG8_SFD_7_0_DEFAULT);

    /* 1 second delay after board power-up to allow radio crystal stabilization. */
    while (sr_util_get_system_time_ms() < POWER_UP_TIME);

    if (reset) {
        sr_access_reset_reset_pin(radio->radio_id);
        sr_utils_wait_delay(10);
        sr_access_set_reset_pin(radio->radio_id);
        sr_utils_wait_delay(10);
    }

    sr_access_write_reg(radio->radio_id, REG8_PERIPHERAL_CONTROL,
                        radio->std_spi | radio->clock_source.pll_clk_source | radio->clock_source.pll_dis |
                            radio->clock_source.xtal_clk_source);

    if (reset) {
        for (uint8_t i = 0; i < byte_count; i++) {
            default_sfd_value |= (sr_access_read_reg(radio->radio_id, REG8_SFD_31_24 + i)
                                  << (8 * (byte_count - (i + 1))));
        }

        if (default_sfd_value != expected_sfd_value) {
            *err = PHY_MODEL_NOT_FOUND;
        }
    }
}

#ifdef __cplusplus
}
#endif
#endif /* SR_PWR_UP_H_ */
