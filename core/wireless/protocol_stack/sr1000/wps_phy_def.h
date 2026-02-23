/** @file  wps_phy_def.h
 *  @brief Include every definition needed by the WPS PHY layer.
 *
 *  @note Supports little endian only.
 *
 *  @copyright Copyright (C) 2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */
#ifndef WPS_PHY_DEF_H_
#define WPS_PHY_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES *******************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "circular_queue.h"
#include "wps_config.h"
#include "xlayer.h"

/* CONSTANTS ******************************************************************/
/*! Queue size for PHY layer state machine. */
#define PHY_STATE_Q_SIZE 10
/*! Max header size */
#define MAX_HEADER_SIZE 10
/*! Queue size for overwrite registers queue. */
#define PHY_OVERWRITE_REG_Q_SIZE 10
/*! Size of the empty byte for the RX frame data */
#define EMPTY_BYTE 1

/* TYPES **********************************************************************/
/** @brief Wireless protocol stack PHY Layer input signal.
 */
typedef enum phy_input_signal {
    /*! PHY Radio IRQ signal */
    PHY_SIGNAL_RADIO_IRQ = 0,
    /*! PHY DMA transfer complete signal */
    PHY_SIGNAL_DMA_CMPLT,
    /*! PHY prepare radio signal */
    PHY_SIGNAL_PREPARE_RADIO,
    /*! PHY syncing signal */
    PHY_SIGNAL_SYNCING
} phy_input_signal_t;

/** @brief Wireless protocol stack PHY Layer output signal.
 */
typedef enum phy_output_signal {
    /*! PHY no signal */
    PHY_SIGNAL_NONE = 0,
    /*! PHY processing signal */
    PHY_SIGNAL_PROCESSING,
    /*! PHY yield signal */
    PHY_SIGNAL_YIELD,
    /*! PHY config has been sent */
    PHY_SIGNAL_CONFIG_COMPLETE,
    /*! PHY config has been sent (blocking)*/
    PHY_SIGNAL_BLOCKING_CONFIG_DONE,
    /*! PHY connect signal */
    PHY_SIGNAL_CONNECT,
    /*! PHY prepare done signal */
    PHY_SIGNAL_PREPARE_DONE,
    /*! PHY frame sent and ack signal */
    PHY_SIGNAL_FRAME_SENT_ACK,
    /*! PHY frame sent and nack signal */
    PHY_SIGNAL_FRAME_SENT_NACK,
    /*! PHY frame not sent signal */
    PHY_SIGNAL_FRAME_NOT_SENT,
    /*! PHY frame received signal */
    PHY_SIGNAL_FRAME_RECEIVED,
    /*! PHY frame missed signal */
    PHY_SIGNAL_FRAME_MISSED,
    /*! PHY error signal */
    PHY_SIGNAL_ERROR
} phy_output_signal_t;

/** @brief WPS PHY instance.
 */
typedef struct wps_phy wps_phy_t;

/** @brief Layer one state machine function pointer type.
 */
typedef void (*wps_phy_state_t)(wps_phy_t *phy);

/** @brief WPS PHY handle function pointer.
 */
typedef void (*wps_phy_handle_t)(wps_phy_t *phy);

/** @brief PHY layer configuration.
 */
typedef struct phy_cfg {
    /*! Radio instance */
    radio_t *radio;
    /*! Local address */
    uint16_t local_address;
    /*! SFD configuration */
    sfd_cfg_t sfd_cfg;
    /*! Preamble length register value. */
    uint16_t preamble_len_reg_val;
    /*! Sleep level */
    sleep_lvl_t sleep_lvl;
    /*! CRC polynomial */
    uint32_t crc_polynomial;
    /*! Radio chip rate, only 20.48MHz is supported on SR1XXX */
    chip_rate_cfg_t chip_rate;
    /*! Radio RX gain */
    uint8_t rx_gain;
} wps_phy_cfg_t;

/** @brief Configure radio SPI transfer structure.
 */
