/** @file  wps_phy_common.c
 *  @brief Wireless protocol stack PHY control.
 *
 *  @copyright Copyright (C) 2021 SPARK Microsystems International Inc. All rights reserved.
 *  @license   This source code is proprietary and subject to the SPARK Microsystems
 *             Software EULA found in this package in file EULA.txt.
 *  @author    SPARK FW Team.
 */

/* INCLUDES *******************************************************************/
#include "swc_hal_facade.h"
#include "wps_config.h"
#include "wps_phy.h"
#include "xlayer_circular_data.h"

/* CONSTANTS ******************************************************************/
#define HDR_SIZE_SIZE           1
#define DEFAULT_RX_IDLE_PWR     RX_IDLE_PWR_HIGH
#define DISABLE_CCA_THRSH_VALUE BITS_CACTHRES
#define FAST_SYNC_TIMER_VALUE   32000
#define MAX_SLEEP_TIME_VALUE    0xFFFF
#define MAX_RX_TIMEOUT_VALUE    0x0FFF

/* PRIVATE FUNCTION PROTOTYPES ************************************************/
static void prepare_phy(wps_phy_t *phy);
static void prepare_radio(wps_phy_t *phy);
static void prepare_radio_tx(wps_phy_t *phy);
static void prepare_radio_rx(wps_phy_t *phy);
static void set_config(wps_phy_t *phy);
static void set_channel_config(wps_phy_t *phy);
static void enable_radio_irq(wps_phy_t *phy);
static void check_radio_irq(wps_phy_t *phy);
static void set_header(wps_phy_t *phy);
static void set_payload(wps_phy_t *phy);
static void set_header_and_payload(wps_phy_t *phy);
static void read_events(wps_phy_t *phy);
static void read_events_syncing(wps_phy_t *phy);
static void process_event_tx(wps_phy_t *phy);
static void process_event_rx(wps_phy_t *phy);
static void handle_good_frame(wps_phy_t *phy);
static void handle_good_auto_reply(wps_phy_t *phy);
static void get_frame_header(wps_phy_t *phy);
static void get_auto_reply_header(wps_phy_t *phy);
static void get_payload(wps_phy_t *phy);
static void handle_cca_fail(wps_phy_t *phy);
static void close_spi(wps_phy_t *phy);
static void end(wps_phy_t *phy);
static void none(wps_phy_t *phy);
static void prepare_syncing(wps_phy_t *phy);
#if WPS_RADIO_COUNT == 1
static void transfer_register(wps_phy_t *phy);
static void overwrite_registers(wps_phy_t *phy);
static void overwrite_queue_get_next(circular_queue_t *queue, void **it);
static void overwrite_queue_add_transfer(circular_queue_t *queue, void *it, uint8_t starting_reg, uint16_t data);
#endif
static bool main_is_tx(wps_phy_t *phy);
static bool auto_is_tx(wps_phy_t *phy);
static bool tx_complete(read_events_t *read_events);
static bool tx_complete_auto_reply(read_events_t *read_events);
static bool rx_good(read_events_t *read_events);
static bool rx_rejected(read_events_t *read_events);
static bool rx_lost(read_events_t *read_events);
static void set_events_for_tx_with_ack(wps_phy_t *phy);
static void set_events_for_tx_without_ack(wps_phy_t *phy);
static void set_events_for_rx_with_ack(wps_phy_t *phy);
static void set_events_for_rx_without_ack(wps_phy_t *phy);
static void set_events_for_wakeup_only(wps_phy_t *phy);
static void enqueue_states(wps_phy_t *phy, wps_phy_state_t *state);
static void init_transfer_structures(wps_phy_t *phy);
static void set_reg16(uint16_t value, uint8_t **reg);

/* TYPES **********************************************************************/
static wps_phy_state_t prepare_phy_states[] = {prepare_phy, end};
static wps_phy_state_t set_config_states[] = {set_config, close_spi, set_channel_config, end};
static wps_phy_state_t set_header_states[] = {close_spi, set_header, end};
static wps_phy_state_t set_payload_states[] = {set_payload, end};
static wps_phy_state_t set_header_with_payload_states[] = {close_spi, set_header_and_payload, end};
static wps_phy_state_t wait_radio_states_tx[] = {close_spi, enable_radio_irq, read_events,
                                                 close_spi, process_event_tx, end};
static wps_phy_state_t wait_radio_states_rx[] = {close_spi, enable_radio_irq, read_events,
                                                 close_spi, process_event_rx, end};
static wps_phy_state_t get_event_states[] = {read_events, close_spi, process_event_tx, end};
static wps_phy_state_t get_frame_header_states[] = {close_spi, get_frame_header, end};
static wps_phy_state_t get_auto_reply_header_states[] = {close_spi, get_auto_reply_header, end};
static wps_phy_state_t get_payload_states[] = {get_payload, end};
static wps_phy_state_t new_frame_states[] = {close_spi, end};
static wps_phy_state_t syncing_states[] = {
    prepare_syncing, close_spi, enable_radio_irq, read_events_syncing, close_spi, process_event_rx, end};
static wps_phy_state_t wait_to_send_auto_reply[] = {check_radio_irq, end};
#if WPS_RADIO_COUNT == 1
static wps_phy_state_t transfer_register_states[] = {transfer_register, end};
static wps_phy_state_t overwrite_register_states[] = {overwrite_registers, end};
#endif
static wps_phy_state_t end_states[] = {none};

/* PUBLIC FUNCTIONS ***********************************************************/
void phy_init(wps_phy_t *wps_phy, wps_phy_cfg_t *cfg)
{
    wps_phy->wait_for_ack_tx = true;
    wps_phy->state_step = 0;
    wps_phy->radio = cfg->radio;
    wps_phy->local_address = cfg->local_address;
    wps_phy->sleep_lvl = cfg->sleep_lvl;
    wps_phy->current_state = prepare_phy_states;
    wps_phy->end_state = end;
    circular_queue_init(&wps_phy->next_states, wps_phy->next_state_pool, PHY_STATE_Q_SIZE, sizeof(wps_phy_state_t **));
    circular_queue_init(&wps_phy->overwrite_regs_queue, wps_phy->overwrite_regs_pool, PHY_OVERWRITE_REG_Q_SIZE,
                        sizeof(reg_t));
    init_transfer_structures(wps_phy);

    /* Disable IRQ during INIT */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG, wps_phy->spi_xfer.irq_polarity_mask);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS, 0);

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_SFD_SETTINGS,
                        cfg->sfd_cfg.sfd_length | SET_SWBITCOST(cfg->sfd_cfg.sfd_bit_cost) |
                            SET_SWCORRTOL(cfg->sfd_cfg.sfd_tolerance));
    sr_access_write_reg32(wps_phy->radio->radio_id, REG8_SFD_31_24, cfg->sfd_cfg.sfd);

    /* Configure CRC */
    sr_access_write_reg16(wps_phy->radio->radio_id, REG8_CRC_15_8, cfg->crc_polynomial);

    /* Preamble */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PREAMBLE_LEN, cfg->preamble_len_reg_val);

    /* Set TX/RX len */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_PKT_SIZE, MAX_FRAMESIZE);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TX_PKT_SIZE, MAX_FRAMESIZE);

    /* Config local address */
    sr_access_write_reg16(wps_phy->radio->radio_id, REG8_RECEIVER_ADDR_15_8, cfg->local_address);

    /* Set sleep level */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_SLEEP_CONFIG,
                        cfg->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1);

    /* Flush RX/TX FIFO */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, GO_SLEEP_0b1 | FLUSH_RX_0b1 | FLUSH_TX_0b1);

    /* Enable IRQ on NEW_PACKET_IT */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG,
                        wps_phy->spi_xfer.irq_polarity_mask | NEWPKTE_0b1 | RXTIMEOE_0b1 | TXENDE_0b1);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS, 0);

    /* Set RX waited source to use with address filtering */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_WAITED_14_8_WAIT_SRC, RXWAISRC_0b1);

    if ((cfg->sleep_lvl != SLEEP_IDLE) && (wps_phy->radio->phy_version == PHY_VERSION_8_3)) {
        sr_access_write_reg(wps_phy->radio->radio_id, REG8_BASEBAND_TUNING, INTEGLEN_0b1);
    }

    /* Enable phase tracking */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_MODEM_DBG_FEAT, BITS_MANUPHASE);

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_MAC_LAYER_CFG, DEFAULT_PACKET_CONFIGURATION);

    /* Clear Status */
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG);
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS);

    uint8_t empty_pattern[NB_PULSES + 2] = {0};

    empty_pattern[0] = REG_WRITE_BURST | REG8_TX_PULSE_PATTERN_12;
    sr_access_spi_transfer_blocking(wps_phy->radio->radio_id, empty_pattern, wps_phy->spi_xfer.spi_dummy_buffer,
                                    NB_PULSES + 2);
}

