#pragma once
#igndef __ST7565_Device__
#define __ST7565_Device__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
    class ST7565_Device {
        public:
            virtual ~ST7565_Device() ) default;
            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    }
    
    class ST7565_SPI_Device final: public ST7565_Device {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinA0;
            htl::gpio::Pin *_pinRST;
            htl::spi::SPIDevice *_devSPI;
            
        public:
            ST7565_SPI_Device();

            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinA0, htl::gpio::Pin *pinRST, htl::spi::SPIDevice *devSPI);
            void deinitialize() override;

            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    }
    
    class ST7565_8080_Device final: public ST7565_Device {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinA0;
            htl::gpio::Pin *_pinRST;
            htl::gpio::Pin *_pinRD;
            htl::gpio::Pin *_pinWR;
            htl::gpio::Port *_portD;
            
        public:
            ST7565_8080_Device();
        
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinA0, htl::gpio::Pin *pinRST, 
                htl::gpio::Port *portD, htl::gpio::Pin *pinRD, htl::gpio::Pin *pinWR);
            void deinitialize() override;
        
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    }
}


#endif // __ST7565_Device__