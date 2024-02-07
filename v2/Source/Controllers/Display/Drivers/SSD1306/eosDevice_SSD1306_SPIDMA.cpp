#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pinCS: El pin CS
/// \param    pinDC: El pin DC
/// \param    pinRST: El pin RST
/// \param    devSPI: El dispositiu SPI
/// \param    devDMA: El dispositiu DMA
///
Device_SSD1306_SPIDMA::Device_SSD1306_SPIDMA(
    Pin *pinCS,
    Pin *pinDC,
    Pin *pinRST,
    DevSPI *devSPI,
    DevDMA *devDMA) :

    Device_SSD1306_SPI(pinCS, pinDC, pinRST, devSPI),

    _devDMA {devDMA} {
    
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void Device_SSD1306_SPIDMA::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmitDMA(_devDMA, data, dataSize);
    _pinCS->set();
}