void phy_connect(wps_phy_t *wps_phy)
{
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_CALIB_RES_IMP_TUNE, wps_phy->radio->reg_resistune_value);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD1, 0xFF);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD0_PWR_UP_DELAY, 0xF3);

    /* Clear Status */
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG);
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS);

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS,
                        FLUSH_RX_0b1 | FLUSH_TX_0b1 | INITIMER_0b1 | GO_SLEEP_0b1);

    sr_access_enable_radio_irq(wps_phy->radio->radio_id);
    sr_access_enable_dma_irq(wps_phy->radio->radio_id);

    wps_phy->state_step = 0;
    wps_phy->current_state = prepare_phy_states;
    circular_queue_init(&wps_phy->next_states, wps_phy->next_state_pool, PHY_STATE_Q_SIZE, sizeof(wps_phy_state_t **));
    wps_phy->signal_main = PHY_SIGNAL_CONNECT;
}

void phy_connect_single(wps_phy_t *wps_phy)
{
    uint8_t pwr_status = 0;

    /* Wait for radio to wakeup */
    do {
        /* Disable sleep to wakeup radio */
        sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, 0);
        pwr_status = sr_access_read_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS);
    } while (!GET_AWAKE(pwr_status));

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TIMER_CONFIG, AUTOWAKE_0b1 | WAKEONCE_0b1);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, INITIMER_0b1 | GO_SLEEP_0b1);

    phy_connect(wps_phy);
    sr_access_radio_context_switch(wps_phy->radio->radio_id);
}

void phy_connect_multi(wps_phy_t *wps_phy)
{
    uint8_t pwr_status = 0;

    /* Wait for radio to wakeup */
    do {
        /* Disable sleep to wakeup radio */
        sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, 0);
        pwr_status = sr_access_read_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS);
    } while (!GET_AWAKE(pwr_status));

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TIMER_CONFIG, WAKEONCE_0b1);
}

void phy_wakeup_multi(wps_phy_t *wps_phy)
{
    wps_phy->radio_actions |= INITIMER_0b1;
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, wps_phy->radio_actions);
}

void phy_abort_radio_events(wps_phy_t *wps_phy)
{
    while (sr_access_is_spi_busy(wps_phy->radio->radio_id)) {
        /* wait for any SPI transfer to complete */
    }

    sr_access_close(wps_phy->radio->radio_id);

    /* Disable peripherals interrupts */
    sr_access_disable_dma_irq(wps_phy->radio->radio_id);
    sr_access_disable_radio_irq(wps_phy->radio->radio_id);

    /* Disable radio interrupts */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG, 0);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS, 0);

    /* Clear radio interrupts */
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG);
    (void)sr_access_read_reg(wps_phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS);
}

void phy_disconnect(wps_phy_t *wps_phy)
{
    uint8_t pwr_status = 0;

    /* Reset timer configuration and disable AUTOWAKE to allow radio to wake up */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TIMER_CONFIG, 0);

    /* Wait for radio to wakeup */
    do {
        /* Disable sleep to wakeup radio */
        sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, 0);
        pwr_status = sr_access_read_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS);
    } while (!GET_AWAKE(pwr_status));

    /* Set sleep level to deep sleep when disconnecting */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_SLEEP_CONFIG,
                        SLEEP_DEEP | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1);

    /* Reset CCA & go to sleep */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_COLLISION_AVOIDANCE,
                        DEFAULT_RX_IDLE_PWR | DISABLE_CCA_THRSH_VALUE);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, FLUSH_TX_0b1 | FLUSH_RX_0b1 | GO_SLEEP_0b1);

    uint8_t empty_pattern[NB_PULSES + 2] = {0};

    empty_pattern[0] = REG_WRITE_BURST | REG8_TX_PULSE_PATTERN_12;
    sr_access_spi_transfer_blocking(wps_phy->radio->radio_id, empty_pattern, wps_phy->spi_xfer.spi_dummy_buffer,
                                    NB_PULSES + 2);

    /* Set timer to max value */
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, INITIMER_0b1 | GO_SLEEP_0b1);

    uint8_t rx_timeout_lsb = SET_RX_TIMEOUT_LSB(MAX_RX_TIMEOUT_VALUE);
    uint8_t rx_timeout_msb = SET_RX_TIMEOUT_MSB(MAX_RX_TIMEOUT_VALUE);

    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD1, rx_timeout_msb);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD0_PWR_UP_DELAY, rx_timeout_lsb);
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TIMER_COUNTER_15_8, 0xFF);
    sr_access_write_reg16(wps_phy->radio->radio_id, REG8_TIMER_COUNTER_15_8, MAX_SLEEP_TIME_VALUE);

    /* Wait until we are in deep sleep */
    do {
        pwr_status = sr_access_read_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS);
    } while (pwr_status != 0);
}

void phy_start_tx_now(wps_phy_t *wps_phy)
{
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_TIMER_CONFIG, WAKEONCE_0b1);
    wps_phy->radio_actions = INITIMER_0b1 | START_TX_0b1;
    sr_access_write_reg(wps_phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, wps_phy->radio_actions);
}

phy_output_signal_t phy_get_main_signal(wps_phy_t *wps_phy)
{
    return wps_phy->signal_main;
}

phy_output_signal_t phy_get_auto_signal(wps_phy_t *wps_phy)
{
    return wps_phy->signal_auto;
}

void phy_set_main_xlayer(wps_phy_t *wps_phy, xlayer_t *xlayer, xlayer_cfg_internal_t *xlayer_cfg)
{
    wps_phy->config = xlayer_cfg;
    wps_phy->xlayer_main = xlayer;
}

void phy_set_auto_xlayer(wps_phy_t *wps_phy, xlayer_t *xlayer)
{
    wps_phy->xlayer_auto = xlayer;
}

void phy_write_register(wps_phy_t *wps_phy, uint8_t starting_reg, uint16_t data, reg_write_cfg_t cfg)
{
#if WPS_RADIO_COUNT == 1
    circular_queue_t *queue = &wps_phy->overwrite_regs_queue;
    void *dequeue_ptr = circular_queue_front_raw(queue);

    if (cfg == WRITE_ONCE) {
        wps_phy->write_request_info.target_register = starting_reg;
        wps_phy->write_request_info.data = data;
        wps_phy->write_request_info.pending_request = true;
        enqueue_states(wps_phy, transfer_register_states);
    } else if (cfg == WRITE_PERIODIC) {
        overwrite_queue_add_transfer(queue, dequeue_ptr, starting_reg, data);
    }
#else
    (void)wps_phy;
    (void)starting_reg;
    (void)data;
    (void)cfg;
#endif
}

void phy_clear_write_register(wps_phy_t *wps_phy)
{
    circular_queue_init(&wps_phy->overwrite_regs_queue, wps_phy->overwrite_regs_pool, PHY_OVERWRITE_REG_Q_SIZE,
                        sizeof(reg_t));
}

void phy_read_register(wps_phy_t *wps_phy, uint8_t target_register, uint16_t *rx_buffer, volatile bool *xfer_cmplt)
{
#if WPS_RADIO_COUNT == 1
    wps_phy->read_request_info.rx_buffer = rx_buffer;
    wps_phy->read_request_info.xfer_cmplt = xfer_cmplt;
    wps_phy->read_request_info.target_register = target_register;
    wps_phy->read_request_info.pending_request = true;
    enqueue_states(wps_phy, transfer_register_states);
#else
    (void)wps_phy;
    (void)target_register;
    (void)rx_buffer;
    (void)xfer_cmplt;
#endif
}

void phy_enqueue_prepare(wps_phy_t *wps_phy)
{
    wps_phy->next_states.enqueue_it = wps_phy->next_states.buffer_begin;
    wps_phy->next_states.dequeue_it = wps_phy->next_states.buffer_begin;
    wps_phy->state_step = 0;
    wps_phy->current_state = prepare_phy_states;
}

void phy_enqueue_none(wps_phy_t *wps_phy)
{
    wps_phy->next_states.enqueue_it = wps_phy->next_states.buffer_begin;
    wps_phy->next_states.dequeue_it = wps_phy->next_states.buffer_begin;
    wps_phy->state_step = 0;
    wps_phy->current_state = end_states;
}

