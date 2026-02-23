/** @file  sr1020_V8_3_reg.h
 *  @brief SR1020_V8_3 registers map. This file assumes a little-endian processor.
 *
 *  @copyright Copyright (C) 2025 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is confidential and proprietary.
 *  @author    SPARK FW Team.
 */
/*
 *                                                                     /##
 *                                                                 ,#####
 *                                  . /(######((/,.            .#######(
 *                          /######################         ##########*
 *                     /#######################.        /############.
 *                 *##########%/                    .###############
 *              /#########,                      ##########((#########.
 *            %#######/                      (#########%   #############(
 *          #######(                     *##########,     %#####(  ########
 *        %######.                    ##########(        ######*     #######(
 *      *######,                  (##########          .######.        #######
 *     (#####%                (##########.            ,######           .######*
 *    ######/             ,##########/               /######              ######/
 *   (#####*           %##########                  #######                %#####,
 *  ,######        (##########(                    %#####/                  ######
 *  ######           .%############%              /#####,                   *#####(
 *  #####(                 /#############*                                   ######
 * .#####*                      ,#############(                              ######
 * .#####*                           .#############(.                        ######
 *  #####/                                 (#############*                   %#####
 *  ######                    .###,             *#############/              ######
 *  /#####*                  ,######                  %############%.       ######.
 *   %#####                 (######                   /##########.         *#####(
 *    ######               %#####(                ,##########*            *######
 *     ######.            ######(              ##########(               #######
 *      #######          ######*           (##########                  ######%
 *       *######(      .######         *##########,                   #######.
 *         #######%   *######       %#########/                     ########
 *           ###############    (#########(                      (#######(
 *             *##########( /#########%                       %########.
 *                /################,                     /##########/
 *                #############(                ./%#############%
 *              ,###########         (######################/
 *             *#######%         *%#################%#
 *            (#####*
 *           ###(
 *          #
 */

// clang-format off

#ifndef SR1020_V8_3_H_
#define SR1020_V8_3_H_


/******************************************************************************/
/*                     Register MAIN_DEVICE_FLAG (8 bits)                     */
/******************************************************************************/
#define REG8_MAIN_DEVICE_FLAG 0x0

          /* [rw] Interrupt signal polarity
           */
#define   BIT_IRQPOLAR  BIT(7)
            /* Active high
             */
#define     IRQPOLAR_0b1  MOV2MASK(0b1, BIT_IRQPOLAR)
            /* Active low
             */
#define     IRQPOLAR_0b0  MOV2MASK(0b0, BIT_IRQPOLAR)
            /* Get IRQPOLAR value
             */
#define     GET_IRQPOLAR(reg_val)  MASK2VAL(reg_val, BIT_IRQPOLAR)
            /* IRQPOLAR default value
             */
#define     IRQPOLAR_DEFAULT  MOV2MASK(0x1, BIT_IRQPOLAR)

          /* [wo]
           */
#define   BIT_PKBEGINE  BIT(6)
            /* Controls IRQ signal based on PKBEGINI, no effect on PKBEGINI
             */
#define     PKBEGINE_0b1  MOV2MASK(0b1, BIT_PKBEGINE)
            /* Disable this interrupt
             */
#define     PKBEGINE_0b0  MOV2MASK(0b0, BIT_PKBEGINE)
            /* PKBEGINE default value
             */
#define     PKBEGINE_DEFAULT  MOV2MASK(0x0, BIT_PKBEGINE)

          /* [wo] Receiver timeout interrupt enable
           */
#define   BIT_RXTIMEOE  BIT(5)
            /* Enable receiver timeout interrupt
             */
#define     RXTIMEOE_0b1  MOV2MASK(0b1, BIT_RXTIMEOE)
            /* Disable this interrupt
             */
#define     RXTIMEOE_0b0  MOV2MASK(0b0, BIT_RXTIMEOE)
            /* RXTIMEOE default value
             */
#define     RXTIMEOE_DEFAULT  MOV2MASK(0x0, BIT_RXTIMEOE)

          /* [wo] Standalone frame transmission end interrupt enable
           */
#define   BIT_TXENDE  BIT(4)
            /* Controls IRQ signal based on TXENDI, no effect on TXENDI
             */
#define     TXENDE_0b1  MOV2MASK(0b1, BIT_TXENDE)
            /* Disable this interrupt
             */
#define     TXENDE_0b0  MOV2MASK(0b0, BIT_TXENDE)
            /* TXENDE default value
             */
#define     TXENDE_DEFAULT  MOV2MASK(0x1, BIT_TXENDE)

          /* [wo]
           */
#define   BIT_NEWPKTE  BIT(3)
            /* Controls IRQ signal based on NEWPKTI, no effect on NEWPKTI
             */
#define     NEWPKTE_0b1  MOV2MASK(0b1, BIT_NEWPKTE)
            /* Disable this interrupt
             */
#define     NEWPKTE_0b0  MOV2MASK(0b0, BIT_NEWPKTE)
            /* NEWPKTE default value
             */
#define     NEWPKTE_DEFAULT  MOV2MASK(0x1, BIT_NEWPKTE)

          /* [wo] Frame address field match interrupt enable
           */
#define   BIT_ADDRMATE  BIT(2)
            /* Controls IRQ signal based on ADDRMATI, no effect on ADDRMATI
             */
#define     ADDRMATE_0b1  MOV2MASK(0b1, BIT_ADDRMATE)
            /* Disable this interrupt
             */
#define     ADDRMATE_0b0  MOV2MASK(0b0, BIT_ADDRMATE)
            /* ADDRMATE default value
             */
#define     ADDRMATE_DEFAULT  MOV2MASK(0x0, BIT_ADDRMATE)

          /* [wo] Broadcast frame reception end interrupt enable
           */
#define   BIT_BRDCASTE  BIT(1)
            /* Controls IRQ signal based on BRDCASTI, no effect on BRDCASTI
             */
#define     BRDCASTE_0b1  MOV2MASK(0b1, BIT_BRDCASTE)
            /* Disable this interrupt
             */
#define     BRDCASTE_0b0  MOV2MASK(0b0, BIT_BRDCASTE)
            /* BRDCASTE default value
             */
#define     BRDCASTE_DEFAULT  MOV2MASK(0x0, BIT_BRDCASTE)

          /* [wo] CRC pass interrupt enable
           */
#define   BIT_CRCPASSE  BIT(0)
            /* Controls IRQ signal based on CRCPASSI, no effect on CRCPASSI
             */
#define     CRCPASSE_0b1  MOV2MASK(0b1, BIT_CRCPASSE)
            /* Disable this interrupt
             */
#define     CRCPASSE_0b0  MOV2MASK(0b0, BIT_CRCPASSE)
            /* CRCPASSE default value
             */
#define     CRCPASSE_DEFAULT  MOV2MASK(0x0, BIT_CRCPASSE)

          /* [ro] STATUS2 register holds interrupt
           */
#define   BIT_STAT2IRQ  BIT(7)
            /* At least one of the status bits in register STATUS2 (at register address
             * 0x01) is holding the IRQ pin asserted
             */
#define     STAT2IRQ_0b1  MOV2MASK(0b1, BIT_STAT2IRQ)
            /* No bits in register STATUS2 (at register address 0x01) is holding the IRQ pin
             * asserted
             */
#define     STAT2IRQ_0b0  MOV2MASK(0b0, BIT_STAT2IRQ)
            /* Get STAT2IRQ value
             */
#define     GET_STAT2IRQ(reg_val)  MASK2VAL(reg_val, BIT_STAT2IRQ)
            /* STAT2IRQ default value
             */
#define     STAT2IRQ_DEFAULT  MOV2MASK(1, BIT_STAT2IRQ)

          /* [ro] Packet beginning interrupt
           */
#define   BIT_PKBEGINI  BIT(6)
            /* This is a sticky bit. Set to '1' when the modem transmits or detects a
             * synchronization word in reception
             */
#define     GET_PKBEGINI(reg_val)  MASK2VAL(reg_val, BIT_PKBEGINI)
            /* PKBEGINI default value
             */
#define     PKBEGINI_DEFAULT  MOV2MASK(0, BIT_PKBEGINI)

          /* [ro] Receiver timeout interrupt
           */
#define   BIT_RXTIMEOI  BIT(5)
            /* This is a sticky bit. Set to '1' when wake-up timer matches RXTIMEOUT during
             * receiver timeout or auto-reply frame with no preamble detected
             */
#define     GET_RXTIMEOI(reg_val)  MASK2VAL(reg_val, BIT_RXTIMEOI)
            /* RXTIMEOI default value
             */
#define     RXTIMEOI_DEFAULT  MOV2MASK(0, BIT_RXTIMEOI)

          /* [ro] Standalone frame transmission end interrupt
           */
#define   BIT_TXENDI  BIT(4)
            /* This is a sticky bit. Set to '1' when standalone frame transmission completes
             *
             */
#define     GET_TXENDI(reg_val)  MASK2VAL(reg_val, BIT_TXENDI)
            /* TXENDI default value
             */
#define     TXENDI_DEFAULT  MOV2MASK(1, BIT_TXENDI)

          /* [ro]  New packet reception interrupt
           */
#define   BIT_NEWPKTI  BIT(3)
            /* This is a sticky bit. Set to '1' every time the modem completes the reception
             * of a packet into the reception buffer
             */
#define     GET_NEWPKTI(reg_val)  MASK2VAL(reg_val, BIT_NEWPKTI)
            /* NEWPKTI default value
             */
#define     NEWPKTI_DEFAULT  MOV2MASK(1, BIT_NEWPKTI)

          /* [ro] Frame address field match interrupt
           */
#define   BIT_ADDRMATI  BIT(2)
            /* This is a sticky bit. Set to '1' when received address matches device's
             * RXADDRESS
             */
#define     GET_ADDRMATI(reg_val)  MASK2VAL(reg_val, BIT_ADDRMATI)
            /* ADDRMATI default value
             */
#define     ADDRMATI_DEFAULT  MOV2MASK(0, BIT_ADDRMATI)

          /* [ro] Broadcast frame reception end interrupt
           */
#define   BIT_BRDCASTI  BIT(1)
            /* This is a sticky bit. Set to '1' when broadcast address matches in frame
             */
#define     GET_BRDCASTI(reg_val)  MASK2VAL(reg_val, BIT_BRDCASTI)
            /* BRDCASTI default value
             */
#define     BRDCASTI_DEFAULT  MOV2MASK(0, BIT_BRDCASTI)

          /* [ro] CRC pass interrupt
           */
#define   BIT_CRCPASSI  BIT(0)
            /* This is a sticky bit. Set to '1' when received CRC matches computed CRC for a
             * frame
             */
#define     GET_CRCPASSI(reg_val)  MASK2VAL(reg_val, BIT_CRCPASSI)
            /* CRCPASSI default value
             */
#define     CRCPASSI_DEFAULT  MOV2MASK(0, BIT_CRCPASSI)

#define REG8_MAIN_DEVICE_FLAG_DEFAULT  0x0098



/******************************************************************************/
/*                     Register AUX_DEVICE_FLAGS (8 bits)                     */
/******************************************************************************/
#define REG8_AUX_DEVICE_FLAGS 0x1

          /* [wo] Crystal oscillator timer interrupt enable
           */
#define   BIT_XOTIMERE  BIT(7)
            /* Controls IRQ signal based on XOTIMERI, no effect on XOTIMERI
             */
#define     XOTIMERE_0b1  MOV2MASK(0b1, BIT_XOTIMERE)
            /* Disable this interrupt
             */
#define     XOTIMERE_0b0  MOV2MASK(0b0, BIT_XOTIMERE)
            /* XOTIMERE default value
             */
#define     XOTIMERE_DEFAULT  MOV2MASK(0x0, BIT_XOTIMERE)

          /* [wo] Wake-up interrupt enable
           */
#define   BIT_WAKEUPE  BIT(6)
            /* Controls IRQ signal based on WAKEUPI, no effect on WAKEUPI
             */
#define     WAKEUPE_0b1  MOV2MASK(0b1, BIT_WAKEUPE)
            /* Disable this interrupt
             */
#define     WAKEUPE_0b0  MOV2MASK(0b0, BIT_WAKEUPE)
            /* WAKEUPE default value
             */
#define     WAKEUPE_DEFAULT  MOV2MASK(0x1, BIT_WAKEUPE)

          /* [wo] Clear-channel assessment failure interrupt enable
           */
#define   BIT_CCAFAILE  BIT(5)
            /* Controls IRQ signal based on CCAFAILI, no effect on CCAFAILI
             */
#define     CCAFAILE_0b1  MOV2MASK(0b1, BIT_CCAFAILE)
            /* Disable this interrupt
             */
#define     CCAFAILE_0b0  MOV2MASK(0b0, BIT_CCAFAILE)
            /* CCAFAILE default value
             */
#define     CCAFAILE_DEFAULT  MOV2MASK(0x1, BIT_CCAFAILE)

          /* [wo]
           */
#define   BIT_TXUDRFLE  BIT(4)
            /* Controls IRQ signal based on TXOVRFLI, no effect on TXOVRFLI
             */
#define     TXUDRFLE_0b1  MOV2MASK(0b1, BIT_TXUDRFLE)
            /* Disable this interrupt
             */
#define     TXUDRFLE_0b0  MOV2MASK(0b0, BIT_TXUDRFLE)
            /* TXUDRFLE default value
             */
#define     TXUDRFLE_DEFAULT  MOV2MASK(0x1, BIT_TXUDRFLE)

          /* [wo]
           */
#define   BIT_RXOVRFLE  BIT(3)
            /* Controls IRQ signal based on RXOVRFLI, no effect on RXOVRFLI
             */
#define     RXOVRFLE_0b1  MOV2MASK(0b1, BIT_RXOVRFLE)
            /* Disable this interrupt
             */
#define     RXOVRFLE_0b0  MOV2MASK(0b0, BIT_RXOVRFLE)
            /* RXOVRFLE default value
             */
#define     RXOVRFLE_DEFAULT  MOV2MASK(0x1, BIT_RXOVRFLE)

          /* [wo]
           */
#define   BIT_TXOVRFLE  BIT(2)
            /* Controls IRQ signal based on TXOVRFLI, no effect on TXOVRFLI
             */
#define     TXOVRFLE_0b1  MOV2MASK(0b1, BIT_TXOVRFLE)
            /* Disable this interrupt
             */
#define     TXOVRFLE_0b0  MOV2MASK(0b0, BIT_TXOVRFLE)
            /* TXOVRFLE default value
             */
#define     TXOVRFLE_DEFAULT  MOV2MASK(0x1, BIT_TXOVRFLE)

          /* [wo]
           */
#define   BIT_BUFLOADE  BIT(1)
            /* Controls IRQ signal based on BUFLOADI, no effect on BUFLOADI
             */
#define     BUFLOADE_0b1  MOV2MASK(0b1, BIT_BUFLOADE)
            /* Disable this interrupt
             */
#define     BUFLOADE_0b0  MOV2MASK(0b0, BIT_BUFLOADE)
            /* BUFLOADE default value
             */
#define     BUFLOADE_DEFAULT  MOV2MASK(0x1, BIT_BUFLOADE)

          /* [wo]
           */
#define   BIT_BUFSTOPE  BIT(0)
            /* Controls IRQ signal based on BUFSTOPI, no effect on BUFSTOPI
             */
#define     BUFSTOPE_0b1  MOV2MASK(0b1, BIT_BUFSTOPE)
            /* Disable this interrupt
             */
#define     BUFSTOPE_0b0  MOV2MASK(0b0, BIT_BUFSTOPE)
            /* BUFSTOPE default value
             */
#define     BUFSTOPE_DEFAULT  MOV2MASK(0x0, BIT_BUFSTOPE)

          /* [ro] Crystal oscillator timer interrupt
           */
#define   BIT_XOTIMERI  BIT(7)
            /* This is a sticky bit. Set to '1' when crystal oscillator wake-up timer
             * matches SLPPERIOD during sleep (except lightest sleep)
             */
#define     GET_XOTIMERI(reg_val)  MASK2VAL(reg_val, BIT_XOTIMERI)
            /* XOTIMERI default value
             */
#define     XOTIMERI_DEFAULT  MOV2MASK(0, BIT_XOTIMERI)

          /* [ro] Wake-up interrupt
           */
#define   BIT_WAKEUPI  BIT(6)
            /* This is a sticky bit. Set to '1' when device finishes waking from sleep
             */
#define     GET_WAKEUPI(reg_val)  MASK2VAL(reg_val, BIT_WAKEUPI)
            /* WAKEUPI default value
             */
#define     WAKEUPI_DEFAULT  MOV2MASK(1, BIT_WAKEUPI)

          /* [ro] Clear-channel assessment failure interrupt
           */
