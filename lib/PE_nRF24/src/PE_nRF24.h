#ifndef PE_NRF24_H
#define PE_NRF24_H

#include <stdint.h>

/** Instructions **************************************************************/

// Register read
#define nRF24_CMD_R_REGISTER(_reg_) ((0x00U) | ((0x1FU) & (_reg_)))

// Register write
#define nRF24_CMD_W_REGISTER(_reg_) ((0x20U) | ((0x1FU) & (_reg_)))

// Read RX payload
#define nRF24_CMD_R_RX_PAYLOAD 0x61U

// Write TX payload
#define nRF24_CMD_W_TX_PAYLOAD 0xA0U

// Flush TX FIFO
#define nRF24_CMD_FLUSH_TX 0xE1U

// Flush RX FIFO
#define nRF24_CMD_FLUSH_RX 0xE2U

// Reuse TX payload
#define nRF24_CMD_REUSE_TX_PL 0xE3U

// ONLY FOR nRF24L01+
// Read RX payload width for the top R_RX_PAYLOAD in the RX FIFO
#define nRF24_R_RX_PL_WID 0x60U

// ONLY FOR nRF24L01+
// Write Payload to be transmitted together with ACK packet on PIPE
#define nRF24_W_ACK_PAYLOAD(_pipe_) ((0xA8U) | ((0x7U) & (_pipe_)))

// ONLY FOR nRF24L01+
// Disables AUTO ACK on this specific packet.
#define nRF24_W_TX_PAYLOAD_NO_ACK 0xB0U

// No operation (used for reading status register)
#define nRF24_CMD_NOP 0xFFU

/** Registers *****************************************************************/

#define nRF24_CONFIG      0x00U
#define nRF24_EN_AA       0x01U
#define nRF24_EN_RXADDR   0x02U
#define nRF24_SETUP_AW    0x03U
#define nRF24_SETUP_RETR  0x04U
#define nRF24_RF_CH       0x05U
#define nRF24_RF_SETUP    0x06U
#define nRF24_STATUS      0x07U
#define nRF24_OBSERVE_TX  0x08U
#define nRF24_RPD         0x09U
#define nRF24_RX_ADDR_P0  0x0AU
#define nRF24_RX_ADDR_P1  0x0BU
#define nRF24_RX_ADDR_P2  0x0CU
#define nRF24_RX_ADDR_P3  0x0DU
#define nRF24_RX_ADDR_P4  0x0EU
#define nRF24_RX_ADDR_P5  0x0FU
#define nRF24_TX_ADDR     0x10U
#define nRF24_RX_PW_P0    0x11U
#define nRF24_RX_PW_P1    0x12U
#define nRF24_RX_PW_P2    0x13U
#define nRF24_RX_PW_P3    0x14U
#define nRF24_RX_PW_P4    0x15U
#define nRF24_RX_PW_P5    0x16U
#define nRF24_FIFO_STATUS 0x17U
#define nRF24_DYNPD       0x1CU
#define nRF24_FEATURE     0x1DU // Feature Register

/** CONFIG bits ***************************************************************/

// 1 == PRX, 0 == PTX
#define nRF24_CONFIG_PRIM_RX_Pos (0U)
#define nRF24_CONFIG_PRIM_RX_Msk (1U << nRF24_CONFIG_PRIM_RX_Pos)
#define nRF24_CONFIG_PRIM_RX     nRF24_CONFIG_PRIM_RX_Msk

// 1 == POWER UP, 0 == POWER DOWN
#define nRF24_CONFIG_PWR_UP_Pos (1U)
#define nRF24_CONFIG_PWR_UP_Msk (1U << nRF24_CONFIG_PWR_UP_Pos)
#define nRF24_CONFIG_PWR_UP     nRF24_CONFIG_PWR_UP_Msk

// CRC encoding scheme
#define nRF24_CONFIG_CRCO_Pos (2U)
#define nRF24_CONFIG_CRCO_Msk (1U << nRF24_CONFIG_CRCO_Pos)
#define nRF24_CONFIG_CRCO     nRF24_CONFIG_CRCO_Msk

