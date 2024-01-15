#pragma once
#ifndef __eosDevice_SSD1306__
#define __eosDevice_SSD1306__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

    /// \brief Clase que representa un dispositiu SSD1306 generic
    //
    class Device_SSD1306 {
        private:
            Device_SSD1306(const Device_SSD1306 &) = delete;
            Device_SSD1306 & operator = (const Device_SSD1306 &) = delete;
            
        protected:
            Device_SSD1306();

            void writeScript(const uint8_t *script, uint16_t scriptSize);

        public:
            virtual ~Device_SSD1306() = default;

            virtual void writeCommand(const uint8_t *data, uint16_t dataSize) = 0;
            virtual void writeData(const uint8_t *data, uint16_t dataSize) = 0;
    };
    

    /// \brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI
    //
    class Device_SSD1306_SPI: public Device_SSD1306 {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;
            struct CreateParams {
                Pin *pinCS;
                Pin *pinDC;
                Pin *pinRST;
                DevSPI devSPI;
            };

        private:
            Pin const * const _pinCS;
            Pin const * const _pinDC;
            Pin const * const _pinRST;
            DevSPI * const _devSPI;
            
        public:
            Device_SSD1306_SPI(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI);
            Device_SSD1306_SPI(const CreateParams *params);
            ~Device_SSD1306_SPI();

            void initialize(const uint8_t *script, uint16_t scriptSize);
            void deinitialize();
            
            void writeCommand(const uint8_t *data, uint16_t dataSize) override;
            void writeData(const uint8_t *data, uint16_t dataSize) override;
    };

}


#endif // __eosDevice_SSD1306__