#define   BIT_CCAFAILI  BIT(5)
            /* This is a sticky bit. Set to '1' when CCA failure cancels standalone frame
             * transmission
             */
#define     GET_CCAFAILI(reg_val)  MASK2VAL(reg_val, BIT_CCAFAILI)
            /* CCAFAILI default value
             */
#define     CCAFAILI_DEFAULT  MOV2MASK(1, BIT_CCAFAILI)

          /* [ro] Transmission data buffer underflow interrupt
           */
#define   BIT_TXUDRFLI  BIT(4)
            /* Set to '1' when incomplete frame due to buffer underflow
             */
#define     TXUDRFLI_0b1  MOV2MASK(0b1, BIT_TXUDRFLI)
            /* Cleared by FLUSHTX
             */
#define     TXUDRFLI_0b0  MOV2MASK(0b0, BIT_TXUDRFLI)
            /* Get TXUDRFLI value
             */
#define     GET_TXUDRFLI(reg_val)  MASK2VAL(reg_val, BIT_TXUDRFLI)
            /* TXUDRFLI default value
             */
#define     TXUDRFLI_DEFAULT  MOV2MASK(1, BIT_TXUDRFLI)

          /* [ro] Reception buffer overflow interrupt
           */
#define   BIT_RXOVRFLI  BIT(3)
            /* Set to '1' when SPI writes to full reception buffer
             */
#define     RXOVRFLI_0b1  MOV2MASK(0b1, BIT_RXOVRFLI)
            /* Cleared by FLUSHRX
             */
#define     RXOVRFLI_0b0  MOV2MASK(0b0, BIT_RXOVRFLI)
            /* Get RXOVRFLI value
             */
#define     GET_RXOVRFLI(reg_val)  MASK2VAL(reg_val, BIT_RXOVRFLI)
            /* RXOVRFLI default value
             */
#define     RXOVRFLI_DEFAULT  MOV2MASK(1, BIT_RXOVRFLI)

          /* [ro] Transmission data buffer overflow interrupt
           */
#define   BIT_TXOVRFLI  BIT(2)
            /* Set to '1' when SPI writes to full transmission buffer
             */
#define     TXOVRFLI_0b1  MOV2MASK(0b1, BIT_TXOVRFLI)
            /* Cleared by FLUSHTX
             */
#define     TXOVRFLI_0b0  MOV2MASK(0b0, BIT_TXOVRFLI)
            /* Get TXOVRFLI value
             */
#define     GET_TXOVRFLI(reg_val)  MASK2VAL(reg_val, BIT_TXOVRFLI)
            /* TXOVRFLI default value
             */
#define     TXOVRFLI_DEFAULT  MOV2MASK(1, BIT_TXOVRFLI)

          /* [ro] Reception data buffer load interrupt
           */
#define   BIT_BUFLOADI  BIT(1)
            /* Set to '1' when reception data buffer load exceeds RXTHRESH
             */
#define     BUFLOADI_0b1  MOV2MASK(0b1, BIT_BUFLOADI)
            /* Cleared by buffer load decrease or disabling
             */
#define     BUFLOADI_0b0  MOV2MASK(0b0, BIT_BUFLOADI)
            /* Get BUFLOADI value
             */
#define     GET_BUFLOADI(reg_val)  MASK2VAL(reg_val, BIT_BUFLOADI)
            /* BUFLOADI default value
             */
#define     BUFLOADI_DEFAULT  MOV2MASK(1, BIT_BUFLOADI)

          /* [ro] Data buffer stop interrupt
           */
#define   BIT_BUFSTOPI  BIT(0)
            /* The current direction buffer`s load is less than two bytes away from being at
             * the limit of what the SPI master can extract of push
             */
#define     BUFSTOPI_0b1  MOV2MASK(0b1, BIT_BUFSTOPI)
            /* Cleared when the current direction buffer load is more or equal than 2 bytes
             * away from being at the limit
             */
#define     BUFSTOPI_0b0  MOV2MASK(0b0, BIT_BUFSTOPI)
            /* Get BUFSTOPI value
             */
#define     GET_BUFSTOPI(reg_val)  MASK2VAL(reg_val, BIT_BUFSTOPI)
            /* BUFSTOPI default value
             */
#define     BUFSTOPI_DEFAULT  MOV2MASK(0, BIT_BUFSTOPI)

#define REG8_AUX_DEVICE_FLAGS_DEFAULT  0x007E



/******************************************************************************/
/*                     Register TX_BUFFER_STATUS (8 bits)                     */
/******************************************************************************/
#define REG8_TX_BUFFER_STATUS 0x2

          /* [wo] Transmission buffer load threshold enable
           */
#define   BIT_TXIRQEN  BIT(7)
            /* The TXTHRESH value is used to define the load threshold at or below which the
             * BUFLOADI status bit will be set to 1
             */
#define     TXIRQEN_0b1  MOV2MASK(0b1, BIT_TXIRQEN)
            /* No value of TXBUFLOAD can set the BUFLOADI status bit
             */
#define     TXIRQEN_0b0  MOV2MASK(0b0, BIT_TXIRQEN)
            /* TXIRQEN default value
             */
#define     TXIRQEN_DEFAULT  MOV2MASK(0x0, BIT_TXIRQEN)

          /* [wo] Transmission buffer load threshold
           */
#define   BITS_TXTHRESH  BITS8(5, 0)
            /* Value telling at or below which number of bytes stored in the transmission
             * buffer to set the BUFLOADI register bit to 1
             */
#define     SET_TXTHRESH(value)  MOV2MASK(value, BITS_TXTHRESH)
            /* TXTHRESH default value
             */
#define     TXTHRESH_DEFAULT  MOV2MASK(0x0, BITS_TXTHRESH)

          /* [ro] Transmission buffer load
           */
#define   BITS_TXBUFLOAD  BITS8(7, 0)
            /* Tells the number of bytes of data currenlty stored in the transmission buffer
             *
             */
#define     GET_TXBUFLOAD(reg_val)  MASK2VAL(reg_val, BITS_TXBUFLOAD)
            /* TXBUFLOAD default value
             */
#define     TXBUFLOAD_DEFAULT  MOV2MASK(0, BITS_TXBUFLOAD)

#define REG8_TX_BUFFER_STATUS_DEFAULT  0x0000



/******************************************************************************/
/*                     Register RX_BUFFER_STATUS (8 bits)                     */
/******************************************************************************/
#define REG8_RX_BUFFER_STATUS 0x3

          /* [wo] Reception buffer load threshold enable
           */
#define   BIT_RXIRQEN  BIT(7)
            /* The RXTHRESH value is used to define the load threshold above which the
             * BUFLOADI status bit will be set to 1
             */
#define     RXIRQEN_0b1  MOV2MASK(0b1, BIT_RXIRQEN)
            /* No value of RXBUFLOAD can set the BUFLOADI status bit
             */
#define     RXIRQEN_0b0  MOV2MASK(0b0, BIT_RXIRQEN)
            /* RXIRQEN default value
             */
#define     RXIRQEN_DEFAULT  MOV2MASK(0x0, BIT_RXIRQEN)

          /* [wo] Reception buffer load threshold
           */
#define   BITS_RXTHRESH  BITS8(5, 0)
            /* Value telling above which number of bytes stored in the reception buffer to
             * set the BUFLOADI register bit to 1
             */
#define     SET_RXTHRESH(value)  MOV2MASK(value, BITS_RXTHRESH)
            /* RXTHRESH default value
             */
#define     RXTHRESH_DEFAULT  MOV2MASK(0x0, BITS_RXTHRESH)

          /* [ro] Reception buffer load
           */
#define   BITS_RXBUFLOAD  BITS8(7, 0)
            /* Tells the number of bytes of data currenlty stored in the reception buffer
             */
#define     GET_RXBUFLOAD(reg_val)  MASK2VAL(reg_val, BITS_RXBUFLOAD)
            /* RXBUFLOAD default value
             */
#define     RXBUFLOAD_DEFAULT  MOV2MASK(0, BITS_RXBUFLOAD)

#define REG8_RX_BUFFER_STATUS_DEFAULT  0x0000



/******************************************************************************/
/*                       Register SLEEP_CONFIG (8 bits)                       */
/******************************************************************************/
#define REG8_SLEEP_CONFIG 0x4

          /* [rw] Sleep Depth
           */
#define   BITS_SLPDEPTH  BITS8(7, 6)
            /* Deep sleep
             */
#define     SLPDEPTH_0b11  MOV2MASK(0b11, BITS_SLPDEPTH)
            /* Shallow sleep
             */
#define     SLPDEPTH_0b10  MOV2MASK(0b10, BITS_SLPDEPTH)
            /* Lightest sleep(IDLE)
             */
#define     SLPDEPTH_0b01  MOV2MASK(0b01, BITS_SLPDEPTH)
            /* Lightest sleep(IDLE)
             */
#define     SLPDEPTH_0b00  MOV2MASK(0b00, BITS_SLPDEPTH)
            /* Get SLPDEPTH value
             */
#define     GET_SLPDEPTH(reg_val)  MASK2VAL(reg_val, BITS_SLPDEPTH)
            /* SLPDEPTH default value
             */
#define     SLPDEPTH_DEFAULT  MOV2MASK(0x3, BITS_SLPDEPTH)

          /* [rw] Sleep on receiver timeout event
           */
#define   BIT_SLPRXTO  BIT(5)
            /* The device will automatically go to sleep following the triggering of a
             * receiver timeout event
             */
#define     SLPRXTO_0b1  MOV2MASK(0b1, BIT_SLPRXTO)
            /* Deactivate sleep on receiver timeout event
             */
#define     SLPRXTO_0b0  MOV2MASK(0b0, BIT_SLPRXTO)
            /* Get SLPRXTO value
             */
#define     GET_SLPRXTO(reg_val)  MASK2VAL(reg_val, BIT_SLPRXTO)
            /* SLPRXTO default value
             */
#define     SLPRXTO_DEFAULT  MOV2MASK(0x0, BIT_SLPRXTO)

          /* [rw] Sleep on transmission end event
           */
#define   BIT_SLPTXEND  BIT(4)
            /* The device will automatically go to sleep following the triggering of a frame
             * transmission end event
             */
#define     SLPTXEND_0b1  MOV2MASK(0b1, BIT_SLPTXEND)
            /* Deactivate sleep on transmission end event
             */
#define     SLPTXEND_0b0  MOV2MASK(0b0, BIT_SLPTXEND)
            /* Get SLPTXEND value
             */
#define     GET_SLPTXEND(reg_val)  MASK2VAL(reg_val, BIT_SLPTXEND)
            /* SLPTXEND default value
             */
#define     SLPTXEND_DEFAULT  MOV2MASK(0x0, BIT_SLPTXEND)

          /* [rw] Sleep on frame reception end event
           */
#define   BIT_SLPRXEND  BIT(3)
            /* The device will automatically go to sleep following the triggering of a frame
             * reception end event
             */
#define     SLPRXEND_0b1  MOV2MASK(0b1, BIT_SLPRXEND)
            /* Deactivate sleep on frame reception end event
             */
#define     SLPRXEND_0b0  MOV2MASK(0b0, BIT_SLPRXEND)
            /* Get SLPRXEND value
             */
#define     GET_SLPRXEND(reg_val)  MASK2VAL(reg_val, BIT_SLPRXEND)
            /* SLPRXEND default value
             */
#define     SLPRXEND_DEFAULT  MOV2MASK(0x0, BIT_SLPRXEND)

          /* [rw] Sleep on frame address field match event
           */
#define   BIT_SLPMATCH  BIT(2)
            /* The device will automatically go to sleep following the triggering of a frame
             * address field match event (happens at the end of the frame reception)
             */
#define     SLPMATCH_0b1  MOV2MASK(0b1, BIT_SLPMATCH)
            /* Deactivate sleep on frame address field match event
             */
#define     SLPMATCH_0b0  MOV2MASK(0b0, BIT_SLPMATCH)
            /* Get SLPMATCH value
             */
#define     GET_SLPMATCH(reg_val)  MASK2VAL(reg_val, BIT_SLPMATCH)
            /* SLPMATCH default value
             */
#define     SLPMATCH_DEFAULT  MOV2MASK(0x0, BIT_SLPMATCH)

          /* [rw] Sleep on broadcast frame reception end event
           */
#define   BIT_SLPBRDCA  BIT(1)
            /* The device will automatically go to sleep following the triggering of a
             * broadcast frame reception end event
             */
#define     SLPBRDCA_0b1  MOV2MASK(0b1, BIT_SLPBRDCA)
            /* Deactivate sleep on broadcast event
             */
#define     SLPBRDCA_0b0  MOV2MASK(0b0, BIT_SLPBRDCA)
            /* Get SLPBRDCA value
             */
#define     GET_SLPBRDCA(reg_val)  MASK2VAL(reg_val, BIT_SLPBRDCA)
            /* SLPBRDCA default value
             */
#define     SLPBRDCA_DEFAULT  MOV2MASK(0x0, BIT_SLPBRDCA)

          /* [rw] Sleep on collision-avoidance check failure event
           */
#define   BIT_SLPNOISY  BIT(0)
            /* The device will automatically go to sleep following the triggering of a
             * collision-avoidance check failure event
             */
#define     SLPNOISY_0b1  MOV2MASK(0b1, BIT_SLPNOISY)
            /* Deactivate sleep on collision-avoidance check failure event
             */
#define     SLPNOISY_0b0  MOV2MASK(0b0, BIT_SLPNOISY)
            /* Get SLPNOISY value
             */
#define     GET_SLPNOISY(reg_val)  MASK2VAL(reg_val, BIT_SLPNOISY)
            /* SLPNOISY default value
             */
#define     SLPNOISY_DEFAULT  MOV2MASK(0x0, BIT_SLPNOISY)

#define REG8_SLEEP_CONFIG_DEFAULT  0x00C0



/******************************************************************************/
/*                       Register TIMER_CONFIG (8 bits)                       */
/******************************************************************************/
#define REG8_TIMER_CONFIG 0x5

          /* [rw] Automatically wake-up
           */
#define   BIT_AUTOWAKE  BIT(7)
            /* The device uses the wake-up timer to decide when to wake-up on its own
             */
#define     AUTOWAKE_0b1  MOV2MASK(0b1, BIT_AUTOWAKE)
            /* The device will only wake up by manually clearing the bit GO_SLEEP (at
             * register address 0x1F)
             */
#define     AUTOWAKE_0b0  MOV2MASK(0b0, BIT_AUTOWAKE)
            /* Get AUTOWAKE value
             */
#define     GET_AUTOWAKE(reg_val)  MASK2VAL(reg_val, BIT_AUTOWAKE)
            /* AUTOWAKE default value
             */
#define     AUTOWAKE_DEFAULT  MOV2MASK(0x0, BIT_AUTOWAKE)

          /* [rw] Wake-up only once
           */
#define   BIT_WAKEONCE  BIT(6)
            /* The wake-up timer running on the symbol clock is configured to produce a
             * wake-up event only once after each time at least one of the two register
             * addresses 0x06 and 0x07 of register field SLPPERIOD is written
             */
#define     WAKEONCE_0b1  MOV2MASK(0b1, BIT_WAKEONCE)
            /* The wake-up timer always reset itself to 0x0000 when it reach the value
             * defined in SLPPERIOD and produce a wake-up event that can wake-up the device
             * from sleep if AUTOWAKE is set to 1
             */
#define     WAKEONCE_0b0  MOV2MASK(0b0, BIT_WAKEONCE)
            /* Get WAKEONCE value
             */
#define     GET_WAKEONCE(reg_val)  MASK2VAL(reg_val, BIT_WAKEONCE)
            /* WAKEONCE default value
             */
#define     WAKEONCE_DEFAULT  MOV2MASK(0x0, BIT_WAKEONCE)

          /* [rw] Synchronize wake-up timer at the end of frames
           */
#define   BIT_SYNATEND  BIT(5)
            /* Register bits SYNPKTTX and SYNPKTRX can be used to enable automatic timer
             * synchronization upon finishing the transmission or reception (unconditionally)
             * of any frame
             */
#define     SYNATEND_0b1  MOV2MASK(0b1, BIT_SYNATEND)
            /* Register bits SYNPKTTX and SYNPKTRX can only enable automatic wake-up timer
             * synchronization upon sending or detecting the synchronization word of each frame
             *
             */
#define     SYNATEND_0b0  MOV2MASK(0b0, BIT_SYNATEND)
            /* Get SYNATEND value
             */
#define     GET_SYNATEND(reg_val)  MASK2VAL(reg_val, BIT_SYNATEND)
            /* SYNATEND default value
             */
