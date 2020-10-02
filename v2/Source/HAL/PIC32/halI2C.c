#include "eos.h"
#include "HAL/PIC32/halI2C.h"
#include "HAL/PIC32/halSYS.h"

#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


typedef struct  __attribute__((packed , aligned(4))) {
   __I2C1CONbits_t I2CxCON;
   volatile uint32_t I2CxCONCLR;
   volatile uint32_t I2CxCONSET;
   volatile uint32_t I2CxCONINV;
   __I2C1STATbits_t I2CxSTAT;
   volatile uint32_t I2CxSTATCLR;
   volatile uint32_t I2CxSTATSET;
   volatile uint32_t I2CxSTATINV;
   volatile uint32_t I2CxADD;
   uint32_t DONTUSE1[3];
   volatile uint32_t I2CxMSK;
   uint32_t DONTUSE2[3];
   volatile uint32_t I2CxBRG;
   uint32_t DONTUSE3[3];
   volatile uint32_t I2CxTRN;
   uint32_t DONTUSE4[3];
   volatile uint32_t I2CxRCV;
   uint32_t DONTUSE5[3];
} I2CRegisters;

typedef struct {
    I2CInterruptFunction isrFunction;
    void* isrParams;
} I2CData;


static I2CData dataTbl[] = {
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL }    
};


extern void __ISR(_I2C_1_VECTOR, IPL2SOFT) isrI2C1Wrapper(void);
#ifdef _I2C2
extern void __ISR(_I2C_2_VECTOR, IPL2SOFT) isrI2C2Wrapper(void);
#endif
#ifdef _I2C3
extern void __ISR(_I2C_3_VECTOR, IPL2SOFT) isrI2C3Wrapper(void);
#endif
#ifdef _I2C4
extern void __ISR(_I2C_4_VECTOR, IPL2SOFT) isrI2C4Wrapper(void);
#endif
#ifdef _I2C5
extern void __ISR(_I2C_5_VECTOR, IPL2SOFT) isrI2C5Wrapper(void);
#endif

#define __getRegisterPtr(channel)      ((I2CRegisters*) channel)
#define __getDataPtr(channel)          ((I2CData*) &dataTbl[((channel - HAL_I2C_ADDR_1) / 0x200)])


