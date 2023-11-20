#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosSDD1306_Device.h"


using namespace eos;


SSD1306_SPI_Device::SSD1306_SPI_Device() :
    _pinCS {nullptr}, 
    _pinDS {nullptr},
    _pinRST {nullptr},
    _devSPI {nullptr} {
    
}


SSD1306_SPI_Device::~SSD1305_SPI_Device() {
    
    deinitialize();               
}


void SSD1306_SPI_Device::initialize(
    htl::gpio::Pin *pinCS, 
    htl::gpio::Pin *pinDS, 
    htl::gpio::Pin *pinRST, 
    htp::spi::SPIDevice *devSPI) {

    _pinCS = pinCS;
    _pinDS = pinDS;
    _pinRST = pinRST;
    _devSPI = devSPI;
    
    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        _pinRST->set();
    }
}


void SSD1306_SPI_Device::deinitialize() {
    
    _pinCS->set();
}


void SSD1306_SPI_Device::writeCommand(
    uint8_t cmd) {

    _pinDS->clear();
    _pinCS->clear;
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


void SSD1306_SPI_Device::writeData(
    uint8_t data) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(&data, 1);
    _pinCS->set();
}


void SSD1306_SPI_Device::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataLength);
    _pinCS->set();
}