#define     SYNATEND_DEFAULT  MOV2MASK(0x0, BIT_SYNATEND)

          /* [rw] Synchronize wake-up timer on frame transmission event
           */
#define   BIT_SYNPKTTX  BIT(4)
            /* The device will automatically reset the wake-up timer at every frame
             * transmission event without any discrimination between frames
             */
#define     SYNPKTTX_0b1  MOV2MASK(0b1, BIT_SYNPKTTX)
            /* Deactivate the timer reset at every frame transmission
             */
#define     SYNPKTTX_0b0  MOV2MASK(0b0, BIT_SYNPKTTX)
            /* Get SYNPKTTX value
             */
#define     GET_SYNPKTTX(reg_val)  MASK2VAL(reg_val, BIT_SYNPKTTX)
            /* SYNPKTTX default value
             */
#define     SYNPKTTX_DEFAULT  MOV2MASK(0x0, BIT_SYNPKTTX)

          /* [rw] Synchronize wake-up timer on frame reception event
           */
#define   BIT_SYNPKTRX  BIT(3)
            /* The device will automatically reset the wake-up timer at every frame
             * reception event without any discrimination between frames
             */
#define     SYNPKTRX_0b1  MOV2MASK(0b1, BIT_SYNPKTRX)
            /* Deactivate the timer reset on frame reception
             */
#define     SYNPKTRX_0b0  MOV2MASK(0b0, BIT_SYNPKTRX)
            /* Get SYNPKTRX value
             */
#define     GET_SYNPKTRX(reg_val)  MASK2VAL(reg_val, BIT_SYNPKTRX)
            /* SYNPKTRX default value
             */
#define     SYNPKTRX_DEFAULT  MOV2MASK(0x0, BIT_SYNPKTRX)

          /* [rw] Synchronize wake-up timer on frame address field match event
           */
#define   BIT_SYNMATCH  BIT(2)
            /* The device will automatically reset the wake-up timer at the end of the
             * reception of a frame with an address field that matches the receiver's own
             * address
             */
#define     SYNMATCH_0b1  MOV2MASK(0b1, BIT_SYNMATCH)
            /* Deactivate the timer reset on an address match
             */
#define     SYNMATCH_0b0  MOV2MASK(0b0, BIT_SYNMATCH)
            /* Get SYNMATCH value
             */
#define     GET_SYNMATCH(reg_val)  MASK2VAL(reg_val, BIT_SYNMATCH)
            /* SYNMATCH default value
             */
#define     SYNMATCH_DEFAULT  MOV2MASK(0x0, BIT_SYNMATCH)

          /* [rw] Synchronize wake-up timer on broadcast frame reception event
           */
#define   BIT_SYNBRDCA  BIT(1)
            /* The device will automatically reset the wake-up timer at the end of the
             * reception of a frame with an address field that matches the receiver's
             * sub-network broadcast address
             */
#define     SYNBRDCA_0b1  MOV2MASK(0b1, BIT_SYNBRDCA)
            /* Deactivate the timer reset on a reception of a broadcast
             */
#define     SYNBRDCA_0b0  MOV2MASK(0b0, BIT_SYNBRDCA)
            /* Get SYNBRDCA value
             */
#define     GET_SYNBRDCA(reg_val)  MASK2VAL(reg_val, BIT_SYNBRDCA)
            /* SYNBRDCA default value
             */
#define     SYNBRDCA_DEFAULT  MOV2MASK(0x0, BIT_SYNBRDCA)

          /* [rw] Synchronize wake-up timer on cyclic redundancy check pass event
           */
#define   BIT_SYNRXCRC  BIT(0)
            /* The device will require a correct CRC field from each received frame to
             * automatically reset the wake-up timer
             */
#define     SYNRXCRC_0b1  MOV2MASK(0b1, BIT_SYNRXCRC)
            /* Deactivate the timer reset on a correct CRC field.
             */
#define     SYNRXCRC_0b0  MOV2MASK(0b0, BIT_SYNRXCRC)
            /* Get SYNRXCRC value
             */
#define     GET_SYNRXCRC(reg_val)  MASK2VAL(reg_val, BIT_SYNRXCRC)
            /* SYNRXCRC default value
             */
#define     SYNRXCRC_DEFAULT  MOV2MASK(0x0, BIT_SYNRXCRC)

#define REG8_TIMER_CONFIG_DEFAULT  0x0000



/******************************************************************************/
/*                    Register TIMER_COUNTER_15_8 (8 bits)                    */
/******************************************************************************/
#define REG8_TIMER_COUNTER_15_8 0x6

          /* [wo] Sleep Cycle Duration [15:8]
           */
#define   BITS_SLPPERIOD_15_8  BITS8(7, 0)
            /* This register sets the power cycle duration in clock cycles. The wake-up
             * timer's count resets at this value
             */
#define     SET_SLPPERIOD_15_8(value)  MOV2MASK(value, BITS_SLPPERIOD_15_8)
            /* SLPPERIOD_15_8 default value
             */
#define     SLPPERIOD_15_8_DEFAULT  MOV2MASK(0x8, BITS_SLPPERIOD_15_8)

          /* [ro] Crystal oscillator clock wake-up timer count [15:8]
           */
#define   BITS_XTALCOUNT_15_8  BITS8(7, 0)
            /* Reflects the low-frequency-clocked timer count value around the last time the
             * nCS pin was pulled down
             */
#define     GET_XTALCOUNT_15_8(reg_val)  MASK2VAL(reg_val, BITS_XTALCOUNT_15_8)
            /* XTALCOUNT_15_8 default value
             */
#define     XTALCOUNT_15_8_DEFAULT  MOV2MASK(0x08, BITS_XTALCOUNT_15_8)

#define REG8_TIMER_COUNTER_15_8_DEFAULT  0x0008



/******************************************************************************/
/*                    Register TIMER_COUNTER_7_0 (8 bits)                     */
/******************************************************************************/
#define REG8_TIMER_COUNTER_7_0 0x7

          /* [wo] Sleep Cycle Duration [15:8]
           */
#define   BITS_SLPPERIOD_7_0  BITS8(7, 0)
            /* This register sets the power cycle duration in clock cycles. The wake-up
             * timer's count resets at this value
             */
#define     SET_SLPPERIOD_7_0(value)  MOV2MASK(value, BITS_SLPPERIOD_7_0)
            /* SLPPERIOD_7_0 default value
             */
#define     SLPPERIOD_7_0_DEFAULT  MOV2MASK(0x0, BITS_SLPPERIOD_7_0)

          /* [ro] Crystal oscillator clock wake-up timer count [7:0]
           */
#define   BITS_XTALCOUNT_7_0  BITS8(7, 0)
            /* Reflects the low-frequency-clocked timer count value around the last time the
             * nCS pin was pulled down
             */
#define     GET_XTALCOUNT_7_0(reg_val)  MASK2VAL(reg_val, BITS_XTALCOUNT_7_0)
            /* XTALCOUNT_7_0 default value
             */
#define     XTALCOUNT_7_0_DEFAULT  MOV2MASK(0x00, BITS_XTALCOUNT_7_0)

#define REG8_TIMER_COUNTER_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                    Register RX_TIMEOUT_PERIOD1 (8 bits)                    */
/******************************************************************************/
#define REG8_RX_TIMEOUT_PERIOD1 0x8

          /* [rw] Receiver timeout period[11:4]
           */
#define   BITS_RXPERIOD_11_4  BITS8(7, 0)
            /* Defines how long will the modem wait in reception mode while being idle
             * before triggering for the first time a receiver timeout event
             */
#define     SET_RXPERIOD_11_4(value)    MOV2MASK(value, BITS_RXPERIOD_11_4)
#define     GET_RXPERIOD_11_4(reg_val)  MASK2VAL(reg_val, BITS_RXPERIOD_11_4)
            /* RXPERIOD_11_4 default value
             */
#define     RXPERIOD_11_4_DEFAULT  MOV2MASK(0xff, BITS_RXPERIOD_11_4)

#define REG8_RX_TIMEOUT_PERIOD1_DEFAULT  0x00FF



/******************************************************************************/
/*             Register RX_TIMEOUT_PERIOD0_PWR_UP_DELAY (8 bits)              */
/******************************************************************************/
#define REG8_RX_TIMEOUT_PERIOD0_PWR_UP_DELAY 0x9

          /* [rw] Receiver timeout period[3:0]
           */
#define   BITS_RXPERIOD_3_0  BITS8(7, 4)
            /* Defines how long will the modem wait in reception mode while being idle
             * before triggering for the first time a receiver timeout event
             */
#define     SET_RXPERIOD_3_0(value)    MOV2MASK(value, BITS_RXPERIOD_3_0)
#define     GET_RXPERIOD_3_0(reg_val)  MASK2VAL(reg_val, BITS_RXPERIOD_3_0)
            /* RXPERIOD_3_0 default value
             */
#define     RXPERIOD_3_0_DEFAULT  MOV2MASK(0x3, BITS_RXPERIOD_3_0)

          /* [rw] Receiver power-up delay
           */
#define   BITS_RXPUDELAY  BITS8(3, 0)
            /* Tells the modem how long to wait in symbol clock cycles for the receiver's
             * bias signals to settle before considering the receiver's ADC outputs valid
             */
#define     SET_RXPUDELAY(value)    MOV2MASK(value, BITS_RXPUDELAY)
#define     GET_RXPUDELAY(reg_val)  MASK2VAL(reg_val, BITS_RXPUDELAY)
            /* RXPUDELAY default value
             */
#define     RXPUDELAY_DEFAULT  MOV2MASK(0xf, BITS_RXPUDELAY)

#define REG8_RX_TIMEOUT_PERIOD0_PWR_UP_DELAY_DEFAULT  0x003F



/******************************************************************************/
/*                     Register TX_PWR_UP_DELAY (8 bits)                      */
/******************************************************************************/
#define REG8_TX_PWR_UP_DELAY 0xA

          /* [rw] Fine-grained transceiver power-up delay
           */
#define   BITS_PWRUPDEL  BITS8(7, 0)
            /* Defines how long to delay the power-up of the transmitter or receiver after
             * waking up the device from sleep
             */
#define     SET_PWRUPDEL(value)    MOV2MASK(value, BITS_PWRUPDEL)
#define     GET_PWRUPDEL(reg_val)  MASK2VAL(reg_val, BITS_PWRUPDEL)
            /* PWRUPDEL default value
             */
#define     PWRUPDEL_DEFAULT  MOV2MASK(0x0, BITS_PWRUPDEL)

#define REG8_TX_PWR_UP_DELAY_DEFAULT  0x0000



/******************************************************************************/
/*                   Register PLL_STARTUP_DURATION (8 bits)                   */
/******************************************************************************/
#define REG8_PLL_STARTUP_DURATION 0xB

          /* [rw] Phase-locked loop power-up waiting time
           */
#define   BITS_PLLPUWAIT  BITS8(7, 0)
            /* Defines how long to wait for the integrated PLL to lock and settle before
             * powering up any other supply block who take far less time to settle and be ready
             * for transceiver operation
             */
#define     SET_PLLPUWAIT(value)    MOV2MASK(value, BITS_PLLPUWAIT)
#define     GET_PLLPUWAIT(reg_val)  MASK2VAL(reg_val, BITS_PLLPUWAIT)
            /* PLLPUWAIT default value
             */
#define     PLLPUWAIT_DEFAULT  MOV2MASK(0x60, BITS_PLLPUWAIT)

#define REG8_PLL_STARTUP_DURATION_DEFAULT  0x0060



/******************************************************************************/
/*                    Register PLL_DIVIDER_RATIO (8 bits)                     */
/******************************************************************************/
#define REG8_PLL_DIVIDER_RATIO 0xC

          /* [rw] Automatic frame reply transmission extra delay
           */
#define   BITS_RPLYTXDEL  BITS8(7, 6)
            /* Add an extra delay of 112 symbol clock cycles for the transmission of
             * auto-reply
             */
#define     RPLYTXDEL_0b11  MOV2MASK(0b11, BITS_RPLYTXDEL)
            /* Add an extra delay of 48 symbol clock cycles for the transmission of
             * auto-reply
             */
#define     RPLYTXDEL_0b10  MOV2MASK(0b10, BITS_RPLYTXDEL)
            /* Add an extra delay of 16 symbol clock cycles for the transmission of
             * auto-reply
             */
#define     RPLYTXDEL_0b01  MOV2MASK(0b01, BITS_RPLYTXDEL)
            /* Add an extra delay of 0 for the transmission of auto-reply
             */
#define     RPLYTXDEL_0b00  MOV2MASK(0b00, BITS_RPLYTXDEL)
            /* Get RPLYTXDEL value
             */
#define     GET_RPLYTXDEL(reg_val)  MASK2VAL(reg_val, BITS_RPLYTXDEL)
            /* RPLYTXDEL default value
             */
#define     RPLYTXDEL_DEFAULT  MOV2MASK(0x0, BITS_RPLYTXDEL)

          /* [rw] Phase-locked loop divider ratio
           */
#define   BITS_PLL_RATIO  BITS8(5, 0)
            /* Defines the PLL divider ratio used to synthesize the symbol clock frequency
             * from the crystal oscillator frequency
             */
#define     SET_PLL_RATIO(value)    MOV2MASK(value, BITS_PLL_RATIO)
#define     GET_PLL_RATIO(reg_val)  MASK2VAL(reg_val, BITS_PLL_RATIO)
            /* PLL_RATIO default value
             */
#define     PLL_RATIO_DEFAULT  MOV2MASK(0x3f, BITS_PLL_RATIO)

#define REG8_PLL_DIVIDER_RATIO_DEFAULT  0x003F



/******************************************************************************/
/*                    Register CALIB_RES_IMP_TUNE (8 bits)                    */
/******************************************************************************/
#define REG8_CALIB_RES_IMP_TUNE 0xD

          /* [rw] Low-noise amplifier impedance tuning
           */
#define   BIT_LNAIMPED  BIT(7)
            /* Increases the bias current of the LNA by 700 mA and slightly degrades the
             * impedance matching for a reduction of approximately 0.25 dB of the LNA's noise
             * figure
             */
#define     LNAIMPED_0b1  MOV2MASK(0b1, BIT_LNAIMPED)
            /* The LNA's operating point is more favorable to impedance matching and power
             * consumption to the detriment of the noise figure
             */
#define     LNAIMPED_0b0  MOV2MASK(0b0, BIT_LNAIMPED)
            /* Get LNAIMPED value
             */
#define     GET_LNAIMPED(reg_val)  MASK2VAL(reg_val, BIT_LNAIMPED)
            /* LNAIMPED default value
             */
#define     LNAIMPED_DEFAULT  MOV2MASK(0x0, BIT_LNAIMPED)

          /* [rw] Phase-locked loop voltage-controlled oscillator resistor tuning
           */
#define   BITS_PLL_RES  BITS8(6, 4)
            /* Used as digital calibration to adjust the effective resistance value in the
             * PLL's VCO so that it can reach the desired output frequency for a wide range of
             * manufacturing process variations
             */
#define     SET_PLL_RES(value)    MOV2MASK(value, BITS_PLL_RES)
#define     GET_PLL_RES(reg_val)  MASK2VAL(reg_val, BITS_PLL_RES)
            /* PLL_RES default value
             */
#define     PLL_RES_DEFAULT  MOV2MASK(0x2, BITS_PLL_RES)

          /* [rw] Transceiver supply voltage reference tuning
           */
#define   BITS_VREF_TUNE  BITS8(3, 0)
            /* Used to fine-tune the output voltage of the main reference buffer. This may
             * be used to compensate for frequency, gain and overall performance variations
             * between individual units
             */
#define     SET_VREF_TUNE(value)    MOV2MASK(value, BITS_VREF_TUNE)
#define     GET_VREF_TUNE(reg_val)  MASK2VAL(reg_val, BITS_VREF_TUNE)
            /* VREF_TUNE default value
             */
#define     VREF_TUNE_DEFAULT  MOV2MASK(0xa, BITS_VREF_TUNE)

#define REG8_CALIB_RES_IMP_TUNE_DEFAULT  0x002A



/******************************************************************************/
/*                    Register PERIPHERAL_CONTROL (8 bits)                    */
/******************************************************************************/
#define REG8_PERIPHERAL_CONTROL 0xE

          /* [rw] Standard SPI operation
           */
#define   BIT_STDSPI  BIT(7)
            /* The device is fully compliant with the de facto industry standard for SPI
             * communications
             */
#define     STDSPI_0b1  MOV2MASK(0b1, BIT_STDSPI)
            /* Enable fast non standard SPI communications
             */
#define     STDSPI_0b0  MOV2MASK(0b0, BIT_STDSPI)
            /* Get STDSPI value
             */
#define     GET_STDSPI(reg_val)  MASK2VAL(reg_val, BIT_STDSPI)
            /* STDSPI default value
             */
