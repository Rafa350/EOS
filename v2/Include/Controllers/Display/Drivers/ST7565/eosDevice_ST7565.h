#pragma once
#ifndef __eosDevice_ST7565__
#define __eosDevice_ST7565__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
    class Device_ST7565 {
        public:
            virtual ~Device_ST7565() = default;

            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    };
    
    class Device_ST7565_SPI final: public Device_ST7565 {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinA0;
            htl::gpio::Pin *_pinRST;
            htl::spi::SPIDevice *_devSPI;
            
        public:
            Device_ST7565_SPI();

            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinA0, htl::gpio::Pin *pinRST, htl::spi::SPIDevice *devSPI);
            void deinitialize() override;

            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
    
    class Device_ST7565_8080_Port final: public Device_ST7565 {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinA0;
            htl::gpio::Pin *_pinRST;
            htl::gpio::Port *_portD;
            htl::gpio::Pin *_pinWR;
            htl::gpio::Pin *_pinRD;
            
        public:
            Device_ST7565_8080_Port();
        
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinA0, htl::gpio::Pin *pinRST, 
                htl::gpio::Port *portD, htl::gpio::Pin *pinWR, htl::gpio::Pin *pinRD);
            void deinitialize() override;
        
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };

    class Device_ST7565_8080_Pin final: public Device_ST7565 {
        private:
            htl::gpio::Pin *_pinCS;
            htl::gpio::Pin *_pinA0;
            htl::gpio::Pin *_pinRST;
            htl::gpio::Pin *_pinD0;
            htl::gpio::Pin *_pinD1;
            htl::gpio::Pin *_pinD2;
            htl::gpio::Pin *_pinD3;
            htl::gpio::Pin *_pinD4;
            htl::gpio::Pin *_pinD5;
            htl::gpio::Pin *_pinD6;
            htl::gpio::Pin *_pinD7;
            htl::gpio::Pin *_pinWR;
            htl::gpio::Pin *_pinRD;
            
        public:
            Device_ST7565_8080_Pin();
        
            void initialize(htl::gpio::Pin *pinCS, htl::gpio::Pin *pinA0, htl::gpio::Pin *pinRST, 
                htl::gpio::Pin *pinD0, htl::gpio::Pin *pinD1, htl::gpio::Pin *pinD2, htl::gpio::Pin *pinD3, 
                htl::gpio::Pin *pinD4, htl::gpio::Pin *pinD5, htl::gpio::Pin *pinD6, htl::gpio::Pin *pinD7, 
                htl::gpio::Pin *pinWR, htl::gpio::Pin *pinRD);
            void deinitialize() override;
        
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
}


#endif // __eosDevice_ST7565__
