/** @file sr1000_def.h
 *  @brief SR1000 API definitions
 *
 *  @copyright Copyright (C) 2020 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef API_SR1000_API_DEF_H_
#define API_SR1000_API_DEF_H_

/* INCLUDES *******************************************************************/
#include <stdint.h>
#include "sr_access.h"
#include "sr_reg.h"

/** @brief Legacy table containing the 16 originals SFD.
 */
static const uint32_t sfd_table_legacy[] = {
    0x08ecad3e, 0x09ae74e5, 0x0a2fb635, 0x0ade3365, 0x0b1ae937, 0x0cbad627, 0x0ce2a76d, 0x0e6ae45b,
    0xe129ab17, 0xe126eac6, 0xe1225779, 0xe620a5db, 0xe92e8c4e, 0xe5a0af32, 0x0daf91ac, 0x0ca2fb72,
};

/** @brief Table containing the SFD with the best orthogonal properties and PDR performance.
 */
static const uint32_t sfd_table[] = {
    0xFCC8D605, 0xFD01993A, 0xFD23E281, 0xFD427129, 0xFE2D841A, 0xFE0328D5, 0xFE18D116, 0xFD9E0115, 0xFF062B60,
    0xFE301B51, 0xFD689388, 0xFD2D3222, 0xFD265542, 0xFF8B9021, 0xFD54A641, 0xFF286710, 0xFD6148C6, 0xFE4401F6,
    0xFDA009E9, 0xFF601C25, 0xFFC14432, 0xFF16601A, 0xFFA42C82, 0xFEA44649, 0xFFCC202C, 0xFE4D06A1, 0xFE64E850,
    0xFE4B7240, 0xE1225779, 0xFFA08346, 0x0DAF91AC, 0x0CE2A76D, 0xFE705682, 0x09AE74E5, 0xFFC4C181, 0xFFE61210,
    0xF95038F1, 0xFCB86426, 0xFC079709, 0xE616A695, 0xFB0941F1, 0xFA03672A, 0xFC8758A2, 0xFC5A2A25, 0xF8C49BE0,
    0xF8937431, 0xE5B640F1, 0xC9123DCD, 0xFA473C03, 0xF92C2C59, 0xFA0C4FC2, 0xFC3A234A, 0xF9464A55, 0xF900FE26,
    0xFA55131A, 0xF8F0299A, 0xFC762530, 0xC99C3656, 0xD4E27D81, 0xF8872696, 0xFC129672, 0xF9D662A0, 0xFA5285C5,
    0xFC05F065, 0xE0563E9A, 0xD613B15C, 0xD48E0FB1, 0xD742B790, 0xC989CB72, 0xE535B849, 0xD926D2AA, 0xD4C6CA6A,
    0xC502FD72, 0xC6963F41, 0xF5710336, 0xD631E1AA, 0xF48C91D9, 0x49B9DB88, 0xD6194CDA, 0x06C7DF48, 0xD9281DE6,
    0x797B3209, 0xD328FB82, 0xC639C971, 0xF6AC3930, 0x3636536A, 0x3311BBC3, 0xC81B39F2, 0xD4889F56, 0x1A52CBF1,
    0xE053CB6C, 0xD0477B25, 0x93C06BE9, 0xC65A3999, 0xC84D7AC9, 0x162CAF69, 0xC35957B0, 0xC1ED1B1A, 0x06383D7E,
    0xE589B2F0, 0xE45AA3B2, 0xCC5D4936, 0xF60A96CC, 0x6309FA3A, 0xF4B21596, 0xF5C6B08A, 0xC04ADEE5, 0x305EDF90,
    0xC301DBD5, 0x5E266CB1, 0xF5432D4A, 0xE159DC19, 0xE1E6D780, 0x245F372A, 0xF63B0D22, 0xF53A30AC, 0x960BE395,
    0x31BCD45A, 0xE13DC26A, 0xE117663C, 0x607753F0, 0xF3B02D15, 0xF325AE0C, 0xF22690F5, 0xF4724399, 0xF0CE6E09,
    0xF371D340, 0x1602FAEE};

