/** @file sr1000_reg.h
 *  @brief SR1010/SR1020 registers map main include.
 *
 *  @copyright Copyright (C) 2018 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef SR1000_REG_H_
#define SR1000_REG_H_

/* MACROS *********************************************************************/
#define FIRST_BYTE_OFFSET  0
#define SECOND_BYTE_OFFSET 8

/*! Register field single bit mask */
#define BIT(n) (1 << (n))
/*! Calculates leftshift for given mask (e.g BITS2SHIFT(0x30) = 16, where log2(16) = 4, to shift 4). */
#define BITS2SHIFT(mask) ((mask) & -(mask))
/*! Register field multibit mask, 8-bit.  */
#define BITS8(b, a) ((0xff >> (7 - (b))) & ~((1U << (a)) - 1))
/*! Register field multibit mask, 16-bit */
#define BITS16_1(b, a) ((0xffff >> (15 - ((b) + FIRST_BYTE_OFFSET))) & ~((1U << ((a) + FIRST_BYTE_OFFSET)) - 1))
/*! Register field multibit mask, 16-bit */
#define BITS16_2(b, a) ((0xffff >> (15 - ((b) + SECOND_BYTE_OFFSET))) & ~((1U << ((a) + SECOND_BYTE_OFFSET)) - 1))
/*! Register field multibit mask, 24-bit */
#define BITS24(b, a) ((0xffffff >> (23 - (b))) & ~((1U << (a)) - 1))
/*! Register field multibit mask, 32-bit */
#define BITS32(b, a) ((0xffffffff >> (31 - (b))) & ~((1U << (a)) - 1))
/*! Returns values written in mask */
#define MASK2VAL(val, mask) (((val) & (mask)) / BITS2SHIFT(mask))
/*! Returns a value within the given mask */
#define MOV2MASK(val, mask) (((val) * BITS2SHIFT(mask)) & (mask))
/*! Return the max value of a given mask */
#define MASK_MAX_VALUE(mask) ((mask) / BITS2SHIFT(mask))

/* CONSTANTS ******************************************************************/
#define REG_READ_BURST  BIT(7)
#define REG_WRITE       BIT(6)
#define REG_WRITE_BURST (BIT(7) | REG_WRITE)

/* INCLUDES *******************************************************************/
#include "sr1020_V8_3_reg.h"

#endif /* SR1000_REG_H_ */