// Enable CRC
#define nRF24_CONFIG_EN_CRC_Pos (3U)
#define nRF24_CONFIG_EN_CRC_Msk (1U << nRF24_CONFIG_EN_CRC_Pos)
#define nRF24_CONFIG_EN_CRC     nRF24_CONFIG_EN_CRC_Msk

// Mask interrupt caused by MAX_RT
#define nRF24_CONFIG_MASK_MAX_RT_Pos (4U)
#define nRF24_CONFIG_MASK_MAX_RT_Msk (1U << nRF24_CONFIG_MASK_MAX_RT_Pos)
#define nRF24_CONFIG_MASK_MAX_RT     nRF24_CONFIG_MASK_MAX_RT_Msk

// Mask interrupt caused by TX_DS
#define nRF24_CONFIG_MASK_TX_DS_Pos (5U)
#define nRF24_CONFIG_MASK_TX_DS_Msk (1U << nRF24_CONFIG_MASK_TX_DS_Pos)
#define nRF24_CONFIG_MASK_TX_DS     nRF24_CONFIG_MASK_TX_DS_Msk

// Mask interrupt caused by RX_DR
#define nRF24_CONFIG_MASK_RX_DR_Pos (6U)
#define nRF24_CONFIG_MASK_RX_DR_Msk (1U << nRF24_CONFIG_MASK_RX_DR_Pos)
#define nRF24_CONFIG_MASK_RX_DR     nRF24_CONFIG_MASK_RX_DR_Msk

/** EN_AA bits ****************************************************************/

// Enable ‘Auto Acknowledgment’ Function
#define nRF24_EN_AA_ENAA_P0_Pos (0U)
#define nRF24_EN_AA_ENAA_P0_Msk (1U << nRF24_EN_AA_ENAA_P0_Pos)
#define nRF24_EN_AA_ENAA_P0     nRF24_EN_AA_ENAA_P0_Msk

#define nRF24_EN_AA_ENAA_P1_Pos (1U)
#define nRF24_EN_AA_ENAA_P1_Msk (1U << nRF24_EN_AA_ENAA_P1_Pos)
#define nRF24_EN_AA_ENAA_P1     nRF24_EN_AA_ENAA_P1_Msk

#define nRF24_EN_AA_ENAA_P2_Pos (2U)
#define nRF24_EN_AA_ENAA_P2_Msk (1U << nRF24_EN_AA_ENAA_P2_Pos)
#define nRF24_EN_AA_ENAA_P2     nRF24_EN_AA_ENAA_P2_Msk

#define nRF24_EN_AA_ENAA_P3_Pos (3U)
#define nRF24_EN_AA_ENAA_P3_Msk (1U << nRF24_EN_AA_ENAA_P3_Pos)
#define nRF24_EN_AA_ENAA_P3     nRF24_EN_AA_ENAA_P3_Msk

#define nRF24_EN_AA_ENAA_P4_Pos (4U)
#define nRF24_EN_AA_ENAA_P4_Msk (1U << nRF24_EN_AA_ENAA_P4_Pos)
#define nRF24_EN_AA_ENAA_P4     nRF24_EN_AA_ENAA_P4_Msk

#define nRF24_EN_AA_ENAA_P5_Pos (5U)
#define nRF24_EN_AA_ENAA_P5_Msk (1U << nRF24_EN_AA_ENAA_P5_Pos)
#define nRF24_EN_AA_ENAA_P5     nRF24_EN_AA_ENAA_P5_Msk

/** EN_RXADDR bits ************************************************************/

// Enable data pipe 0, default 1
#define nRF24_EN_RXADDR_ERX_P0_Pos (0U)
#define nRF24_EN_RXADDR_ERX_P0_Msk (1U << nRF24_EN_RXADDR_ERX_P0_Pos)
#define nRF24_EN_RXADDR_ERX_P0     nRF24_EN_RXADDR_ERX_P0_Msk

// Enable data pipe 1, default 1
#define nRF24_EN_RXADDR_ERX_P1_Pos (1U)
#define nRF24_EN_RXADDR_ERX_P1_Msk (1U << nRF24_EN_RXADDR_ERX_P1_Pos)
#define nRF24_EN_RXADDR_ERX_P1     nRF24_EN_RXADDR_ERX_P1_Msk