typedef struct __packed radio_cfg {
#if WPS_RADIO_COUNT == 2
    /*! Register address for timer configuration */
    uint8_t addr_timer_conf;
    /*! Data value for timer configuration */
    uint8_t data_timer_conf;
#endif
    /*! Register address for constant gain */
    uint8_t addr_const_gain;
    /*! Data value for constant gain */
    uint8_t data_const_gain;
    /*! Register address for CCA */
    uint8_t addr_cca;
    /*! Data value for CCA */
    uint8_t data_cca;
    /*! Register address for RX size */
    uint8_t addr_rx_size;
    /*! Data value for RX size */
    uint8_t data_rx_size;
    /*! Register address for RX wait source */
    uint8_t addr_rx_wait_src;
    /*! Data value for RX wait source */
    uint8_t data_rx_wait_src;
    /*! Register address for TX size */
    uint8_t addr_tx_size;
    /*! Data value for TX size */
    uint8_t data_tx_size;
    /*! Register address for RX pause time */
    uint8_t addr_rx_pause_time;
    /*! Data value for RX pause time */
    uint8_t data_rx_pause_time;
    /*! Register address for status 1 */
    uint8_t addr_status1;
    /*! Data value for status 1 */
    uint8_t data_status1;
    /*! Register address for status 2 */
    uint8_t addr_status2;
    /*! Data value for status 2 */
    uint8_t data_status2;
    /*! Register address for remote address 0 */
    uint8_t addr_remote_addr0;
    /*! Data value for remote address 0 */
    uint8_t data_remote_addr0;
    /*! Register address for remote address 1 */
    uint8_t addr_remote_addr1;
    /*! Data value for remote address 1 */
    uint8_t data_remote_addr1;
    /*! Register address for main modem */
    uint8_t addr_main_modem;
    /*! Data value for main modem */
    uint8_t data_main_modem;
    /*! Register address for IRQ mask 1 */
    uint8_t addr_irq_mask1;
    /*! Data value for IRQ mask 1 */
    uint8_t data_irq_mask1;
    /*! Register address for IRQ mask 2 */
    uint8_t addr_irq_mask2;
    /*! Data value for IRQ mask 2 */
    uint8_t data_irq_mask2;
    /*! Register address for actions */
    uint8_t addr_actions;
    /*! Data value for actions */
    uint8_t data_actions;
    /*! Register address for sleep configuration */
    uint8_t addr_sleep_conf;
    /*! Data value for sleep configuration */
    uint8_t data_sleep_conf;
    /*! Register address for timers (burst write) */
    uint8_t addr_timers_cfg;
    /*! Data value for timer period 1 */
    uint8_t data_timer_period1;
    /*! Data value for timer period 0 */
    uint8_t data_timer_period0;
    /*! Data value for RX timeout 1 */
    uint8_t data_rx_timeout1;
    /*! Data value for RX timeout 0 */
    uint8_t data_rx_timeout0;
    /*! Data value for power-up delay */
    uint8_t data_pwr_up_delay;
} radio_cfg_t;

/** @brief Set channel SPI transfer structure.
 */
typedef struct __packed set_chan {
    /*! Register address for DLL tune 0 */
    uint8_t addr_dll_tune0;
    /*! Data value for DLL tune 0 */
    uint8_t data_dll_tune0;
    /*! Register address for DLL tune 1 */
    uint8_t addr_dll_tune1;
    /*! Data value for DLL tune 1 */
    uint8_t data_dll_tune1;
    /*! Register address for RX (Receive) filters */
    uint8_t addr_rx_filters;
    /*! Data value for RX filters */
    uint8_t data_rx_filters;
    /*! Register address for channels (burst write) */
    uint8_t addr_channels;
    /*! Data values for channels */
    uint8_t data_channels[NB_PULSES + 1];
} set_chan_t;

/** @brief Fill header SPI transfer structure.
 */
typedef struct __packed fill_header {
    /*! Register address for FIFO (burst write) */
    uint8_t addr_fifo;
    /*! Header data buffer */
    uint8_t data_fifo[MAX_HEADER_SIZE];
} fill_header_t;

/** @brief Read events SPI transfer structure.
 */
typedef struct __packed read_events {
    /*! Register address for status 1*/
    uint8_t addr_status1;
    /*! Data value for status 1 */
    uint8_t data_status1;
    /*! Register address for status 2 */
    uint8_t addr_status2;
    /*! Data value for status 2 */
    uint8_t data_status2;
    /*! Register address for power status */
    uint8_t addr_pwr_status;
    /*! Data value for power status */
    uint8_t data_pwr_status;
} read_events_t;

/** @brief Read info SPI transfer structure.
 */
typedef struct __packed read_info {
    /*! Register address for RX wait time 1 */
    uint8_t addr_rx_wait_time1;
    /*! Data value for RX wait time 1 */
    uint8_t data_rx_wait_time1;
    /*! Register address for RX wait time 0 */
    uint8_t addr_rx_wait_time0;
    /*! Data value for RX wait time 0 */
    uint8_t data_rx_wait_time0;
    /*! Register address for RSSI */
    uint8_t addr_rssi;
    /*! Data value for RSSI */
    uint8_t data_rssi;
    /*! Register address for RNSI */
    uint8_t addr_rnsi;
    /*! Data value for RNSI */
    uint8_t data_rnsi;
    /*! Register address for frame size */
    uint8_t addr_frame_size;
    /*! Data value for frame size */
    uint8_t data_frame_size;
    /*! Register address for header size */
    uint8_t addr_header_size;
    /*! Data value for header size, if 'data_frame_size' == 0 then header size contains random value */
    uint8_t data_header_size;
    /*! Register address for phase info (burst read) */
    uint8_t addr_phase_info;
    /*! Phase information buffer */
    uint8_t data_phase_info[NB_PHASES];
} read_info_t;