/* PRIVATE FUNCTION ***********************************************************/
#if WPS_RADIO_COUNT == 1
/** @brief Write to target register.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void transfer_register(wps_phy_t *phy)
{
    uint8_t tx_buffer[2] = {0};
    uint8_t rx_buffer[2] = {0};

    if (phy->write_request_info.pending_request) {

        /* Write register request */
        tx_buffer[0] = phy->write_request_info.target_register | REG_WRITE;
        tx_buffer[1] = phy->write_request_info.data;
        while (sr_access_is_spi_busy(phy->radio->radio_id)) {};
        sr_access_close(phy->radio->radio_id);
        sr_access_spi_transfer_blocking(phy->radio->radio_id, tx_buffer, rx_buffer, 2);
        phy->write_request_info.pending_request = false;

    } else if (phy->read_request_info.pending_request) {

        /* Read register request */
        tx_buffer[0] = phy->read_request_info.target_register;
        while (sr_access_is_spi_busy(phy->radio->radio_id)) {};
        sr_access_close(phy->radio->radio_id);
        sr_access_spi_transfer_blocking(phy->radio->radio_id, tx_buffer, rx_buffer, 2);
        *phy->read_request_info.rx_buffer = rx_buffer[1];

        /* Thread safety */
        do {
            *phy->read_request_info.xfer_cmplt = true;
        } while (!(*phy->read_request_info.xfer_cmplt));
        /* Read register request */
        phy->read_request_info.pending_request = false;
    }
}

/** @brief Overwrite registers.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void overwrite_registers(wps_phy_t *phy)
{
    circular_queue_t *queue = &phy->overwrite_regs_queue;
    void *dequeue_ptr = circular_queue_front_raw(queue);

    sr_access_close(phy->radio->radio_id);
    for (uint8_t i = 0; i < circular_queue_size(queue); i++) {
        sr_access_spi_transfer_blocking(phy->radio->radio_id, (uint8_t *)dequeue_ptr, phy->spi_xfer.spi_dummy_buffer,
                                        2);
        overwrite_queue_get_next(queue, &dequeue_ptr);
    }
}

/** @brief Get the next element after provided it and increment the it.
 *
 *  @note Allows to go through the queue, without dequeuing elements.
 *
 *  @param[in] queue  Cross layer queue instance.
 *  @param[in] it     Element to increment.
 */
static void overwrite_queue_get_next(circular_queue_t *queue, void **it)
{
    *it = (void *)((char *)*it + queue->item_size);

    if (*it >= queue->buffer_end) {
        *it = queue->buffer_begin;
    }
}

/** @brief Add transfer to overwrite queue.
 *
 *  @note Enqueue new element if register transfer is not there,
 *        replace value if register is there.
 *
 *  @param[in] queue  Cross layer queue instance.
 *  @param[in] it     Element to increment.
 */
void overwrite_queue_add_transfer(circular_queue_t *queue, void *it, uint8_t starting_reg, uint16_t data)
{
    reg_t *reg = (reg_t *)it;

    for (uint8_t i = 0; i < circular_queue_size(queue); i++) {
        if ((reg->addr & ~REG_WRITE) == starting_reg) {
            reg->val = data;
            return;
        }
        overwrite_queue_get_next(queue, &it);
    }

    reg = (reg_t *)circular_queue_get_free_slot_raw(queue);

    reg->addr = REG_WRITE | starting_reg;
    reg->val = data;

    circular_queue_enqueue(queue);
}
#endif

/** @brief Enqueue a new state to the state machine.
 *
 *   @param[in] wps_phy  PHY instance struct.
 *   @param[in] state    New state to enqueue.
 */
static void enqueue_states(wps_phy_t *wps_phy, wps_phy_state_t *state)
{
    wps_phy_state_t **enqueue_states = NULL;

    enqueue_states = (wps_phy_state_t **)circular_queue_get_free_slot_raw(&wps_phy->next_states);
    *enqueue_states = state;
    circular_queue_enqueue_raw(&wps_phy->next_states);
}

/** @brief Setup the state machine to send the frame payload to the radio.
 *
 *  @param[in] wps_phy        PHY instance struct.
 *  @param[in] payload_size   Frame payload size.
 *  @param[in] user_payload   Denotes if payload is provided from user space or from xlayer queue
 * buffer
 */
static void enqueue_tx_prepare_frame_states(wps_phy_t *wps_phy, uint8_t header_size, uint8_t payload_size,
                                            bool user_payload)
{
    /*
     * When the payload comes from user space memory, separate states are used for setting
     * the header and payload. Othersize, both the header and payload are transferred in a single
     * SPI operation.
     */
    if (user_payload) {
        if (header_size + payload_size != 0) {
            enqueue_states(wps_phy, set_header_states);
        }

        if (payload_size != 0) {
            enqueue_states(wps_phy, set_payload_states);
        }
    } else {
        if (header_size + payload_size != 0) {
            enqueue_states(wps_phy, set_header_with_payload_states);
        }
    }
}

/** @brief Setup the state machine to receive payload from the radio.
 *
 *  @param[in] wps_phy  PHY instance struct.
 */
static void enqueue_rx_prepare_frame_states(wps_phy_t *wps_phy)
{
    enqueue_states(wps_phy, wait_radio_states_rx);
}

/** @brief Setup the PHY state machine.
 *
 *  @param[in] wps_phy       PHY instance struct.
 *  @param[in] payload_size  Frame payload size.
 */
static void prepare_phy(wps_phy_t *phy)
{
    if (phy->input_signal == PHY_SIGNAL_SYNCING) {
        enqueue_states(phy, syncing_states);
    } else {
        enqueue_states(phy, set_config_states);
#if WPS_RADIO_COUNT == 1
        if (circular_queue_size(&phy->overwrite_regs_queue) != 0) {
            enqueue_states(phy, overwrite_register_states);
        }
#endif
        prepare_radio(phy);
    }
}

/** @brief Sub function to prepare a transmit frame.
 *
 *  @param[in] signal_data   Data required to process the state. The type shall be wps_phy_t.
 *  @param[in] radio_actions   Radio actions instance.
 */
static void prepare_radio_tx(wps_phy_t *phy)
{
    uint8_t header_size = 0;
    uint8_t rx_packet_size = 0;
    uint8_t tx_payload_size = 0;

    tx_payload_size = phy->xlayer_main->frame.payload_end_it - phy->xlayer_main->frame.payload_begin_it;
    header_size = phy->xlayer_main->frame.header_end_it - phy->xlayer_main->frame.header_begin_it;

#if WPS_RADIO_COUNT == 2
    if (wps_phy_multi_get_tx_wakeup_mode() == MULTI_TX_WAKEUP_MODE_AUTO) {
        /* Leading radio will autowake. */
        phy->spi_xfer.radio_cfg_out.data_timer_conf = AUTOWAKE_0b1 | WAKEONCE_0b1;
    } else {
        /* following radio will be manually awakened. */
        phy->spi_xfer.radio_cfg_out.data_timer_conf = WAKEONCE_0b1;
    }
#endif

    /* Autoreply mode */
    if (phy->xlayer_auto != NULL) {
        phy->spi_xfer.radio_cfg_out.data_main_modem = AUTORPLY_0b1;
        rx_packet_size = phy->xlayer_auto->frame.payload_memory_size + phy->xlayer_auto->frame.header_memory_size +
                         HDR_SIZE_SIZE;
        set_events_for_tx_with_ack(phy);
        /* Ack mode */
    } else if (phy->config->expect_ack) {
        phy->spi_xfer.radio_cfg_out.data_main_modem = AUTORPLY_0b1;
        rx_packet_size = 1;
        set_events_for_tx_with_ack(phy);
        /* Nack mode */
    } else {
        phy->spi_xfer.radio_cfg_out.data_main_modem = 0;
        rx_packet_size = 1;
        set_events_for_tx_without_ack(phy);
    }

    phy->spi_xfer.radio_cfg_out.data_const_gain = phy->config->rx_constgain;

    if ((header_size == 0) && !phy->config->certification_header_en) {
        /* If header_size == 0 and certification header is enabled, send an empty payload to
         * simulate an ACK.
         */
        phy->spi_xfer.radio_cfg_out.data_cca = DEFAULT_RX_IDLE_PWR | DISABLE_CCA_THRSH_VALUE;
        set_events_for_wakeup_only(phy);
        rx_packet_size = 1;
    } else {
        phy->spi_xfer.radio_cfg_out.data_cca = RX_IDLE_PWR_HIGH | SET_CACTHRES(phy->config->cca_threshold);
        phy->radio_actions |= START_TX_0b1;
    }

    if ((phy->config->cca_max_try_count <= 1) && (phy->config->cca_fail_action == CCA_FAIL_ACTION_ABORT_TX)) {
        phy->spi_xfer.radio_cfg_out.data_sleep_conf = phy->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1 |
                                                      SLPNOISY_0b1;
    } else {
        phy->spi_xfer.radio_cfg_out.data_sleep_conf = phy->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1;
    }

    phy->spi_xfer.radio_cfg_out.data_rx_size = rx_packet_size;
    phy->spi_xfer.radio_cfg_out.data_rx_wait_src = 0;
    if ((header_size + tx_payload_size) == 0) {
        phy->spi_xfer.radio_cfg_out.data_tx_size = 0;
    } else {
        phy->spi_xfer.radio_cfg_out.data_tx_size = header_size + tx_payload_size + HDR_SIZE_SIZE;
    }
    phy->spi_xfer.radio_cfg_out.data_rx_pause_time = SET_CCA_PAUSE_TIME(phy->config->cca_retry_time);
    phy->radio_actions |= TX_MODE;
    set_reg16(phy->xlayer_main->frame.destination_address, phy->spi_xfer.remote_addr);

    enqueue_tx_prepare_frame_states(phy, header_size, tx_payload_size, phy->xlayer_main->frame.user_payload);
    enqueue_states(phy, wait_radio_states_tx);
}