#define     STDSPI_DEFAULT  MOV2MASK(0x1, BIT_STDSPI)

          /* [rw] Reception buffer automatic flush disable
           */
#define   BIT_FLUSHDIS  BIT(6)
            /* Disable the auto-flush feature of the radio
             */
#define     FLUSHDIS_0b1  MOV2MASK(0b1, BIT_FLUSHDIS)
            /* Enable the auto-flush feature of the radio
             */
#define     FLUSHDIS_0b0  MOV2MASK(0b0, BIT_FLUSHDIS)
            /* Get FLUSHDIS value
             */
#define     GET_FLUSHDIS(reg_val)  MASK2VAL(reg_val, BIT_FLUSHDIS)
            /* FLUSHDIS default value
             */
#define     FLUSHDIS_DEFAULT  MOV2MASK(0x0, BIT_FLUSHDIS)

          /* [rw] Storage capacitor switch disable
           */
#define   BIT_V1SW_DIS  BIT(5)
            /* The discrete storage capacitor is never disconnected from the internal 1-volt
             * power domains and little to no energy is preserved on the discrete capacitor
             * during the DC/DC converter's off time
             */
#define     V1SW_DIS_0b1  MOV2MASK(0b1, BIT_V1SW_DIS)
            /* The discrete storage capacitor holding the transceiver's supply voltage
             * charge is cut off from the internal supply nets of the transceiver and the modem
             * when the DC/DC converter is off
             */
#define     V1SW_DIS_0b0  MOV2MASK(0b0, BIT_V1SW_DIS)
            /* Get V1SW_DIS value
             */
#define     GET_V1SW_DIS(reg_val)  MASK2VAL(reg_val, BIT_V1SW_DIS)
            /* V1SW_DIS default value
             */
#define     V1SW_DIS_DEFAULT  MOV2MASK(0x0, BIT_V1SW_DIS)

          /* [rw] DC/DC converter disable
           */
#define   BIT_DCDC_DIS  BIT(4)
            /* Disable the DC/DC
             */
#define     DCDC_DIS_0b1  MOV2MASK(0b1, BIT_DCDC_DIS)
            /* Enable the DC/DC
             */
#define     DCDC_DIS_0b0  MOV2MASK(0b0, BIT_DCDC_DIS)
            /* Get DCDC_DIS value
             */
#define     GET_DCDC_DIS(reg_val)  MASK2VAL(reg_val, BIT_DCDC_DIS)
            /* DCDC_DIS default value
             */
#define     DCDC_DIS_DEFAULT  MOV2MASK(0x0, BIT_DCDC_DIS)

          /* [rw] Phase-locked loop disable
           */
#define   BIT_PLL_DIS  BIT(3)
            /* Disable the PLL
             */
#define     PLL_DIS_0b1  MOV2MASK(0b1, BIT_PLL_DIS)
            /* Enable the PLL
             */
#define     PLL_DIS_0b0  MOV2MASK(0b0, BIT_PLL_DIS)
            /* Get PLL_DIS value
             */
#define     GET_PLL_DIS(reg_val)  MASK2VAL(reg_val, BIT_PLL_DIS)
            /* PLL_DIS default value
             */
#define     PLL_DIS_DEFAULT  MOV2MASK(0x0, BIT_PLL_DIS)

          /* [rw] Symbol rate clock source
           */
#define   BIT_SYMBCSRC  BIT(2)
            /* The PLL_CLK package pin is configured to be an input and the internal PLL
             * output clock signal is replaced by the signal on the PLL_CLK pin to drive the
             * symbol clock signal
             */
#define     SYMBCSRC_0b1  MOV2MASK(0b1, BIT_SYMBCSRC)
            /* The PLL output clock is used to provide the symbol rate to the radio
             */
#define     SYMBCSRC_0b0  MOV2MASK(0b0, BIT_SYMBCSRC)
            /* Get SYMBCSRC value
             */
#define     GET_SYMBCSRC(reg_val)  MASK2VAL(reg_val, BIT_SYMBCSRC)
            /* SYMBCSRC default value
             */
#define     SYMBCSRC_DEFAULT  MOV2MASK(0x0, BIT_SYMBCSRC)

          /* [rw] Crystal oscillator clock source
           */
#define   BIT_XTALCSRC  BIT(1)
            /* The XTAL_CLK package pin is configured to be an input and the crystal
             * oscillator output clock signal is replaced by the signal on the XTAL_CLK pin to
             * drive the low-frequency reference clock signal
             */
#define     XTALCSRC_0b1  MOV2MASK(0b1, BIT_XTALCSRC)
            /* The integrated crystal oscillator output is used to run the sleep control
             * state machine
             */
#define     XTALCSRC_0b0  MOV2MASK(0b0, BIT_XTALCSRC)
            /* Get XTALCSRC value
             */
#define     GET_XTALCSRC(reg_val)  MASK2VAL(reg_val, BIT_XTALCSRC)
            /* XTALCSRC default value
             */
#define     XTALCSRC_DEFAULT  MOV2MASK(0x0, BIT_XTALCSRC)

          /* [rw] Output crystal oscillator clock signal
           */
#define   BIT_OUTPXTAL  BIT(0)
            /* Enable the outputting of the crystal oscillator clock signal through the
             * XTAL\_CLK pin (mainly for debug)
             */
#define     OUTPXTAL_0b1  MOV2MASK(0b1, BIT_OUTPXTAL)
            /* Disable the outputting of the crystal oscillator clock signal through the
             * XTAL\_CLK pin
             */
#define     OUTPXTAL_0b0  MOV2MASK(0b0, BIT_OUTPXTAL)
            /* Get OUTPXTAL value
             */
#define     GET_OUTPXTAL(reg_val)  MASK2VAL(reg_val, BIT_OUTPXTAL)
            /* OUTPXTAL default value
             */
#define     OUTPXTAL_DEFAULT  MOV2MASK(0x0, BIT_OUTPXTAL)

#define REG8_PERIPHERAL_CONTROL_DEFAULT  0x0080



/******************************************************************************/
/*                      Register RX_FREQ_TUNING (8 bits)                      */
/******************************************************************************/
#define REG8_RX_FREQ_TUNING 0xF

          /* [rw] Low-noise amplifier peak frequency
           */
#define   BITS_LNA_PEAK  BITS8(7, 5)
            /* Sets the LNA peak frequency by digitally tuning the capacitance of its LC
             * tank
             */
#define     SET_LNA_PEAK(value)    MOV2MASK(value, BITS_LNA_PEAK)
#define     GET_LNA_PEAK(reg_val)  MASK2VAL(reg_val, BITS_LNA_PEAK)
            /* LNA_PEAK default value
             */
#define     LNA_PEAK_DEFAULT  MOV2MASK(0x6, BITS_LNA_PEAK)

          /* [rw] Radio-frequency filter frequency
           */
#define   BITS_RXFILFREQ  BITS8(4, 0)
            /* Sets the center frequency of the receiver's radio-frequency active pass-band
             * filter by tuning the DCRO providing it its reference frequency
             */
#define     SET_RXFILFREQ(value)    MOV2MASK(value, BITS_RXFILFREQ)
#define     GET_RXFILFREQ(reg_val)  MASK2VAL(reg_val, BITS_RXFILFREQ)
            /* RXFILFREQ default value
             */
#define     RXFILFREQ_DEFAULT  MOV2MASK(0xa, BITS_RXFILFREQ)

#define REG8_RX_FREQ_TUNING_DEFAULT  0x00CA



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_12 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_12 0x10

          /* [rw] Width of 12th pulse
           */
#define   BITS_PULSE12WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 12th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE12WID(value)    MOV2MASK(value, BITS_PULSE12WID)
#define     GET_PULSE12WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE12WID)
            /* PULSE12WID default value
             */
#define     PULSE12WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE12WID)

          /* [rw] Frequency of pulse 12
           */
#define   BITS_PULS12FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 12th pulse
             * position of each symbol transmitted. If both PULSE12WID and PULS12FREQ fields
             * are null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS12FREQ(value)    MOV2MASK(value, BITS_PULS12FREQ)
#define     GET_PULS12FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS12FREQ)
            /* PULS12FREQ default value
             */
#define     PULS12FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS12FREQ)

#define REG8_TX_PULSE_PATTERN_12_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_11 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_11 0x11

          /* [rw] Width of 11th pulse
           */
#define   BITS_PULSE11WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 11th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE11WID(value)    MOV2MASK(value, BITS_PULSE11WID)
#define     GET_PULSE11WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE11WID)
            /* PULSE11WID default value
             */
#define     PULSE11WID_DEFAULT  MOV2MASK(0x6, BITS_PULSE11WID)

          /* [rw] Frequency of pulse 11
           */
#define   BITS_PULS11FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 11th pulse
             * position of each symbol transmitted. If both PULSE11WID and PULS11FREQ fields
             * are null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS11FREQ(value)    MOV2MASK(value, BITS_PULS11FREQ)
#define     GET_PULS11FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS11FREQ)
            /* PULS11FREQ default value
             */
#define     PULS11FREQ_DEFAULT  MOV2MASK(0x14, BITS_PULS11FREQ)

#define REG8_TX_PULSE_PATTERN_11_DEFAULT  0x00D4



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_10 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_10 0x12

          /* [rw] Width of 10th pulse
           */
#define   BITS_PULSE10WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 10th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE10WID(value)    MOV2MASK(value, BITS_PULSE10WID)
#define     GET_PULSE10WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE10WID)
            /* PULSE10WID default value
             */
#define     PULSE10WID_DEFAULT  MOV2MASK(0x6, BITS_PULSE10WID)

          /* [rw] Frequency of pulse 10
           */
#define   BITS_PULS10FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 10th pulse
             * position of each symbol transmitted. If both PULSE10WID and PULS10FREQ fields
             * are null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS10FREQ(value)    MOV2MASK(value, BITS_PULS10FREQ)
#define     GET_PULS10FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS10FREQ)
            /* PULS10FREQ default value
             */
#define     PULS10FREQ_DEFAULT  MOV2MASK(0x16, BITS_PULS10FREQ)

#define REG8_TX_PULSE_PATTERN_10_DEFAULT  0x00D6



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_09 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_09 0x13

          /* [rw] Width of 9th pulse
           */
#define   BITS_PULSE9WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 9th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE9WID(value)    MOV2MASK(value, BITS_PULSE9WID)
#define     GET_PULSE9WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE9WID)
            /* PULSE9WID default value
             */
#define     PULSE9WID_DEFAULT  MOV2MASK(0x6, BITS_PULSE9WID)

          /* [rw] Frequency of pulse 9
           */
#define   BITS_PULS9FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 9th pulse
             * position of each symbol transmitted. If both PULSE9WID and PULS9FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS9FREQ(value)    MOV2MASK(value, BITS_PULS9FREQ)
#define     GET_PULS9FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS9FREQ)
            /* PULS9FREQ default value
             */
#define     PULS9FREQ_DEFAULT  MOV2MASK(0x18, BITS_PULS9FREQ)

#define REG8_TX_PULSE_PATTERN_09_DEFAULT  0x00D8



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_08 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_08 0x14

          /* [rw] Width of 8th pulse
           */
#define   BITS_PULSE8WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 8th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE8WID(value)    MOV2MASK(value, BITS_PULSE8WID)
#define     GET_PULSE8WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE8WID)
            /* PULSE8WID default value
             */
#define     PULSE8WID_DEFAULT  MOV2MASK(0x6, BITS_PULSE8WID)

          /* [rw] Frequency of pulse 8
           */
#define   BITS_PULS8FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 8th pulse
             * position of each symbol transmitted. If both PULSE8WID and PULS8FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS8FREQ(value)    MOV2MASK(value, BITS_PULS8FREQ)
#define     GET_PULS8FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS8FREQ)
            /* PULS8FREQ default value
             */
#define     PULS8FREQ_DEFAULT  MOV2MASK(0x1a, BITS_PULS8FREQ)

#define REG8_TX_PULSE_PATTERN_08_DEFAULT  0x00DA



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_07 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_07 0x15

          /* [rw] Width of 7th pulse
           */
#define   BITS_PULSE7WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 7th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE7WID(value)    MOV2MASK(value, BITS_PULSE7WID)
#define     GET_PULSE7WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE7WID)
            /* PULSE7WID default value
             */
#define     PULSE7WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE7WID)

          /* [rw] Frequency of pulse 7
           */
#define   BITS_PULS7FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 7th pulse
             * position of each symbol transmitted. If both PULSE7WID and PULS7FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS7FREQ(value)    MOV2MASK(value, BITS_PULS7FREQ)
#define     GET_PULS7FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS7FREQ)
            /* PULS7FREQ default value
             */
#define     PULS7FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS7FREQ)

#define REG8_TX_PULSE_PATTERN_07_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_06 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_06 0x16

          /* [rw] Width of 6th pulse
           */
#define   BITS_PULSE6WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 6th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE6WID(value)    MOV2MASK(value, BITS_PULSE6WID)
#define     GET_PULSE6WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE6WID)
            /* PULSE6WID default value
             */
#define     PULSE6WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE6WID)

          /* [rw] Frequency of pulse 6
           */
#define   BITS_PULS6FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 6th pulse
             * position of each symbol transmitted. If both PULSE6WID and PULS6FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS6FREQ(value)    MOV2MASK(value, BITS_PULS6FREQ)
#define     GET_PULS6FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS6FREQ)
            /* PULS6FREQ default value
             */
#define     PULS6FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS6FREQ)

#define REG8_TX_PULSE_PATTERN_06_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_05 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_05 0x17

          /* [rw] Width of 5th pulse
           */
#define   BITS_PULSE5WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 5th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE5WID(value)    MOV2MASK(value, BITS_PULSE5WID)
#define     GET_PULSE5WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE5WID)
            /* PULSE5WID default value
             */
#define     PULSE5WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE5WID)

          /* [rw] Frequency of pulse 5
           */
#define   BITS_PULS5FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 5th pulse
             * position of each symbol transmitted. If both PULSE5WID and PULS5FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS5FREQ(value)    MOV2MASK(value, BITS_PULS5FREQ)
#define     GET_PULS5FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS5FREQ)
            /* PULS5FREQ default value
             */
#define     PULS5FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS5FREQ)

#define REG8_TX_PULSE_PATTERN_05_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_04 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_04 0x18

          /* [rw] Width of 4th pulse
           */
#define   BITS_PULSE4WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 4th pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE4WID(value)    MOV2MASK(value, BITS_PULSE4WID)
#define     GET_PULSE4WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE4WID)
            /* PULSE4WID default value
             */
#define     PULSE4WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE4WID)

          /* [rw] Frequency of pulse 4
           */
#define   BITS_PULS4FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 4th pulse
             * position of each symbol transmitted. If both PULSE4WID and PULS4FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS4FREQ(value)    MOV2MASK(value, BITS_PULS4FREQ)
#define     GET_PULS4FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS4FREQ)
            /* PULS4FREQ default value
             */
#define     PULS4FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS4FREQ)

#define REG8_TX_PULSE_PATTERN_04_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_03 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_03 0x19

          /* [rw] Width of 3rd pulse
           */
#define   BITS_PULSE3WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 3rd pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE3WID(value)    MOV2MASK(value, BITS_PULSE3WID)
#define     GET_PULSE3WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE3WID)
            /* PULSE3WID default value
             */
#define     PULSE3WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE3WID)

          /* [rw] Frequency of pulse 3
           */
#define   BITS_PULS3FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 3rd pulse
             * position of each symbol transmitted. If both PULSE3WID and PULS3FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS3FREQ(value)    MOV2MASK(value, BITS_PULS3FREQ)
#define     GET_PULS3FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS3FREQ)
            /* PULS3FREQ default value
             */
#define     PULS3FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS3FREQ)

#define REG8_TX_PULSE_PATTERN_03_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_02 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_02 0x1A

          /* [rw] Width of 2nd pulse
           */
#define   BITS_PULSE2WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 2nd pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE2WID(value)    MOV2MASK(value, BITS_PULSE2WID)
#define     GET_PULSE2WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE2WID)
            /* PULSE2WID default value
             */
#define     PULSE2WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE2WID)

          /* [rw] Frequency of pulse 2
           */
#define   BITS_PULS2FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 2nd pulse
             * position of each symbol transmitted. If both PULSE2WID and PULS2FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS2FREQ(value)    MOV2MASK(value, BITS_PULS2FREQ)
#define     GET_PULS2FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS2FREQ)
            /* PULS2FREQ default value
             */
#define     PULS2FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS2FREQ)

#define REG8_TX_PULSE_PATTERN_02_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TX_PULSE_PATTERN_01 (8 bits)                    */
/******************************************************************************/
#define REG8_TX_PULSE_PATTERN_01 0x1B

          /* [rw] Width of 1st pulse
           */
