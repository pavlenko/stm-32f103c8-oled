#ifndef PE_NRF24_H
#define PE_NRF24_H

#include <stdint.h>

// nRF24L0 instruction definitions
#define nRF24_CMD_R_REGISTER       (uint8_t)0x00 // Register read
#define nRF24_CMD_W_REGISTER       (uint8_t)0x20 // Register write
#define nRF24_CMD_R_RX_PAYLOAD     (uint8_t)0x61 // Read RX payload
#define nRF24_CMD_W_TX_PAYLOAD     (uint8_t)0xA0 // Write TX payload
#define nRF24_CMD_FLUSH_TX         (uint8_t)0xE1 // Flush TX FIFO
#define nRF24_CMD_FLUSH_RX         (uint8_t)0xE2 // Flush RX FIFO
#define nRF24_CMD_REUSE_TX_PL      (uint8_t)0xE3 // Reuse TX payload
#define nRF24_CMD_LOCK_UNLOCK      (uint8_t)0x50 // Lock/unlock exclusive features
#define nRF24_CMD_NOP              (uint8_t)0xFF // No operation (used for reading status register)

// nRF24L0 register definitions
#define nRF24_REG_CONFIG           (uint8_t)0x00 // Configuration register
#define nRF24_REG_EN_AA            (uint8_t)0x01 // Enable "Auto acknowledgment"
#define nRF24_REG_EN_RXADDR        (uint8_t)0x02 // Enable RX addresses
#define nRF24_REG_SETUP_AW         (uint8_t)0x03 // Setup of address widths
#define nRF24_REG_SETUP_RETR       (uint8_t)0x04 // Setup of automatic retransmit
#define nRF24_REG_RF_CH            (uint8_t)0x05 // RF channel
#define nRF24_REG_RF_SETUP         (uint8_t)0x06 // RF setup register
#define nRF24_REG_STATUS           (uint8_t)0x07 // Status register
#define nRF24_REG_OBSERVE_TX       (uint8_t)0x08 // Transmit observe register
#define nRF24_REG_RPD              (uint8_t)0x09 // Received power detector
#define nRF24_REG_RX_ADDR_P0       (uint8_t)0x0A // Receive address data pipe 0
#define nRF24_REG_RX_ADDR_P1       (uint8_t)0x0B // Receive address data pipe 1
#define nRF24_REG_RX_ADDR_P2       (uint8_t)0x0C // Receive address data pipe 2
#define nRF24_REG_RX_ADDR_P3       (uint8_t)0x0D // Receive address data pipe 3
#define nRF24_REG_RX_ADDR_P4       (uint8_t)0x0E // Receive address data pipe 4
#define nRF24_REG_RX_ADDR_P5       (uint8_t)0x0F // Receive address data pipe 5
#define nRF24_REG_TX_ADDR          (uint8_t)0x10 // Transmit address
#define nRF24_REG_RX_PW_P0         (uint8_t)0x11 // Number of bytes in RX payload in data pipe 0
#define nRF24_REG_RX_PW_P1         (uint8_t)0x12 // Number of bytes in RX payload in data pipe 1
#define nRF24_REG_RX_PW_P2         (uint8_t)0x13 // Number of bytes in RX payload in data pipe 2
#define nRF24_REG_RX_PW_P3         (uint8_t)0x14 // Number of bytes in RX payload in data pipe 3
#define nRF24_REG_RX_PW_P4         (uint8_t)0x15 // Number of bytes in RX payload in data pipe 4
#define nRF24_REG_RX_PW_P5         (uint8_t)0x16 // Number of bytes in RX payload in data pipe 5
#define nRF24_REG_FIFO_STATUS      (uint8_t)0x17 // FIFO status register
#define nRF24_REG_DYNPD            (uint8_t)0x1C // Enable dynamic payload length
#define nRF24_REG_FEATURE          (uint8_t)0x1D // Feature register

// Register bits definitions
#define nRF24_CONFIG_PRIM_RX       (uint8_t)0x01 // PRIM_RX bit in CONFIG register
#define nRF24_CONFIG_PWR_UP        (uint8_t)0x02 // PWR_UP bit in CONFIG register
#define nRF24_FLAG_RX_DR           (uint8_t)0x40 // RX_DR bit (data ready RX FIFO interrupt)
#define nRF24_FLAG_TX_DS           (uint8_t)0x20 // TX_DS bit (data sent TX FIFO interrupt)
#define nRF24_FLAG_MAX_RT          (uint8_t)0x10 // MAX_RT bit (maximum number of TX retransmits interrupt)

