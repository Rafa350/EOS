module;


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/htlDMA.h"


export module Eos.Controllers.Display.SSD1306.SPIDMA;


import Eos.Controllers.Display.SSD1306.SPI;


export namespace eos {

    /// \brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI-DMA
    //
    class DisplayDevice_SSD1306_SPIDMA: public DisplayDevice_SSD1306_SPI {
        public:
            using DevDMA = htl::dma::DMADevice;

        private:
            DevDMA * const _devDMA;

        public:
            DisplayDevice_SSD1306_SPIDMA(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI, DevDMA *devDMA);

            void writeData(const uint8_t *data, size_t dataSize) override;
    };
}



/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pinCS: El pin CS
/// \param    pinDC: El pin DC
/// \param    pinRST: El pin RST
/// \param    devSPI: El dispositiu SPI
/// \param    devDMA: El dispositiu DMA
///
eos::DisplayDevice_SSD1306_SPIDMA::Device_SSD1306_SPIDMA(
    Pin *pinCS,
    Pin *pinDC,
    Pin *pinRST,
    DevSPI *devSPI,
    DevDMA *devDMA) :

    DisplayDevice_SSD1306_SPI {pinCS, pinDC, pinRST, devSPI},

    _devDMA {devDMA} {

}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void eos::DisplayDevice_SSD1306_SPIDMA::writeData(
    const uint8_t *data,
    size_t dataSize) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit_DMA(_devDMA, data, dataSize);
    _pinCS->set();
}
