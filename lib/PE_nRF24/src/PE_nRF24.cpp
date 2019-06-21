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
    //nRF24_ClearIRQFlags();

    // Deassert CSN pin (chip release)
    //nRF24_CSN_H();
}

void PE_nRF24::flushRX()
{
    _sendByte(nRF24_CMD_FLUSH_RX, nRF24_CMD_NOP);
}

void PE_nRF24::flushTX()
{
    _sendByte(nRF24_CMD_FLUSH_TX, nRF24_CMD_NOP);
}

void PE_nRF24::setRFChannel(uint8_t channel)
{
    _sendByte(nRF24_RF_CH, channel);
}

void PE_nRF24::setTXPower(nRF24_RF_SETUP_RF_PWR_t power)
{
    // Get RF_SETUP
    uint8_t rfSetup = _readByte(nRF24_CMD_R_REGISTER(nRF24_RF_SETUP));

    // Modify RF_PWR bits
    rfSetup &= ~nRF24_RF_SETUP_RF_PWR;
    rfSetup |= power;

    // Set RF_SETUP
    _sendByte(nRF24_CMD_W_REGISTER(nRF24_RF_SETUP), rfSetup);
}

void PE_nRF24::setDataRate(nRF24_RF_SETUP_RF_DR_t dataRate)
{
    // Get RF_SETUP
    uint8_t rfSetup = _readByte(nRF24_CMD_R_REGISTER(nRF24_RF_SETUP));

    // Modify RF_DR bits
    rfSetup &= ~(nRF24_RF_SETUP_RF_DR_HIGH|nRF24_RF_SETUP_RF_DR_LOW);
    rfSetup |= dataRate;

    // Set RF_SETUP
    _sendByte(nRF24_CMD_W_REGISTER(nRF24_RF_SETUP), rfSetup);
}

void PE_nRF24::setCRCScheme(nRF24_CONFIG_CRC_t scheme)
{
    // Get CONFIG register
    uint8_t config = _readByte(nRF24_CMD_R_REGISTER(nRF24_CONFIG));

    // Update EN_CRC[3] and CRCO[2] bits
    config &= ~(nRF24_CONFIG_EN_CRC|nRF24_CONFIG_CRCO);
    config |= scheme;

    // Get CONFIG register
    _sendByte(nRF24_CMD_R_REGISTER(nRF24_CONFIG), config);
}

void PE_nRF24::readPayload(uint8_t *data, uint8_t *size)
{
    // Read the STATUS register
    uint8_t status = _readByte(nRF24_CMD_R_REGISTER(nRF24_STATUS));

    // Extract a payload pipe number from the STATUS register
    uint8_t pipe = (status & nRF24_STATUS_RX_P_NO_Msk) >> nRF24_STATUS_RX_P_NO_Pos;

    // RX FIFO empty?
    if (pipe < 6) {
        // Get payload length
        *size = _readByte(nRF24_RX_PW_P0 + pipe);

        // Read a payload from the RX FIFO
        if (*size) {
            _readData(nRF24_CMD_R_RX_PAYLOAD, data, *size);
        }
    } else {
        // The RX FIFO is empty
        *size = 0;
    }
}

void PE_nRF24::sendPayload(uint8_t *data, uint8_t size)
{
    _sendData(nRF24_CMD_W_TX_PAYLOAD, data, size);
}