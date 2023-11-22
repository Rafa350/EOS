#pragma once
#ifndef __eosDevice_SSD1306__
#define __eosDevice_SSD1306__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/htlI2C.h"


namespace eos {

    class Device_SSD1306 {
        public:
            virtual ~Device_SSD1306() = default;

            virtual void hardwareReset() = 0;
            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    };
    

    class Device_SSD1306_SPI final: public Device_SSD1306 {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinDC;
            htl::gpio::Pin *_pinRST;
            htl::spi::SPIDevice *_devSPI;
            
        public:
            Device_SSD1306_SPI();
            ~Device_SSD1306_SPI();
            
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinDC, htl::spi::SPIDevice *devSPI, htl::gpio::Pin *pinRST = nullptr);
            void deinitialize();
            
            void hardwareReset() override;

            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };


    class Device_SSD1306_I2C final: public Device_SSD1306 {

    };
}


#endif // __eosDevice_SSD1306__