/** @brief Sub function to prepare a receive frame.
 *
 *  @param[in] signal_data   Data required to process the state. The type shall be wps_phy_t.
 *  @param[in] radio_actions   Radio actions instance.
 */
static void prepare_radio_rx(wps_phy_t *phy)
{
    uint8_t payload_size = 0;
    uint8_t header_size = 0;
    uint8_t tx_packet_size = 0;

#if WPS_RADIO_COUNT == 2
    phy->spi_xfer.radio_cfg_out.data_timer_conf = WAKEONCE_0b1;
#endif

    /* Autoreply mode */
    if (phy->xlayer_auto != NULL) {
        phy->spi_xfer.radio_cfg_out.data_main_modem = AUTORPLY_0b1;
        payload_size = phy->xlayer_auto->frame.payload_end_it - phy->xlayer_auto->frame.payload_begin_it;
        header_size = phy->xlayer_auto->frame.header_end_it - phy->xlayer_auto->frame.header_begin_it;
        tx_packet_size = (header_size + payload_size == 0) ? 0 : (header_size + payload_size + HDR_SIZE_SIZE);
        set_events_for_rx_with_ack(phy);
        set_reg16(phy->xlayer_auto->frame.destination_address, phy->spi_xfer.remote_addr);
        enqueue_tx_prepare_frame_states(phy, header_size, payload_size, phy->xlayer_auto->frame.user_payload);
        enqueue_states(phy, wait_radio_states_rx);
        /* Ack mode */
    } else if (phy->config->expect_ack) {
        phy->spi_xfer.radio_cfg_out.data_main_modem = AUTORPLY_0b1;
        tx_packet_size = 0;
        set_events_for_rx_with_ack(phy);
        set_reg16(phy->xlayer_main->frame.source_address, phy->spi_xfer.remote_addr);
        enqueue_rx_prepare_frame_states(phy);
        /* Nack mode */
    } else {
        phy->spi_xfer.radio_cfg_out.data_main_modem = 0;
        tx_packet_size = 0;
        set_events_for_rx_without_ack(phy);
        set_reg16(phy->xlayer_main->frame.source_address, phy->spi_xfer.remote_addr);
        enqueue_rx_prepare_frame_states(phy);
    }

    phy->spi_xfer.radio_cfg_out.data_tx_size = tx_packet_size;
    phy->spi_xfer.radio_cfg_out.data_rx_size = phy->xlayer_main->frame.payload_memory_size +
                                               phy->xlayer_main->frame.header_memory_size + HDR_SIZE_SIZE;
    phy->spi_xfer.radio_cfg_out.data_const_gain = phy->config->rx_constgain;
    phy->spi_xfer.radio_cfg_out.data_rx_wait_src = RXWAISRC_0b1;
    /* Disable CCA */
    phy->spi_xfer.radio_cfg_out.data_cca = DEFAULT_RX_IDLE_PWR | DISABLE_CCA_THRSH_VALUE;
    phy->spi_xfer.radio_cfg_out.data_rx_pause_time = 0;
    phy->spi_xfer.radio_cfg_out.data_sleep_conf = phy->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1;
    phy->radio_actions |= RX_MODE;
}

/** @brief State : prepare the radio to send or receive a frame.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void prepare_radio(wps_phy_t *phy)
{
    phy->signal_auto = PHY_SIGNAL_NONE;
    phy->radio_actions = 0;

    if (main_is_tx(phy)) {
        prepare_radio_tx(phy);
    } else {
        prepare_radio_rx(phy);
    }

    /* Setup auto-reply in radio */
    phy->spi_xfer.radio_cfg_out.data_main_modem |= phy->config->modulation | phy->config->fec | ISI_MITIG_0;

#if WPS_RADIO_COUNT == 1
    phy->spi_xfer.radio_cfg_out.data_actions = phy->radio_actions | GO_SLEEP_0b1 | FLUSH_RX_0b1 | FLUSH_TX_0b1;
#else
    if (main_is_tx(phy) && (wps_phy_multi_get_tx_wakeup_mode() == MULTI_TX_WAKEUP_MODE_AUTO)) {
        phy->spi_xfer.radio_cfg_out.data_actions = phy->radio_actions | GO_SLEEP_0b1 | FLUSH_RX_0b1 | FLUSH_TX_0b1;
    } else {
        phy->spi_xfer.radio_cfg_out.data_actions = GO_SLEEP_0b1 | FLUSH_RX_0b1 | FLUSH_TX_0b1;
    }
#endif

    phy->spi_xfer.radio_cfg_out.data_pwr_up_delay = SET_PWRUP_DELAY(phy->config->power_up_delay);
    set_reg16(phy->config->sleep_time, phy->spi_xfer.timer_period);
    phy->spi_xfer.radio_cfg_out.data_rx_timeout1 = SET_RX_TIMEOUT_MSB(phy->config->rx_timeout);
    phy->spi_xfer.radio_cfg_out.data_rx_timeout0 = SET_RX_TIMEOUT_LSB(phy->config->rx_timeout);
}

/** @brief State : Send the Radio config through the SPI.
 *
 *  @param[in] signal_data Data required to process the state. The type shall be wps_phy_t.
 */
static void set_config(wps_phy_t *phy)
{
    phy->signal_main = PHY_SIGNAL_PREPARE_DONE;
    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.radio_cfg_out,
                                        (uint8_t *)&phy->spi_xfer.spi_dummy_buffer, sizeof(radio_cfg_t));
}

static void set_channel_config(wps_phy_t *phy)
{
    uint8_t write_pulse_size = phy->spi_xfer.tx_pulse_size < phy->config->channel->pulse_size ?
                                   phy->spi_xfer.tx_pulse_size :
                                   phy->config->channel->pulse_size;

    phy->signal_main = PHY_SIGNAL_YIELD;

    phy->spi_xfer.set_chan_out.data_dll_tune1 = phy->spi_xfer.dll_tune_mask | phy->config->channel->integgain;
    phy->spi_xfer.set_chan_out.data_rx_filters = phy->config->channel->channel.rx_filter;
    phy->spi_xfer.set_chan_out.addr_channels = REG_WRITE_BURST | (REG8_TX_PULSE_PATTERN_12 + write_pulse_size);
    memcpy(&phy->spi_xfer.set_chan_out.data_channels, (phy->config->channel->channel.tx_pattern + write_pulse_size),
           NB_PULSES + 1 - write_pulse_size);
    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.set_chan_out,
                                        (uint8_t *)&phy->spi_xfer.spi_dummy_buffer,
                                        sizeof(set_chan_t) - write_pulse_size);
    phy->spi_xfer.tx_pulse_size = phy->config->channel->pulse_size;
}

/** @brief State : Fill the header of the frame in the radio tx fifo.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void set_header(wps_phy_t *phy)
{
    xlayer_frame_t *frame = main_is_tx(phy) ? &phy->xlayer_main->frame : &phy->xlayer_auto->frame;
    uint8_t hdr_len = frame->header_end_it - frame->header_begin_it;

    sr_access_disable_radio_irq(phy->radio->radio_id);

    phy->signal_main = PHY_SIGNAL_YIELD;

    phy->spi_xfer.fill_header_out.data_fifo[0] = hdr_len;
    memcpy(&phy->spi_xfer.fill_header_out.data_fifo[1], frame->header_begin_it, hdr_len);
    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.fill_header_out,
                                        (uint8_t *)&phy->spi_xfer.spi_dummy_buffer,
                                        hdr_len + HDR_SIZE_SIZE + EMPTY_BYTE);
}

/** @brief State : Fill the payload of the frame in the radio tx fifo.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void set_payload(wps_phy_t *phy)
{
    xlayer_frame_t *frame = main_is_tx(phy) ? &phy->xlayer_main->frame : &phy->xlayer_auto->frame;

    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    phy->signal_main = PHY_SIGNAL_YIELD;

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, frame->payload_begin_it, phy->spi_xfer.spi_dummy_buffer,
                                        frame->payload_end_it - frame->payload_begin_it);
}

/** @brief State: Fills the radio TX FIFO with the frame header and payload
 * as a single SPI operation. This process uses a continuous memory area from the xlayer
 * frame data for SPI communication.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void set_header_and_payload(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    xlayer_frame_t *frame = main_is_tx(phy) ? &phy->xlayer_main->frame : &phy->xlayer_auto->frame;

    sr_access_disable_radio_irq(phy->radio->radio_id);

    phy->signal_main = PHY_SIGNAL_YIELD;

    uint8_t *spi_tx_fifo = frame->header_begin_it - XLAYER_QUEUE_SPI_COMM_ADDITIONAL_BYTES;
    uint8_t header_size = frame->header_end_it - frame->header_begin_it;
    uint8_t payload_size = frame->payload_end_it - frame->payload_begin_it;

    /* Set register TXFIFO as burst mode to send whole frame */
    spi_tx_fifo[XLAYER_QUEUE_SPI_COMM_REG_POSITION_OFFSET] = REG_WRITE_BURST | REG8_FIFO_BUFFERS;
    /* Set header size */
    spi_tx_fifo[XLAYER_QUEUE_SPI_COMM_HEADER_SIZE_POSITION_OFFSET] = header_size;

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, spi_tx_fifo, phy->spi_xfer.spi_dummy_buffer,
                                        header_size + payload_size + XLAYER_QUEUE_SPI_COMM_ADDITIONAL_BYTES);
}

