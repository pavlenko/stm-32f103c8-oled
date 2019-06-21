#include "PE_nRF24.h"

PE_nRF24 nRF24 = PE_nRF24();

int main()
{
    //TODO description about gpio

    nRF24.initialize(); // Initialize with defaults

    // Set RF channel
    nRF24.setRFChannel(40);

    // Set TX power for Auto-ACK (maximum, to ensure that transmitter will hear ACK reply)
    nRF24.setTXPower(nRF24_RF_SETUP_RF_PWR_0dBm);

    // Set data rate
    nRF24.setDataRate(nRF24_RF_SETUP_RF_DR_2Mbps);

    // Set CRC scheme
    nRF24.setCRCScheme(nRF24_CONFIG_CRC_2byte);

    // Set address width, its common for all pipes (RX and TX)
    nRF24.setAddressLength(3);

    // Configure RX PIPE
    static const uint8_t nRF24_ADDR[] = {'E', 'S', 'B'};
    nRF24.setAddressPipe(nRF24_PIPE1, nRF24_ADDR);

    //TODO configure & use
}