// Register masks definitions
#define nRF24_MASK_REG_MAP         (uint8_t)0x1F // Mask bits[4:0] for CMD_RREG and CMD_WREG commands
#define nRF24_MASK_CRC             (uint8_t)0x0C // Mask for CRC bits [3:2] in CONFIG register
#define nRF24_MASK_STATUS_IRQ      (uint8_t)0x70 // Mask for all IRQ bits in STATUS register
#define nRF24_MASK_RF_PWR          (uint8_t)0x06 // Mask RF_PWR[2:1] bits in RF_SETUP register
#define nRF24_MASK_RX_P_NO         (uint8_t)0x0E // Mask RX_P_NO[3:1] bits in STATUS register
#define nRF24_MASK_DATARATE        (uint8_t)0x28 // Mask RD_DR_[5,3] bits in RF_SETUP register
#define nRF24_MASK_EN_RX           (uint8_t)0x3F // Mask ERX_P[5:0] bits in EN_RXADDR register
#define nRF24_MASK_RX_PW           (uint8_t)0x3F // Mask [5:0] bits in RX_PW_Px register
#define nRF24_MASK_RETR_ARD        (uint8_t)0xF0 // Mask for ARD[7:4] bits in SETUP_RETR register
#define nRF24_MASK_RETR_ARC        (uint8_t)0x0F // Mask for ARC[3:0] bits in SETUP_RETR register
#define nRF24_MASK_RXFIFO          (uint8_t)0x03 // Mask for RX FIFO status bits [1:0] in FIFO_STATUS register
#define nRF24_MASK_TXFIFO          (uint8_t)0x30 // Mask for TX FIFO status bits [5:4] in FIFO_STATUS register
#define nRF24_MASK_PLOS_CNT        (uint8_t)0xF0 // Mask for PLOS_CNT[7:4] bits in OBSERVE_TX register
#define nRF24_MASK_ARC_CNT         (uint8_t)0x0F // Mask for ARC_CNT[3:0] bits in OBSERVE_TX register

// Retransmit delay
enum {
    nRF24_ARD_NONE   = (uint8_t)0x00, // Dummy value for case when retransmission is not used
    nRF24_ARD_250us  = (uint8_t)0x00,
    nRF24_ARD_500us  = (uint8_t)0x01,
    nRF24_ARD_750us  = (uint8_t)0x02,
    nRF24_ARD_1000us = (uint8_t)0x03,
    nRF24_ARD_1250us = (uint8_t)0x04,
    nRF24_ARD_1500us = (uint8_t)0x05,
    nRF24_ARD_1750us = (uint8_t)0x06,
    nRF24_ARD_2000us = (uint8_t)0x07,
    nRF24_ARD_2250us = (uint8_t)0x08,
    nRF24_ARD_2500us = (uint8_t)0x09,
    nRF24_ARD_2750us = (uint8_t)0x0A,
    nRF24_ARD_3000us = (uint8_t)0x0B,
    nRF24_ARD_3250us = (uint8_t)0x0C,
    nRF24_ARD_3500us = (uint8_t)0x0D,
    nRF24_ARD_3750us = (uint8_t)0x0E,
    nRF24_ARD_4000us = (uint8_t)0x0F
};

// Data rate
enum {
    nRF24_DR_250kbps = (uint8_t)0x20, // 250kbps data rate
    nRF24_DR_1Mbps   = (uint8_t)0x00, // 1Mbps data rate
    nRF24_DR_2Mbps   = (uint8_t)0x08  // 2Mbps data rate
};

// RF output power in TX mode
enum {
    nRF24_TXPWR_18dBm = (uint8_t)0x00, // -18dBm
    nRF24_TXPWR_12dBm = (uint8_t)0x02, // -12dBm
    nRF24_TXPWR_6dBm  = (uint8_t)0x04, //  -6dBm
    nRF24_TXPWR_0dBm  = (uint8_t)0x06  //   0dBm
};

// CRC encoding scheme
enum {
    nRF24_CRC_off   = (uint8_t)0x00, // CRC disabled
    nRF24_CRC_1byte = (uint8_t)0x08, // 1-byte CRC
    nRF24_CRC_2byte = (uint8_t)0x0c  // 2-byte CRC
};

