#include "PE_nRF24.h"

static uint8_t nRF24_ReadReg(uint8_t reg) {
    uint8_t value;

    nRF24_CSN_L();
    nRF24_LL_RW(reg & nRF24_MASK_REG_MAP);
    value = nRF24_LL_RW(nRF24_CMD_NOP);
    nRF24_CSN_H();

    return value;
}

static void nRF24_ReadMBReg(uint8_t reg, uint8_t *pBuf, uint8_t count) {
    nRF24_CSN_L();
    nRF24_LL_RW(reg);
    while (count--) {
        *pBuf++ = nRF24_LL_RW(nRF24_CMD_NOP);
    }
    nRF24_CSN_H();
}


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

void PE_nRF24::readPayload(uint8_t *data, uint8_t *size) {
    uint8_t pipe;
    uint8_t status;

    // Read the STATUS register
    _read(nRF24_CMD_R_REGISTER(nRF24_STATUS), &status, 1);

    // Extract a payload pipe number from the STATUS register
    pipe = (status & nRF24_STATUS_RX_P_NO_Msk) >> nRF24_STATUS_RX_P_NO_Pos;

    // RX FIFO empty?
    if (pipe < 6) {
        // Get payload length
        _read(nRF24_RX_PW_P0 + pipe, size, 1);

        // Read a payload from the RX FIFO
        if (*size) {
            _read(nRF24_CMD_R_RX_PAYLOAD, data, *size);
        }
    } else {
        // The RX FIFO is empty
        *size = 0;
    }
}

void PE_nRF24::sendPayload(uint8_t *data, uint8_t size) {
    _send(nRF24_CMD_W_TX_PAYLOAD, data, size);
}