/** @brief IRQ event IRQPOLAR field enum.
 *
 *  This enumeration defines the possible values for the IRQ polarity field,
 *  indicating whether the interrupt pin is active in the LOW or HIGH state.
 */
typedef enum irq_polarity {
    /*! Interrupt pin active in LOW state */
    IRQ_ACTIVE_LOW = IRQPOLAR_0b0,
    /*! Interrupt pin active in HIGH state */
    IRQ_ACTIVE_HIGH = IRQPOLAR_0b1,
} irq_polarity_t;

/******************************************************************************/
/*                        Sleep configuration, 0x04                           */
/******************************************************************************/
/** @brief Radio's sleep level.
 *
 *  This enumeration defines the different sleep levels at which the radio can go when asleep.
 */
typedef enum sleep_lvl {
    /*! Radio sleep level IDLE */
    SLEEP_IDLE = SLPDEPTH_0b00,
    /*! Radio sleep level SHALLOW */
    SLEEP_SHALLOW = SLPDEPTH_0b01,
    /*! Radio sleep level DEEP */
    SLEEP_DEEP = SLPDEPTH_0b11,
} sleep_lvl_t;

/******************************************************************************/
/*                      Disables and clock control, 0x0E                      */
/******************************************************************************/

/** @brief Peripherals controls STDSPI field enum.
 *
 *  This enumeration defines the possible values for the standard SPI operations.
 */
typedef enum std_spi {
    /*! Standard SPI operations */
    SPI_FAST = STDSPI_0b0,
    /*! Standard SPI operations */
    SPI_STANDARD = STDSPI_0b1,
} std_spi_t;

/** @brief Peripherals controls PLLDIS field enum.
 *
 *  This enumeration defines whether to disable or enable the internal PLL clock source.
 */
typedef enum pll_dis {
    /*! Disable internal PLL clock source */
    PLL_DISABLE = PLL_DIS_0b1,
    /*! Enable internal PLL clock source */
    PLL_ENABLE = PLL_DIS_0b0,
} pll_dis_t;

/** @brief Peripherals controls SYMBCSRC field enum.
 *
 *  This enumeration defines the source for the symbol rate clock, whether internal or external.
 */
typedef enum symbol_rate_clk_source {
    /*! Enable internal symbol rate clock source */
    SYMBSRC_INTERNAL = SYMBCSRC_0b0,
    /*! Enable external symbol rate clock source */
    SYMBSRC_EXTERNAL = SYMBCSRC_0b1,
} symbol_rate_clk_source_t;

/** @brief Peripherals controls XTALCSRC field enum.
 *
 *  This enumeration defines the source for the crystal oscillator clock, whether internal or
 * external.
 */
typedef enum xtal_osc_clk_source {
    /*! Enable internal XTAL clock source */
    XTALSRC_INTERNAL = XTALCSRC_0b0,
    /*! Enable external XTAL clock source */
    XTALSRC_EXTERNAL = XTALCSRC_0b1,
} xtal_osc_clk_source_t;

/******************************************************************************/
/*                      Transmitter parameters, 0x1C                          */
/******************************************************************************/

/** @brief Transmitter parameters RNDPHASE field enum.
 *
 *  This enumeration defines whether to enable or disable randomization phase.
 */
typedef enum rnd_phase {
    /*! Randomization phase disabled */
    RND_PHASE_DISABLE = RNDPHASE_0b0,
    /*! Randomization phase enabled */
    RND_PHASE_ENABLE = RNDPHASE_0b1,
} rnd_phase_t;

/** @brief Radio's TX power level enumeration in dBFs.
 *
 *  This enumeration defines various TX power levels in dBFs and includes
 *  settings for different spectrum presets and ranging scenarios.
 */
