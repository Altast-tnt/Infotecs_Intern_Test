#include <iostream>
#include "Eeprom25LC040A.h"

Eeprom25LC040A::Eeprom25LC040A(SpiDriver& driver)
    : m_driver(driver)
{

}

uint8_t Eeprom25LC040A::readByte(uint16_t address)
{
    m_driver.select();
    //uint8_t cmd = CMD_READ | 512;
    m_driver.deselect();
    return ;
}

void Eeprom25LC040A::writeByte(uint16_t address, uint8_t data)
{

}

