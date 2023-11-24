#pragma once
#ifndef __eosDevice_ST7565__
#define __eosDevice_ST7565__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
    class Device_ST7565 {
        private:
            Device_ST7565(const Device_ST7565 &) = delete;
            Device_ST7565 & operator = (const Device_ST7565 &) = delete;
        
        public:
            virtual ~Device_ST7565() = default;

            virtual void writeCommand(uint8_t cmd) = 0;
            virtual void writeData(uint8_t data) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    };
    
    
    class Device_ST7565_SPI final: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;
            using DevSPI = htl::spi::SPIDevice;

        private:
            Pin const * _pinCS;
            Pin const * _pinA0;
            Pin const * _pinRST;
            DevSPI * _devSPI;
            
        protected:
            Device_ST7565_SPI();

        public:
            void initialize(Pin *pinCS, Pin *pinA0, in *pinRST, DevSPI *devSPI);
            void deinitialize() override;

            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
    
    
    class Device_ST7565_8080_Port: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;
            using Port = htl::gpio::Port;

        private:
            Pin const * _pinCS;
            Pin const * _pinA0;
            Pin const * _pinRST;
            Port const * _portD;
            Pin const * _pinWR;
            Pin const * _pinRD;
            
        protected:
            Device_ST7565_8080_Port();
        
        public:
            void initialize(Pin *pinCS, Pin *pinA0, Pin *pinRST,
                Port *portD, Pin *pinWR, Pin *pinRD);
            void deinitialize() override;
        
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };


    class Device_ST7565_8080_Pin: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;

        private:
            Pin * _pinCS;
            Pin * _pinA0;
            Pin * _pinRST;
            Pin * _pinD0;
            Pin * _pinD1;
            Pin * _pinD2;
            Pin * _pinD3;
            Pin * _pinD4;
            Pin * _pinD5;
            Pin * _pinD6;
            Pin * _pinD7;
            Pin * _pinWR;
            Pin * _pinRD;
            
        protected:
            Device_ST7565_8080_Pin();
        
        public:
            void initialize(Pin *pinCS, Pin *pinA0, Pin *pinRST,
                Pin *pinD0, Pin *pinD1, Pin *pinD2, Pin *pinD3,
                Pin *pinD4, Pin *pinD5, Pin *pinD6, Pin *pinD7,
                Pin *pinWR, Pin *pinRD);
            void deinitialize() override;
        
            void writeCommand(uint8_t cmd) override;
            void writeData(uint8_t data) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
}


#endif // __eosDevice_ST7565__