#define   BITS_PULSE1WID  BITS8(7, 5)
            /* This register field sets the pulse duration of all pulses at the 1st pulse
             * position of each symbol transmitted. A wider pulse translates to more output
             * power
             */
#define     SET_PULSE1WID(value)    MOV2MASK(value, BITS_PULSE1WID)
#define     GET_PULSE1WID(reg_val)  MASK2VAL(reg_val, BITS_PULSE1WID)
            /* PULSE1WID default value
             */
#define     PULSE1WID_DEFAULT  MOV2MASK(0x0, BITS_PULSE1WID)

          /* [rw] Frequency of pulse 1
           */
#define   BITS_PULS1FREQ  BITS8(4, 0)
            /* This register field sets the center frequency of all pulses at the 1st pulse
             * position of each symbol transmitted. If both PULSE1WID and PULS1FREQ fields are
             * null (0x00), no pulse is transmitted at this position
             */
#define     SET_PULS1FREQ(value)    MOV2MASK(value, BITS_PULS1FREQ)
#define     GET_PULS1FREQ(reg_val)  MASK2VAL(reg_val, BITS_PULS1FREQ)
            /* PULS1FREQ default value
             */
#define     PULS1FREQ_DEFAULT  MOV2MASK(0x0, BITS_PULS1FREQ)

#define REG8_TX_PULSE_PATTERN_01_DEFAULT  0x0000



/******************************************************************************/
/*                     Register PULSE_PARAMETERS (8 bits)                     */
/******************************************************************************/
#define REG8_PULSE_PARAMETERS 0x1C

          /* [rw] Hold transmitter's data signal on
           */
#define   BIT_HOLDTXON  BIT(7)
            /* The data input pin of the transmitter is forced to '1' which makes it
             * transmit its pulse pattern at every single symbol clock cycle for which it is
             * powered up
             */
#define     HOLDTXON_0b1  MOV2MASK(0b1, BIT_HOLDTXON)
            /* Deactivate the holding of the transmitter's data signal
             */
#define     HOLDTXON_0b0  MOV2MASK(0b0, BIT_HOLDTXON)
            /* Get HOLDTXON value
             */
#define     GET_HOLDTXON(reg_val)  MASK2VAL(reg_val, BIT_HOLDTXON)
            /* HOLDTXON default value
             */
#define     HOLDTXON_DEFAULT  MOV2MASK(0x0, BIT_HOLDTXON)

          /* [rw] Randomize transmitted pulse phase
           */
#define   BIT_RNDPHASE  BIT(6)
            /* Transmitted pulses will have their oscillation phase randomly flipped to
             * spread energy more uniformly across the exploited frequency spectrum
             */
#define     RNDPHASE_0b1  MOV2MASK(0b1, BIT_RNDPHASE)
            /* All pulses oscillations have the same phase
             */
#define     RNDPHASE_0b0  MOV2MASK(0b0, BIT_RNDPHASE)
            /* Get RNDPHASE value
             */
#define     GET_RNDPHASE(reg_val)  MASK2VAL(reg_val, BIT_RNDPHASE)
            /* RNDPHASE default value
             */
#define     RNDPHASE_DEFAULT  MOV2MASK(0x1, BIT_RNDPHASE)

          /* [rw] Transmission power
           */
#define   BITS_TX_POWER  BITS8(5, 4)
            /* Attenuating the TX power level by 1.8dB
             */
#define     TX_POWER_0b11  MOV2MASK(0b11, BITS_TX_POWER)
            /* Attenuating the TX power level by 1.2dB
             */
#define     TX_POWER_0b10  MOV2MASK(0b10, BITS_TX_POWER)
            /* Attenuating the TX power level by 0.6dB
             */
#define     TX_POWER_0b01  MOV2MASK(0b01, BITS_TX_POWER)
            /* Attenuating the TX power level by 0dB
             */
#define     TX_POWER_0b00  MOV2MASK(0b00, BITS_TX_POWER)
            /* Every increment in this register attenuate the TX power level by 0.6dB
             */
#define     SET_TX_POWER(value)    MOV2MASK(value, BITS_TX_POWER)
#define     GET_TX_POWER(reg_val)  MASK2VAL(reg_val, BITS_TX_POWER)
            /* TX_POWER default value
             */
#define     TX_POWER_DEFAULT  MOV2MASK(0x0, BITS_TX_POWER)

          /* [rw] Intermediate-frequency filter enable
           */
#define   BIT_IFFILTEN  BIT(3)
            /* Enable the intermediate-frequency N-path filter of the receiver
             */
#define     IFFILTEN_0b1  MOV2MASK(0b1, BIT_IFFILTEN)
            /* Disable the intermediate-frequency N-path filter of the receiver
             */
#define     IFFILTEN_0b0  MOV2MASK(0b0, BIT_IFFILTEN)
            /* Get IFFILTEN value
             */
#define     GET_IFFILTEN(reg_val)  MASK2VAL(reg_val, BIT_IFFILTEN)
            /* IFFILTEN default value
             */
#define     IFFILTEN_DEFAULT  MOV2MASK(0x0, BIT_IFFILTEN)

          /* [ro] Device supply voltage level
           */
#define   BITS_VDDLEVEL  BITS8(2, 0)
            /* Reflect the current amplitude of the main voltage supply relative to the
             * amplitude of the 1 volt supply
             */
#define     GET_VDDLEVEL(reg_val)  MASK2VAL(reg_val, BITS_VDDLEVEL)
            /* VDDLEVEL default value
             */
#define     VDDLEVEL_DEFAULT  MOV2MASK(0, BITS_VDDLEVEL)

#define REG8_PULSE_PARAMETERS_DEFAULT  0x0040



/******************************************************************************/
/*                     Register BASEBAND_TUNING (8 bits)                      */
/******************************************************************************/
#define REG8_BASEBAND_TUNING 0x1D

          /* [rw] Delay line tuning value
           */
#define   BITS_DL_TUNE  BITS8(7, 4)
            /* Adjusts the propagation delay through the delay line
             */
#define     SET_DL_TUNE(value)    MOV2MASK(value, BITS_DL_TUNE)
#define     GET_DL_TUNE(reg_val)  MASK2VAL(reg_val, BITS_DL_TUNE)
            /* DL_TUNE default value
             */
#define     DL_TUNE_DEFAULT  MOV2MASK(0x8, BITS_DL_TUNE)

          /* [wo] Collision-avoidance check radio-frequency gain override
           */
#define   BIT_CAGAINOV  BIT(3)
            /* Override the CCA gain setting to use its own gain, which will be the max one
             *
             */
#define     CAGAINOV_0b1  MOV2MASK(0b1, BIT_CAGAINOV)
            /* CCA gain will be the same as the constant gain
             */
#define     CAGAINOV_0b0  MOV2MASK(0b0, BIT_CAGAINOV)
            /* CAGAINOV default value
             */
#define     CAGAINOV_DEFAULT  MOV2MASK(0x0, BIT_CAGAINOV)

          /* [rw] Receiver integration window length
           */
#define   BIT_INTEGLEN  BIT(2)
            /* The length of each integration windows is reduced to 18 ns which is helpful
             * to reduce the magnitude of the integrators offset and the amount of noise
             * integrated and may improve the link margin consistently but only if the pulse
             * energy envelop is narrow enough
             */
#define     INTEGLEN_0b1  MOV2MASK(0b1, BIT_INTEGLEN)
            /* All four integration windows of the receiver are 24 ns long which maximize
             * the overlap between these windows and ensure that as much signal energy as
             * possible is accumulated in at least one of those four windows
             */
#define     INTEGLEN_0b0  MOV2MASK(0b0, BIT_INTEGLEN)
            /* Get INTEGLEN value
             */
#define     GET_INTEGLEN(reg_val)  MASK2VAL(reg_val, BIT_INTEGLEN)
            /* INTEGLEN default value
             */
#define     INTEGLEN_DEFAULT  MOV2MASK(0x0, BIT_INTEGLEN)

          /* [rw] Receiver integrators gain
           */
#define   BITS_INTEGGAIN  BITS8(1, 0)
            /* Sets the gain factor of the receiver integrators by tuning their input
             * resistors. Higher value means higher gain factor.A higher gain factor helps to
             * reduce the input signal saturation through the automatic gain control loop or
             * other forms of gain adjustments but also exacerbates the impact of the
             * integrator offsets on the integrator outputs.
             */
#define     SET_INTEGGAIN(value)    MOV2MASK(value, BITS_INTEGGAIN)
#define     GET_INTEGGAIN(reg_val)  MASK2VAL(reg_val, BITS_INTEGGAIN)
            /* INTEGGAIN default value
             */
#define     INTEGGAIN_DEFAULT  MOV2MASK(0x1, BITS_INTEGGAIN)

          /* [ro] Delay line leads or lags the symbol rate
           */
#define   BIT_LEAD_LAG  BIT(3)
            /* The delay line is lagging behind the symbol rate(longer)
             */
#define     LEAD_LAG_0b1  MOV2MASK(0b1, BIT_LEAD_LAG)
            /* The delay line is leading the symbol rate (shorter)
             */
#define     LEAD_LAG_0b0  MOV2MASK(0b0, BIT_LEAD_LAG)
            /* Get LEAD_LAG value
             */
#define     GET_LEAD_LAG(reg_val)  MASK2VAL(reg_val, BIT_LEAD_LAG)
            /* LEAD_LAG default value
             */
#define     LEAD_LAG_DEFAULT  MOV2MASK(0, BIT_LEAD_LAG)

#define REG8_BASEBAND_TUNING_DEFAULT  0x0081



/******************************************************************************/
/*                        Register DCRO_CALIB (8 bits)                        */
/******************************************************************************/
#define REG8_DCRO_CALIB 0x1E

          /* [wo] Digitally-controlled ring oscillator frequency code
           */
#define   BITS_DCRO_CODE  BITS8(4, 0)
            /* Provides the 5-bit frequency code for which the on-chip calibration block
             * will measure the corresponding DCRO frequency
             */
#define     SET_DCRO_CODE(value)  MOV2MASK(value, BITS_DCRO_CODE)
            /* DCRO_CODE default value
             */
#define     DCRO_CODE_DEFAULT  MOV2MASK(0xa, BITS_DCRO_CODE)

          /* [ro] Digitally-controlled ring oscillator frequency
           */
#define   BITS_DCRO_FREQ  BITS8(7, 0)
            /* The DCRO frequency expressed in multiples of 41 MHz
             */
#define     GET_DCRO_FREQ(reg_val)  MASK2VAL(reg_val, BITS_DCRO_FREQ)
            /* DCRO_FREQ default value
             */
#define     DCRO_FREQ_DEFAULT  MOV2MASK(0, BITS_DCRO_FREQ)

#define REG8_DCRO_CALIB_DEFAULT  0x000A



/******************************************************************************/
/*                   Register PWR_STATUS_COMMANDS (8 bits)                    */
/******************************************************************************/
#define REG8_PWR_STATUS_COMMANDS 0x1F

          /* [wo] Calibrate digitally-controlled ring oscillator
           */
#define   BIT_CAL_DCRO  BIT(7)
            /* Triggers the calibration block counting process
             */
#define     CAL_DCRO_0b1  MOV2MASK(0b1, BIT_CAL_DCRO)
            /* No effect
             */
#define     CAL_DCRO_0b0  MOV2MASK(0b0, BIT_CAL_DCRO)
            /* CAL_DCRO default value
             */
#define     CAL_DCRO_DEFAULT  MOV2MASK(0x0, BIT_CAL_DCRO)

          /* [wo] Skip next scheduled wake-up
           */
#define   BIT_SKIPWAKE  BIT(6)
            /* Make the device skip its automated wake-up process and remain asleep the next
             * time the wake-up timer running on the crystal oscillator clock signal triggers
             * the device wake-up
             */
#define     SKIPWAKE_0b1  MOV2MASK(0b1, BIT_SKIPWAKE)
            /* No effect
             */
#define     SKIPWAKE_0b0  MOV2MASK(0b0, BIT_SKIPWAKE)
            /* SKIPWAKE default value
             */
#define     SKIPWAKE_DEFAULT  MOV2MASK(0x0, BIT_SKIPWAKE)

          /* [wo] Receiver mode device operation
           */
#define   BIT_RX_MODE  BIT(5)
            /* Device is configured for frame reception
             */
#define     RX_MODE_0b1  MOV2MASK(0b1, BIT_RX_MODE)
            /* Device is configured for frame transmissions
             */
#define     RX_MODE_0b0  MOV2MASK(0b0, BIT_RX_MODE)
            /* RX_MODE default value
             */
#define     RX_MODE_DEFAULT  MOV2MASK(0x1, BIT_RX_MODE)

          /* [wo] Start transmission
           */
#define   BIT_START_TX  BIT(4)
            /* Schedules a frame transmission attempt for the next time the modem is awake,
             * idle and in transmission mode
             */
#define     START_TX_0b1  MOV2MASK(0b1, BIT_START_TX)
            /* No effect
             */
#define     START_TX_0b0  MOV2MASK(0b0, BIT_START_TX)
            /* START_TX default value
             */
#define     START_TX_DEFAULT  MOV2MASK(0x0, BIT_START_TX)

          /* [wo] Initialize wake-up timers
           */
#define   BIT_INITIMER  BIT(3)
            /* Immediately resets both wake-up timers to 0x0000
             */
#define     INITIMER_0b1  MOV2MASK(0b1, BIT_INITIMER)
            /* No effect
             */
#define     INITIMER_0b0  MOV2MASK(0b0, BIT_INITIMER)
            /* INITIMER default value
             */
#define     INITIMER_DEFAULT  MOV2MASK(0x0, BIT_INITIMER)

          /* [wo] Go to sleep
           */
#define   BIT_GO_SLEEP  BIT(2)
            /* Put the device to sleep if it is awake and idle
             */
#define     GO_SLEEP_0b1  MOV2MASK(0b1, BIT_GO_SLEEP)
            /* Wake up the device only if it is asleep and the AUTOWAKE register bit at
             * register address 0x05 is cleared
             */
#define     GO_SLEEP_0b0  MOV2MASK(0b0, BIT_GO_SLEEP)
            /* GO_SLEEP default value
             */
#define     GO_SLEEP_DEFAULT  MOV2MASK(0x1, BIT_GO_SLEEP)

          /* [wo] Flush and reset reception buffer
           */
#define   BIT_FLUSH_RX  BIT(1)
            /* Resets the state of the reception data buffer to its initial empty state
             */
#define     FLUSH_RX_0b1  MOV2MASK(0b1, BIT_FLUSH_RX)
            /* No effect
             */
#define     FLUSH_RX_0b0  MOV2MASK(0b0, BIT_FLUSH_RX)
            /* FLUSH_RX default value
             */
#define     FLUSH_RX_DEFAULT  MOV2MASK(0x0, BIT_FLUSH_RX)

          /* [wo] Flush and reset transmission buffer
           */
#define   BIT_FLUSH_TX  BIT(0)
            /* Resets the state of the transmission data buffer to its initial empty state
             *
             */
#define     FLUSH_TX_0b1  MOV2MASK(0b1, BIT_FLUSH_TX)
            /* No effect
             */
#define     FLUSH_TX_0b0  MOV2MASK(0b0, BIT_FLUSH_TX)
            /* FLUSH_TX default value
             */
#define     FLUSH_TX_DEFAULT  MOV2MASK(0x0, BIT_FLUSH_TX)

          /* [ro] Read-Only Memory enabled
           */
#define   BIT_ROM_EN  BIT(7)
            /* This is a sticky bit. '1' if ROM is powered up
             */
#define     GET_ROM_EN(reg_val)  MASK2VAL(reg_val, BIT_ROM_EN)
            /* ROM_EN default value
             */
#define     ROM_EN_DEFAULT  MOV2MASK(0, BIT_ROM_EN)

          /* [ro] Receiver enabled
           */
#define   BIT_RX_EN  BIT(6)
            /* This is a sticky bit. '1' if receiver powered up
             */
#define     GET_RX_EN(reg_val)  MASK2VAL(reg_val, BIT_RX_EN)
            /* RX_EN default value
             */
#define     RX_EN_DEFAULT  MOV2MASK(0, BIT_RX_EN)

          /* [ro] Transmitter enabled
           */
#define   BIT_TX_EN  BIT(5)
            /* This is a sticky bit. '1' if transmitter powered up
             */
#define     GET_TX_EN(reg_val)  MASK2VAL(reg_val, BIT_TX_EN)
            /* TX_EN default value
             */
#define     TX_EN_DEFAULT  MOV2MASK(1, BIT_TX_EN)

          /* [ro] Fully awake
           */