// nRF24L01 power control
enum {
    nRF24_PWR_UP   = (uint8_t)0x02, // Power up
    nRF24_PWR_DOWN = (uint8_t)0x00  // Power down
};

// Transceiver mode
enum {
    nRF24_MODE_RX = (uint8_t)0x01, // PRX
    nRF24_MODE_TX = (uint8_t)0x00  // PTX
};

// Enumeration of RX pipe addresses and TX address
enum {
    nRF24_PIPE0  = (uint8_t)0x00, // pipe0
    nRF24_PIPE1  = (uint8_t)0x01, // pipe1
    nRF24_PIPE2  = (uint8_t)0x02, // pipe2
    nRF24_PIPE3  = (uint8_t)0x03, // pipe3
    nRF24_PIPE4  = (uint8_t)0x04, // pipe4
    nRF24_PIPE5  = (uint8_t)0x05, // pipe5
    nRF24_PIPETX = (uint8_t)0x06  // TX address (not a pipe in fact)
};

// State of auto acknowledgment for specified pipe
enum {
    nRF24_AA_OFF = (uint8_t)0x00,
    nRF24_AA_ON  = (uint8_t)0x01
};

// Status of the RX FIFO
enum {
    nRF24_STATUS_RXFIFO_DATA  = (uint8_t)0x00, // The RX FIFO contains data and available locations
    nRF24_STATUS_RXFIFO_EMPTY = (uint8_t)0x01, // The RX FIFO is empty
    nRF24_STATUS_RXFIFO_FULL  = (uint8_t)0x02, // The RX FIFO is full
    nRF24_STATUS_RXFIFO_ERROR = (uint8_t)0x03  // Impossible state: RX FIFO cannot be empty and full at the same time
};

// Status of the TX FIFO
enum {
    nRF24_STATUS_TXFIFO_DATA  = (uint8_t)0x00, // The TX FIFO contains data and available locations
    nRF24_STATUS_TXFIFO_EMPTY = (uint8_t)0x01, // The TX FIFO is empty
    nRF24_STATUS_TXFIFO_FULL  = (uint8_t)0x02, // The TX FIFO is full
    nRF24_STATUS_TXFIFO_ERROR = (uint8_t)0x03  // Impossible state: TX FIFO cannot be empty and full at the same time
};

// Result of RX FIFO reading
typedef enum {
    nRF24_RX_PIPE0  = (uint8_t)0x00, // Packet received from the PIPE#0
    nRF24_RX_PIPE1  = (uint8_t)0x01, // Packet received from the PIPE#1
    nRF24_RX_PIPE2  = (uint8_t)0x02, // Packet received from the PIPE#2
    nRF24_RX_PIPE3  = (uint8_t)0x03, // Packet received from the PIPE#3
    nRF24_RX_PIPE4  = (uint8_t)0x04, // Packet received from the PIPE#4
    nRF24_RX_PIPE5  = (uint8_t)0x05, // Packet received from the PIPE#5
    nRF24_RX_EMPTY  = (uint8_t)0xff  // The RX FIFO is empty
} nRF24_RXResult;


// Addresses of the RX_PW_P# registers
static const uint8_t nRF24_RX_PW_PIPE[6] = {
    nRF24_REG_RX_PW_P0,
    nRF24_REG_RX_PW_P1,
    nRF24_REG_RX_PW_P2,
    nRF24_REG_RX_PW_P3,
    nRF24_REG_RX_PW_P4,
    nRF24_REG_RX_PW_P5
};

// Addresses of the address registers
static const uint8_t nRF24_ADDR_REGS[7] = {
    nRF24_REG_RX_ADDR_P0,
    nRF24_REG_RX_ADDR_P1,
    nRF24_REG_RX_ADDR_P2,
    nRF24_REG_RX_ADDR_P3,
    nRF24_REG_RX_ADDR_P4,
    nRF24_REG_RX_ADDR_P5,
    nRF24_REG_TX_ADDR
};

//TODO example bits definition
//#define GPIO_CRL_MODE0_Pos                   (0U)
//#define GPIO_CRL_MODE0_Msk                   (0x3U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000003 */
//#define GPIO_CRL_MODE0                       GPIO_CRL_MODE0_Msk                /*!< MODE0[1:0] bits (Port x mode bits, pin 0) */
//#define GPIO_CRL_MODE0_0                     (0x1U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000001 */
//#define GPIO_CRL_MODE0_1                     (0x2U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000002 */