typedef enum tx_power {
    /*! TX power 0.0 dBFs */
    TX_PWR_0_0_DB = TX_POWER_0b00,
    /*! TX power 0.6 dBFs */
    TX_PWR_0_6_DB = TX_POWER_0b01,
    /*! TX power 1.2 dBFs */
    TX_PWR_1_2_DB = TX_POWER_0b10,
    /*! TX power 1.8 dBFs */
    TX_PWR_1_8_DB = TX_POWER_0b11,

    /* Config Spectrum Preset */
    /*! TX power -9.9 dBFs */
    TX_PWR_MINUS_9_9_DBFS = 0,
    /*! TX power -9.0 dBFs */
    TX_PWR_MINUS_9_0_DBFS,
    /*! TX power -8.1 dBFs */
    TX_PWR_MINUS_8_1_DBFS,
    /*! TX power -7.2 dBFs */
    TX_PWR_MINUS_7_2_DBFS,
    /*! TX power -6.3 dBFs */
    TX_PWR_MINUS_6_3_DBFS,
    /*! TX power -5.4 dBFs */
    TX_PWR_MINUS_5_4_DBFS,
    /*! TX power -4.5 dBFs */
    TX_PWR_MINUS_4_5_DBFS,
    /*! TX power -3.6 dBFs */
    TX_PWR_MINUS_3_6_DBFS,
    /*! TX power -2.7 dBFs */
    TX_PWR_MINUS_2_7_DBFS,
    /*! TX power -1.8 dBFs */
    TX_PWR_MINUS_1_8_DBFS,
    /*! TX power -0.9 dBFs */
    TX_PWR_MINUS_0_9_DBFS,
    /*! TX power -0.0 dBFs */
    TX_PWR_MINUS_0_0_DBFS,
    /*! TX power -9.9 dBFs for ranging */
    TX_PWR_MINUS_9_9_DBFS_RANGING,
    /*! TX power -9.0 dBFs for ranging */
    TX_PWR_MINUS_9_0_DBFS_RANGING,
    /*! TX power -8.1 dBFs for ranging */
    TX_PWR_MINUS_8_1_DBFS_RANGING,
    /*! TX power -7.2 dBFs for ranging */
    TX_PWR_MINUS_7_2_DBFS_RANGING,
    /*! TX power -6.3 dBFs for ranging */
    TX_PWR_MINUS_6_3_DBFS_RANGING,
    /*! TX power -5.4 dBFs for ranging */
    TX_PWR_MINUS_5_4_DBFS_RANGING,
    /*! TX power -4.5 dBFs for ranging */
    TX_PWR_MINUS_4_5_DBFS_RANGING,
    /*! TX power -3.6 dBFs for ranging */
    TX_PWR_MINUS_3_6_DBFS_RANGING,
    /*! TX power -2.7 dBFs for ranging */
    TX_PWR_MINUS_2_7_DBFS_RANGING,
    /*! TX power -1.8 dBFs for ranging */
    TX_PWR_MINUS_1_8_DBFS_RANGING,
    /*! TX power -0.9 dBFs for ranging */
    TX_PWR_MINUS_0_9_DBFS_RANGING,
    /*! TX power -0.0 dBFs for ranging */
    TX_PWR_MINUS_0_0_DBFS_RANGING,
    /*! Recommended short-range power setting */
    TX_PWR_LOW_OUTPUT_POWER_RANGING,
    /*! Recommended long-range power setting */
    TX_PWR_HIGH_OUTPUT_POWER_RANGING,
} tx_power_t;

/******************************************************************************/
/*                          Modem Main Features , 0x2C                        */
/******************************************************************************/
/** @brief Radio's modulation type enumeration.
 *
 *  This enumeration defines the possible modulation types used by the radio.
 */
