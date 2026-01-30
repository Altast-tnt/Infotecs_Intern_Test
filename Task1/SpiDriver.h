#ifndef SPIDRIVER_H
#define SPIDRIVER_H

#include <cstdint>

/**
 * @brief Класс для программной реализации интерфейса SPI (Bit-banging).
 *
 * Позволяет управлять внешними устройствами по протоколу SPI,
 * используя обычные GPIO пины микроконтроллера.
 */
class SpiDriver
{
private:
    uint8_t m_mosi, m_miso, m_sck, m_cs;

    // Вспомогательные функции для работы с пинами
    void setPin(uint8_t pin, bool level);
    bool readPin(uint8_t pin);

public:
    /**
     * @brief Конструктор драйвера с настройкой пинов.
     *
     * Создает экземпляр драйвера и запоминает, какие пины используются.
     *
     * @param mosiPin Номер пина выхода данных (Master Out Slave In).
     * @param misoPin Номер пина входа данных (Master In Slave Out).
     * @param sckPin  Номер пина тактового сигнала (Serial Clock).
     * @param csPin   Номер пина выбора устройства (Chip Select).
     */
    SpiDriver(uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin, uint8_t csPin);

    /**
     * @brief Инициализация пинов.
     *
     * Устанавливает начальные значения на линиях SCK, MOSI и CS.
     */
    void begin();

    /**
     * @brief Выбор ведомого устройства (Chip Select).
     *
     * Устанавливает линию CS в низкий уровень (Low), активируя устройство.
     */
    void select();

    /**
     * @brief Завершение обмена (Chip Deselect).
     *
     * Устанавливает линию CS в высокий уровень (High), отключая устройство.
     */
    void deselect();

    /**
     * @brief Одновременная передача и прием байта.
     *
     * Реализует протокол SPI Mode 0 (CPOL=0, CPHA=0).
     * Данные передаются от старшего бита к младшему (MSB First).
     *
     * @param byteToSend Байт, который нужно отправить устройству.
     * @return uint8_t Байт, полученный от устройства.
     */
    uint8_t transferByte(uint8_t byteToSend);

};
#endif // SPIDRIVER_H