// Enable data pipe 2, default 0
#define nRF24_EN_RXADDR_ERX_P2_Pos (2U)
#define nRF24_EN_RXADDR_ERX_P2_Msk (1U << nRF24_EN_RXADDR_ERX_P2_Pos)
#define nRF24_EN_RXADDR_ERX_P2     nRF24_EN_RXADDR_ERX_P2_Msk

// Enable data pipe 3, default 0
#define nRF24_EN_RXADDR_ERX_P3_Pos (3U)
#define nRF24_EN_RXADDR_ERX_P3_Msk (1U << nRF24_EN_RXADDR_ERX_P3_Pos)
#define nRF24_EN_RXADDR_ERX_P3     nRF24_EN_RXADDR_ERX_P3_Msk

// Enable data pipe 4, default 0
#define nRF24_EN_RXADDR_ERX_P4_Pos (4U)
#define nRF24_EN_RXADDR_ERX_P4_Msk (1U << nRF24_EN_RXADDR_ERX_P4_Pos)
#define nRF24_EN_RXADDR_ERX_P4     nRF24_EN_RXADDR_ERX_P4_Msk

// Enable data pipe 5, default 0
#define nRF24_EN_RXADDR_ERX_P5_Pos (5U)
#define nRF24_EN_RXADDR_ERX_P5_Msk (1U << nRF24_EN_RXADDR_ERX_P5_Pos)
#define nRF24_EN_RXADDR_ERX_P5     nRF24_EN_RXADDR_ERX_P5_Msk

/** SETUP_AW bits *************************************************************/

// RX/TX Address field width
// 0x00 == Illegal
// 0x01 == 3 bytes
// 0x10 == 4 bytes
// 0x11 == 5 bytes (default)
#define nRF24_SETUP_AW_AW_Pos (0U)
#define nRF24_SETUP_AW_AW_Msk (0x3U << nRF24_SETUP_AW_AW_Pos)
#define nRF24_SETUP_AW_AW     nRF24_SETUP_AW_AW_Msk
#define nRF24_SETUP_AW_AW_0   (0x1U << nRF24_SETUP_AW_AW_Pos)
#define nRF24_SETUP_AW_AW_1   (0x2U << nRF24_SETUP_AW_AW_Pos)

/** SETUP_RETR bits ***********************************************************/

// Auto Retransmit Count, default 0b0000
#define nRF24_SETUP_RETR_ARC_Pos (0U)
#define nRF24_SETUP_RETR_ARC_Msk (0x0FU << nRF24_SETUP_RETR_ARC_Pos)
#define nRF24_SETUP_RETR_ARC     nRF24_SETUP_RETR_ARC_Msk
#define nRF24_SETUP_RETR_ARC_0   (0x1U << nRF24_SETUP_RETR_ARC_Pos)
#define nRF24_SETUP_RETR_ARC_1   (0x2U << nRF24_SETUP_RETR_ARC_Pos)
#define nRF24_SETUP_RETR_ARC_2   (0x4U << nRF24_SETUP_RETR_ARC_Pos)
#define nRF24_SETUP_RETR_ARC_3   (0x8U << nRF24_SETUP_RETR_ARC_Pos)

// Auto Re-transmit Delay, default 0b0011
#define nRF24_SETUP_RETR_ARD_Pos (4U)
#define nRF24_SETUP_RETR_ARD_Msk (0x0FU << nRF24_SETUP_RETR_ARD_Pos)
#define nRF24_SETUP_RETR_ARD     nRF24_SETUP_RETR_ARD_Msk
#define nRF24_SETUP_RETR_ARD_0   (0x1U << nRF24_SETUP_RETR_ARD_Pos)
#define nRF24_SETUP_RETR_ARD_1   (0x2U << nRF24_SETUP_RETR_ARD_Pos)
#define nRF24_SETUP_RETR_ARD_2   (0x4U << nRF24_SETUP_RETR_ARD_Pos)
#define nRF24_SETUP_RETR_ARD_3   (0x8U << nRF24_SETUP_RETR_ARD_Pos)

/** RF_CH bits ****************************************************************/

// Sets the frequency channel, default 0b0000010
#define nRF24_RF_CH_RF_CH_Pos (0U)
#define nRF24_RF_CH_RF_CH_Msk (0x3FU << nRF24_RF_CH_RF_CH_Pos)
#define nRF24_RF_CH_RF_CH     nRF24_RF_CH_RF_CH_Msk

