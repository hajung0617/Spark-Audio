/** @file  swc_cfg.h
 *  @brief Application specific configuration constants for the SPARK Wireless Core.
 *
 *  @copyright Copyright (C) 2025 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef SWC_CFG_H_
#define SWC_CFG_H_

/* CONSTANTS ******************************************************************/

/* SWC queue size */
#define SWC_QUEUE_SIZE 2

/* Schedule configuration */
#define SCHEDULE        {250}
#define COORD_TIMESLOTS {MAIN_TIMESLOT(0)}

/* Channels */
#define CHANNEL_FREQ     {88, 105, 122, 139}
#define CHANNEL_SEQUENCE {0, 1, 2, 3}

/* CCA settings */
#define SWC_CCA_RETRY_TIME 512 /* 25 us CCA intervals. */
#define SWC_CCA_TRY_COUNT  5   /* 100 us total CCA time. */

#endif /* SWC_CFG_H_ */
