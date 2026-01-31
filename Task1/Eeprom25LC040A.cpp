#include <iostream>
#include "Eeprom25LC040A.h"

Eeprom25LC040A::Eeprom25LC040A(SpiDriver& driver)
    : m_driver(driver)
{

}

uint8_t Eeprom25LC040A::readStatus()
{
    m_driver.select();
    m_driver.transferByte(CMD_RDSR);
    uint8_t status = m_driver.transferByte(0x00);
    m_driver.deselect();
    return status;
}

void Eeprom25LC040A::sentCommandAndAddress(uint8_t command, uint16_t address)
{
    if ((address >> 8) & 1)
    {
        command |= (1 << 3);
    }

    m_driver.transferByte(command);
    m_driver.transferByte(address & 0xFF);
}

uint8_t Eeprom25LC040A::read(uint16_t address)
{
    m_driver.select();

    sentCommandAndAddress(CMD_READ, address);

    uint8_t receivedData = m_driver.transferByte(0x00);

    m_driver.deselect();
    return receivedData;
}

void Eeprom25LC040A::read(uint16_t address, uint8_t* buffer, size_t size)
{
    m_driver.select();

    sentCommandAndAddress(CMD_READ, address);

    for (size_t i = 0; i < size; ++i)
    {
        buffer[i] = m_driver.transferByte(0x00);
    }
    m_driver.deselect();

}


void Eeprom25LC040A::write(uint16_t address, uint8_t data)
{
    // Разрешение записи (Write Enable)
    m_driver.select();
    m_driver.transferByte(CMD_WREN);
    m_driver.deselect();

    // Операция записи
    m_driver.select();
    sentCommandAndAddress(CMD_WRITE, address);
    m_driver.transferByte(data);

    // Ожидание записи
    while (readStatus() & 1)
    {

    }

}

void Eeprom25LC040A::write(uint16_t address, const uint8_t* data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        write(address + i, data[i]);
    }
}

