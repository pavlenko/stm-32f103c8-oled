#include "PE_nRF24.h"

void PE_nRF24::initialize() {
    // Write to registers their initial values
    nRF24_WriteReg(nRF24_REG_CONFIG, 0x08);
    nRF24_WriteReg(nRF24_REG_EN_AA, 0x3F);
    nRF24_WriteReg(nRF24_REG_EN_RXADDR, 0x03);
    nRF24_WriteReg(nRF24_REG_SETUP_AW, 0x03);
    nRF24_WriteReg(nRF24_REG_SETUP_RETR, 0x03);
    nRF24_WriteReg(nRF24_REG_RF_CH, 0x02);
    nRF24_WriteReg(nRF24_REG_RF_SETUP, 0x0E);
    nRF24_WriteReg(nRF24_REG_STATUS, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P0, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P1, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P2, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P3, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P4, 0x00);
    nRF24_WriteReg(nRF24_REG_RX_PW_P5, 0x00);
    nRF24_WriteReg(nRF24_REG_DYNPD, 0x00);
    nRF24_WriteReg(nRF24_REG_FEATURE, 0x00);

    // Clear the FIFO's
    this->flushRX();
    this->flushTX();

    // Clear any pending interrupt flags
    nRF24_ClearIRQFlags();

    // Deassert CSN pin (chip release)
    nRF24_CSN_H();
}

void PE_nRF24::flushRX() {
    nRF24_WriteReg(nRF24_CMD_FLUSH_RX, nRF24_CMD_NOP);
}

void PE_nRF24::flushTX() {
    nRF24_WriteReg(nRF24_CMD_FLUSH_TX, nRF24_CMD_NOP);
}
