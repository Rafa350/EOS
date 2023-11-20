#pragma once
#ifndef __SSD1306_Device__
#define __SSD1306_Device__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h


namespace eos {

    class SSD1306_Device {
        public:
            virtual ~SSD1306_Device() = default;
            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    }
    
    class SSD1306_SPI_Device final: public SSD1306_Device {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinDC;
            htl::gpio::Pin *_pinRST;
            htp::spi::DevSPI *_devSPI;
            
        public:
            SSD1306_SPI_Device();
            ~SSD1305_SPI_Device();
            
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinDS, htl::gpio::Pin *pinRST, htp::spi::SPIDevice *devSPI);
            void deinitialize();
            
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    }
}


#endif
