#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosDevice_7565_SPI.h"


namespace eos;


Device_ST7565_SPI::Device_ST7565_SPI():
    _pinCS {nullptr},
    _pinDC {nullptr},
    _pinRST {nullptr},
    _devSPI {nullptr} {

}


void Device_ST7565_SPI::initialize(
    htl::gpio::Pin *pinCS,
    htl::gpio::Pin *pinDC,
    htl::gpio::Pin *pinRST,
    htl::spi::SPIDevice *devSPI) {

    _pinCS = pinCS;
    _pinDC = pinDC;
    _pinRST = pinRST;
    _devSPI = devSPI;

    _pinCS.set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        _pinRST->set();
    }
}


void Device_ST7565_SPI::deinitialize() {

    _pinCS->set();
}



void Device_ST7565_SPI::writeCommand(
    uint8_t cmd) {
    
    _pinDC->clear();
    _pinCS->clear;
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


void Device_ST7565_SPI::writeData(
    uint8_t data) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, 1);
    _pinCS->set();
}


void Device_ST7565_SPI::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, dataSize);
    _pinCS->set();
}
