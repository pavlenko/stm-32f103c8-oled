#include "PE_nRF24.h"

void PE_nRF24::initialize() {
    // Write to registers their initial values

    // TODO maybe create config structure
    _writeByte(nRF24_CONFIG, nRF24_CONFIG_MASK_MAX_RT);
    _writeByte(nRF24_EN_AA, nRF24_EN_AA_ENAA_P0|nRF24_EN_AA_ENAA_P1|nRF24_EN_AA_ENAA_P2|nRF24_EN_AA_ENAA_P3|nRF24_EN_AA_ENAA_P4|nRF24_EN_AA_ENAA_P5);
    _writeByte(nRF24_EN_RXADDR, nRF24_EN_RXADDR_ERX_P0|nRF24_EN_RXADDR_ERX_P1);
    _writeByte(nRF24_SETUP_AW, nRF24_SETUP_AW_AW_0|nRF24_SETUP_AW_AW_1);
    _writeByte(nRF24_SETUP_RETR, nRF24_SETUP_RETR_ARC_0|nRF24_SETUP_RETR_ARC_1);
    _writeByte(nRF24_RF_CH, 0x02);
    _writeByte(nRF24_RF_SETUP, nRF24_RF_SETUP_RF_DR_2Mbps|nRF24_RF_SETUP_RF_PWR_0dBm);
    _writeByte(nRF24_STATUS, 0x00);
    _writeByte(nRF24_RX_PW_P0, 0x00);
    _writeByte(nRF24_RX_PW_P1, 0x00);
    _writeByte(nRF24_RX_PW_P2, 0x00);
    _writeByte(nRF24_RX_PW_P3, 0x00);
    _writeByte(nRF24_RX_PW_P4, 0x00);
    _writeByte(nRF24_RX_PW_P5, 0x00);
    _writeByte(nRF24_DYNPD, 0x00);
    _writeByte(nRF24_FEATURE, 0x00);

    // Clear the FIFO's
    this->flushRX();
    this->flushTX();

    // Clear any pending interrupt flags
    nRF24_ClearIRQFlags();

    // Deassert CSN pin (chip release)
    nRF24_CSN_H();
}

void PE_nRF24::flushRX() {
    _writeByte(nRF24_CMD_FLUSH_RX, nRF24_CMD_NOP);
}

void PE_nRF24::flushTX() {
    _writeByte(nRF24_CMD_FLUSH_TX, nRF24_CMD_NOP);
}