/// ----------------------------------------------------------------------
/// \brief   Inicialitza el modul I2C
/// \param   info: Informacio d'inicialitzacio.
///
void halI2CMasterInitialize(
    const I2CMasterInitializeInfo* info) {
    
    I2CChannel channel = info->channel;
       
    // Inicialitzacio general del modul
    //
    PLIB_I2C_SlaveClockStretchingEnable(channel);
    PLIB_I2C_SMBDisable(channel);
    PLIB_I2C_HighFrequencyDisable(channel);
    PLIB_I2C_StopInIdleEnable(channel);

    // Selecciona la frequencia de treball
    //
    if (info->baudRate > 100000)
        PLIB_I2C_HighFrequencyEnable(channel);
    else
        PLIB_I2C_HighFrequencyDisable(channel);
    PLIB_I2C_BaudRateSet(channel, halSYSGetPeripheralClockFrequency(), info->baudRate);

    // Activa el modul
    //
    PLIB_I2C_Enable(channel);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    channel: El identificador del modul.
///
void halI2CMasterDeinitialize(
    I2CChannel channel) {

    PLIB_I2C_Disable(channel);

    I2CData* data = __getDataPtr(channel);
    data->isrFunction = NULL;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia START
/// \param   channel: El identificador del modul.
///
void halI2CMasterStart(
    I2CChannel channel) {
    
    I2CRegisters* regs = __getRegisterPtr(channel);
    regs->I2CxCON.SEN = 1;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia STOP
/// \param   channel: El identificador del modul.
///
void halI2CMasterStop(
    I2CChannel channel) {
 
    I2CRegisters* regs = __getRegisterPtr(channel);
    regs->I2CxCON.PEN = 1;
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia RESTART
/// \param   channel: El identificador del modul.
///
void halI2CMasterStartRepeat(
    I2CChannel channel) {

    I2CRegisters* regs = __getRegisterPtr(channel);
    regs->I2CxCON.RSEN = 1;
}


bool halI2CIsBusIdle(
    I2CChannel channel) {
 
    return PLIB_I2C_BusIsIdle(channel);
}


bool halI2CArbitrationLossHasOccurred(
    I2CChannel channel) {

    return PLIB_I2C_ArbitrationLossHasOccurred(channel);
}


void halI2CArbitrationLossClear(
    I2CChannel channel) {

    PLIB_I2C_ArbitrationLossClear(channel);
}


void halI2CTransmitterByteSend(
    I2CChannel channel, 
    uint8_t data) {
    
    PLIB_I2C_TransmitterByteSend(channel, data);
}


bool halI2CTransmitterByteWasAcknowledged(
    I2CChannel channel) {
                    
    return PLIB_I2C_TransmitterByteWasAcknowledged(channel);
}


uint8_t halI2CReceivedByteGet(
    I2CChannel channel) {

    return PLIB_I2C_ReceivedByteGet(channel);
}


void halI2CMasterReceiverClock1Byte(
    I2CChannel channel) {
 
    PLIB_I2C_MasterReceiverClock1Byte(channel);
}


void halI2CReceivedByteAcknowledge(
    I2CChannel channel, 
    bool ack) {
 
    PLIB_I2C_ReceivedByteAcknowledge(channel, ack);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la fuincio d'interrupcio.
/// \param    channel: Identificador del modul.
/// \param    function: La funcio.
/// \param    params: Els parametres.
///
void halI2CSetInterruptFunction(
    I2CChannel channel,
    I2CInterruptFunction function, 
    void* params) {
    
    I2CData* data = __getDataPtr(channel);
    data->isrFunction = function;
    data->isrParams = params;
    
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcionsd el modul.
/// \param    channel: Identificador del modul.
/// \params   sources: Els events a activat
///
void halI2CEnableInterruptSources(
    I2CChannel channel, 
    uint32_t sources) {
    
    switch (channel) {
        case HAL_I2C_CHANNEL_1:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC0bits.I2C1MIE = 1;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC0bits.I2C1SIE = 1;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC0bits.I2C1BIE = 1;
            break;

#ifdef _I2C2            
        case HAL_I2C_CHANNEL_2:
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
/// \param    channel: Identificador del modul.
/// \params   sources: Els events a activat
///
void halI2CDisableInterruptSources(
    I2CChannel channel, 
    uint32_t sources) {
    
    switch (channel) {
        case HAL_I2C_CHANNEL_1:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC0bits.I2C1MIE = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC0bits.I2C1SIE = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC0bits.I2C1BIE = 0;
            break;

#ifdef _I2C2            
        case HAL_I2C_CHANNEL_2:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IEC1bits.I2C2MIE = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IEC1bits.I2C2SIE = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IEC1bits.I2C2BIE = 0;
            break;
#endif            
    }
}


void halI2CClearInterruptSourceFlag(
    I2CChannel channel,
    uint32_t sources) {
    
    switch (channel) {
        case HAL_I2C_CHANNEL_1:
            if ((sources & HAL_I2C_EVENT_MASTER) == HAL_I2C_EVENT_MASTER)
                IFS0bits.I2C1BIF = 0;
            if ((sources & HAL_I2C_EVENT_SLAVE) == HAL_I2C_EVENT_SLAVE)
                IFS0bits.I2C1SIF = 0;
            if ((sources & HAL_I2C_EVENT_BUS) == HAL_I2C_EVENT_BUS)
                IFS0bits.I2C1MIF = 0;
            break;

#ifdef _I2C2            
        case HAL_I2C_CHANNEL_2:
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


bool halI2CGetInterruptSourceFlag(
    I2CChannel channel,
    uint32_t source) {
    
    switch (channel) {
        case HAL_I2C_CHANNEL_1:
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
        case HAL_I2C_CHANNEL_2:
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
static void invokeInterruptFunction(
    I2CChannel channel) {
    
    I2CData* data = __getDataPtr(channel);
    if (data->isrFunction != NULL)
        data->isrFunction(channel, data->isrParams);
}


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_1_VECTOR
///
void isrI2C1Handler(void) {

    if (IFS0bits.I2C1MIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_1);
        IFS0bits.I2C1MIF = 0;
    }
    
    if (IFS0bits.I2C1SIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_1);
        IFS0bits.I2C1SIF = 0;
    }

    if (IFS0bits.I2C1BIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_1);
        IFS0bits.I2C1BIF = 0;
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_2_VECTOR
///
#ifdef _I2C2
void isrI2C2Handler(void) {

    if (IFS1bits.I2C2MIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_2); 
        IFS1bits.I2C2MIF = 0;
    }
}
#endif            


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_3_VECTOR
///
#ifdef _I2C3
void isrI2C3Handler(void) {

    if (IFS2bits.I2C3MIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_3);
        IFS1bits.I2C3MIF = 0;
    }
}
#endif            


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_4_VECTOR
///
#ifdef _I2C4
void isrI2C4Handler(void) {

    if (IFS1bits.I2C4MIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_4);
        IFS1bits.I2C4MIF = 0;
    }
}
#endif            


/// ----------------------------------------------------------------------
/// \brief Procesa el vector _I2C_5_VECTOR
///
#ifdef _I2C5
void isrI2C5Handler(void) {

    if (IFS1bits.I2C5MIF) {
        invokeInterruptFunction(HAL_I2C_CHANNEL_5);
        IFS1bits.I2C5MIF = 0);
    }
}
#endif            
