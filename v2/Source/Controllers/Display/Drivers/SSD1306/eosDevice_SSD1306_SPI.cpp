#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SSD1306_SPI_Device::SSD1306_SPI_Device() :
    _pinCS {nullptr}, 
    _pinDC {nullptr},
    _devSPI {nullptr} {
    
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
SSD1306_SPI_Device::~SSD1306_SPI_Device() {
    
    deinitialize();               
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    pinCS: El pin CS (Chip Select)
/// \param    pinDC: El pin DC (Data/Command)
/// \param    devSPI: El dispositiu SPI
///
void SSD1306_SPI_Device::initialize(
    htl::gpio::Pin *pinCS, 
    htl::gpio::Pin *pinDC,
    htl::spi::SPIDevice *devSPI) {

    _pinCS = pinCS;
    _pinDC = pinDC;
    _devSPI = devSPI;
    
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void SSD1306_SPI_Device::deinitialize() {
    
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de comandes
/// \param    cmd: La comanda.
///
void SSD1306_SPI_Device::writeCommand(
    uint8_t cmd) {

    _pinDC->clear();
    _pinCS->clear();
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de dades.
/// \brief    data: Les dades.
///
void SSD1306_SPI_Device::writeData(
    uint8_t data) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, 1);
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: El tasmany de les dades.
///
void SSD1306_SPI_Device::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize);
    _pinCS->set();
}
