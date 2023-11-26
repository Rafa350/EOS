#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Device_SSD1306_SPI::Device_SSD1306_SPI() :
    Device_SSD1306(),

    _pinCS {nullptr}, 
    _pinDC {nullptr},
    _pinRST {nullptr},
    _devSPI {nullptr} {
    
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
    Pin *pinCS,
    Pin *pinDC,
    DevSPI *devSPI,
    Pin *pinRST) {

    _pinCS = pinCS;
    _pinDC = pinDC;
    _pinRST = pinRST;
    _devSPI = devSPI;
    
    _pinCS->set();
    if (_pinRST != nullptr)
        _pinRST->set();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void Device_SSD1306_SPI::deinitialize() {
    
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Reseteja el dispoditiu.
///
void Device_SSD1306_SPI::hardwareReset() {

    if (_pinRST != nullptr) {
        _pinCS->set();
        _pinRST->clear();
        htl::waitTicks(100);
        _pinRST->set();
        htl::waitTicks(300);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de comandes
/// \param    cmd: La comanda.
///
void Device_SSD1306_SPI::writeCommand(
    uint8_t cmd) {

    _pinDC->clear();
    _pinCS->clear();
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void Device_SSD1306_SPI::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize);
    _pinCS->set();
}