#define   BIT_AWAKE  BIT(4)
            /* This is a sticky bit. '1' if frame processor awake, regardless of activity.
             * Matches delay line circuitry state
             */
#define     GET_AWAKE(reg_val)  MASK2VAL(reg_val, BIT_AWAKE)
            /* AWAKE default value
             */
#define     AWAKE_DEFAULT  MOV2MASK(0, BIT_AWAKE)

          /* [ro]
           */
#define   BIT_MODEM_ON  BIT(3)
            /* This is a sticky bit. '1' if the modem is powered up and its reset signal is
             * released
             */
#define     GET_MODEM_ON(reg_val)  MASK2VAL(reg_val, BIT_MODEM_ON)
            /* MODEM_ON default value
             */
#define     MODEM_ON_DEFAULT  MOV2MASK(0, BIT_MODEM_ON)

          /* [ro] DC/DC voltage converter enabled
           */
#define   BIT_DCDC_EN  BIT(2)
            /* This is a sticky bit. '1' if DC/DC converter enabled
             */
#define     GET_DCDC_EN(reg_val)  MASK2VAL(reg_val, BIT_DCDC_EN)
            /* DCDC_EN default value
             */
#define     DCDC_EN_DEFAULT  MOV2MASK(1, BIT_DCDC_EN)

          /* [ro] Phase-locked loop enabled
           */
#define   BIT_PLL_EN  BIT(1)
            /* This is a sticky bit. '1' if PLL powered up
             */
#define     GET_PLL_EN(reg_val)  MASK2VAL(reg_val, BIT_PLL_EN)
            /* PLL_EN default value
             */
#define     PLL_EN_DEFAULT  MOV2MASK(0, BIT_PLL_EN)

          /* [ro] Reference buffers enabled
           */
#define   BIT_REF_EN  BIT(0)
            /* This is a sticky bit. '1' if voltage/current reference buffers powered up
             */
#define     GET_REF_EN(reg_val)  MASK2VAL(reg_val, BIT_REF_EN)
            /* REF_EN default value
             */
#define     REF_EN_DEFAULT  MOV2MASK(0, BIT_REF_EN)

#define REG8_PWR_STATUS_COMMANDS_DEFAULT  0x0024



/******************************************************************************/
/*                           Register ROM (8 bits)                            */
/******************************************************************************/
#define REG8_ROM 0x20

          /* [wo] Read-Only Memory power switch
           */
#define   BIT_ROMPWRSW  BIT(7)
            /* Connect the ROM module's supply net from the 1 volt power domain
             */
#define     ROMPWRSW_0b1  MOV2MASK(0b1, BIT_ROMPWRSW)
            /* Disconnect the ROM module's supply net from the 1 volt power domain
             */
#define     ROMPWRSW_0b0  MOV2MASK(0b0, BIT_ROMPWRSW)
            /* ROMPWRSW default value
             */
#define     ROMPWRSW_DEFAULT  MOV2MASK(0x0, BIT_ROMPWRSW)

          /* [wo] Read-Only Memory byte address
           */
#define   BITS_ROM_ADDR  BITS8(5, 0)
            /* Indicates to the ROM module which of its 128 bytes to output to read-only
             * register field ROM_BYTE
             */
#define     SET_ROM_ADDR(value)  MOV2MASK(value, BITS_ROM_ADDR)
            /* ROM_ADDR default value
             */
#define     ROM_ADDR_DEFAULT  MOV2MASK(0x0, BITS_ROM_ADDR)

          /* [ro] Read-Only Memory output byte
           */
#define   BITS_ROM_BYTE  BITS8(7, 0)
            /* Reflects the current ROM module's output from where the content of the ROM
             * can be read
             */
#define     GET_ROM_BYTE(reg_val)  MASK2VAL(reg_val, BITS_ROM_BYTE)
            /* ROM_BYTE default value
             */
#define     ROM_BYTE_DEFAULT  MOV2MASK(0, BITS_ROM_BYTE)

#define REG8_ROM_DEFAULT  0x0000



/******************************************************************************/
/*                        Register BIT_THRESH (8 bits)                        */
/******************************************************************************/
#define REG8_BIT_THRESH 0x21

          /* [ro] Bit decision threshold
           */
#define   BITS_BIT_THRESH  BITS8(3, 0)
            /* Contains the bit decision threshold that the modem chose to discriminate
             * between 1s and 0s from the last received frame through the ADC outputs
             */
#define     GET_BIT_THRESH(reg_val)  MASK2VAL(reg_val, BITS_BIT_THRESH)
            /* BIT_THRESH default value
             */
#define     BIT_THRESH_DEFAULT  MOV2MASK(0x0, BITS_BIT_THRESH)

#define REG8_BIT_THRESH_DEFAULT  0x0000



/******************************************************************************/
/*                           Register RSSI (8 bits)                           */
/******************************************************************************/
#define REG8_RSSI 0x22

          /* [ro] Received Signal Strength Indicator
           */
#define   BITS_RSSI  BITS8(5, 0)
            /* Contains the gain value the modem selected for the intermediate-frequency
             * variable gain amplifier stages to decode the last frame received
             */
#define     GET_RSSI(reg_val)  MASK2VAL(reg_val, BITS_RSSI)
            /* RSSI default value
             */
#define     RSSI_DEFAULT  MOV2MASK(0x0, BITS_RSSI)

#define REG8_RSSI_DEFAULT  0x0000



/******************************************************************************/
/*                           Register RNSI (8 bits)                           */
/******************************************************************************/
#define REG8_RNSI 0x23

          /* [ro] Received Noise Strength Indicator
           */
#define   BITS_RNSI  BITS8(5, 0)
            /* Contains the last gain value the modem selected for the variable gain
             * amplifier stages to maximize the receiver sensitivity to incoming frames during
             * the last time the receiver was idle
             */
#define     GET_RNSI(reg_val)  MASK2VAL(reg_val, BITS_RNSI)
            /* RNSI default value
             */
#define     RNSI_DEFAULT  MOV2MASK(0x0, BITS_RNSI)

#define REG8_RNSI_DEFAULT  0x0000



/******************************************************************************/
/*                 Register RX_WAITED_14_8_WAIT_SRC (8 bits)                  */
/******************************************************************************/
#define REG8_RX_WAITED_14_8_WAIT_SRC 0x24

          /* [rw] Receiver waiting time source counter
           */
#define   BIT_RXWAISRC  BIT(7)
            /* The modem's wake-up timer value is the one that gets stored in the RX_WAITED
             * register field whenever a synchronization word is detected and the one that can
             * trigger timeout events
             */
#define     RXWAISRC_0b1  MOV2MASK(0b1, BIT_RXWAISRC)
            /* The default receiver idle time counter reusing the output shift register of
             * the modem is used to keep track of time before detecting the synchronization
             * word
             */
#define     RXWAISRC_0b0  MOV2MASK(0b0, BIT_RXWAISRC)
            /* Get RXWAISRC value
             */
#define     GET_RXWAISRC(reg_val)  MASK2VAL(reg_val, BIT_RXWAISRC)
            /* RXWAISRC default value
             */
#define     RXWAISRC_DEFAULT  MOV2MASK(0x0, BIT_RXWAISRC)

          /* [ro] Receiver time waited[14:8]
           */
#define   BITS_RX_WAITED_14_8  BITS8(6, 0)
            /* Contains the amount of time spent in symbol clock periods by the modem
             * waiting in reception for information to decode before detecting the last
             * received frame's synchronization word
             */
#define     GET_RX_WAITED_14_8(reg_val)  MASK2VAL(reg_val, BITS_RX_WAITED_14_8)
            /* RX_WAITED_14_8 default value
             */
#define     RX_WAITED_14_8_DEFAULT  MOV2MASK(0, BITS_RX_WAITED_14_8)

#define REG8_RX_WAITED_14_8_WAIT_SRC_DEFAULT  0x0000



/******************************************************************************/
/*                      Register RX_WAITED_7_0 (8 bits)                       */
/******************************************************************************/
#define REG8_RX_WAITED_7_0 0x25

          /* [ro] Receiver time waited[7:0]
           */
#define   BITS_RX_WAITED_7_0  BITS8(7, 0)
            /* Contains the amount of time spent in symbol clock periods by the modem
             * waiting in reception for information to decode before detecting the last
             * received frame's synchronization word
             */
#define     GET_RX_WAITED_7_0(reg_val)  MASK2VAL(reg_val, BITS_RX_WAITED_7_0)
            /* RX_WAITED_7_0 default value
             */
#define     RX_WAITED_7_0_DEFAULT  MOV2MASK(0x0, BITS_RX_WAITED_7_0)

#define REG8_RX_WAITED_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                     Register FRAME_ADDR_15_8 (8 bits)                      */
/******************************************************************************/
#define REG8_FRAME_ADDR_15_8 0x26

          /* [ro] Frame address[15:8]
           */
#define   BITS_FRAME_ADDR_15_8  BITS8(7, 0)
            /* Contains the last address field read from a received frame
             */
#define     GET_FRAME_ADDR_15_8(reg_val)  MASK2VAL(reg_val, BITS_FRAME_ADDR_15_8)
            /* FRAME_ADDR_15_8 default value
             */
#define     FRAME_ADDR_15_8_DEFAULT  MOV2MASK(0x0, BITS_FRAME_ADDR_15_8)

#define REG8_FRAME_ADDR_15_8_DEFAULT  0x0000



/******************************************************************************/
/*                      Register FRAME_ADDR_7_0 (8 bits)                      */
/******************************************************************************/
#define REG8_FRAME_ADDR_7_0 0x27

          /* [ro] Frame address[7:0]
           */
#define   BITS_FRAME_ADDR_7_0  BITS8(7, 0)
            /* Contains the last address field read from a received frame
             */
#define     GET_FRAME_ADDR_7_0(reg_val)  MASK2VAL(reg_val, BITS_FRAME_ADDR_7_0)
            /* FRAME_ADDR_7_0 default value
             */
#define     FRAME_ADDR_7_0_DEFAULT  MOV2MASK(0x0, BITS_FRAME_ADDR_7_0)

#define REG8_FRAME_ADDR_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                       Register NOISE_FLOOR (8 bits)                        */
/******************************************************************************/
#define REG8_NOISE_FLOOR 0x28

          /* [wo] Maximum average ADC output signal level
           */
#define   BITS_MAXADCSIG  BITS8(7, 4)
            /* Holds the threshold for received signal energy integration at or below which
             * the automatic gain control loop will try to keep the average of the integration
             * window phase picking up the most received signal energy
             */
#define     SET_MAXADCSIG(value)  MOV2MASK(value, BITS_MAXADCSIG)
            /* MAXADCSIG default value
             */
#define     MAXADCSIG_DEFAULT  MOV2MASK(0x6, BITS_MAXADCSIG)

          /* [wo] Minimum average ADC output signal level
           */
#define   BITS_MINADCSIG  BITS8(3, 0)
            /* Holds the threshold for received signal energy integration above which the
             * automatic gain control loop will try to keep the average of the integration
             * window phase picking up the most received signal energy
             */
#define     SET_MINADCSIG(value)  MOV2MASK(value, BITS_MINADCSIG)
            /* MINADCSIG default value
             */
#define     MINADCSIG_DEFAULT  MOV2MASK(0x8, BITS_MINADCSIG)

          /* [ro] Preamble phase correlation metric #1
           */
#define   BITS_PHSDATA1  BITS8(7, 0)
            /* Contains a correlation metric between the preamble of the last received frame
             * and the expected preamble pattern with a specific phase offset in the form of
             * accumulated energy (Ranging purpose)
             */
#define     GET_PHSDATA1(reg_val)  MASK2VAL(reg_val, BITS_PHSDATA1)
            /* PHSDATA1 default value
             */
#define     PHSDATA1_DEFAULT  MOV2MASK(0, BITS_PHSDATA1)

#define REG8_NOISE_FLOOR_DEFAULT  0x0068



/******************************************************************************/
/*                     Register PREAMBLE_TUNING (8 bits)                      */
/******************************************************************************/
#define REG8_PREAMBLE_TUNING 0x29

          /* [wo] Delay automatic frame replies
           */
#define   BIT_DLAYRPLY  BIT(7)
            /* Enable the user to control both the receiver reply timeout delay(applicable
             * for the reception of auto-reply frames only) and the delay before transmitting
             * the reply(applicable for the transmission of auto-reply frames only)
             */
#define     DLAYRPLY_0b1  MOV2MASK(0b1, BIT_DLAYRPLY)
            /* Disable this feature.
             */
#define     DLAYRPLY_0b0  MOV2MASK(0b0, BIT_DLAYRPLY)
            /* DLAYRPLY default value
             */
#define     DLAYRPLY_DEFAULT  MOV2MASK(0x0, BIT_DLAYRPLY)

          /* [wo] Number of consecutive preamble detections
           */
#define   BITS_NUMPREDET  BITS8(6, 4)
            /* Sets the number of consecutive preamble detections that must occur for the
             * modem to decide that it is actually receiving a frame preamble and not noise or
             * some other interferer that just happened to match the preamble pattern looked
             * for by the modem at any given time
             */
#define     SET_NUMPREDET(value)  MOV2MASK(value, BITS_NUMPREDET)
            /* NUMPREDET default value
             */
#define     NUMPREDET_DEFAULT  MOV2MASK(0x5, BITS_NUMPREDET)

          /* [wo] Preamble detection threshold
           */
#define   BITS_PREATHRES  BITS8(3, 0)
            /* Sets the minimum level of correlation with a preamble pattern (set of
             * alternating highs and lows) that must be observed from the last 4 ADC samples of
             * any of the four integration windows
             */
#define     SET_PREATHRES(value)  MOV2MASK(value, BITS_PREATHRES)
            /* PREATHRES default value
             */
#define     PREATHRES_DEFAULT  MOV2MASK(0x2, BITS_PREATHRES)

          /* [ro] Preamble phase correlation metric #2
           */
#define   BITS_PHSDATA2  BITS8(7, 0)
            /* Contains a correlation metric between the preamble of the last received frame
             * and the expected preamble pattern with a specific phase offset in the form of
             * accumulated energy (Ranging purpose)
             */
#define     GET_PHSDATA2(reg_val)  MASK2VAL(reg_val, BITS_PHSDATA2)
            /* PHSDATA2 default value
             */
#define     PHSDATA2_DEFAULT  MOV2MASK(0, BITS_PHSDATA2)

#define REG8_PREAMBLE_TUNING_DEFAULT  0x0052



/******************************************************************************/
/*                      Register GAIN_LOOP_OVR (8 bits)                       */
/******************************************************************************/
#define REG8_GAIN_LOOP_OVR 0x2A

          /* [wo] Frame data source
           */
#define   BITS_DATASRC  BITS8(7, 6)
            /* Frame payload is filled with all 1s to emulate the worst case scenario for EM
             * emissions and energy consumption when using OOK pulse modulation coding
             */
#define     DATASRC_0b11  MOV2MASK(0b11, BITS_DATASRC)
            /* Frame payload is filled with a pattern of alternating 1s and 0s identical to
             * the preamble pattern
             */
#define     DATASRC_0b10  MOV2MASK(0b10, BITS_DATASRC)
            /* Frame payload is filled with the pseudo-random sequence of the integrated
             * LFSR
             */
#define     DATASRC_0b01  MOV2MASK(0b01, BITS_DATASRC)
            /* Modem use the data in the transmission buffer to fill payload of frames to
             * transmit
             */
#define     DATASRC_0b00  MOV2MASK(0b00, BITS_DATASRC)
            /* DATASRC default value
             */
#define     DATASRC_DEFAULT  MOV2MASK(0x0, BITS_DATASRC)

          /* [wo] Manual gain control
           */
#define   BITS_MANUGAIN  BITS8(5, 0)
            /* Disables the automatic gain control feedback loop and dictates a fixed gain
             * value for all the receiver stages controlled by this feedback loop
             */
#define     SET_MANUGAIN(value)  MOV2MASK(value, BITS_MANUGAIN)
            /* MANUGAIN default value
             */
#define     MANUGAIN_DEFAULT  MOV2MASK(0x3f, BITS_MANUGAIN)

          /* [ro] Preamble phase correlation metric #3
           */
#define   BITS_PHSDATA3  BITS8(7, 0)
            /* Contains a correlation metric between the preamble of the last received frame
             * and the expected preamble pattern with a specific phase offset in the form of
             * accumulated energy (Ranging purpose)
             */
#define     GET_PHSDATA3(reg_val)  MASK2VAL(reg_val, BITS_PHSDATA3)
            /* PHSDATA3 default value
             */
#define     PHSDATA3_DEFAULT  MOV2MASK(0, BITS_PHSDATA3)

#define REG8_GAIN_LOOP_OVR_DEFAULT  0x003F