/** RF_SETUP bits *************************************************************/

// ONLY FOR nRF24L01
// Setup LNA gain
#define nRF24_RF_SETUP_LNA_HCURR_Pos (0U)
#define nRF24_RF_SETUP_LNA_HCURR_Msk (1U << nRF24_RF_SETUP_LNA_HCURR_Pos)
#define nRF24_RF_SETUP_LNA_HCURR     nRF24_RF_SETUP_LNA_HCURR_Msk

// Set RF output power in TX mode
#define nRF24_RF_SETUP_RF_PWR_Pos (1U)
#define nRF24_RF_SETUP_RF_PWR_Msk (0x3U << nRF24_RF_SETUP_RF_PWR_Pos)
#define nRF24_RF_SETUP_RF_PWR     nRF24_RF_SETUP_RF_PWR_Msk
#define nRF24_RF_SETUP_RF_PWR_0   (0x1U << nRF24_RF_SETUP_RF_PWR_Pos)
#define nRF24_RF_SETUP_RF_PWR_1   (0x2U << nRF24_RF_SETUP_RF_PWR_Pos)

// Select between the high speed data rates: 0x1 == 2 Mbps, 0x0 == 1 Mbps
#define nRF24_RF_SETUP_RF_DR_HIGH_Pos (3U)
#define nRF24_RF_SETUP_RF_DR_HIGH_Msk (1U << nRF24_RF_SETUP_RF_DR_HIGH_Pos)
#define nRF24_RF_SETUP_RF_DR_HIGH     nRF24_RF_SETUP_RF_DR_HIGH_Msk

// Force PLL lock signal. Only used in test
#define nRF24_RF_SETUP_PLL_LOCK_Pos (4U)
#define nRF24_RF_SETUP_PLL_LOCK_Msk (1U << nRF24_RF_SETUP_PLL_LOCK_Pos)
#define nRF24_RF_SETUP_PLL_LOCK     nRF24_RF_SETUP_PLL_LOCK_Msk

// ONLY FOR nRF24L01+
// Set RF Data Rate to 250kbps
#define nRF24_RF_SETUP_RF_DR_LOW_Pos (5U)
#define nRF24_RF_SETUP_RF_DR_LOW_Msk (1U << nRF24_RF_SETUP_RF_DR_LOW_Pos)
#define nRF24_RF_SETUP_RF_DR_LOW     nRF24_RF_SETUP_RF_DR_LOW_Msk

// ONLY FOR nRF24L01+
// Enables continuous carrier transmit when high
#define nRF24_RF_SETUP_CONT_WAVE_Pos (7U)
#define nRF24_RF_SETUP_CONT_WAVE_Msk (1U << nRF24_RF_SETUP_CONT_WAVE_Pos)
#define nRF24_RF_SETUP_CONT_WAVE     nRF24_RF_SETUP_CONT_WAVE_Msk

/** STATUS bits ***************************************************************/

// TX FIFO full flag, readonly, default 0
#define nRF24_STATUS_TX_FULL_Pos (0U)
#define nRF24_STATUS_TX_FULL_Msk (1U << nRF24_STATUS_TX_FULL_Pos)
#define nRF24_STATUS_TX_FULL     nRF24_STATUS_TX_FULL_Msk

// Data pipe number for the payload, readonly, default 0b111
#define nRF24_STATUS_RX_P_NO_Pos (1U)
#define nRF24_STATUS_RX_P_NO_Msk (0x7U << nRF24_STATUS_RX_P_NO_Pos)
#define nRF24_STATUS_RX_P_NO     nRF24_STATUS_RX_P_NO_Msk

// Maximum number of TX retries interrupt, default 0
#define nRF24_STATUS_MAX_RT_Pos (4U)
#define nRF24_STATUS_MAX_RT_Msk (1U << nRF24_STATUS_MAX_RT_Pos)
#define nRF24_STATUS_MAX_RT     nRF24_STATUS_MAX_RT_Msk

