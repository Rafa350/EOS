#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halI2C.h"
#include "HAL/PIC32/halSYS.h"

#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


/// ----------------------------------------------------------------------
/// \brief   Inicialitza el modul I2C
/// \param   info: Informacio d'inicialitzacio.
///
I2CHandler halI2CMasterInitialize(
    I2CData *data,
    const I2CMasterSettings *settings) {

    I2CHandler handler = data;

    switch(settings->channel) {
        case HAL_I2C_CHANNEL_1:
            handler->regs = (I2CRegisters*) _I2C1_BASE_ADDRESS;
            break;

        case HAL_I2C_CHANNEL_2:
            handler->regs = (I2CRegisters*) _I2C2_BASE_ADDRESS;
            break;
    }

    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    // Inicialitzacio general del modul
    //
    //PLIB_I2C_SlaveClockStretchingEnable((I2C_MODULE_ID) handler->regs);
    handler->regs->I2CxCON.STREN = 1;
    //PLIB_I2C_SMBDisable(handler->regs);
    handler->regs->I2CxCON.SMEN = 0;
    //PLIB_I2C_StopInIdleEnable(handler->regs);
    handler->regs->I2CxCON.SIDL = 1;

    // Selecciona la frequencia de treball
    //
    if (settings->baudRate > 100000) {
        //PLIB_I2C_HighFrequencyEnable(handler->regs);
        handler->regs->I2CxCON.DISSLW = 1;
    }
    else {
        //PLIB_I2C_HighFrequencyDisable(handler->regs);
        handler->regs->I2CxCON.DISSLW = 0;
    }
    PLIB_I2C_BaudRateSet((I2C_MODULE_ID) handler->regs, halSYSGetPeripheralClockFrequency(), settings->baudRate);

    // Activa el modul
    //
    handler->regs->I2CxCON.ON = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    handler: Handler del modul.
///
void halI2CMasterDeinitialize(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    handler->regs->I2CxCON.ON = 0;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia START
/// \param   handler: Handler del modul.
///
void halI2CMasterStart(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    handler->regs->I2CxCON.SEN = 1;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia STOP
/// \param   handler: Handler del modul.
///
void halI2CMasterStop(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    handler->regs->I2CxCON.PEN = 1;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia RESTART
/// \param   channel: El identificador del modul.
///
void halI2CMasterStartRepeat(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    handler->regs->I2CxCON.RSEN = 1;
}


bool halI2CIsBusIdle(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    return PLIB_I2C_BusIsIdle((I2C_MODULE_ID)handler->regs);
}


bool halI2CArbitrationLossHasOccurred(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    return PLIB_I2C_ArbitrationLossHasOccurred((I2C_MODULE_ID)handler->regs);
}


void halI2CArbitrationLossClear(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    PLIB_I2C_ArbitrationLossClear((I2C_MODULE_ID)handler->regs);
}


void halI2CTransmitterByteSend(
    I2CHandler handler,
    uint8_t data) {

    eosAssert(handler != NULL);

    PLIB_I2C_TransmitterByteSend((I2C_MODULE_ID)handler->regs, data);
}


bool halI2CTransmitterByteWasAcknowledged(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    return PLIB_I2C_TransmitterByteWasAcknowledged((I2C_MODULE_ID)handler->regs);
}


uint8_t halI2CReceivedByteGet(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    return PLIB_I2C_ReceivedByteGet((I2C_MODULE_ID)handler->regs);
}


void halI2CMasterReceiverClock1Byte(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    PLIB_I2C_MasterReceiverClock1Byte((I2C_MODULE_ID)handler->regs);
}


void halI2CReceivedByteAcknowledge(
    I2CHandler handler,
    bool ack) {

    eosAssert(handler != NULL);

    PLIB_I2C_ReceivedByteAcknowledge((I2C_MODULE_ID)handler->regs, ack);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fuincio d'interrupcio.
/// \param    handler: Handler del modul.
/// \param    function: La funcio.
/// \param    params: Els parametres.
///
void halI2CSetInterruptFunction(
    I2CHandler handler,
    I2CInterruptFunction function,
    void* params) {

    eosAssert(handler != NULL);

    handler->isrFunction = function;
    handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcionsd el modul.
/// \param    handler: Handler del modul.
/// \params   sources: Els events a activat
///
void halI2CEnableInterrupts(
    I2CHandler handler,
    uint32_t sources) {

    switch ((uint32_t) handler->regs) {
        case _I2C1_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC0bits.I2C1MIE = 1;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC0bits.I2C1SIE = 1;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC0bits.I2C1BIE = 1;
            break;

#ifdef _I2C2
        case _I2C2_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC1bits.I2C2MIE = 1;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC1bits.I2C2SIE = 1;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC1bits.I2C2BIE = 1;
            break;
#endif
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcionsd el modul.
/// \param    handler: Handler del modul.
/// \params   sources: Els events a activat
///
uint32_t halI2CDisableInterrupts(
    I2CHandler handler,
    uint32_t sources) {

    switch ((uint32_t)handler->regs) {
        case _I2C1_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC0bits.I2C1MIE = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC0bits.I2C1SIE = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC0bits.I2C1BIE = 0;
            break;

#ifdef _I2C2
        case _I2C2_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC1bits.I2C2MIE = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC1bits.I2C2SIE = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC1bits.I2C2BIE = 0;
            break;
#endif
    }

    return 0;
}


void halI2CClearInterruptFlags(
    I2CHandler handler,
    uint32_t sources) {

    switch ((uint32_t) handler->regs) {
        case _I2C1_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IFS0bits.I2C1BIF = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IFS0bits.I2C1SIF = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IFS0bits.I2C1MIF = 0;
            break;

#ifdef _I2C2
        case _I2C2_BASE_ADDRESS:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IFS1bits.I2C2MIF = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IFS1bits.I2C2SIF = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IFS1bits.I2C2BIF = 0;
            break;
#endif
    }
}


bool halI2CGetInterruptFlag(
    I2CHandler handler,
    uint32_t source) {

    switch ((uint32_t) handler->regs) {
        case _I2C1_BASE_ADDRESS:
            switch (source) {
                case HAL_I2C_EVENT_MASTER:
                    return IFS0bits.I2C1BIF;

                case HAL_I2C_EVENT_SLAVE:
                    return IFS0bits.I2C1SIF;

                case HAL_I2C_EVENT_BUS:
                    return IFS0bits.I2C1MIF;
            }
            break;

#ifdef _I2C2
        case _I2C2_BASE_ADDRESS:
            switch (source) {
                case HAL_I2C_EVENT_MASTER:
                    return IFS1bits.I2C2MIF;

                case HAL_I2C_EVENT_SLAVE:
                    return IFS1bits.I2C2SIF;

                case HAL_I2C_EVENT_BUS:
                    return IFS1bits.I2C2BIF;
            }
            break;
#endif
    }

    return false;
}


/// ----------------------------------------------------------------------
/// \brief    Crida a la funcio callback de la interrupcio.
/// \param    i2cId: identificacod del modul.
///
void halI2CInterruptHandler(
    I2CHandler handler) {

    eosAssert(handler != NULL);

    // Comprova si es un event MASTER
    //
    if (halI2CGetInterruptFlag(handler, HAL_I2C_EVENT_MASTER)) {

        if (handler->isrFunction != NULL)
            handler->isrFunction(handler, handler->isrParams);

        halI2CClearInterruptFlags(handler, HAL_I2C_EVENT_MASTER);
    }
}
