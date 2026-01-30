#include <iostream>
#include "SpiDriver.h"

int main()
{
    SpiDriver spi(10, 11, 12, 13);

    spi.begin();
    std::cout << "Starting SPI transfer..." << std::endl;

    spi.select();

    uint8_t response = spi.transferByte(170);
    spi.deselect();

    std::cout << "Transfer complete. Received: " << (int)response << std::endl;

    return 0;
}
