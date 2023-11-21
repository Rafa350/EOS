#pragma once
#ifndef __eosDriver_SSD1306__
#define __eosDriver_SSD1306__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

    class SSD1306_Device {
        public:
            virtual ~SSD1306_Device() = default;
            virtual void hardwareReset() = 0;
            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    };
    
    class SSD1306_SPI_Device final: public SSD1306_Device {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinDC;
            htl::gpio::Pin *_pinRST;
            htl::spi::SPIDevice *_devSPI;
            
        public:
            SSD1306_SPI_Device();
            ~SSD1306_SPI_Device();
            
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinDC, htl::spi::SPIDevice *devSPI, htl::gpio::Pin *pinRST = nullptr);
            void deinitialize();
            
            void hardwareReset() override;

            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
}


#endif // __eosDevice_SSD1306__