typedef enum modulation {
    /*! Frame modulation OOK (On-off keying) */
    MODULATION_OOK = MODCODING_0b00,
    /*! Frame modulation OOK (On-off keying) */
    MODULATION_IOOK = MODCODING_0b01,
    /*! Frame modulation PPM (Pulse-position modulation) */
    MODULATION_PPM = MODCODING_0b10,
    /*! Frame modulation 2BITPPM (2-bit Pulse-position modulation) */
    MODULATION_2BITPPM = MODCODING_0b11,
} modulation_t;

/** @brief Radio's chip repetition type enumeration.
 */
typedef enum chip_repetition {
    /*! CHIP repetition 1X */
    CHIP_REPET_1 = 0,
} chip_repetition_t;

/** @brief Radio's Forward error correction enumeration.
 *
 *  This enumeration defines the possible forward error correction levels used by the radio.
 */
typedef enum fec_level {
    /*! Forward error correction ratio 1.00 */
    FEC_LVL_0 = FEC_RATE_0b00,
    /*! Forward error correction ratio 1.33 */
    FEC_LVL_1 = FEC_RATE_0b01,
    /*! Forward error correction ratio 1.66 */
    FEC_LVL_2 = FEC_RATE_0b10,
    /*! Forward error correction ratio 2.00 */
    FEC_LVL_3 = FEC_RATE_0b11,
} fec_level_t;

#define FEC_TYPE_TO_RAW(fec_level) GET_FEC_RATE(fec_level)

/** @brief Inter-symbol interference mitigation enum.
 *
 *  This enumeration defines the possible levels of inter-symbol interference mitigation.
 */
typedef enum isi_mitig {
    /*! Inter-symbol interference mitigation level 0 */
    ISI_MITIG_0 = ISIMITIG_0b00,
    /*! Inter-symbol interference mitigation level 1 */
    ISI_MITIG_1 = ISIMITIG_0b01,
    /*! Inter-symbol interference mitigation level 2 */
    ISI_MITIG_2 = ISIMITIG_0b10,
    /*! Inter-symbol interference mitigation level 3 */
    ISI_MITIG_3 = ISIMITIG_0b11,
} isi_mitig_t;

#define ISI_TYPE_TO_RAW(isi)               GET_ISIMITIG(isi)

#define CHIP_REPET_TO_RAW(chip_repetition) 1
/******************************************************************************/
/*                 Start Frame Delimiter settings , 0x31                      */
/******************************************************************************/
/** @brief Radio's SFD length enumeration.
 *
 *  This enumeration defines the possible synchronization word lengths used by the radio.
 */
typedef enum sfd_length {
    /*! SFD length on 16-bit */
    SFD_LENGTH_16 = SWLENGTH_0b0,
    /*! SFD length on 32-bit */
    SFD_LENGTH_32 = SWLENGTH_0b1,
} sfd_length_t;

/** @brief Transceiver chip rate enumeration.
 *
 *  This enumeration defines the possible chip rates for the transceiver.
 */
typedef enum chip_rate_cfg {
    /*! 20.48 MHz is the only possible option for SR1000 */
    CHIP_RATE_20_48_MHZ = 0,
    /*! Unused */
    CHIP_RATE_27_30_MHZ = 1,
    /*! Unused */
    CHIP_RATE_40_96_MHZ = 2,
} chip_rate_cfg_t;

#define DEFAULT_PACKET_CONFIGURATION (ADDRFILT_0b11 | ADDRLEN_0b1 | SIZEHDRE_0b1 | ADDRHDRE_0b1 | SAVESIZE_0b1)
/******************************************************************************/
/*                                 PLL                                        */
/******************************************************************************/
#define PLL_RATIO               625
#define PLL_FREQ_HZ(chip_rate)  ((chip_rate) == (CHIP_RATE_20_48_MHZ) ? (20480000) : (20480000))
#define PLL_FREQ_KHZ(chip_rate) ((chip_rate) == (CHIP_RATE_20_48_MHZ) ? (20480) : (20480))
#define PHASE_OFFSET_BYTE_COUNT 1