/******************************************************************************/
/*                      Register MODEM_DBG_FEAT (8 bits)                      */
/******************************************************************************/
#define REG8_MODEM_DBG_FEAT 0x2B

          /* [wo] Override modem
           */
#define   BIT_OVERRIDE  BIT(7)
            /* Override modem (ASIC debug feature)
             */
#define     OVERRIDE_0b1  MOV2MASK(0b1, BIT_OVERRIDE)
            /* Normal operation
             */
#define     OVERRIDE_0b0  MOV2MASK(0b0, BIT_OVERRIDE)
            /* OVERRIDE default value
             */
#define     OVERRIDE_DEFAULT  MOV2MASK(0x0, BIT_OVERRIDE)

          /* [wo] Manual receiver phase selection / Phase tracking enable
           */
#define   BITS_MANUPHASE  BITS8(6, 5)
            /* If OVERRIDE = 1, this register field selects which one of the four
             * integration windows of the receiver to use to decode received frames and to
             * propagate to the STRM_OUT pins of the device. Otherwise, the two bits of this
             * register field are used to independently enable or disable the two main
             * components of the phase tracking algorithm
             */
#define     SET_MANUPHASE(value)  MOV2MASK(value, BITS_MANUPHASE)
            /* MANUPHASE default value
             */
#define     MANUPHASE_DEFAULT  MOV2MASK(0x0, BITS_MANUPHASE)

          /* [wo] Manual bit decision threshold
           */
#define   BIT_MANBITHR  BIT(4)
            /* The bit decision threshold is 'manually' fixed by the value of BITTHRADJ and
             * the modem will use it directly to decode every frame it receives
             */
#define     MANBITHR_0b1  MOV2MASK(0b1, BIT_MANBITHR)
            /* Disable this feature
             */
#define     MANBITHR_0b0  MOV2MASK(0b0, BIT_MANBITHR)
            /* MANBITHR default value
             */
#define     MANBITHR_DEFAULT  MOV2MASK(0x0, BIT_MANBITHR)

          /* [wo]
           */
#define   BITS_BITTHRADJ  BITS8(3, 0)
            /* Adjusts or overrides the bit decision threshold selected by the modem
             * depending on the value of register bit MANBITHR
             */
#define     SET_BITTHRADJ(value)  MOV2MASK(value, BITS_BITTHRADJ)
            /* BITTHRADJ default value
             */
#define     BITTHRADJ_DEFAULT  MOV2MASK(0x0, BITS_BITTHRADJ)

          /* [ro] Preamble phase correlation metric #4
           */
#define   BITS_PHSDATA4  BITS8(7, 0)
            /* Contains a correlation metric between the preamble of the last received frame
             * and the expected preamble pattern with a specific phase offset in the form of
             * accumulated energy (Ranging purpose)
             */
#define     GET_PHSDATA4(reg_val)  MASK2VAL(reg_val, BITS_PHSDATA4)
            /* PHSDATA4 default value
             */
#define     PHSDATA4_DEFAULT  MOV2MASK(0, BITS_PHSDATA4)

#define REG8_MODEM_DBG_FEAT_DEFAULT  0x0000



/******************************************************************************/
/*                     Register MAIN_MODEM_FEATS (8 bits)                     */
/******************************************************************************/
#define REG8_MAIN_MODEM_FEATS 0x2C

          /* [rw] Automatic transmission
           */
#define   BIT_AUTOTX  BIT(7)
            /* The write-only register bit START_TX is set internally by wake-up events
             * always at the same time the WAKEUPI status flag at register address 0x01 is set
             *
             */
#define     AUTOTX_0b1  MOV2MASK(0b1, BIT_AUTOTX)
            /* Transmissions only occur as explained in the description of the register bit
             * START_TX at register address 0x1F
             */
#define     AUTOTX_0b0  MOV2MASK(0b0, BIT_AUTOTX)
            /* Get AUTOTX value
             */
#define     GET_AUTOTX(reg_val)  MASK2VAL(reg_val, BIT_AUTOTX)
            /* AUTOTX default value
             */
#define     AUTOTX_DEFAULT  MOV2MASK(0x0, BIT_AUTOTX)

          /* [rw] Automatic frame reply enable
           */
#define   BIT_AUTORPLY  BIT(6)
            /* Enable auto-reply of received frame or enable a short listening window after
             * transmission
             */
#define     AUTORPLY_0b1  MOV2MASK(0b1, BIT_AUTORPLY)
            /* Disable the auto-reply feature
             */
#define     AUTORPLY_0b0  MOV2MASK(0b0, BIT_AUTORPLY)
            /* Get AUTORPLY value
             */
#define     GET_AUTORPLY(reg_val)  MASK2VAL(reg_val, BIT_AUTORPLY)
            /* AUTORPLY default value
             */
#define     AUTORPLY_DEFAULT  MOV2MASK(0x0, BIT_AUTORPLY)

          /* [rw] Inter-symbol interference mitigation
           */
#define   BITS_ISIMITIG  BITS8(5, 4)
            /* ISI Mitigation level 3
             */
#define     ISIMITIG_0b11  MOV2MASK(0b11, BITS_ISIMITIG)
            /* ISI Mitigation level 2
             */
#define     ISIMITIG_0b10  MOV2MASK(0b10, BITS_ISIMITIG)
            /* ISI Mitigation level 1
             */
#define     ISIMITIG_0b01  MOV2MASK(0b01, BITS_ISIMITIG)
            /* ISI Mitigation level 0
             */
#define     ISIMITIG_0b00  MOV2MASK(0b00, BITS_ISIMITIG)
            /* Get ISIMITIG value
             */
#define     GET_ISIMITIG(reg_val)  MASK2VAL(reg_val, BITS_ISIMITIG)
            /* ISIMITIG default value
             */
#define     ISIMITIG_DEFAULT  MOV2MASK(0x0, BITS_ISIMITIG)

          /* [rw] Digital modulation coding
           */
#define   BITS_MODCODING  BITS8(3, 2)
            /* 2BITPPM modulation
             */
#define     MODCODING_0b11  MOV2MASK(0b11, BITS_MODCODING)
            /* PPM modulation
             */
#define     MODCODING_0b10  MOV2MASK(0b10, BITS_MODCODING)
            /* IOOK modulation
             */
#define     MODCODING_0b01  MOV2MASK(0b01, BITS_MODCODING)
            /* OOK modulation
             */
#define     MODCODING_0b00  MOV2MASK(0b00, BITS_MODCODING)
            /* Get MODCODING value
             */
#define     GET_MODCODING(reg_val)  MASK2VAL(reg_val, BITS_MODCODING)
            /* MODCODING default value
             */
#define     MODCODING_DEFAULT  MOV2MASK(0x0, BITS_MODCODING)

          /* [rw] Forward error correction redundancy rate
           */
#define   BITS_FEC_RATE  BITS8(1, 0)
            /* FEC Level 3
             */
#define     FEC_RATE_0b11  MOV2MASK(0b11, BITS_FEC_RATE)
            /* FEC Level 2
             */
#define     FEC_RATE_0b10  MOV2MASK(0b10, BITS_FEC_RATE)
            /* FEC Level 1
             */
#define     FEC_RATE_0b01  MOV2MASK(0b01, BITS_FEC_RATE)
            /* FEC Level 0
             */
#define     FEC_RATE_0b00  MOV2MASK(0b00, BITS_FEC_RATE)
            /* Get FEC_RATE value
             */
#define     GET_FEC_RATE(reg_val)  MASK2VAL(reg_val, BITS_FEC_RATE)
            /* FEC_RATE default value
             */
#define     FEC_RATE_DEFAULT  MOV2MASK(0x0, BITS_FEC_RATE)

#define REG8_MAIN_MODEM_FEATS_DEFAULT  0x0000



/******************************************************************************/
/*                   Register COLLISION_AVOIDANCE (8 bits)                    */
/******************************************************************************/
#define REG8_COLLISION_AVOIDANCE 0x2D

          /* [rw] Receiver's idle power consumption
           */
#define   BITS_RXIDLEPWR  BITS8(7, 6)
            /* The receiver will always remain on when waiting for preamble
             */
#define     RXIDLEPWR_0b11  MOV2MASK(0b11, BITS_RXIDLEPWR)
            /* The receiver will always remain on when waiting for preamble
             */
#define     RXIDLEPWR_0b10  MOV2MASK(0b10, BITS_RXIDLEPWR)
            /* The receive r will remain on for only 16 symbol clock cycle after the
             * RXPUDELAY before turning off again
             */
#define     RXIDLEPWR_0b01  MOV2MASK(0b01, BITS_RXIDLEPWR)
            /* The receiver will remain on for only 8 symbol clock cycle after the RXPUDELAY
             * before turning off again
             */
#define     RXIDLEPWR_0b00  MOV2MASK(0b00, BITS_RXIDLEPWR)
            /* Get RXIDLEPWR value
             */
#define     GET_RXIDLEPWR(reg_val)  MASK2VAL(reg_val, BITS_RXIDLEPWR)
            /* RXIDLEPWR default value
             */
#define     RXIDLEPWR_DEFAULT  MOV2MASK(0x3, BITS_RXIDLEPWR)

          /* [rw] Collision-avoidance check threshold
           */
#define   BITS_CACTHRES  BITS8(5, 0)
            /* Dictates at which level of energy captured by the receiver is the UWB channel
             * considered obstructed by interferers which is then used to decide whether to
             * postpone the transmission of the frame the device seeks to transmit
             */
#define     SET_CACTHRES(value)    MOV2MASK(value, BITS_CACTHRES)
#define     GET_CACTHRES(reg_val)  MASK2VAL(reg_val, BITS_CACTHRES)
            /* CACTHRES default value
             */
#define     CACTHRES_DEFAULT  MOV2MASK(0x3f, BITS_CACTHRES)

#define REG8_COLLISION_AVOIDANCE_DEFAULT  0x00FF



/******************************************************************************/
/*                   Register RECEIVER_PAUSE_TIME (8 bits)                    */
/******************************************************************************/
#define REG8_RECEIVER_PAUSE_TIME 0x2E

          /* [rw] Receiver off time interval
           */
#define   BITS_RXOFFTIME  BITS8(7, 0)
            /* Defines how long is the receiver powered down between the short listening
             * periods used to detect the presence of interferences or the preamble of an
             * incoming frame as explained in the descriptions of both register fields of
             * register address 0x2D
             */
#define     SET_RXOFFTIME(value)    MOV2MASK(value, BITS_RXOFFTIME)
#define     GET_RXOFFTIME(reg_val)  MASK2VAL(reg_val, BITS_RXOFFTIME)
            /* RXOFFTIME default value
             */
#define     RXOFFTIME_DEFAULT  MOV2MASK(0x4, BITS_RXOFFTIME)

#define REG8_RECEIVER_PAUSE_TIME_DEFAULT  0x0004



/******************************************************************************/
/*                       Register PREAMBLE_LEN (8 bits)                       */
/******************************************************************************/
#define REG8_PREAMBLE_LEN 0x2F

          /* [rw] Frame preamble length
           */
#define   BITS_PREAMBLEN  BITS8(7, 0)
            /* Dictates the number of preamble bits to transmit before the synchronization
             * word
             */
#define     SET_PREAMBLEN(value)    MOV2MASK(value, BITS_PREAMBLEN)
#define     GET_PREAMBLEN(reg_val)  MASK2VAL(reg_val, BITS_PREAMBLEN)
            /* PREAMBLEN default value
             */
#define     PREAMBLEN_DEFAULT  MOV2MASK(0x27, BITS_PREAMBLEN)

#define REG8_PREAMBLE_LEN_DEFAULT  0x0027



/******************************************************************************/
/*                   Register RECEIVER_CONST_GAINS (8 bits)                   */
/******************************************************************************/
#define REG8_RECEIVER_CONST_GAINS 0x30

          /* [rw] Intermediate-frequency variable gain amplifier #3
           */
#define   BITS_IF_GAIN3  BITS8(7, 5)
            /* Defines the gain of the last variable gain amplifier before the receiver
             * integrator with a uniform granularity of 2 dB which translates into an
             * equivalent of 4 dB increments at the ADC outputs
             */
#define     SET_IF_GAIN3(value)    MOV2MASK(value, BITS_IF_GAIN3)
#define     GET_IF_GAIN3(reg_val)  MASK2VAL(reg_val, BITS_IF_GAIN3)
            /* IF_GAIN3 default value
             */
#define     IF_GAIN3_DEFAULT  MOV2MASK(0x0, BITS_IF_GAIN3)

          /* [rw] Intermediate-frequency operational amplifier gain
           */
#define   BITS_IFOA_GAIN  BITS8(4, 2)
            /* Sets the gain of the intermediate-frequency operational amplifier immediately
             * before the first self-mixer
             */
#define     SET_IFOA_GAIN(value)    MOV2MASK(value, BITS_IFOA_GAIN)
#define     GET_IFOA_GAIN(reg_val)  MASK2VAL(reg_val, BITS_IFOA_GAIN)
            /* IFOA_GAIN default value
             */
#define     IFOA_GAIN_DEFAULT  MOV2MASK(0x0, BITS_IFOA_GAIN)

          /* [rw] Radio-frequency amplifier gain
           */
#define   BITS_RF_GAIN  BITS8(1, 0)
            /* Sets the gain of the radio-frequency amplifier immediately following the
             * low-noisw amplifier. Each increment of the unsigned value of this register field
             * results in a 2 dB reduction in RF gain meaning the default value of 0b00
             * corresponds to the highest gain
             */
#define     SET_RF_GAIN(value)    MOV2MASK(value, BITS_RF_GAIN)
#define     GET_RF_GAIN(reg_val)  MASK2VAL(reg_val, BITS_RF_GAIN)
            /* RF_GAIN default value
             */
#define     RF_GAIN_DEFAULT  MOV2MASK(0x0, BITS_RF_GAIN)

#define REG8_RECEIVER_CONST_GAINS_DEFAULT  0x0000



/******************************************************************************/
/*                       Register SFD_SETTINGS (8 bits)                       */
/******************************************************************************/
#define REG8_SFD_SETTINGS 0x31

          /* [rw] Start Frame Delimiter length
           */
#define   BIT_SWLENGTH  BIT(7)
            /* SFD length is 32 bits
             */
#define     SWLENGTH_0b1  MOV2MASK(0b1, BIT_SWLENGTH)
            /* SFD length is 16 bits
             */
#define     SWLENGTH_0b0  MOV2MASK(0b0, BIT_SWLENGTH)
            /* Get SWLENGTH value
             */
#define     GET_SWLENGTH(reg_val)  MASK2VAL(reg_val, BIT_SWLENGTH)
            /* SWLENGTH default value
             */
#define     SWLENGTH_DEFAULT  MOV2MASK(0x1, BIT_SWLENGTH)

          /* [rw] Start Frame Delimiter detection bit mismatch extra cost
           */
#define   BITS_SWBITCOST  BITS8(6, 5)
            /* Provides an additional degree of rejection against false positive detections
             * of a synchronization word
             */
#define     SET_SWBITCOST(value)    MOV2MASK(value, BITS_SWBITCOST)
#define     GET_SWBITCOST(reg_val)  MASK2VAL(reg_val, BITS_SWBITCOST)
            /* SWBITCOST default value
             */
#define     SWBITCOST_DEFAULT  MOV2MASK(0x2, BITS_SWBITCOST)

          /* [rw] Start Frame Delimiter detection correlator tolerance
           */
#define   BITS_SWCORRTOL  BITS8(4, 0)
            /* Ddefines the level of tolerance in the synchronization word detection process
             * when in reception by accepting detection for a level of correlation that falls
             * within a certain margin below the expected level of energy of the
             * synchronization word correlation
             */
#define     SET_SWCORRTOL(value)    MOV2MASK(value, BITS_SWCORRTOL)
#define     GET_SWCORRTOL(reg_val)  MASK2VAL(reg_val, BITS_SWCORRTOL)
            /* SWCORRTOL default value
             */
#define     SWCORRTOL_DEFAULT  MOV2MASK(0xc, BITS_SWCORRTOL)

#define REG8_SFD_SETTINGS_DEFAULT  0x00CC



/******************************************************************************/
/*                        Register SFD_31_24 (8 bits)                         */
/******************************************************************************/
#define REG8_SFD_31_24 0x32

          /* [rw] Start Frame Delimiter[31:24]
           */
#define   BITS_SFD_31_24  BITS8(7, 0)
            /* Contains the synchronization word inserted in transmitted frames and used to
             * synchronize the receiver's modem on the frame data
             */
#define     SET_SFD_31_24(value)    MOV2MASK(value, BITS_SFD_31_24)
#define     GET_SFD_31_24(reg_val)  MASK2VAL(reg_val, BITS_SFD_31_24)
            /* SFD_31_24 default value
             */