// Data Sent TX FIFO interrupt, default 0
#define nRF24_STATUS_TX_DS_Pos (5U)
#define nRF24_STATUS_TX_DS_Msk (1U << nRF24_STATUS_TX_DS_Pos)
#define nRF24_STATUS_TX_DS     nRF24_STATUS_TX_DS_Msk

// Data Ready RX FIFO interrupt, default 0
#define nRF24_STATUS_RX_DR_Pos (6U)
#define nRF24_STATUS_RX_DR_Msk (1U << nRF24_STATUS_RX_DR_Pos)
#define nRF24_STATUS_RX_DR     nRF24_STATUS_RX_DR_Msk

/** OBSERVE_TX bits ***********************************************************/

// Count resent packets, read only
#define nRF24_OBSERVE_TX_ARC_CNT_Pos (0U)
#define nRF24_OBSERVE_TX_ARC_CNT_Msk (0xFU << nRF24_OBSERVE_TX_ARC_CNT_Pos)
#define nRF24_OBSERVE_TX_ARC_CNT     nRF24_OBSERVE_TX_ARC_CNT_Msk

// Count lost packets, read only
#define nRF24_OBSERVE_TX_PLOS_CNT_Pos (4U)
#define nRF24_OBSERVE_TX_PLOS_CNT_Msk (0xFU << nRF24_OBSERVE_TX_PLOS_CNT_Pos)
#define nRF24_OBSERVE_TX_PLOS_CNT     nRF24_OBSERVE_TX_PLOS_CNT_Msk

/** FIFO_STATUS bits **********************************************************/

// RX FIFO empty flag, default 1
#define nRF24_FIFO_STATUS_RX_EMPTY_Pos (0U)
#define nRF24_FIFO_STATUS_RX_EMPTY_Msk (1U << nRF24_FIFO_STATUS_RX_EMPTY_Pos)
#define nRF24_FIFO_STATUS_RX_EMPTY     nRF24_FIFO_STATUS_RX_EMPTY_Msk

// RX FIFO full flag, default 0
#define nRF24_FIFO_STATUS_RX_FULL_Pos (1U)
#define nRF24_FIFO_STATUS_RX_FULL_Msk (1U << nRF24_FIFO_STATUS_RX_FULL_Pos)
#define nRF24_FIFO_STATUS_RX_FULL     nRF24_FIFO_STATUS_RX_FULL_Msk

// TX FIFO empty flag, default 1
#define nRF24_FIFO_STATUS_TX_EMPTY_Pos (4U)
#define nRF24_FIFO_STATUS_TX_EMPTY_Msk (1U << nRF24_FIFO_STATUS_TX_EMPTY_Pos)
#define nRF24_FIFO_STATUS_TX_EMPTY     nRF24_FIFO_STATUS_TX_EMPTY_Msk

// TX FIFO full flag, default 0
#define nRF24_FIFO_STATUS_TX_FULL_Pos (5U)
#define nRF24_FIFO_STATUS_TX_FULL_Msk (1U << nRF24_FIFO_STATUS_TX_FULL_Pos)
#define nRF24_FIFO_STATUS_TX_FULL     nRF24_FIFO_STATUS_TX_FULL_Msk

// Pulse the rfce high for at least 10μs to Reuse last transmitted payload, default 0
#define nRF24_FIFO_STATUS_TX_REUSE_Pos (6U)
#define nRF24_FIFO_STATUS_TX_REUSE_Msk (1U << nRF24_FIFO_STATUS_TX_REUSE_Pos)
#define nRF24_FIFO_STATUS_TX_REUSE     nRF24_FIFO_STATUS_TX_REUSE_Msk

/** DYNPD bits ****************************************************************/

// Enable dynamic payload length data pipe 0, default 0
#define nRF24_DYNPD_DPL_P0_Pos (0U)
#define nRF24_DYNPD_DPL_P0_Msk (1U << nRF24_DYNPD_DPL_P0_Pos)
#define nRF24_DYNPD_DPL_P0     nRF24_DYNPD_DPL_P0_Msk

// Enable dynamic payload length data pipe 1, default 0
#define nRF24_DYNPD_DPL_P1_Pos (1U)
#define nRF24_DYNPD_DPL_P1_Msk (1U << nRF24_DYNPD_DPL_P1_Pos)
#define nRF24_DYNPD_DPL_P1     nRF24_DYNPD_DPL_P1_Msk

