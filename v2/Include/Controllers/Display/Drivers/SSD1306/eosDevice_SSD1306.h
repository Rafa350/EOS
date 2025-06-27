#pragma once
#ifndef __eosDevice_SSD1306__
#define __eosDevice_SSD1306__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/htlDMA.h"


#define SSD1306_CMD_DISPLAY_ON              0xAF
#define SSD1306_CMD_DISPLAY_OFF             0xAE
#define SSD1306_CMD_SET_ADDRESSING_MODE     0x20
#define SSD1306_CMD_SET_COLUMN              0x21
#define SSD1306_CMD_SET_PAGE                0x22


namespace eos {

    /// \brief Clase que representa un dispositiu SSD1306 generic
    //
    class Device_SSD1306 {
        private:
            Device_SSD1306(const Device_SSD1306 &) = delete;
            Device_SSD1306 & operator = (const Device_SSD1306 &) = delete;

        protected:
            Device_SSD1306();

            void writeScript(const uint8_t *script, unsigned scriptSize);

        public:
            virtual ~Device_SSD1306() = default;

            virtual void writeCommand(const uint8_t *data, unsigned dataSize) = 0;
            virtual void writeData(const uint8_t *data, unsigned dataSize) = 0;
    };


    /// \brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI
    //
    class Device_SSD1306_SPI: public Device_SSD1306 {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;

        protected:
            Pin const * const _pinCS;
            Pin const * const _pinDC;
            Pin const * const _pinRST;
            DevSPI * const _devSPI;

        public:
            Device_SSD1306_SPI(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI);
            ~Device_SSD1306_SPI();

            void initialize(const uint8_t *script, unsigned scriptSize);
            void deinitialize();

            void writeCommand(const uint8_t *data, unsigned dataSize) override;
            void writeData(const uint8_t *data, unsigned dataSize) override;
    };


    /// \brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI-DMA
    //
#if HTL_SPI_OPTION_DMA == 1
    class Device_SSD1306_SPIDMA: public Device_SSD1306_SPI {
        public:
            using DevDMA = htl::dma::DMADevice;

        private:
            DevDMA * const _devDMA;

        public:
            Device_SSD1306_SPIDMA(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI, DevDMA *devDMA);

            void writeData(const uint8_t *data, unsigned dataSize) override;
    };
#endif
}


#endif // __eosDevice_SSD1306__