/** @brief State : Re-enable the radio when the data have been written on the radio.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void enable_radio_irq(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }
    phy->signal_main = PHY_SIGNAL_CONFIG_COMPLETE;
    sr_access_enable_radio_irq(phy->radio->radio_id);

    /* If we missed the rising edge, do a context switch */
    if (sr_access_read_irq_pin(phy->radio->radio_id)) {
        sr_access_radio_context_switch(phy->radio->radio_id);
    }
}

/** @brief State : Re-enable the radio when the data have been written on the radio.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void check_radio_irq(wps_phy_t *phy)
{
    /* irq pin is low, auto-reply has not finish to send */
    sr_access_enable_radio_irq(phy->radio->radio_id);
    if (!sr_access_read_irq_pin(phy->radio->radio_id)) {
        phy->signal_main = PHY_SIGNAL_YIELD;
    }
}

/** @brief State : Ask the radio for the irq flags after a radio interrupt.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void read_events(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_RADIO_IRQ) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    phy->signal_main = PHY_SIGNAL_YIELD;

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.read_events_out,
                                        (uint8_t *)&phy->spi_xfer.read_events_in, sizeof(read_events_t));
}

/** @brief State : Ask the radio for the IRQ flags after a radio interrupt when syncing.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void read_events_syncing(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_RADIO_IRQ) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    sr_access_write_reg(phy->radio->radio_id, REG8_TIMER_CONFIG, AUTOWAKE_0b1 | WAKEONCE_0b1);
    sr_access_write_reg(phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS, GO_SLEEP_0b1);
    sr_access_write_reg(phy->radio->radio_id, REG8_SLEEP_CONFIG,
                        phy->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1);

    phy->signal_main = PHY_SIGNAL_YIELD;

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.read_events_out,
                                        (uint8_t *)&phy->spi_xfer.read_events_in, sizeof(read_events_t));
}

/** @brief State : Read the IRQ flags and take action regarding of the outcome for TX.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void process_event_tx(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    /* Handle CCA fail */
    if (GET_CCAFAILI(phy->spi_xfer.read_events_in.data_status2)) {
        handle_cca_fail(phy);
        /* Handle autoreply reception */
    } else if (rx_good(&phy->spi_xfer.read_events_in)) {
        phy->xlayer_main->frame.frame_outcome = FRAME_SENT_ACK;
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_RECEIVED;
        }
        handle_good_auto_reply(phy);
    } else if (rx_lost(&phy->spi_xfer.read_events_in)) {
        /* #1: When a timeout occurs, check if the RXEN bit of the transceiver is set and if so, clear
         *     any pending IRQs and disable the transceiver interrupts to ensure proper operation.
         *     Interrupts will be automatically re-enabled in a subsequent stage of the state machine.
         */
        if (GET_RX_EN(phy->spi_xfer.read_events_in.data_pwr_status)) {
            sr_access_disable_radio_irq(phy->radio->radio_id);
        }
        phy->xlayer_main->frame.frame_outcome = FRAME_SENT_ACK_LOST;
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_LOST;
        }
        phy->signal_main = PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
        enqueue_states(phy, prepare_phy_states);
    } else if (rx_rejected(&phy->spi_xfer.read_events_in)) {
        phy->xlayer_main->frame.frame_outcome = FRAME_SENT_ACK_REJECTED;
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_REJECTED;
        }
        phy->signal_main = PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
        phy->spi_xfer.read_info_in.data_rssi = sr_access_read_reg(phy->radio->radio_id, REG8_RSSI);
        phy->spi_xfer.read_info_in.data_rnsi = sr_access_read_reg(phy->radio->radio_id, REG8_RNSI);
        phy->config->rssi_raw = phy->spi_xfer.read_info_in.data_rssi;
        phy->config->rnsi_raw = phy->spi_xfer.read_info_in.data_rnsi;
        enqueue_states(phy, prepare_phy_states);
        /* Handle TX */
    } else if (tx_complete(&phy->spi_xfer.read_events_in)) {
        phy->signal_main = PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
        phy->xlayer_main->frame.frame_outcome = FRAME_SENT_ACK_LOST;
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_LOST;
        }
        enqueue_states(phy, prepare_phy_states);
    } else if (GET_WAKEUPI(phy->spi_xfer.read_events_in.data_status2) ||
               GET_TXUDRFLI(phy->spi_xfer.read_events_in.data_status2)) {
        phy->signal_main = PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
        phy->xlayer_main->frame.frame_outcome = FRAME_WAIT;
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_LOST;
        }
        enqueue_states(phy, prepare_phy_states);
    }
}

/** @brief State : Read the IRQ flags and take action regarding of the outcome for RX.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void process_event_rx(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    /* Handle RX frame */
    if (rx_good(&phy->spi_xfer.read_events_in)) {
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_SENT_ACK;
        }
        phy->xlayer_main->frame.frame_outcome = FRAME_RECEIVED;
        handle_good_frame(phy);
    } else if (rx_lost(&phy->spi_xfer.read_events_in)) {
        /* #1: When a timeout occurs, check if the RXEN bit of the transceiver is set and if so, clear
         *     any pending IRQs and disable the transceiver interrupts to ensure proper operation.
         *     Interrupts will be automatically re-enabled in a subsequent stage of the state machine.
         */
        if (GET_RX_EN(phy->spi_xfer.read_events_in.data_pwr_status)) {
            sr_access_disable_radio_irq(phy->radio->radio_id);
        }
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_SENT_ACK_LOST;
        }
        phy->xlayer_main->frame.frame_outcome = FRAME_LOST;
        phy->signal_auto = (phy->xlayer_auto != NULL) ? PHY_SIGNAL_FRAME_NOT_SENT : PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_main = PHY_SIGNAL_FRAME_MISSED;
        enqueue_states(phy, prepare_phy_states);
    } else if (rx_rejected(&phy->spi_xfer.read_events_in)) {
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.frame_outcome = FRAME_SENT_ACK_REJECTED;
        }
        phy->xlayer_main->frame.frame_outcome = FRAME_REJECTED;
        phy->signal_auto = (phy->xlayer_auto != NULL) ? PHY_SIGNAL_FRAME_NOT_SENT : PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_main = PHY_SIGNAL_FRAME_MISSED;
        phy->spi_xfer.read_info_in.data_rssi = sr_access_read_reg(phy->radio->radio_id, REG8_RSSI);
        phy->spi_xfer.read_info_in.data_rnsi = sr_access_read_reg(phy->radio->radio_id, REG8_RNSI);
        phy->config->rssi_raw = phy->spi_xfer.read_info_in.data_rssi;
        phy->config->rnsi_raw = phy->spi_xfer.read_info_in.data_rnsi;
        enqueue_states(phy, prepare_phy_states);
    }
}

/** @brief Handle a good frame received by the radio.
 *
 *  Ask the radio for RX wait time, RSSI, RNSI and payload size.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void handle_good_frame(wps_phy_t *phy)
{
    uint8_t transfer_size = (phy->config->phases_info == NULL) ? sizeof(read_info_t) - NB_PHASES - 1 :
                                                                 sizeof(read_info_t);

    phy->signal_main = PHY_SIGNAL_YIELD;

    if (phy->xlayer_auto != NULL) {
        if (auto_is_tx(phy) && !(GET_BRDCASTI(phy->spi_xfer.read_events_in.data_status1))) {
            phy->wait_for_ack_tx = true;
            if (!tx_complete_auto_reply(&phy->spi_xfer.read_events_in)) {
                /* Tx end is enable to wait the transmission of the autoreply.*/
                sr_access_write_reg(phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG,
                                    BIT_TXENDE | BIT_RXTIMEOE | phy->spi_xfer.irq_polarity_mask);
                sr_access_write_reg(phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS, 0);
                sr_access_disable_radio_irq(phy->radio->radio_id);
            } else {
                phy->wait_for_ack_tx = false;
            }

            phy->signal_auto = PHY_SIGNAL_FRAME_SENT_NACK;
        }
    }

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.read_info_out,
                                        (uint8_t *)&phy->spi_xfer.read_info_in, transfer_size);
    enqueue_states(phy, get_frame_header_states);
}

