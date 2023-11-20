#include "eos.h"
#include "Controllers/Display/eos7565_Device.h"


namespace eos;


ST7565_SPI_Device::ST7565_SPI_Device():
    _pinCS {nullptr},
    _pinDC {nullptr},
    _pinRST {nullptr},
    _devSPI {nullptr} {

}


void ST7565_SPI_Device::initialize(
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


void ST7565_SPI_Device::deinitialize() {

    _pinCS->set();
}



void ST7565_SPI_Device::writeCommand(
    uint8_t cmd) {
    
    _pinDC->clear();
    _pinCS->clear;
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


void ST7565_SPI_Device::writeData(
    uint8_t data) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, 1);
    _pinCS->set();
}


void ST7565_SPI_Device::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, dataSize);
    _pinCS->set();
}