/******************************************************************************/
/*                             Frame outcome                                  */
/******************************************************************************/
/** @brief Frame outcome enumeration.
 *
 *  This enumeration defines the possible outcomes for a frame, such as received, lost, or rejected.
 */
typedef enum frame_outcome {
    /*! Frame received */
    FRAME_RECEIVED,
    /*! Frame lost */
    FRAME_LOST,
    /*! Frame rejected */
    FRAME_REJECTED,
    /*! Frame sent and acknowledged */
    FRAME_SENT_ACK,
    /*! Frame sent and ack is lost */
    FRAME_SENT_ACK_LOST,
    /*! Frame sent and ack is rejected */
    FRAME_SENT_ACK_REJECTED,
    /*! No frame sent or received */
    FRAME_WAIT
} frame_outcome_t;

/******************************************************************************/
/*                                  CCA                                       */
/******************************************************************************/
#define CCA_DISABLE           0xFF
#define CCA_DEFAULT_MARGIN    12
#define CCA_MAX_RETRY_TIME_US 50

/******************************************************************************/
/*                                RF CHANNEL                                  */
/******************************************************************************/

#define NB_CHANNEL            10
#define NB_PULSES             12
#define NB_PHASES             4
#define TX_PATTERN_BYTE_COUNT 12
#define MAX_PULSE_WIDTH       7
#define MAX_INTEGGAIN         3

/** @brief Radio's RF channel ID enumeration.
 */
typedef enum rf_channel_id {
    /*! RF Channel 0 */
    CHANNEL_0 = 0,
    /*! RF Channel 1 */
    CHANNEL_1,
    /*! RF Channel 2 */
    CHANNEL_2,
    /*! RF Channel 3 */
    CHANNEL_3,
    /*! RF Channel 4 */
    CHANNEL_4,
    /*! RF Channel 5 */
    CHANNEL_5,
    /*! RF Channel 6 */
    CHANNEL_6,
    /*! RF Channel 7 */
    CHANNEL_7,
    /*! RF Channel 8 */
    CHANNEL_8,
    /*! RF Channel 9 */
    CHANNEL_9,
    /*! Reference to all RF channel */
    CHANNEL_ALL
} rf_channel_id_t;

/** @brief Radio internal or external clock source.
 */
typedef struct clock_source {
    /*! Disable internal PLL clock source */
    pll_dis_t pll_dis;
    /*! Enable external PLL clock source */
    symbol_rate_clk_source_t pll_clk_source;
    /*! Enable external XTAL clock source */
    xtal_osc_clk_source_t xtal_clk_source;
} clock_source_t;

/** @brief Radio instance.
 */
typedef struct radio {
    /*! Radio Number */
    uint8_t radio_id;
    /*! Interrupt polarity */
    irq_polarity_t irq_polarity;
    /*! Register 0x0D value */
    uint8_t reg_resistune_value;
    /*! Standard SPI operations */
    std_spi_t std_spi;
    /*! Radio version */
    uint8_t phy_version;
    /*! Radio PLL and XTAL clock source (Internal or external) */
    clock_source_t clock_source;
    /*! Chip rate */
    chip_rate_cfg_t chip_rate;
} radio_t;

/** @brief Receiver timeout and power-up duration instance.
 */
typedef struct rx_timeout {
    /*! Receiver timeout, in us */
    uint32_t rx_period_us;
    /*! Receiver power-up delay, in ns */
    uint16_t rx_power_up_delay_ns;
} rx_timeout_t;

/** @brief Start Frame Delimiter configuration.
 */
typedef struct sfd_cfg {
    /*! Start Frame Delimiter, 16 or 32 bits.*/
    uint32_t sfd;
    /*! Start Frame Delimiter detection bit mismatch's extra cost, 3 bits range value */
    uint8_t sfd_bit_cost;
    /*! Start Frame Delimiter detection tolerance, 5 bits range value */
    uint8_t sfd_tolerance;
    /*! Start Frame Delimiter length, either SFD_LENGTH_16 or SFD_LENGTH_32 */
    sfd_length_t sfd_length;
} sfd_cfg_t;