/** CONFIG bits ***************************************************************/

// 1 == PRX, 0 == PTX
#define nRF24_PRIM_RX_Pos (0U)
#define nRF24_PRIM_RX_Msk (1U << nRF24_PRIM_RX_Pos)
#define nRF24_PRIM_RX     nRF24_PRIM_RX_Msk

// 1 == POWER UP, 0 == POWER DOWN
#define nRF24_PWR_UP_Pos (1U)
#define nRF24_PWR_UP_Msk (1U << nRF24_PWR_UP_Pos)
#define nRF24_PWR_UP     nRF24_PWR_UP_Msk

// CRC encoding scheme
#define nRF24_CRCO_Pos (2U)
#define nRF24_CRCO_Msk (1U << nRF24_CRCO_Pos)
#define nRF24_CRCO     nRF24_CRCO_Msk

// Enable CRC
#define nRF24_EN_CRC_Pos (3U)
#define nRF24_EN_CRC_Msk (1U << nRF24_EN_CRC_Pos)
#define nRF24_EN_CRC     nRF24_EN_CRC_Msk

// Mask interrupt caused by MAX_RT
#define nRF24_MASK_MAX_RT_Pos (4U)
#define nRF24_MASK_MAX_RT_Msk (1U << nRF24_MASK_MAX_RT_Pos)
#define nRF24_MASK_MAX_RT     nRF24_MASK_MAX_RT_Msk

// Mask interrupt caused by TX_DS
#define nRF24_MASK_TX_DS_Pos (5U)
#define nRF24_MASK_TX_DS_Msk (1U << nRF24_MASK_TX_DS_Pos)
#define nRF24_MASK_TX_DS     nRF24_MASK_TX_DS_Msk

// Mask interrupt caused by RX_DR
#define nRF24_MASK_RX_DR_Pos (6U)
#define nRF24_MASK_RX_DR_Msk (1U << nRF24_MASK_RX_DR_Pos)
#define nRF24_MASK_RX_DR     nRF24_MASK_RX_DR_Msk

/** EN_AA bits ****************************************************************/

// Enable ‘Auto Acknowledgment’ Function
#define nRF24_ENAA_P0_Pos (0U)
#define nRF24_ENAA_P0_Msk (1U << nRF24_ENAA_P0_Pos)
#define nRF24_ENAA_P0     nRF24_ENAA_P0_Msk

#define nRF24_ENAA_P1_Pos (0U)
#define nRF24_ENAA_P1_Msk (1U << nRF24_ENAA_P1_Pos)
#define nRF24_ENAA_P1     nRF24_ENAA_P1_Msk

#define nRF24_ENAA_P2_Pos (0U)
#define nRF24_ENAA_P2_Msk (1U << nRF24_ENAA_P2_Pos)
#define nRF24_ENAA_P2     nRF24_ENAA_P2_Msk

#define nRF24_ENAA_P3_Pos (0U)
#define nRF24_ENAA_P3_Msk (1U << nRF24_ENAA_P3_Pos)
#define nRF24_ENAA_P3     nRF24_ENAA_P3_Msk

#define nRF24_ENAA_P4_Pos (0U)
#define nRF24_ENAA_P4_Msk (1U << nRF24_ENAA_P4_Pos)
#define nRF24_ENAA_P4     nRF24_ENAA_P4_Msk

#define nRF24_ENAA_P5_Pos (0U)
#define nRF24_ENAA_P5_Msk (1U << nRF24_ENAA_P5_Pos)
#define nRF24_ENAA_P5     nRF24_ENAA_P5_Msk

/** EN_RXADDR bits ************************************************************/

// Enable data pipe 0, default 1
#define nRF24_ERX_P0_Pos (0U)
#define nRF24_ERX_P0_Msk (1U << nRF24_ERX_P0_Pos)
#define nRF24_ERX_P0     nRF24_ERX_P0_Msk

// Enable data pipe 1, default 1
#define nRF24_ERX_P1_Pos (1U)
#define nRF24_ERX_P1_Msk (1U << nRF24_ERX_P1_Pos)
#define nRF24_ERX_P1     nRF24_ERX_P1_Msk

// Enable data pipe 2, default 0
#define nRF24_ERX_P2_Pos (2U)
#define nRF24_ERX_P2_Msk (1U << nRF24_ERX_P2_Pos)
#define nRF24_ERX_P2     nRF24_ERX_P2_Msk