// Enable dynamic payload length data pipe 2, default 0
#define nRF24_DYNPD_DPL_P2_Pos (2U)
#define nRF24_DYNPD_DPL_P2_Msk (1U << nRF24_DYNPD_DPL_P2_Pos)
#define nRF24_DYNPD_DPL_P2     nRF24_DYNPD_DPL_P2_Msk

// Enable dynamic payload length data pipe 3, default 0
#define nRF24_DYNPD_DPL_P3_Pos (3U)
#define nRF24_DYNPD_DPL_P3_Msk (1U << nRF24_DYNPD_DPL_P3_Pos)
#define nRF24_DYNPD_DPL_P3     nRF24_DYNPD_DPL_P3_Msk

// Enable dynamic payload length data pipe 4, default 0
#define nRF24_DYNPD_DPL_P4_Pos (4U)
#define nRF24_DYNPD_DPL_P4_Msk (1U << nRF24_DYNPD_DPL_P4_Pos)
#define nRF24_DYNPD_DPL_P4     nRF24_DYNPD_DPL_P4_Msk

// Enable dynamic payload length data pipe 5, default 0
#define nRF24_DYNPD_DPL_P5_Pos (5U)
#define nRF24_DYNPD_DPL_P5_Msk (1U << nRF24_DYNPD_DPL_P5_Pos)
#define nRF24_DYNPD_DPL_P5     nRF24_DYNPD_DPL_P5_Msk

/** FEATURE bits **************************************************************/

// Enables the W_TX_PAYLOAD_NOACK command, default 0
#define nRF24_FEATURE_EN_DYN_ACK_Pos (0U)
#define nRF24_FEATURE_EN_DYN_ACK_Msk (1U << nRF24_FEATURE_EN_DYN_ACK_Pos)
#define nRF24_FEATURE_EN_DYN_ACK     nRF24_FEATURE_EN_DYN_ACK_Msk

// Enables Payload with ACK, default 0
#define nRF24_FEATURE_EN_ACK_PAY_Pos (1U)
#define nRF24_FEATURE_EN_ACK_PAY_Msk (1U << nRF24_FEATURE_EN_ACK_PAY_Pos)
#define nRF24_FEATURE_EN_ACK_PAY     nRF24_FEATURE_EN_ACK_PAY_Msk

// Enables Dynamic Payload Length, default 0
#define nRF24_FEATURE_EN_DPL_Pos (2U)
#define nRF24_FEATURE_EN_DPL_Msk (1U << nRF24_FEATURE_EN_DPL_Pos)
#define nRF24_FEATURE_EN_DPL     nRF24_FEATURE_EN_DPL_Msk

/** Enums *********************************************************************/

typedef enum {
    nRF24_CONFIG_CRC_OFF   = 0x0U,
    nRF24_CONFIG_CRC_1byte = nRF24_CONFIG_EN_CRC,
    nRF24_CONFIG_CRC_2byte = nRF24_CONFIG_EN_CRC|nRF24_CONFIG_CRCO,
} nRF24_CONFIG_CRC_t;

typedef enum {
    nRF24_RF_SETUP_RF_PWR_18dBm = 0x0U,
    nRF24_RF_SETUP_RF_PWR_12dBm = nRF24_RF_SETUP_RF_PWR_1,
    nRF24_RF_SETUP_RF_PWR_6dBm  = nRF24_RF_SETUP_RF_PWR_0,
    nRF24_RF_SETUP_RF_PWR_0dBm  = nRF24_RF_SETUP_RF_PWR_1|nRF24_RF_SETUP_RF_PWR_0,
} nRF24_RF_SETUP_RF_PWR_t;

typedef enum {
    nRF24_RF_SETUP_RF_DR_250kbps = nRF24_RF_SETUP_RF_DR_LOW,
    nRF24_RF_SETUP_RF_DR_1Mbps   = 0x0U,
    nRF24_RF_SETUP_RF_DR_2Mbps   = nRF24_RF_SETUP_RF_DR_HIGH,
} nRF24_RF_SETUP_RF_DR_t;

