#include <iostream>
#include <iomanip>
#include "SpiDriver.h"

SpiDriver::SpiDriver(uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin, uint8_t csPin)
    : m_mosi(mosiPin), m_miso(misoPin), m_sck(sckPin), m_cs(csPin)
{

}

void SpiDriver::begin()
{
    setPin(m_cs, 1);
    setPin(m_sck, 0);
    setPin(m_mosi, 0);
}

void SpiDriver::select()
{
    setPin(m_cs, 0);
}

void SpiDriver::deselect()
{
    setPin(m_cs, 1);
}

void SpiDriver::setPin(uint8_t pin, bool level) {
    // Для проверки корректности установки пинов
    // std::cout << "Pin " << (int)pin << " set to " << level << std::endl;
}

bool SpiDriver::readPin(uint8_t pin) {
    return 0;
}

uint8_t SpiDriver::transferByte(uint8_t byteToSend)
{
    // Вывод в HEX формате данные отправки
    std::cout << "[SPI] Sending: 0x"
              << std::hex << std::uppercase << (int)byteToSend << std::dec << std::endl;
    uint8_t receivedByte = 0;

    for (int i = 7; i >= 0; --i)
    {
        bool bitValue = (byteToSend >> i) & 1;
        setPin(m_mosi, bitValue);

        setPin(m_sck, 1);

        if (readPin(m_miso))
        {
            receivedByte |= (1 << i);
        }

        setPin(m_sck, 0);
    }
    return receivedByte;
}