// Enable data pipe 3, default 0
#define nRF24_ERX_P3_Pos (3U)
#define nRF24_ERX_P3_Msk (1U << nRF24_ERX_P3_Pos)
#define nRF24_ERX_P3     nRF24_ERX_P3_Msk

// Enable data pipe 4, default 0
#define nRF24_ERX_P4_Pos (4U)
#define nRF24_ERX_P4_Msk (1U << nRF24_ERX_P4_Pos)
#define nRF24_ERX_P4     nRF24_ERX_P4_Msk

// Enable data pipe 5, default 0
#define nRF24_ERX_P5_Pos (5U)
#define nRF24_ERX_P5_Msk (1U << nRF24_ERX_P5_Pos)
#define nRF24_ERX_P5     nRF24_ERX_P5_Msk

/** SETUP_AW bits *************************************************************/

// RX/TX Address field width
// 0x00 == Illegal
// 0x01 == 3 bytes
// 0x10 == 4 bytes
// 0x11 == 5 bytes (default)
#define nRF24_AW_Pos (0U)
#define nRF24_AW_Msk (0x3U << nRF24_AW_Pos)
#define nRF24_AW     nRF24_AW_Msk
#define nRF24_AW_0   (0x1U << nRF24_AW_Pos)
#define nRF24_AW_1   (0x2U << nRF24_AW_Pos)

/** SETUP_RETR bits ***********************************************************/

// Auto Retransmit Count, default 0b0000
#define nRF24_ARC_Pos (0U)
#define nRF24_ARC_Msk (0xFU << nRF24_ARC_Pos)
#define nRF24_ARC     nRF24_ARC_Msk
#define nRF24_ARC_0   (0x1U << nRF24_ARC_Pos)
#define nRF24_ARC_1   (0x2U << nRF24_ARC_Pos)
#define nRF24_ARC_2   (0x4U << nRF24_ARC_Pos)
#define nRF24_ARC_3   (0x8U << nRF24_ARC_Pos)

// Auto Re-transmit Delay, default 0b0011
#define nRF24_ARD_Pos (4U)
#define nRF24_ARD_Msk (0xFU << nRF24_ARD_Pos)
#define nRF24_ARD     nRF24_ARD_Msk
#define nRF24_ARD_0   (0x1U << nRF24_ARD_Pos)
#define nRF24_ARD_1   (0x2U << nRF24_ARD_Pos)
#define nRF24_ARD_2   (0x4U << nRF24_ARD_Pos)
#define nRF24_ARD_3   (0x8U << nRF24_ARD_Pos)

/** RF_CH bits ****************************************************************/

// Sets the frequency channel
#define nRF24_RF_CH_Pos (0U)
#define nRF24_RF_CH_Msk (0x3FU << nRF24_RF_CH_Pos)
#define nRF24_RF_CH     nRF24_RF_CH_Msk
#define nRF24_RF_CH_0   (0x01U << nRF24_RF_CH_Pos)
#define nRF24_RF_CH_1   (0x02U << nRF24_RF_CH_Pos)
#define nRF24_RF_CH_2   (0x04U << nRF24_RF_CH_Pos)
#define nRF24_RF_CH_3   (0x08U << nRF24_RF_CH_Pos)
#define nRF24_RF_CH_4   (0x10U << nRF24_RF_CH_Pos)
#define nRF24_RF_CH_5   (0x20U << nRF24_RF_CH_Pos)

/** RF_SETUP bits *************************************************************/

// ONLY FOR nRF24L01
// Setup LNA gain
#define nRF24_LNA_HCURR_Pos (0U)
#define nRF24_LNA_HCURR_Msk (1U << nRF24_LNA_HCURR_Pos)
#define nRF24_LNA_HCURR     nRF24_LNA_HCURR_Msk

// Set RF output power in TX mode
#define nRF24_RF_PWR_Pos (1U)
#define nRF24_RF_PWR_Msk (0x3U << nRF24_RF_PWR_Pos)
#define nRF24_RF_PWR     nRF24_RF_PWR_Msk
#define nRF24_RF_PWR_0   (0x1U << nRF24_RF_PWR_Pos)
#define nRF24_RF_PWR_1   (0x2U << nRF24_RF_PWR_Pos)