/** @brief Handle a good auto reply received by the radio.
 *
 *  Ask the radio for RX wait time, RSSI, RNSI and payload size.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void handle_good_auto_reply(wps_phy_t *phy)
{
    uint8_t transfer_size = (phy->config->phases_info == NULL) ? sizeof(read_info_t) - NB_PHASES - 1 :
                                                                 sizeof(read_info_t);

    phy->signal_main = PHY_SIGNAL_YIELD;

    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.read_info_out,
                                        (uint8_t *)&phy->spi_xfer.read_info_in, transfer_size);
    enqueue_states(phy, get_auto_reply_header_states);
}

/** @brief Handle a Clear Channel Assessment (CCA) fail.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void handle_cca_fail(wps_phy_t *phy)
{

    phy->signal_main = PHY_SIGNAL_YIELD;

    (phy->config->cca_try_count)++;

    if (phy->config->cca_fail_action == CCA_FAIL_ACTION_ABORT_TX) {
        if ((phy->config->cca_max_try_count == 0) ||
            (phy->config->cca_try_count < (phy->config->cca_max_try_count - 1))) {
            enqueue_states(phy, get_event_states);
        } else if (phy->config->cca_try_count < phy->config->cca_max_try_count) {
            sr_access_write_reg(phy->radio->radio_id, REG8_SLEEP_CONFIG,
                                phy->sleep_lvl | SLPRXTO_0b1 | SLPTXEND_0b1 | SLPRXEND_0b1 | SLPNOISY_0b1);
            enqueue_states(phy, get_event_states);
        } else {
            phy->signal_main = PHY_SIGNAL_FRAME_SENT_NACK;
            phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
            phy->xlayer_main->frame.frame_outcome = FRAME_SENT_ACK_LOST;
            if (phy->xlayer_auto != NULL) {
                phy->xlayer_auto->frame.frame_outcome = FRAME_LOST;
            }
            enqueue_states(phy, prepare_phy_states);
        }
    } else if (phy->config->cca_fail_action == CCA_FAIL_ACTION_TX) {
        if (phy->config->cca_try_count >= phy->config->cca_max_try_count) {
            /* Disable CCA */
            phy->spi_xfer.handle_cca_out.data_cca = DEFAULT_RX_IDLE_PWR | DISABLE_CCA_THRSH_VALUE;
            sr_access_spi_transfer_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.handle_cca_out,
                                            (uint8_t *)&phy->spi_xfer.spi_dummy_buffer, 2);
        }
        enqueue_states(phy, get_event_states);
    }
}

/** @brief State : Ask the radio to get the frame header.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void get_frame_header(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    phy->config->rx_wait_time = (GET_RX_WAITED_14_8(phy->spi_xfer.read_info_in.data_rx_wait_time1) << 8) |
                                GET_RX_WAITED_7_0(phy->spi_xfer.read_info_in.data_rx_wait_time0);
    phy->config->rssi_raw = phy->spi_xfer.read_info_in.data_rssi;
    phy->config->rnsi_raw = phy->spi_xfer.read_info_in.data_rnsi;
    if (phy->config->phases_info != NULL) {
        phy->config->phases_info->phase1 = phy->spi_xfer.read_info_in.data_phase_info[0];
        phy->config->phases_info->phase2 = phy->spi_xfer.read_info_in.data_phase_info[1];
        phy->config->phases_info->phase3 = phy->spi_xfer.read_info_in.data_phase_info[2];
        phy->config->phases_info->phase4 = phy->spi_xfer.read_info_in.data_phase_info[3];
    }

    uint8_t max_expected_frame_size = phy->config->max_expected_header_size + phy->config->max_expected_payload_size +
                                      HDR_SIZE_SIZE;

    /* Protect frame size for CRC false positive */
    if ((phy->spi_xfer.read_info_in.data_frame_size == 0) ||
        (phy->spi_xfer.read_info_in.data_frame_size > max_expected_frame_size)) {
        /* Data frame size is invalid. */
        phy->xlayer_main->frame.payload_end_it = phy->xlayer_main->frame.header_begin_it;
        phy->signal_auto = PHY_SIGNAL_FRAME_SENT_NACK;
        phy->signal_main = PHY_SIGNAL_FRAME_MISSED;
        enqueue_states(phy, prepare_phy_states);
    } else {
        phy->spi_xfer.read_info_in.data_frame_size -= HDR_SIZE_SIZE;
        phy->header_size = phy->spi_xfer.read_info_in.data_header_size;
        /* Protect header size for CRC false positive */
        if (phy->header_size > phy->config->max_expected_header_size) {
            /* Header size is invalid. */
            phy->xlayer_main->frame.payload_end_it = phy->xlayer_main->frame.header_begin_it;
            phy->signal_auto = PHY_SIGNAL_FRAME_SENT_NACK;
            phy->signal_main = PHY_SIGNAL_FRAME_MISSED;
            enqueue_states(phy, prepare_phy_states);
        } else {
            phy->signal_main = PHY_SIGNAL_YIELD;
            phy->xlayer_main->frame.header_begin_it = phy->xlayer_main->frame.header_memory;
            phy->xlayer_main->frame.payload_end_it = phy->xlayer_main->frame.header_memory + phy->header_size +
                                                     EMPTY_BYTE;

            phy->spi_xfer.spi_dummy_buffer[0] = REG_READ_BURST | REG8_FIFO_BUFFERS;
            sr_access_spi_transfer_non_blocking(phy->radio->radio_id, phy->spi_xfer.spi_dummy_buffer,
                                                phy->xlayer_main->frame.header_memory, phy->header_size + EMPTY_BYTE);
            enqueue_states(phy, get_payload_states);
            enqueue_states(phy, prepare_phy_states);
        }
    }
}

/** @brief State : Ask the radio to get the auto reply header.
 *
 *  If the payload is empty, the user is notified.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void get_auto_reply_header(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    phy->config->rx_wait_time = (GET_RX_WAITED_14_8(phy->spi_xfer.read_info_in.data_rx_wait_time1) << 8) |
                                GET_RX_WAITED_7_0(phy->spi_xfer.read_info_in.data_rx_wait_time0);
    phy->config->rssi_raw = phy->spi_xfer.read_info_in.data_rssi;
    phy->config->rnsi_raw = phy->spi_xfer.read_info_in.data_rnsi;
    if (phy->config->phases_info != NULL) {
        phy->config->phases_info->phase1 = phy->spi_xfer.read_info_in.data_phase_info[0];
        phy->config->phases_info->phase2 = phy->spi_xfer.read_info_in.data_phase_info[1];
        phy->config->phases_info->phase3 = phy->spi_xfer.read_info_in.data_phase_info[2];
        phy->config->phases_info->phase4 = phy->spi_xfer.read_info_in.data_phase_info[3];
    }

    uint8_t max_expected_auto_frame_size = phy->config->max_expected_auto_header_size +
                                           phy->config->max_expected_auto_payload_size + HDR_SIZE_SIZE;

    /* Protect frame size for CRC false positive */
    if ((phy->spi_xfer.read_info_in.data_frame_size == 0) || (phy->xlayer_auto == NULL) ||
        (phy->spi_xfer.read_info_in.data_frame_size > max_expected_auto_frame_size)) {
        /* Data frame size is invalid. */
        if (phy->xlayer_auto != NULL) {
            phy->xlayer_auto->frame.payload_end_it = phy->xlayer_auto->frame.header_begin_it;
        }
        phy->signal_main = PHY_SIGNAL_FRAME_SENT_ACK;
        phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
        enqueue_states(phy, prepare_phy_states);
    } else {
        phy->spi_xfer.read_info_in.data_frame_size -= HDR_SIZE_SIZE;
        phy->header_size = phy->spi_xfer.read_info_in.data_header_size;
        /* Protect header size for CRC false positive */
        if (phy->header_size > phy->config->max_expected_auto_header_size) {
            /* Header size is invalid. */
            phy->xlayer_auto->frame.payload_end_it = phy->xlayer_auto->frame.header_begin_it;
            phy->signal_main = PHY_SIGNAL_FRAME_SENT_ACK;
            phy->signal_auto = PHY_SIGNAL_FRAME_MISSED;
            enqueue_states(phy, prepare_phy_states);
        } else {
            phy->signal_main = PHY_SIGNAL_YIELD;

            phy->xlayer_auto->frame.header_begin_it = phy->xlayer_auto->frame.header_memory;
            phy->xlayer_auto->frame.payload_end_it = phy->xlayer_auto->frame.header_memory + phy->header_size +
                                                     EMPTY_BYTE;

            phy->spi_xfer.spi_dummy_buffer[0] = REG_READ_BURST | REG8_FIFO_BUFFERS;
            sr_access_spi_transfer_non_blocking(phy->radio->radio_id, phy->spi_xfer.spi_dummy_buffer,
                                                phy->xlayer_auto->frame.header_memory, phy->header_size + EMPTY_BYTE);
            enqueue_states(phy, get_payload_states);
            enqueue_states(phy, prepare_phy_states);
        }
    }
}

