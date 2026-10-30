module Eos.Controllers.Display.Drivers.SSD1306;


using namespace eos;
using namespace eos::hardware::dma;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    pinCS: El pin CS
/// @param    pinDC: El pin DC
/// @param    pinRST: El pin RST
/// @param    devSPI: El dispositiu SPI
/// @param    devDMA: El dispositiu DMA
///
DisplayDevice_SSD1306_SPIDMA::DisplayDevice_SSD1306_SPIDMA(
    PinDevice *pinCS,
    PinDevice *pinDC,
    PinDevice *pinRST,
    SPIDevice *devSPI,
    DMADevice *devDMA) :

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
