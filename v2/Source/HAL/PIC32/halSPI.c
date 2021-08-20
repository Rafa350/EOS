#include <proc/p32mx460f512l.h>

#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halSYS.h"
#include "HAL/PIC32/halSPI.h"


#define __getRegisterPtr(spi)     ((halSPIRegisters*)(_SPI1_BASE_ADDRESS + (spi * 0x00000200)))


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul SPI
/// \param    data: Buffer de dades.
/// \param    settings: Parametres d'inicialitzacio.
///
halSPIHandler halSPIInitialize(
    halSPIData* data,
    const halSPISettings* settings) {

    halSPIHandler handler = data;
    handler->regs = __getRegisterPtr(settings->channel);
    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    // Desactiva el modul
    //
    handler->regs->SPIxCON.ON = 0;

    // Modus MASTER/SLAVE
    handler->regs->SPIxCON.MSTEN = (settings->options & HAL_SPI_MS_mask) == HAL_SPI_MS_MASTER;

    // Tamany de paraula
    //
    switch (settings->options & HAL_SPI_SIZE_mask) {
        case HAL_SPI_SIZE_8:
            handler->regs->SPIxCON.MODE16 = 0;
            handler->regs->SPIxCON.MODE32 = 0;
            break;

        case HAL_SPI_SIZE_16:
            handler->regs->SPIxCON.MODE16 = 1;
            handler->regs->SPIxCON.MODE32 = 0;
            break;

        case HAL_SPI_SIZE_32:
            handler->regs->SPIxCON.MODE16 = 0;
            handler->regs->SPIxCON.MODE32 = 1;
            break;
    }

    // Desactiva el modul en IDLE
    //
    handler->regs->SPIxCON.SIDL = 1;

    // Parametres del rellotge
    //
    handler->regs->SPIxCON.CKP = (settings->options & HAL_SPI_CPOL_mask) == HAL_SPI_CPOL_HIGH;
    handler->regs->SPIxCON.CKE = (settings->options & HAL_SPI_CPHA_mask) == HAL_SPI_CPHA_EDGE1;
    handler->regs->SPIxCON.SMP = 0;

    // Baudrate
    //
    uint32_t clockFrequency = halSYSGetPeripheralClockFrequency();
    uint32_t brg = (((clockFrequency / settings->baudRate) / 2) - 1);
    uint32_t baudHigh = clockFrequency / (2 * (brg + 1));
    uint32_t baudLow = clockFrequency / (2 * (brg + 2));
    uint32_t errorHigh = baudHigh - settings->baudRate;
    uint32_t errorLow = settings->baudRate - baudLow;
    if (errorHigh > errorLow)
        brg++;
    handler->regs->SPIxBRG = brg;

    handler->regs->SPIxSTAT.SPIROV = 0;

    // Activa el modul
    //
    handler->regs->SPIxCON.ON = 1;

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI
/// \param    handler: El handler del modul.
///
void halSPIDeinitialize(
    halSPIHandler handler) {

    handler->regs->SPIxCON.ON = 0;

}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un byte.
/// \param    handler: El handler del modul.
/// \param    data: Les dasdes a transmetre.
///
void halSendData(
    halSPIHandler handler,
    uint8_t data) {

    handler->regs->SPIxBUF = data;
}


/// ----------------------------------------------------------------------
/// \brief    Transmitreix un buffer de bytes.
/// \param    handler: El handler del modul.
/// \param    data: El buffer de dades.
/// \param    size: El tamany del buffer en bytes.
/// \param    blockTime: Temps maxim de bloqueig.
///
void halSPISendBuffer(
    halSPIHandler handler,
    const uint8_t* data,
    int size,
    int blockTime) {

    while (size--) {
        while (!handler->regs->SPIxSTAT.SPITBE)
            continue;
        handler->regs->SPIxBUF = *data++;
    }
}
