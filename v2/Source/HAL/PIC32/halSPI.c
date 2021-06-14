#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halSPI.h"


#define __getRegisterPtr(spi)        ((SPIRegisters*)(_SPI1_BASE_ADDRESS + (spi * 0x00000200)))


SPIHandler halSPIInitialize(
    SPIData* data,
    const SPISettings *settings) {

    SPIHandler handler = data;
    handler->regs = __getRegisterPtr(settings->channel);
    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    return handler;
}


void halSPIDeinitialize(
    SPIHandler handler) {

}

void halSPISendBuffer(
    SPIHandler handler,
    uint8_t *data,
    uint32_t size) {

}