/** @brief State : Ask the radio to get the payload.
 *
 *  If the payload is empty, the user is notified.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void get_payload(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->signal_main = PHY_SIGNAL_ERROR;
        return;
    }

    uint8_t payload_size = phy->spi_xfer.read_info_in.data_frame_size - phy->header_size;
    phy_output_signal_t *signal = main_is_tx(phy) ? &phy->signal_auto : &phy->signal_main;
    xlayer_frame_t *frame = main_is_tx(phy) ? &phy->xlayer_auto->frame : &phy->xlayer_main->frame;

    *signal = PHY_SIGNAL_FRAME_RECEIVED;

    /* Update frame payload data pointer */
    phy->config->update_payload_buffer(phy->mac, frame, payload_size);

    if (payload_size == 0) {
        sr_access_close(phy->radio->radio_id);
    } else {
        if (frame->payload_begin_it != NULL) {
            sr_access_spi_transfer_non_blocking(phy->radio->radio_id, phy->spi_xfer.spi_dummy_buffer,
                                                frame->payload_begin_it, payload_size);
            frame->payload_end_it = frame->payload_begin_it + payload_size;
            enqueue_states(phy, new_frame_states);
        } else {
            /* This situation can happen when more connections are assign to the same timeslot and there is no free
             * space in current RX connection.
             */
            sr_access_close(phy->radio->radio_id);
        }
    }
    if ((phy->xlayer_auto != NULL) && phy->wait_for_ack_tx) {
        if (auto_is_tx(phy) && phy->wait_for_ack_tx && !GET_BRDCASTI(phy->spi_xfer.read_events_in.data_status1)) {
            enqueue_states(phy, wait_to_send_auto_reply);
        } else {
            phy->signal_main = PHY_SIGNAL_FRAME_SENT_ACK;
        }
    }
}

/** @brief State : Close the spi after transmission or reception.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void close_spi(wps_phy_t *phy)
{
    if (phy->input_signal != PHY_SIGNAL_DMA_CMPLT) {
        phy->state_step--;
        phy->signal_main = PHY_SIGNAL_YIELD;
        return;
    }

    sr_access_close(phy->radio->radio_id);
}

/** @brief State : End of a state machine sequence.
 *
 *  @param[in] signal_data  Data required to process the state. The type shall be wps_phy_t.
 */
static void end(wps_phy_t *phy)
{
    wps_phy_state_t **dequeue_state = NULL;

    phy->state_step = 0;
    dequeue_state = (wps_phy_state_t **)circular_queue_front_raw(&phy->next_states);
    phy->current_state = *dequeue_state;
    circular_queue_dequeue_raw(&phy->next_states);
}

static void none(wps_phy_t *phy)
{
    (void)phy;
}

static void prepare_syncing(wps_phy_t *phy)
{
    uint8_t auto_reply = 0;
    uint8_t rx_timeout_lsb = SET_RX_TIMEOUT_LSB(FAST_SYNC_TIMER_VALUE);
    uint8_t rx_timeout_msb = SET_RX_TIMEOUT_MSB(FAST_SYNC_TIMER_VALUE);

    phy->signal_main = PHY_SIGNAL_YIELD;

    sr_access_disable_radio_irq(phy->radio->radio_id);

    if (phy->config->expect_ack) {
        sr_access_write_reg(phy->radio->radio_id, REG8_TX_PKT_SIZE, 0);
    }
    sr_access_write_reg(phy->radio->radio_id, REG8_RX_PKT_SIZE, MAX_FRAMESIZE);
    sr_access_write_reg16(phy->radio->radio_id, REG8_TRANSMITTER_ADDR_15_8, phy->xlayer_main->frame.source_address);

    if (phy->config->expect_ack) {
        auto_reply = AUTORPLY_0b1;
    }
    sr_access_write_reg(phy->radio->radio_id, REG8_MAIN_MODEM_FEATS,
                        auto_reply | phy->config->modulation | phy->config->fec | ISI_MITIG_0);
    sr_access_write_reg(phy->radio->radio_id, REG8_BASEBAND_TUNING, phy->config->channel->integgain);
    sr_access_write_reg(phy->radio->radio_id, REG8_RECEIVER_CONST_GAINS, phy->config->rx_constgain);
    sr_access_write_reg(phy->radio->radio_id, REG8_MAIN_DEVICE_FLAG, phy->spi_xfer.irq_polarity_mask | BIT_NEWPKTE);
    sr_access_write_reg(phy->radio->radio_id, REG8_AUX_DEVICE_FLAGS, 0);
    sr_access_write_reg(phy->radio->radio_id, REG8_TIMER_COUNTER_15_8, 0xFF);
    sr_access_write_reg16(phy->radio->radio_id, REG8_TIMER_COUNTER_15_8, FAST_SYNC_TIMER_VALUE);
    sr_access_write_reg(phy->radio->radio_id, REG8_COLLISION_AVOIDANCE, DEFAULT_RX_IDLE_PWR | DISABLE_CCA_THRSH_VALUE);
    sr_access_write_reg(phy->radio->radio_id, REG8_RECEIVER_PAUSE_TIME, 0);
    sr_access_write_reg(phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD1, rx_timeout_msb);
    sr_access_write_reg(phy->radio->radio_id, REG8_RX_TIMEOUT_PERIOD0_PWR_UP_DELAY, rx_timeout_lsb);
    sr_access_write_reg(phy->radio->radio_id, REG8_TX_PWR_UP_DELAY, SET_PWRUP_DELAY(phy->config->power_up_delay));
    sr_access_write_reg(phy->radio->radio_id, REG8_TIMER_CONFIG, WAKEONCE_0b0 | AUTOWAKE_0b0 | SYNPKTRX_0b1);
    sr_access_write_reg(phy->radio->radio_id, REG8_SLEEP_CONFIG, phy->sleep_lvl);
    sr_access_write_reg(phy->radio->radio_id, REG8_PWR_STATUS_COMMANDS,
                        FLUSH_RX_0b1 | FLUSH_TX_0b1 | INITIMER_0b1 | RX_MODE);
    sr_access_write_reg(phy->radio->radio_id, REG8_RX_FREQ_TUNING, phy->config->channel->channel.rx_filter);

    phy->spi_xfer.set_chan_out.addr_channels = REG_WRITE_BURST | REG8_TX_PULSE_PATTERN_12;
    memcpy(&phy->spi_xfer.set_chan_out.data_channels, (phy->config->channel->channel.tx_pattern), NB_PULSES + 1);
    sr_access_spi_transfer_non_blocking(phy->radio->radio_id, (uint8_t *)&phy->spi_xfer.set_chan_out.addr_channels,
                                        (uint8_t *)&phy->spi_xfer.spi_dummy_buffer, NB_PULSES + 2);
}

/** @brief Get if the main frame is in transmit mode.
 *
 *  @param[in] phy Layer one instance.
 *  @retval true
 *  @retval false
 */
static bool main_is_tx(wps_phy_t *phy)
{
    return (phy->xlayer_main->frame.destination_address != phy->local_address);
}

/** @brief Get if the main frame is in transmit mode.
 *
 *  @param[in] phy Layer one instance.
 *  @retval true
 *  @retval false
 */
static bool auto_is_tx(wps_phy_t *phy)
{
    return (phy->xlayer_auto->frame.destination_address != phy->local_address);
}

/** @brief Get the TX complete status.
 *
 *  @param[in] read_events
 *  @retval true
 *  @retval false
 */
static bool tx_complete(read_events_t *read_events)
{
    return ((GET_TXENDI(read_events->data_status1) && !GET_NEWPKTI(read_events->data_status1) &&
             !GET_RXTIMEOI(read_events->data_status1)));
}

/** @brief Get the TX complete of auto-reply frame status.
 *
 *  @note This is slightly different then tx_complete, since
 *        NEW_PACKET_IT is trigger during reception of frame, so
 *        only event to check is TX_END_IT
 *
 *  @param[in] read_events
 *  @retval true
 *  @retval false
 */
static bool tx_complete_auto_reply(read_events_t *read_events)
{
    return (GET_TXENDI(read_events->data_status1) || GET_TXUDRFLI(read_events->data_status2));
}

/** @brief Get the RX good status.
 *
 *  @param[in] read_events
 *  @retval true
 *  @retval false
 */
static bool rx_good(read_events_t *read_events)
{
    return (GET_NEWPKTI(read_events->data_status1) && GET_CRCPASSI(read_events->data_status1) &&
            (GET_ADDRMATI(read_events->data_status1) || GET_BRDCASTI(read_events->data_status1)));
}

