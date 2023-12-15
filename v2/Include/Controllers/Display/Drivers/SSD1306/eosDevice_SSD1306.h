#pragma once
#ifndef __eosDevice_SSD1306__
#define __eosDevice_SSD1306__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

    class Device_SSD1306 {
        private:
            Device_SSD1306(const Device_SSD1306 &) = delete;
            Device_SSD1306 & operator = (const Device_SSD1306 &) = delete;
            
        protected:
            Device_SSD1306() = default;

        public:
            virtual ~Device_SSD1306() = default;

            virtual void hardwareReset() = 0;

            virtual void writeCommand(const uint8_t *data, uint16_t dataSize) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
            void writeScript(const uint8_t *script, uint16_t scriptSize);
    };
    

    class Device_SSD1306_SPI: public Device_SSD1306 {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;

        private:
            Pin const * _pinCS;
            Pin const * _pinDC;
            Pin const * _pinRST;
            DevSPI *_devSPI;
            
        protected:
            Device_SSD1306_SPI();
            
        public:
            ~Device_SSD1306_SPI();
            
            void initialize(Pin *pinCS, Pin *pinDC, DevSPI *devSPI, Pin *pinRST = nullptr);
            void deinitialize();
            
            void hardwareReset() override;
            
            void writeCommand(const uint8_t *data, uint16_t dataSize) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };
    
    
    template <uint8_t id_>
    class DeviceX_SSD1306_SPI final: public Device_SSD1306_SPI {
        private:
            static DeviceX_SSD1306_SPI _instance;
            
        public:
            static constexpr uint8_t id = id_;
            static constexpr DeviceX_SSD1306_SPI *pInst = &_instance;
            static constexpr DeviceX_SSD1306_SPI &rInst = _instance;
            
        private:
            inline DeviceX_SSD1306_SPI() :
                Device_SSD1306_SPI() {
            }
    };

    template <uint8_t id_>
	DeviceX_SSD1306_SPI<id_> DeviceX_SSD1306_SPI<id_>::_instance;

}


#endif // __eosDevice_SSD1306__
