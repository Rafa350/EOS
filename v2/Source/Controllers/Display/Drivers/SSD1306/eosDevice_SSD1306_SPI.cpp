#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Device_SSD1306_SPI::Device_SSD1306_SPI(
    Pin *pinCS,
    Pin *pinDC,
    Pin *pinRST,
    DevSPI *devSPI) :

    Device_SSD1306(),

    _pinCS {pinCS},
    _pinDC {pinDC},
    _pinRST {pinRST},
    _devSPI {devSPI} {
    
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Device_SSD1306_SPI::~Device_SSD1306_SPI() {
    
    deinitialize();               
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    pinCS: El pin CS (Chip Select)
/// \param    pinDC: El pin DC (Data/Command)
/// \param    devSPI: El dispositiu SPI
/// \param    pinRST: El pin RST (Hardware reset)
///
void Device_SSD1306_SPI::initialize(
    const uint8_t *script,
    unsigned scriptSize) {

    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        htl::waitTicks(100);
        _pinRST->set();
        htl::waitTicks(300);
    }

    writeScript(script, scriptSize);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void Device_SSD1306_SPI::deinitialize() {
    
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de comanda.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void Device_SSD1306_SPI::writeCommand(
    const uint8_t *data,
    unsigned dataSize) {

    _pinDC->clear();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, Tick(1000));
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void Device_SSD1306_SPI::writeData(
    const uint8_t *data, 
    unsigned dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, Tick(1000));
    _pinCS->set();
}