/** @brief Frame configuration structure.
 *
 *  @note Define the modulation, FEC and preamble len of the frame.
 */
typedef struct {
    /*! RF modulation */
    modulation_t modulation;
    /*! Chip repetition */
    chip_repetition_t chip_repet;
    /*! Forward Error Correction level */
    fec_level_t fec;
} frame_cfg_t;

/** @brief Collision-avoidance check radio-frequency gain override.
 */
typedef enum cca_gain_overide {
    /*! 8-bits access */
    CCAGAINOV_DISABLE = CAGAINOV_0b0,
    CCAGAINOV_ENABLE = CAGAINOV_0b1
} cca_gain_overide_t;

/** @brief Clear-to-send IDLERXPWR field enum.
 */
typedef enum rx_idle_pwr {
    /*! The receiver will remain on for only 8 symbol clock cycle after the RXPUDELAY before
     * turning off again
     */
    RX_IDLE_PWR_MIN = RXIDLEPWR_0b00,
    /*! The receive r will remain on for only 16 symbol clock cycle after the RXPUDELAY before
     * turning off again
     */
    RX_IDLE_PWR_MED = RXIDLEPWR_0b01,
    /*! The receiver will always remain on when waiting for preamble */
    RX_IDLE_PWR_HIGH = RXIDLEPWR_0b11
} rx_idle_pwr_t;

/******************************************************************************/
/*                                  MISC                                      */
/******************************************************************************/
#define MAX_FRAMESIZE     128
#define BROADCAST_ADDRESS 0xFF
/*! CCA ON time is fixed in 1020 */
#define CCA_ON_TIME_PLL_CYCLES            17
#define CCA_ON_TIME_PLL_TO_REG(value_pll) ((value_pll / 8) - 1)

/* Set register macros */
#define SET_PREAMBLE_LENGTH(value)    ((value / 2) - 8)
#define SET_CCA_PAUSE_TIME(value)     ((value / 4) - 1)
#define MAX_CCA_PAUSE_TIME_PLL_CYCLES ((GET_RXOFFTIME(UINT8_MAX) + 1) * 4)
#define SET_PWRUP_DELAY(value)        (value / 4)
#define SET_RX_TIMEOUT_LSB(value)     (((EXTRACT_BYTE(((value - 1) / 8), 0) & 0x0F) << 4) | (3 & 0x0F))
#define SET_RX_TIMEOUT_MSB(value) \
    ((EXTRACT_BYTE(((value - 1) / 8), 1) << 4) | (EXTRACT_BYTE(((value - 1) / 8), 0) >> 4))

/*! Symbol Clock factor for fixed point operation */
#define CLOCK_FACTOR 1000
/*! Radio crystal clock frequency */
#define CRYSTAL_CLOCK_PERIOD 32768
/*! Symbol clock frequency */
#define SYMBOL_CLOCK_PERIOD 20480
/*! Radio power up time in seconds */
#define POWER_UP_TIME 1000
/*! Milliseconds to microseconds conversion factor */
#define MS_TO_US 1000
/*! Use any of the PULSEFREQ macro since they are all the same */
#define SET_PULSE_FREQ(value) SET_PULS12FREQ(value)
/*! Use any of the PULSEWID macro since they are all the same */
#define SET_PULSE_WIDTH(value)     SET_PULSE12WID(value)
#define CHIP_RATE_FACTOR_20_48_MHZ 20480000
#define RX_MODE                    RX_MODE_0b1
#define TX_MODE                    RX_MODE_0b0
#define TRIGGER_CALIBRATION        BIT_CAL_DCRO
#define CONNECT_ROM_PWR            ROMPWRSW_0b1
#endif /* API_SR1000_API_DEF_H_ */
