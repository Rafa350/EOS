#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"


using namespace eos;


Device_ILI9341_SPI::Device_ILI9341_SPI():

    _pinCS {nullptr},
    _pinRS {nullptr},
    _pinRST {nullptr},
    _devSPI {nullptr} {

}


void Device_ILI9341_SPI::initialize(
    htl::gpio::Pin *pinCS,
    htl::gpio::Pin *pinRS,
    htl::spi::SPIDevice *devSPI,
    htl::gpio::Pin *pinRST) {

    _pinCS = pinCS;
    _pinRS = pinRS;
    _devSPI = devSPI;
    _pinRST = pinRST;

    _pinCS->set();
    if (_pinRST != nullptr)
        _pinRST->set();
}


void Device_ILI9341_SPI::deinitialize() {

    _pinCS->set();
}


void Device_ILI9341_SPI::hardwareReset() {

    _pinRST->clear();
    htl::waitTicks(10);
    _pinRST->set();
    htl::waitTicks(120);
}


void Device_ILI9341_SPI::writeCommand(
    uint8_t cmd) {

    _pinCS->clear();
    _pinRS->clear();
    _devSPI->transmit(&cmd, 1);
    _pinCS->set();
}


void Device_ILI9341_SPI::writeData(
    uint8_t data) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(&data, 1);
    _pinCS->set();
}


void Device_ILI9341_SPI::writeData(
    const uint8_t *data,
    uint16_t dataSize) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(data, dataSize);
    _pinCS->set();
}