#define     SFD_31_24_DEFAULT  MOV2MASK(0x5e, BITS_SFD_31_24)

#define REG8_SFD_31_24_DEFAULT  0x005E



/******************************************************************************/
/*                        Register SFD_23_16 (8 bits)                         */
/******************************************************************************/
#define REG8_SFD_23_16 0x33

          /* [rw] Start Frame Delimiter[23:16]
           */
#define   BITS_SFD_23_16  BITS8(7, 0)
            /* Contains the synchronization word inserted in transmitted frames and used to
             * synchronize the receiver's modem on the frame data
             */
#define     SET_SFD_23_16(value)    MOV2MASK(value, BITS_SFD_23_16)
#define     GET_SFD_23_16(reg_val)  MASK2VAL(reg_val, BITS_SFD_23_16)
            /* SFD_23_16 default value
             */
#define     SFD_23_16_DEFAULT  MOV2MASK(0xa6, BITS_SFD_23_16)

#define REG8_SFD_23_16_DEFAULT  0x00A6



/******************************************************************************/
/*                         Register SFD_15_8 (8 bits)                         */
/******************************************************************************/
#define REG8_SFD_15_8 0x34

          /* [rw] Start Frame Delimiter[15:8]
           */
#define   BITS_SFD_15_8  BITS8(7, 0)
            /* Contains the synchronization word inserted in transmitted frames and used to
             * synchronize the receiver's modem on the frame data
             */
#define     SET_SFD_15_8(value)    MOV2MASK(value, BITS_SFD_15_8)
#define     GET_SFD_15_8(reg_val)  MASK2VAL(reg_val, BITS_SFD_15_8)
            /* SFD_15_8 default value
             */
#define     SFD_15_8_DEFAULT  MOV2MASK(0xc1, BITS_SFD_15_8)

#define REG8_SFD_15_8_DEFAULT  0x00C1



/******************************************************************************/
/*                         Register SFD_7_0 (8 bits)                          */
/******************************************************************************/
#define REG8_SFD_7_0 0x35

          /* [rw] Start Frame Delimiter[7:0]
           */
#define   BITS_SFD_7_0  BITS8(7, 0)
            /* Contains the synchronization word inserted in transmitted frames and used to
             * synchronize the receiver's modem on the frame data
             */
#define     SET_SFD_7_0(value)    MOV2MASK(value, BITS_SFD_7_0)
#define     GET_SFD_7_0(reg_val)  MASK2VAL(reg_val, BITS_SFD_7_0)
            /* SFD_7_0 default value
             */
#define     SFD_7_0_DEFAULT  MOV2MASK(0x1d, BITS_SFD_7_0)

#define REG8_SFD_7_0_DEFAULT  0x001D



/******************************************************************************/
/*                         Register CRC_15_8 (8 bits)                         */
/******************************************************************************/
#define REG8_CRC_15_8 0x36

          /* [rw] Cyclic redundancy check generator's polynomial[15:8]
           */
#define   BITS_CRCPOLYNO_15_8  BITS8(7, 0)
            /* Enables the use of cyclic redundancy checks for all UWB frame exchanges and
             * sets the polynomial used
             */
#define     SET_CRCPOLYNO_15_8(value)    MOV2MASK(value, BITS_CRCPOLYNO_15_8)
#define     GET_CRCPOLYNO_15_8(reg_val)  MASK2VAL(reg_val, BITS_CRCPOLYNO_15_8)
            /* CRCPOLYNO_15_8 default value
             */
#define     CRCPOLYNO_15_8_DEFAULT  MOV2MASK(0x0, BITS_CRCPOLYNO_15_8)

#define REG8_CRC_15_8_DEFAULT  0x0000



/******************************************************************************/
/*                         Register CRC_7_0 (8 bits)                          */
/******************************************************************************/
#define REG8_CRC_7_0 0x37

          /* [rw] Cyclic redundancy check generator's polynomial[7:0]
           */
#define   BITS_CRCPOLYNO_7_0  BITS8(7, 0)
            /* Enables the use of cyclic redundancy checks for all UWB frame exchanges and
             * sets the polynomial used
             */
#define     SET_CRCPOLYNO_7_0(value)    MOV2MASK(value, BITS_CRCPOLYNO_7_0)
#define     GET_CRCPOLYNO_7_0(reg_val)  MASK2VAL(reg_val, BITS_CRCPOLYNO_7_0)
            /* CRCPOLYNO_7_0 default value
             */
#define     CRCPOLYNO_7_0_DEFAULT  MOV2MASK(0x0, BITS_CRCPOLYNO_7_0)

#define REG8_CRC_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                  Register TRANSMITTER_ADDR_15_8 (8 bits)                   */
/******************************************************************************/
#define REG8_TRANSMITTER_ADDR_15_8 0x38

          /* [rw] Remote node address[15:8]
           */
#define   BITS_REMOTADDR_15_8  BITS8(7, 0)
            /* Holds the address inserted in the address field of every frame header to
             * transmit
             */
#define     SET_REMOTADDR_15_8(value)    MOV2MASK(value, BITS_REMOTADDR_15_8)
#define     GET_REMOTADDR_15_8(reg_val)  MASK2VAL(reg_val, BITS_REMOTADDR_15_8)
            /* REMOTADDR_15_8 default value
             */
#define     REMOTADDR_15_8_DEFAULT  MOV2MASK(0x0, BITS_REMOTADDR_15_8)

#define REG8_TRANSMITTER_ADDR_15_8_DEFAULT  0x0000



/******************************************************************************/
/*                   Register TRANSMITTER_ADDR_7_0 (8 bits)                   */
/******************************************************************************/
#define REG8_TRANSMITTER_ADDR_7_0 0x39

          /* [rw] Remote node address[7:0]
           */
#define   BITS_REMOTADDR_7_0  BITS8(7, 0)
            /* Holds the address inserted in the address field of every frame header to
             * transmit
             */
#define     SET_REMOTADDR_7_0(value)    MOV2MASK(value, BITS_REMOTADDR_7_0)
#define     GET_REMOTADDR_7_0(reg_val)  MASK2VAL(reg_val, BITS_REMOTADDR_7_0)
            /* REMOTADDR_7_0 default value
             */
#define     REMOTADDR_7_0_DEFAULT  MOV2MASK(0x0, BITS_REMOTADDR_7_0)

#define REG8_TRANSMITTER_ADDR_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                    Register RECEIVER_ADDR_15_8 (8 bits)                    */
/******************************************************************************/
#define REG8_RECEIVER_ADDR_15_8 0x3A

          /* [rw] Local node address[15:8]
           */
#define   BITS_LOCALADDR_15_8  BITS8(7, 0)
            /* Holds its own device's physical address that the modem looks for in received
             * frames
             */
#define     SET_LOCALADDR_15_8(value)    MOV2MASK(value, BITS_LOCALADDR_15_8)
#define     GET_LOCALADDR_15_8(reg_val)  MASK2VAL(reg_val, BITS_LOCALADDR_15_8)
            /* LOCALADDR_15_8 default value
             */
#define     LOCALADDR_15_8_DEFAULT  MOV2MASK(0x0, BITS_LOCALADDR_15_8)

#define REG8_RECEIVER_ADDR_15_8_DEFAULT  0x0000



/******************************************************************************/
/*                    Register RECEIVER_ADDR_7_0 (8 bits)                     */
/******************************************************************************/
#define REG8_RECEIVER_ADDR_7_0 0x3B

          /* [rw] Local node address[7:0]
           */
#define   BITS_LOCALADDR_7_0  BITS8(7, 0)
            /* Holds its own device's physical address that the modem looks for in received
             * frames
             */
#define     SET_LOCALADDR_7_0(value)    MOV2MASK(value, BITS_LOCALADDR_7_0)
#define     GET_LOCALADDR_7_0(reg_val)  MASK2VAL(reg_val, BITS_LOCALADDR_7_0)
            /* LOCALADDR_7_0 default value
             */
#define     LOCALADDR_7_0_DEFAULT  MOV2MASK(0x0, BITS_LOCALADDR_7_0)

#define REG8_RECEIVER_ADDR_7_0_DEFAULT  0x0000



/******************************************************************************/
/*                       Register TX_PKT_SIZE (8 bits)                        */
/******************************************************************************/
#define REG8_TX_PKT_SIZE 0x3C

          /* [rw] Transmitted packet size
           */
#define   BITS_TXPKTSIZE  BITS8(7, 0)
            /* Defines how many bytes to extract from the transmission buffer and
             * encapsulate in the next frame to transmit as the payload of that frame
             */
#define     SET_TXPKTSIZE(value)    MOV2MASK(value, BITS_TXPKTSIZE)
#define     GET_TXPKTSIZE(reg_val)  MASK2VAL(reg_val, BITS_TXPKTSIZE)
            /* TXPKTSIZE default value
             */
#define     TXPKTSIZE_DEFAULT  MOV2MASK(0x10, BITS_TXPKTSIZE)

#define REG8_TX_PKT_SIZE_DEFAULT  0x0010



/******************************************************************************/
/*                       Register RX_PKT_SIZE (8 bits)                        */
/******************************************************************************/
#define REG8_RX_PKT_SIZE 0x3D

          /* [rw] Received packet size
           */
#define   BITS_RXPKTSIZE  BITS8(7, 0)
            /* Defines how many bytes of data to expect in the payload of frames in
             * reception
             */
#define     SET_RXPKTSIZE(value)    MOV2MASK(value, BITS_RXPKTSIZE)
#define     GET_RXPKTSIZE(reg_val)  MASK2VAL(reg_val, BITS_RXPKTSIZE)
            /* RXPKTSIZE default value
             */
#define     RXPKTSIZE_DEFAULT  MOV2MASK(0x10, BITS_RXPKTSIZE)

#define REG8_RX_PKT_SIZE_DEFAULT  0x0010



/******************************************************************************/
/*                      Register MAC_LAYER_CFG (8 bits)                       */
/******************************************************************************/
#define REG8_MAC_LAYER_CFG 0x3E

          /* [rw] Address-based frame filtering
           */
#define   BITS_ADDRFILT  BITS8(7, 6)
            /* Enable address filtering for auto-reply and received packet
             */
#define     ADDRFILT_0b11  MOV2MASK(0b11, BITS_ADDRFILT)
            /* Enable auto-reply only when receive packet match the local address and is not
             * the multicast/broadcast one
             */
#define     ADDRFILT_0b10  MOV2MASK(0b10, BITS_ADDRFILT)
            /* Enable address filtering on receive packet only
             */
#define     ADDRFILT_0b01  MOV2MASK(0b01, BITS_ADDRFILT)
            /* Disable address filtering for both receive packet and auto-reply
             */
#define     ADDRFILT_0b00  MOV2MASK(0b00, BITS_ADDRFILT)
            /* Get ADDRFILT value
             */
#define     GET_ADDRFILT(reg_val)  MASK2VAL(reg_val, BITS_ADDRFILT)
            /* ADDRFILT default value
             */
#define     ADDRFILT_DEFAULT  MOV2MASK(0x0, BITS_ADDRFILT)

          /* [rw] Frame address field length
           */
#define   BIT_ADDRLEN  BIT(5)
            /* Radio address on 16-bit
             */
#define     ADDRLEN_0b1  MOV2MASK(0b1, BIT_ADDRLEN)
            /* Radio address on 8-bit
             */
#define     ADDRLEN_0b0  MOV2MASK(0b0, BIT_ADDRLEN)
            /* Get ADDRLEN value
             */
#define     GET_ADDRLEN(reg_val)  MASK2VAL(reg_val, BIT_ADDRLEN)
            /* ADDRLEN default value
             */
#define     ADDRLEN_DEFAULT  MOV2MASK(0x0, BIT_ADDRLEN)

          /* [rw] Frame address field header enable
           */
#define   BIT_ADDRHDRE  BIT(4)
            /* Enable frame address field header
             */
#define     ADDRHDRE_0b1  MOV2MASK(0b1, BIT_ADDRHDRE)
            /* Disable frame address field header
             */
#define     ADDRHDRE_0b0  MOV2MASK(0b0, BIT_ADDRHDRE)
            /* Get ADDRHDRE value
             */
#define     GET_ADDRHDRE(reg_val)  MASK2VAL(reg_val, BIT_ADDRHDRE)
            /* ADDRHDRE default value
             */
#define     ADDRHDRE_DEFAULT  MOV2MASK(0x0, BIT_ADDRHDRE)

          /* [rw] Payload size field header enable
           */
#define   BIT_SIZEHDRE  BIT(3)
            /* Insert a payload size field before frame payload
             */
#define     SIZEHDRE_0b1  MOV2MASK(0b1, BIT_SIZEHDRE)
            /* Disable payload size field header
             */
#define     SIZEHDRE_0b0  MOV2MASK(0b0, BIT_SIZEHDRE)
            /* Get SIZEHDRE value
             */
#define     GET_SIZEHDRE(reg_val)  MASK2VAL(reg_val, BIT_SIZEHDRE)
            /* SIZEHDRE default value
             */
#define     SIZEHDRE_DEFAULT  MOV2MASK(0x0, BIT_SIZEHDRE)

          /* [rw] Transmitted frames payload size source
           */
#define   BIT_SIZESRC  BIT(2)
            /* Use number of byte in TXFIFO for the frame payload size
             */
#define     SIZESRC_0b1  MOV2MASK(0b1, BIT_SIZESRC)
            /* Use value of TXPKTSIZE register for the frame payload size
             */
#define     SIZESRC_0b0  MOV2MASK(0b0, BIT_SIZESRC)
            /* Get SIZESRC value
             */
#define     GET_SIZESRC(reg_val)  MASK2VAL(reg_val, BIT_SIZESRC)
            /* SIZESRC default value
             */
#define     SIZESRC_DEFAULT  MOV2MASK(0x0, BIT_SIZESRC)

          /* [rw] Save frame address field in reception buffer
           */
#define   BIT_SAVEADDR  BIT(1)
            /* Enable save of address field of each received frame into the reception buffer
             * with the frame payload
             */
#define     SAVEADDR_0b1  MOV2MASK(0b1, BIT_SAVEADDR)
            /* Disable save of address field
             */
#define     SAVEADDR_0b0  MOV2MASK(0b0, BIT_SAVEADDR)
            /* Get SAVEADDR value
             */
#define     GET_SAVEADDR(reg_val)  MASK2VAL(reg_val, BIT_SAVEADDR)
            /* SAVEADDR default value
             */
#define     SAVEADDR_DEFAULT  MOV2MASK(0x0, BIT_SAVEADDR)

          /* [rw] Save frame payload size field in reception buffer
           */
#define   BIT_SAVESIZE  BIT(0)
            /* Enable saving of payload size of each received frame into the reception
             * buffer with the frame payload
             */
#define     SAVESIZE_0b1  MOV2MASK(0b1, BIT_SAVESIZE)
            /* Disable saving of payload size
             */
#define     SAVESIZE_0b0  MOV2MASK(0b0, BIT_SAVESIZE)
            /* Get SAVESIZE value
             */
#define     GET_SAVESIZE(reg_val)  MASK2VAL(reg_val, BIT_SAVESIZE)
            /* SAVESIZE default value
             */
#define     SAVESIZE_DEFAULT  MOV2MASK(0x0, BIT_SAVESIZE)

#define REG8_MAC_LAYER_CFG_DEFAULT  0x0000



/******************************************************************************/
/*                       Register FIFO_BUFFERS (8 bits)                       */
/******************************************************************************/
#define REG8_FIFO_BUFFERS 0x3F

          /* [wo] Transmission data buffer
           */
#define   BITS_TXBUFFER  BITS8(7, 0)
            /* Every time this register addres is written into, the byte written through the
             * SPI is pushed into the transmission buffer
             */
#define     SET_TXBUFFER(value)  MOV2MASK(value, BITS_TXBUFFER)
            /* TXBUFFER default value
             */
#define     TXBUFFER_DEFAULT  MOV2MASK(0x0, BITS_TXBUFFER)

          /* [ro] Reception data buffer
           */
#define   BITS_RXBUFFER  BITS8(7, 0)
            /* Every time this register address is read, a byte is extracted from the
             * reception buffer and returned through the MISO pin as the new value read as long
             * as the reception buffer isn't empty
             */
#define     GET_RXBUFFER(reg_val)  MASK2VAL(reg_val, BITS_RXBUFFER)
            /* RXBUFFER default value
             */
#define     RXBUFFER_DEFAULT  MOV2MASK(0, BITS_RXBUFFER)

#define REG8_FIFO_BUFFERS_DEFAULT  0x0000



#endif /* SR1020_V8_3_H_ */

// clang-format on
