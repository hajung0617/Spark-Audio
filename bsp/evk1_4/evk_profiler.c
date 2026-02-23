/** @file  evk_profiler.c
 *  @brief Implementation of the EVK profiler for measuring execution time.
 *
 *  @copyright Copyright (C) 2025 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "evk_profiler.h"

/* PUBLIC FUNCTIONS ***********************************************************/
void evk_profiler_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    ITM->TCR |= ITM_TCR_DWTENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
