#ifndef EEPROM25LC040A_H
#define EEPROM25LC040A_H

#include <cstdint>
#include "SpiDriver.h"

/**
 * @brief Класс для работы с SPI EEPROM памятью серии 25LC040A.
 *
 * Предоставляет высокоуровневый интерфейс для чтения и записи данных
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

    //
    /**
     * @brief Вспомогательный метод для отправки команды и адреса
     *
     * Автоматически обрабатывает 9-битный адрес, встраивая старший бит
     * в команду чтения согласно спецификации 25LC040A.
     *
     * @param command Команда микросхемы (Instruction Set).
     * @param address Адрес ячейки памяти (от 0 до 511).
     *
     */
    void sendCommandAndAddress(uint8_t command, uint16_t address);

    // Чтение регистра статуса (RDSR)
    uint8_t readStatus();

public:
    /**
     * @brief Конструктор.
     * @param driver Ссылка на инициализированный драйвер SPI
     */
    Eeprom25LC040A(SpiDriver& driver);

    /**
     * @brief Чтение одного байта из памяти.
     *
     * @param address Адрес ячейки памяти (от 0 до 511).
     * @return uint8_t Прочитанный байт.
     */
    uint8_t read(uint16_t address);

    /**
     * @brief Чтение массива байт.
     *
     * Использует возможность микросхемы автоматически инкрементировать адрес.
     * Команда и адрес отправляются один раз, затем данные читаются потоком.
     *
     * @param address Начальный адрес чтения.
     * @param buffer Указатель на буфер, куда будут записаны данные.
     * @param size Количество байт, которые нужно прочитать.
     */
    void read(uint16_t address, uint8_t* buffer, size_t size);

    /**
     * @brief Запись одного байта в память.
     *
     * Выполняет полный цикл записи: WREN -> WRITE -> Ожидание завершения (Polling).
     *
     * @param address Адрес ячейки памяти (от 0 до 511).
     * @param data Байт данных для записи.
     */
    void write(uint16_t address, uint8_t data);

    /**
     * @brief Запись массива байт.
     *
     * Записывает данные побайтово (вызывая одиночную запись в цикле).
     *
     * @param address Начальный адрес записи.
     * @param data Указатель на массив данных для записи.
     * @param size Количество байт для записи.
     */
    void write(uint16_t address, const uint8_t* data, size_t size);
};

#endif // EEPROM25LC040A_H