// Select between the high speed data rates: 0x1 == 2 Mbps, 0x0 == 1 Mbps
#define nRF24_RF_DR_HIGH_Pos (3U)
#define nRF24_RF_DR_HIGH_Msk (1U << nRF24_RF_DR_HIGH_Pos)
#define nRF24_RF_DR_HIGH     nRF24_RF_DR_HIGH_Msk

// Force PLL lock signal. Only used in test
#define nRF24_PLL_LOCK_Pos (4U)
#define nRF24_PLL_LOCK_Msk (1U << nRF24_PLL_LOCK_Pos)
#define nRF24_PLL_LOCK     nRF24_PLL_LOCK_Msk

// ONLY FOR nRF24L01+
// Set RF Data Rate to 250kbps
#define nRF24_RF_DR_LOW_Pos (5U)
#define nRF24_RF_DR_LOW_Msk (1U << nRF24_RF_DR_LOW_Pos)
#define nRF24_RF_DR_LOW     nRF24_RF_DR_LOW_Msk

// ONLY FOR nRF24L01+
// Enables continuous carrier transmit when high
#define nRF24_CONT_WAVE_Pos (7U)
#define nRF24_CONT_WAVE_Msk (1U << nRF24_CONT_WAVE_Pos)
#define nRF24_CONT_WAVE     nRF24_CONT_WAVE_Msk

/** STATUS bits ***************************************************************/

// TX FIFO full flag
#define nRF24_TX_FULL_Pos (0U)
#define nRF24_TX_FULL_Msk (1U << nRF24_TX_FULL_Pos)
#define nRF24_TX_FULL     nRF24_TX_FULL_Msk

// Data pipe number for the payload
#define nRF24_RX_P_NO_Pos (1U)
#define nRF24_RX_P_NO_Msk (0x7U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO     nRF24_RX_P_NO_Msk
#define nRF24_RX_P_NO_0   (0x01U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO_1   (0x02U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO_2   (0x04U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO_3   (0x08U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO_4   (0x10U << nRF24_RX_P_NO_Pos)
#define nRF24_RX_P_NO_5   (0x20U << nRF24_RX_P_NO_Pos)

// Maximum number of TX retries interrupt
#define nRF24_MAX_RT_Pos (4U)
#define nRF24_MAX_RT_Msk (1U << nRF24_MAX_RT_Pos)
#define nRF24_MAX_RT     nRF24_MAX_RT_Msk

// Data Sent TX FIFO interrupt
#define nRF24_TX_DS_Pos (5U)
#define nRF24_TX_DS_Msk (1U << nRF24_TX_DS_Pos)
#define nRF24_TX_DS     nRF24_TX_DS_Msk

// Data Ready RX FIFO interrupt
#define nRF24_RX_DR_Pos (6U)
#define nRF24_RX_DR_Msk (1U << nRF24_RX_DR_Pos)
#define nRF24_RX_DR     nRF24_RX_DR_Msk

/** OBSERVE_TX bits ***********************************************************/

// Count resent packets
#define nRF24_ARC_CNT_Pos (0U)
#define nRF24_ARC_CNT_Msk (0xFU << nRF24_ARC_CNT_Pos)
#define nRF24_ARC_CNT     nRF24_ARC_CNT_Msk
#define nRF24_ARC_CNT_0   (0x1U << nRF24_ARC_CNT_Pos)
#define nRF24_ARC_CNT_1   (0x2U << nRF24_ARC_CNT_Pos)
#define nRF24_ARC_CNT_2   (0x4U << nRF24_ARC_CNT_Pos)
#define nRF24_ARC_CNT_3   (0x8U << nRF24_ARC_CNT_Pos)

// Count lost packets
#define nRF24_PLOS_CNT_Pos (4U)
#define nRF24_PLOS_CNT_Msk (0xFU << nRF24_PLOS_CNT_Pos)
#define nRF24_PLOS_CNT     nRF24_PLOS_CNT_Msk
#define nRF24_PLOS_CNT_0   (0x1U << nRF24_PLOS_CNT_Pos)
#define nRF24_PLOS_CNT_1   (0x2U << nRF24_PLOS_CNT_Pos)
#define nRF24_PLOS_CNT_2   (0x4U << nRF24_PLOS_CNT_Pos)
#define nRF24_PLOS_CNT_3   (0x8U << nRF24_PLOS_CNT_Pos)

class PE_nRF24 {
public:
    void initialize();
    void flushRX();
    void flushTX();
};

#endif //PE_NRF24_H
