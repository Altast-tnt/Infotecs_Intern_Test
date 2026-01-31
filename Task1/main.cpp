#include <iostream>
#include "SpiDriver.h"
#include "Eeprom25LC040A.h"

int main()
{
    // Инициализация драйвера с пинами
    SpiDriver spi(10, 11, 12, 13);
    spi.begin();

    // Создание объекта памяти
    Eeprom25LC040A eeprom(spi);

    std::cout << "--- DEMO: Writing data ---" << std::endl;
    uint8_t data[] = {0xAA, 0xBB}; // Пример данных
    eeprom.write(0, data, 2);

    std::cout << "\n--- DEMO: Reading data ---" << std::endl;
    uint8_t buffer[2];
    eeprom.read(0, buffer, 2);

    std::cout << "\nDemo complete (Output is 0 because no hardware attached)." << std::endl;


    return 0;
}
