/** @file link_gain_loop.c
 *  @brief Gain loop module.
 *
 *  @copyright Copyright (C) 2020 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "link_gain_loop.h"
#include "sr_def.h"

/* CONSTANTS ******************************************************************/
#define LOWER_BOUND_MARGIN_TENTH_DB  120
#define HIGHER_BOUND_MARGIN_TENTH_DB 40
#define GAIN_ENTRY_COUNT             17

/* PRIVATE GLOBALS ************************************************************/
static const gain_entry_t gain_lookup_table[GAIN_ENTRY_COUNT] = {
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(0) | SET_IF_GAIN3(4), 0, 235, 74},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(1) | SET_IF_GAIN3(4), 12, 247, 67},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(2) | SET_IF_GAIN3(4), 23, 258, 61},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(3) | SET_IF_GAIN3(4), 42, 277, 54},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(4) | SET_IF_GAIN3(4), 60, 295, 48},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(5) | SET_IF_GAIN3(4), 85, 320, 44},
    {SET_RF_GAIN(1) | SET_IFOA_GAIN(5) | SET_IF_GAIN3(4), 98, 333, 44},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(6) | SET_IF_GAIN3(4), 130, 365, 42},
    {SET_RF_GAIN(1) | SET_IFOA_GAIN(6) | SET_IF_GAIN3(4), 142, 377, 42},
    {SET_RF_GAIN(3) | SET_IFOA_GAIN(6) | SET_IF_GAIN3(4), 173, 408, 42},
    {SET_RF_GAIN(3) | SET_IFOA_GAIN(6) | SET_IF_GAIN3(3), 187, 422, 35},
    {SET_RF_GAIN(0) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(4), 221, 456, 42},
    {SET_RF_GAIN(1) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(4), 241, 476, 42},
    {SET_RF_GAIN(2) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(4), 258, 493, 41},
    {SET_RF_GAIN(3) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(4), 271, 506, 41},
    {SET_RF_GAIN(3) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(3), 292, 527, 35},
    {SET_RF_GAIN(3) | SET_IFOA_GAIN(7) | SET_IF_GAIN3(2), 318, 553, 31},
};

/* PUBLIC FUNCTIONS ***********************************************************/
void link_gain_loop_init(gain_loop_t *gain_loop, bool fixed_gain_enable, uint8_t rx_gain)
{
    gain_loop->gain_index = 0;
    gain_loop->fixed_gain_enable = fixed_gain_enable;
    gain_loop->rx_gain = rx_gain;
}

void link_gain_loop_update(gain_loop_t *gain_loop, frame_outcome_t frame_outcome, uint8_t rssi)
{
    uint16_t normalized_gain = 0;

    switch (frame_outcome) {
    case FRAME_RECEIVED:
    case FRAME_SENT_ACK:
        normalized_gain = calculate_normalized_gain(gain_lookup_table[gain_loop->gain_index].min_tenth_db, rssi);
        if (normalized_gain < (gain_lookup_table[gain_loop->gain_index].min_tenth_db + LOWER_BOUND_MARGIN_TENTH_DB) &&
            (gain_loop->gain_index != 0)) {
            gain_loop->gain_index--;
        } else if (normalized_gain >
                       (gain_lookup_table[gain_loop->gain_index].max_tenth_db - HIGHER_BOUND_MARGIN_TENTH_DB) &&
                   (gain_loop->gain_index != (GAIN_ENTRY_COUNT - 1))) {
            gain_loop->gain_index++;
        }
        break;
    case FRAME_REJECTED:
    case FRAME_SENT_ACK_REJECTED:
    case FRAME_LOST:
    case FRAME_SENT_ACK_LOST:
        break;
    default:
        break;
    }
}

uint8_t link_gain_loop_get_gain_value(gain_loop_t *gain_loop)
{
    if (gain_loop->fixed_gain_enable) {
        return gain_loop->rx_gain;
    } else {
        return gain_lookup_table[gain_loop->gain_index].gain_value;
    }
}

uint16_t link_gain_loop_get_min_tenth_db(uint8_t gain_index)
{
    return gain_lookup_table[gain_index].min_tenth_db;
}

uint16_t link_gain_loop_get_rnsi_tenth_db(uint8_t gain_index)
{
    return gain_lookup_table[gain_index].rnsi_tenth_db;
}
