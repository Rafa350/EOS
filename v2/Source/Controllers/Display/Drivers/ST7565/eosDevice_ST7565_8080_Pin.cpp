#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosST7565_Device.h"


namespace eos;
namespace htl::gpio;


Device_ST7565_8080_Pin::Device_ST7565_8080_Pin() :
    _pinCS {nullptr},
    _pinA0 {nullptr},
    _pinRST {nullptr},
    _pinRD {nullptr},
    _pinWR {nullptr} {
        
}


void Device_ST7565_8080_Pin::initialize(
    htl::gpio::Pin *pinCS, 
    htl::gpio::Pin *pinA0, 
    htl::gpio::Pin *pinRST, 
    htl::gpio::Port *portD, 
    htl::gpio::Pin *pinWR, 
    htl::gpio::Pin *pinRD) {
    
}


void Device_ST7565_8080_Pin::deinitialize() {
    
    _pinCS->set();
}


void Device_ST7565_8080_Pin::writeCommand(
    uint8_t cmd) {
        
}

void Device_ST7565_8080_Pin::writeData(
    uint8_t data) {
    
}


void Device_ST7565_8080_Pin::writeData(
    const uint8_t *data, 
    uint16_t dataSize) {
    
}