typedef enum {
    nRF24_SETUP_AW_AW_Invalid = 0x0U,
    nRF24_SETUP_AW_AW_3bytes  = nRF24_SETUP_AW_AW_0,
    nRF24_SETUP_AW_AW_4bytes  = nRF24_SETUP_AW_AW_1,
    nRF24_SETUP_AW_AW_5bytes  = nRF24_SETUP_AW_AW_1|nRF24_SETUP_AW_AW_0,
} nRF24_SETUP_AW_AW_t;

typedef enum {
    nRF24_SETUP_RETR_ARD_250us  = 0x0U,
    nRF24_SETUP_RETR_ARD_500us  = 0x1U,
    nRF24_SETUP_RETR_ARD_750us  = 0x2U,
    nRF24_SETUP_RETR_ARD_1000us = 0x3U,
    nRF24_SETUP_RETR_ARD_1250us = 0x4U,
    nRF24_SETUP_RETR_ARD_1500us = 0x5U,
    nRF24_SETUP_RETR_ARD_1750us = 0x6U,
    nRF24_SETUP_RETR_ARD_2000us = 0x7U,
    nRF24_SETUP_RETR_ARD_2250us = 0x8U,
    nRF24_SETUP_RETR_ARD_2500us = 0x9U,
    nRF24_SETUP_RETR_ARD_2750us = 0xAU,
    nRF24_SETUP_RETR_ARD_3000us = 0xBU,
    nRF24_SETUP_RETR_ARD_3250us = 0xCU,
    nRF24_SETUP_RETR_ARD_3500us = 0xDU,
    nRF24_SETUP_RETR_ARD_3750us = 0xEU,
    nRF24_SETUP_RETR_ARD_4000us = 0xFU,
} nRF24_SETUP_RETR_ARD_t;

typedef enum {
    nRF24_PIPE0 = (uint8_t)0x00, // pipe0
    nRF24_PIPE1 = (uint8_t)0x01, // pipe1
    nRF24_PIPE2 = (uint8_t)0x02, // pipe2
    nRF24_PIPE3 = (uint8_t)0x03, // pipe3
    nRF24_PIPE4 = (uint8_t)0x04, // pipe4
    nRF24_PIPE5 = (uint8_t)0x05, // pipe5
} nRF24_PIPE_t;

typedef void (*PE_nRF24_writeByte) (uint8_t reg, uint8_t byte);

typedef void (*PE_nRF24_writeData) (uint8_t reg, uint8_t *data, uint8_t size);

// TODO need both callbacks: readData, readByte, sendData, sendByte
typedef uint8_t (*PE_nRF24_readByte) (uint8_t reg);
typedef void (*PE_nRF24_readData) (uint8_t reg, uint8_t *data, uint8_t size);
typedef void (*PE_nRF24_sendByte) (uint8_t reg, uint8_t data);
typedef void (*PE_nRF24_sendData) (uint8_t reg, uint8_t *data, uint8_t size);

class PE_nRF24 {
    PE_nRF24_writeByte _writeByte;
    PE_nRF24_writeData _writeData;

    PE_nRF24_readByte _readByte;
    PE_nRF24_readData _readData;
    PE_nRF24_sendByte _sendByte;
    PE_nRF24_sendData _sendData;
public:
    void initialize();
    void flushRX();
    void flushTX();

    /**
     * Select RF channel
     *
     * @param channel
     */
    void setRFChannel(uint8_t channel);

    /**
     * Set TX power
     *
     * @param power
     */
    void setTXPower(nRF24_RF_SETUP_RF_PWR_t power);

    /**
     * Set data rate
     *
     * @param dataRate
     */
    void setDataRate(nRF24_RF_SETUP_RF_DR_t dataRate);

    /**
     * Set CRC enabled/disabled and select CRC size
     *
     * @param scheme
     */
    void setCRCScheme(nRF24_CONFIG_CRC_t scheme);

    void setAddressLength(uint8_t length);

    void setAddressPipe(nRF24_PIPE_t pipe, const uint8_t *address);

    /**
     * Read payload
     *
     * @param data
     * @param size
     */
    void readPayload(uint8_t *data, uint8_t *size);

    /**
     * Send payload
     *
     * @param data
     * @param size
     */
    void sendPayload(uint8_t *data, uint8_t size);
};

#endif //PE_NRF24_H
