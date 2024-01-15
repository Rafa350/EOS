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

        protected:
            void writeScript(const uint8_t *script, uint16_t scriptSize);
            
        public:
            virtual ~Device_ST7565() = default;
            
            virtual void writeCommand(const uint8_t *cmd, uint16_t cmdSize) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
    };
    
    
    class Device_ST7565_SPI final: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;
            using DevSPI = htl::spi::SPIDevice;
            struct CreateParams {
                Pin *pinCS;
                Pin *pinA0;
                Pin *pinRST;
                DevSPI devSPI;
            };

        private:
            const Pin * const _pinCS;
            const Pin * const _pinA0;
            const Pin * const _pinRST;
            DevSPI * const _devSPI;
            
        public:
            Device_ST7565_SPI(Pin *pinCS, Pin *pinA0, in *pinRST, DevSPI *devSPI);
            Device_ST7565_SPI(const CreateParams *params);

            void initialize(const uint8_t *script, uint16_t scriptSize);
            void deinitialize();

            void writeCommand(const uint8_t *cmd, uint16_t cmdSize) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
    
    
    class Device_ST7565_8080_Port: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;
            using Port = htl::gpio::Port;

        private:
            const Pin * const _pinCS;
            const Pin * const _pinA0;
            const Pin * const _pinRST;
            const Port * const _portData;
            const Pin * const _pinWR;
            const Pin * const _pinRD;
            
        public:
            Device_ST7565_8080_Port(Pin *pinCS, Pin *pinA0, Pin *pinRST,
                Port *portData, Pin *pinWR, Pin *pinRD);
        
            void initialize(const uint8_t *script, uint16_t scriptSize);
            void deinitialize();
        
            void writeCommand(const uint8_t *cmd, uint16_t cmdSize) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };


    class Device_ST7565_8080_Pin: public Device_ST7565 {
        public:
            using Pin = htl::gpio::Pin;

        private:
            const Pin * const _pinCS;
            const Pin * const _pinA0;
            const Pin * const _pinRST;
            const Pin * const _pinD0;
            const Pin * const _pinD1;
            const Pin * const _pinD2;
            const Pin * const _pinD3;
            const Pin * const _pinD4;
            const Pin * const _pinD5;
            const Pin * const _pinD6;
            const Pin * const _pinD7;
            const Pin * const _pinWR;
            const Pin * const _pinRD;
            
        public:
            Device_ST7565_8080_Pin(Pin *pinCS, Pin *pinA0, Pin *pinRST,
                Pin *pinD0, Pin *pinD1, Pin *pinD2, Pin *pinD3,
                Pin *pinD4, Pin *pinD5, Pin *pinD6, Pin *pinD7,
                Pin *pinWR, Pin *pinRD);
        
            void initialize(const uint8_t *script, uint16_t scriptSize);
            void deinitialize();

            void writeCommand(const uint8_t *cmd, uint16_t cmdSize) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
}


#endif // __eosDevice_ST7565__