/** @brief Get the RX rejected status.
 *
 *  @param[in] read_events
 *  @retval true
 *  @retval false
 */
static bool rx_rejected(read_events_t *read_events)
{
    return (GET_NEWPKTI(read_events->data_status1) &&
            (!GET_CRCPASSI(read_events->data_status1) ||
             !(GET_ADDRMATI(read_events->data_status1) || GET_BRDCASTI(read_events->data_status1))));
}

/** @brief Get the RX lost status.
 *
 *  @param[in] read_events
 *  @retval true
 *  @retval false
 */
static bool rx_lost(read_events_t *read_events)
{
    return GET_RXTIMEOI(read_events->data_status1);
}

/** @brief Set the events for tx with ack.
 *
 *  @param[out] read_events
 */
static void set_events_for_tx_with_ack(wps_phy_t *phy)
{
    phy->spi_xfer.radio_cfg_out.data_irq_mask1 = BIT_NEWPKTE | BIT_RXTIMEOE | phy->spi_xfer.irq_polarity_mask;
    phy->spi_xfer.radio_cfg_out.data_irq_mask2 = BIT_CCAFAILE | BIT_TXUDRFLE;
}

/** @brief Set the events for tx without ack.
 *
 *  @param[out] read_events
 */
static void set_events_for_tx_without_ack(wps_phy_t *phy)
{
    phy->spi_xfer.radio_cfg_out.data_irq_mask1 = BIT_TXENDE | phy->spi_xfer.irq_polarity_mask;
    phy->spi_xfer.radio_cfg_out.data_irq_mask2 = BIT_CCAFAILE | BIT_TXUDRFLE;
}

/** @brief Set the events for rx with ack.
 *
 *  @param[out] read_events
 */
static void set_events_for_rx_with_ack(wps_phy_t *phy)
{
    phy->spi_xfer.radio_cfg_out.data_irq_mask1 = BIT_NEWPKTE | BIT_RXTIMEOE | phy->spi_xfer.irq_polarity_mask;
    phy->spi_xfer.radio_cfg_out.data_irq_mask2 = 0;
}

/** @brief Set the events for rx without ack.
 *
 *  @param[out] read_events
 */
static void set_events_for_rx_without_ack(wps_phy_t *phy)
{
    phy->spi_xfer.radio_cfg_out.data_irq_mask1 = BIT_NEWPKTE | BIT_RXTIMEOE | phy->spi_xfer.irq_polarity_mask;
    phy->spi_xfer.radio_cfg_out.data_irq_mask2 = 0;
}

/** @brief Set the events for rx with payload.
 *
 *  @param[out] read_events
 */
static void set_events_for_wakeup_only(wps_phy_t *phy)
{
    phy->spi_xfer.radio_cfg_out.data_irq_mask1 = phy->spi_xfer.irq_polarity_mask;
    phy->spi_xfer.radio_cfg_out.data_irq_mask2 = BIT_WAKEUPE;
}

static void init_transfer_structures(wps_phy_t *wps_phy)
{
#if WPS_RADIO_COUNT == 2
    wps_phy->spi_xfer.radio_cfg_out.addr_timer_conf = REG_WRITE | REG8_TIMER_CONFIG;
#endif
    wps_phy->spi_xfer.radio_cfg_out.addr_const_gain = REG_WRITE | REG8_RECEIVER_CONST_GAINS;
    wps_phy->spi_xfer.radio_cfg_out.addr_cca = REG_WRITE | REG8_COLLISION_AVOIDANCE;
    wps_phy->spi_xfer.radio_cfg_out.addr_rx_size = REG_WRITE | REG8_RX_PKT_SIZE;
    wps_phy->spi_xfer.radio_cfg_out.addr_rx_wait_src = REG_WRITE | REG8_RX_WAITED_14_8_WAIT_SRC;
    wps_phy->spi_xfer.radio_cfg_out.addr_tx_size = REG_WRITE | REG8_TX_PKT_SIZE;
    wps_phy->spi_xfer.radio_cfg_out.addr_rx_pause_time = REG_WRITE | REG8_RECEIVER_PAUSE_TIME;
    wps_phy->spi_xfer.radio_cfg_out.addr_status1 = REG8_MAIN_DEVICE_FLAG;
    wps_phy->spi_xfer.radio_cfg_out.addr_status2 = REG8_AUX_DEVICE_FLAGS;
    wps_phy->spi_xfer.radio_cfg_out.addr_remote_addr0 = REG_WRITE | REG8_TRANSMITTER_ADDR_7_0;
    wps_phy->spi_xfer.radio_cfg_out.addr_remote_addr1 = REG_WRITE | REG8_TRANSMITTER_ADDR_15_8;
    wps_phy->spi_xfer.remote_addr[1] = &wps_phy->spi_xfer.radio_cfg_out.data_remote_addr1;
    wps_phy->spi_xfer.remote_addr[0] = &wps_phy->spi_xfer.radio_cfg_out.data_remote_addr0;

    wps_phy->spi_xfer.radio_cfg_out.addr_main_modem = REG_WRITE | REG8_MAIN_MODEM_FEATS;
    wps_phy->spi_xfer.radio_cfg_out.addr_irq_mask1 = REG_WRITE | REG8_MAIN_DEVICE_FLAG;
    wps_phy->spi_xfer.radio_cfg_out.addr_irq_mask2 = REG_WRITE | REG8_AUX_DEVICE_FLAGS;
    wps_phy->spi_xfer.radio_cfg_out.addr_actions = REG_WRITE | REG8_PWR_STATUS_COMMANDS;
    wps_phy->spi_xfer.radio_cfg_out.addr_sleep_conf = REG_WRITE | REG8_SLEEP_CONFIG;
    wps_phy->spi_xfer.radio_cfg_out.addr_timers_cfg = REG_WRITE_BURST | REG8_TIMER_COUNTER_15_8;
    wps_phy->spi_xfer.timer_period[1] = &wps_phy->spi_xfer.radio_cfg_out.data_timer_period1;
    wps_phy->spi_xfer.timer_period[0] = &wps_phy->spi_xfer.radio_cfg_out.data_timer_period0;

    wps_phy->spi_xfer.dll_tune_mask =
        (sr_access_read_reg(wps_phy->radio->radio_id, REG8_BASEBAND_TUNING) & BITS_DL_TUNE) | CCAGAINOV_ENABLE;
    wps_phy->spi_xfer.set_chan_out.addr_dll_tune0 = REG_WRITE | REG8_BASEBAND_TUNING;
    wps_phy->spi_xfer.set_chan_out.data_dll_tune0 = wps_phy->spi_xfer.dll_tune_mask | INTEGLEN_0b1;
    wps_phy->spi_xfer.set_chan_out.addr_dll_tune1 = REG_WRITE | REG8_BASEBAND_TUNING;
    wps_phy->spi_xfer.set_chan_out.addr_rx_filters = REG_WRITE | REG8_RX_FREQ_TUNING;

    wps_phy->spi_xfer.fill_header_out.addr_fifo = REG_WRITE_BURST | REG8_FIFO_BUFFERS;

    wps_phy->spi_xfer.read_events_out.addr_status1 = REG8_MAIN_DEVICE_FLAG;
    wps_phy->spi_xfer.read_events_out.addr_status2 = REG8_AUX_DEVICE_FLAGS;
    wps_phy->spi_xfer.read_events_out.addr_pwr_status = REG8_PWR_STATUS_COMMANDS;

    wps_phy->spi_xfer.read_info_out.addr_rx_wait_time1 = REG8_RX_WAITED_14_8_WAIT_SRC;
    wps_phy->spi_xfer.read_info_out.addr_rx_wait_time0 = REG8_RX_WAITED_7_0;
    wps_phy->spi_xfer.read_info_out.addr_rssi = REG8_RSSI;
    wps_phy->spi_xfer.read_info_out.addr_rnsi = REG8_RNSI;
    wps_phy->spi_xfer.read_info_out.addr_frame_size = REG8_FIFO_BUFFERS;
    wps_phy->spi_xfer.read_info_out.addr_header_size = REG8_FIFO_BUFFERS;
    wps_phy->spi_xfer.read_info_out.addr_phase_info = REG_READ_BURST | REG8_NOISE_FLOOR;

    wps_phy->spi_xfer.handle_cca_out.addr_cca = REG_WRITE | REG8_COLLISION_AVOIDANCE;
    wps_phy->spi_xfer.handle_cca_out.addr_actions = REG_WRITE | REG8_PWR_STATUS_COMMANDS;

    wps_phy->spi_xfer.irq_polarity_mask = (wps_phy->radio->irq_polarity == IRQ_ACTIVE_HIGH) ? IRQPOLAR_0b1 : 0;
}

static void set_reg16(uint16_t value, uint8_t **reg)
{
    *reg[0] = EXTRACT_BYTE(value, 0);
    *reg[1] = EXTRACT_BYTE(value, 1);
}
