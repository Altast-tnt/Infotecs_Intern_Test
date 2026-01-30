#ifndef EEPROM25LC040A_H
#define EEPROM25LC040A_H

#include <cstdint>
#include "SpiDriver.h"

/**
 * @brief Класс для работы с SPI EEPROM памятью серии 25LC040A.
 *
 * Предоставляет высокоуровневый интерфейс для чтения и записи данных,
 * скрывая детали протокола SPI и битовых операций.
 * Объем памяти: 4 Кбит (512 байт).
 */
class Eeprom25LC040A
{
private:
    SpiDriver& m_driver; ///< Ссылка на драйвер SPI

    // Команды микросхемы (Instruction Set)
    static const uint8_t CMD_READ  = 0x03; ///< Чтение данных (0000 A8 011)
    static const uint8_t CMD_WRITE = 0x02; ///< Запись данных (0000 A8 010)
    static const uint8_t CMD_WRDI  = 0x04; ///< Запрет записи (Reset Write Enable Latch)
    static const uint8_t CMD_WREN  = 0x06; ///< Разрешение записи (Set Write Enable Latch)
    static const uint8_t CMD_RDSR  = 0x05; ///< Чтение регистра статуса
    static const uint8_t CMD_WRSR  = 0x01; ///< Запись регистра статуса
public:
    /**
     * @brief Конструктор.
     * @param driver Ссылка на инициализированный драйвер SPI
     */
    Eeprom25LC040A(SpiDriver& driver);

    /**
     * @brief Чтение одного байта из памяти.
     *
     * Автоматически обрабатывает 9-битный адрес, встраивая старший бит
     * в команду чтения согласно спецификации 25LC040A.
     *
     * @param address Адрес ячейки памяти (от 0 до 511).
     * @return uint8_t Значение байта по указанному адресу.
     */
    uint8_t readByte(uint16_t address);

    /**
     * @brief Запись одного байта в память.
     *
     * Выполняет последовательность: WREN -> Выбор чипа -> Команда+Адрес -> Данные.
     *
     * @param address Адрес ячейки памяти (от 0 до 511).
     * @param data Байт данных для записи.
     */
    void writeByte(uint16_t address, uint8_t data);
};

#endif // EEPROM25LC040A_H
