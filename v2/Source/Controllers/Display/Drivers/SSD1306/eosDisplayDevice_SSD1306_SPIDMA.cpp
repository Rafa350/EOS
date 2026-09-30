module;


#include "eos.h"
#include "HTL/htlGPIO.h"


export module Eos.Controllers.Display.Drivers.SSD1306.SPIDMA;


export import Eos.Controllers.Display.Drivers.SSD1306.SPI;

import Eos.Types;
import Eos.Hardware.SPI;
import Eos.Hardware.DMA;


export namespace eos {

    /// @brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI-DMA
    //
    class DisplayDevice_SSD1306_SPIDMA: public DisplayDevice_SSD1306_SPI {
        public:
            using DevDMA = eos::hardware::dma::DMADevice;

        private:
            DevDMA * const _devDMA;

        public:
            DisplayDevice_SSD1306_SPIDMA(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI, DevDMA *devDMA);

            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    pinCS: El pin CS
/// @param    pinDC: El pin DC
/// @param    pinRST: El pin RST
/// @param    devSPI: El dispositiu SPI
/// @param    devDMA: El dispositiu DMA
///
DisplayDevice_SSD1306_SPIDMA::DisplayDevice_SSD1306_SPIDMA(
    Pin *pinCS,
    Pin *pinDC,
    Pin *pinRST,
    DevSPI *devSPI,
    DevDMA *devDMA) :

    DisplayDevice_SSD1306_SPI {pinCS, pinDC, pinRST, devSPI},

    _devDMA {devDMA} {

}


/// ----------------------------------------------------------------------
/// @brief    Escriu un bloc de dades en el registre de dades.
/// @brief    data: Les dades.
/// @param    dataSize: Tamany de les dades en bytes.
///
void DisplayDevice_SSD1306_SPIDMA::writeData(
    const UInt8 *data,
    UInt32 dataSize) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit_DMA(_devDMA, data, dataSize);
    _pinCS->set();
}