/** @brief Handle CCA SPI transfer structure.
 */
typedef struct __packed handle_cca {
    /*! Register address for CCA */
    uint8_t addr_cca;
    /*! Data value for CCA */
    uint8_t data_cca;
    /*! Register address for actions */
    uint8_t addr_actions;
    /*! Data value for actions */
    uint8_t data_actions;
    /*! Register address for channels */
    uint8_t addr_channels;
    /*! Data values for channels */
    uint8_t data_channels[NB_PULSES + 1];
} handle_cca_t;

/** @brief Wireless protocol stack PHY Layer SPI transfer structures.
 */
typedef struct spi_transfers {
    /*! Configuration for radio, out */
    radio_cfg_t radio_cfg_out;
    /*! Channel configuration, out */
    set_chan_t set_chan_out;
    /*! Header filling, out */
    fill_header_t fill_header_out;
    /*! Event reading, out */
    read_events_t read_events_out;
    /*! Event reading, in */
    read_events_t read_events_in;
    /*! Information reading, out */
    read_info_t read_info_out;
    /*! Information reading, in */
    read_info_t read_info_in;
    /*! CCA handling, out */
    handle_cca_t handle_cca_out;
    /*! SPI dummy buffer */
    uint8_t spi_dummy_buffer[MAX_FRAMESIZE];
    /*! Remote address 16 bits access */
    uint8_t *remote_addr[2];
    /*! Timer period 16 bits access  */
    uint8_t *timer_period[2];
    /*! IRQ polarity mask */
    uint8_t irq_polarity_mask;
    /*! DLL tune mask */
    uint8_t dll_tune_mask;
    /*! Previous TX pulse size */
    uint8_t tx_pulse_size;
} spi_xfer_t;

/** @brief PHY layer configuration.
 */
typedef struct reg {
    /*! Register address */
    uint8_t addr;
    /*! Register value */
    uint8_t val;
} reg_t;

/** @brief WPS PHY instance.
 */
struct wps_phy {
    /*! Wireless protocol stack phy Layer input signal*/
    phy_input_signal_t input_signal;

    /*! Wireless protocol stack phy Layer output signal main*/
    phy_output_signal_t signal_main;
    /*! Wireless protocol stack phy Layer output signal auto*/
    phy_output_signal_t signal_auto;

    /*! Already initialized radio instance. */
    radio_t *radio;

    /*! Node local address */
    uint16_t local_address;
    /*! radio sleep level */
    sleep_lvl_t sleep_lvl;
    /*! Main cross layer*/
    xlayer_t *xlayer_main;
    /*! Auto cross layer*/
    xlayer_t *xlayer_auto;
    /*! Configuration */
    xlayer_cfg_internal_t *config;

    /* Internal Variables */
    /*! Current state machine state*/
    wps_phy_state_t *current_state;
    /*! Current state machine state*/
    wps_phy_state_t end_state;
    /*! Next state machine state queue*/
    circular_queue_t next_states;
    /*! Next state machine state pool*/
    wps_phy_state_t *next_state_pool[PHY_STATE_Q_SIZE];
    /*! Ovewrite registers queue */
    circular_queue_t overwrite_regs_queue;
    /*! Ovewrite registers pool */
    reg_t overwrite_regs_pool[PHY_OVERWRITE_REG_Q_SIZE];
    /*! State index*/
    uint8_t state_step;

    /*! Radio actions register fields settings */
    uint16_t radio_actions;
    /*! Header size */
    uint8_t header_size;

    /*! Syncing period in PLL cycles */
    uint16_t syncing_period_pll_cycles;

    /*! Wait for end of transmission of ack frame */
    bool wait_for_ack_tx;

    /*! Contains info about a write register access */
    xlayer_write_request_info_t write_request_info;
    /*! Contains info about a read register access */
    xlayer_read_request_info_t read_request_info;
    /*! Current state machine state*/
    wps_phy_handle_t phy_handle;
    /*! SPI transfer structures */
    spi_xfer_t spi_xfer;

    /*! MAC pointer */
    void *mac;
    /*! PHY callback */
    void (*wps_phy_callback)(void *mac, wps_phy_t *wps_phy);
};

#if WPS_RADIO_COUNT > 1

/** @brief WPS Dual radio function pointer configuration structure.
 */
typedef struct wps_multi_cfg {
    /*! Radio timer frequency in Hz. */
    uint32_t timer_frequency_hz;
    /*! Leading radio selection average sample count */
    uint16_t avg_sample_count;
    /*! Leading radio selection mode */
    multi_radio_mode_t mode;
    /*! Radio TX wakeup mode. */
    multi_radio_tx_wakeup_mode_t tx_wakeup_mode;
    /*! Leading radio selection RSSI threshold */
    uint8_t rssi_threshold;
} wps_multi_cfg_t;

#endif

#ifdef __cplusplus
}
#endif

#endif /* WPS_PHY_DEF_H_ */
