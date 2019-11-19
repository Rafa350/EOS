#include "eos.h"
#include "HAL/PIC32/halI2C.h"
#include "HAL/PIC32/halSYS.h"

#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

static I2CInterruptCallback callbacks[I2C_NUMBER_OF_MODULES];
static void* params[I2C_NUMBER_OF_MODULES];


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


/// -----------------------------------------------------------------
/// \brief    Obte el identificador 'Harmony' del modul
/// \param    module: El identificaodr 'EOS' del modul I2C.
/// \return   El identificador 'Harmony'
///
static I2C_MODULE_ID getHarmonyID(
    I2CModule module) {
    
    static const I2C_MODULE_ID idTable[] = {
        I2C_ID_1, 
#ifdef _I2C2        
        I2C_ID_2,   
#else
       0,       
#endif        
#ifdef _I2C3        
        I2C_ID_3, 
#else
       0,        
#endif        
#ifdef _I2C4     
        I2C_ID_4, 
#else
       0,        
#endif        
#ifdef _I2C5        
        I2C_ID_5
#else
       0        
#endif        
    };
    
    return idTable[module];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el identificador 'EOS' del modul.
/// \param    id: El identificador 'Harmony' del modul I2C.
/// \return   El identificador 'EOS'.
///
static I2CModule 
    getEosID(I2C_MODULE_ID id) {
    
    switch (id) {
        default:
        case I2C_ID_1: 
            return HAL_I2C_I2C1;
#ifdef _I2C2
        case I2C_ID_2: 
            return HAL_I2C_I2C2;
#endif        
#ifdef _I2C3
        case I2C_ID_3: 
            return HAL_I2C_I2C3;
#endif        
#ifdef _I2C4
        case I2C_ID_4: 
            return HAL_I2C_I2C4;
#endif        
#ifdef _I2C5
        case I2C_ID_5: 
            return HAL_I2C_I2C5;
#endif        
    }
}


/// ----------------------------------------------------------------------
/// \brief   Inicialitza el modul I2C
/// \param   info: Informacio d'inicialitzacio.
///
void halI2CMasterInitialize(
    const I2CMasterInitializeInfo *info) {
    
    callbacks[info->module] = info->irqCallback;
    params[info->module] = info->irqParam;
    
    I2C_MODULE_ID id = getHarmonyID(info->module);

    // Inicialitzacio general del modul
    //
    PLIB_I2C_SlaveClockStretchingEnable(id);
    PLIB_I2C_SMBDisable(id);
    PLIB_I2C_HighFrequencyDisable(id);
    PLIB_I2C_StopInIdleEnable(id);

    // Selecciona la frequencia de treball
    //
    if (info->baudRate > 100000)
        PLIB_I2C_HighFrequencyEnable(id);
    else
        PLIB_I2C_HighFrequencyDisable(id);
    PLIB_I2C_BaudRateSet(id, halSYSGetPeripheralClockFrequency(), info->baudRate);

    // Configura les interrupcions
    //
    switch(id) {
        case I2C_ID_1:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C1, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C1, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_1_MASTER);
            break;

#ifdef _I2C2
        case I2C_ID_2:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C2, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C2, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
            break;
#endif            

#ifdef _I2C3
        case I2C_ID_3:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C3, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C3, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_3_MASTER);
            break;
#endif            

#ifdef _I2C4
        case I2C_ID_4:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C4, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C4, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_4_MASTER);
            break;
#endif            

#ifdef _I2C5
        case I2C_ID_5:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C5, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C5, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_5_MASTER);
            break;
#endif            
    }

    // Activa el modul
    //
    PLIB_I2C_Enable(id);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    module: El modul.
///
void halI2CMasterDeinitialize(
    I2CModule module) {
    
    callbacks[module] = NULL;
    params[module] = NULL;    
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia START
/// \param   module: El modul.
///
void halI2CMasterStart(
    I2CModule module) {

    PLIB_I2C_MasterStart(getHarmonyID(module));    
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia STOP
/// \param   module: El modul.
///
void halI2CMasterStop(
    I2CModule module) {
 
    PLIB_I2C_MasterStop(getHarmonyID(module));
}


/// ----------------------------------------------------------------------
/// \brief   Genera la sequencia RESTART
/// \param   module: El modul.
///
void halI2CMasterStartRepeat(
    I2CModule module) {

    PLIB_I2C_MasterStartRepeat(getHarmonyID(module));
}


bool halI2CIsBusIdle(
    I2CModule module) {
 
    return PLIB_I2C_BusIsIdle(getHarmonyID(module));
}


bool halI2CArbitrationLossHasOccurred(
    I2CModule module) {

    return PLIB_I2C_ArbitrationLossHasOccurred(getHarmonyID(module));
}


void halI2CArbitrationLossClear(
    I2CModule module) {

    PLIB_I2C_ArbitrationLossClear(getHarmonyID(module));
}


void halI2CTransmitterByteSend(uint8_t moduleId, uint8_t data) {
    
    PLIB_I2C_TransmitterByteSend(getHarmonyID(moduleId), data);
}


bool halI2CTransmitterByteWasAcknowledged(uint8_t moduleId) {
                    
    return PLIB_I2C_TransmitterByteWasAcknowledged(getHarmonyID(moduleId));
}


uint8_t halI2CReceivedByteGet(uint8_t moduleId) {

    return PLIB_I2C_ReceivedByteGet(getHarmonyID(moduleId));
}


void halI2CMasterReceiverClock1Byte(uint8_t moduleId) {
 
    PLIB_I2C_MasterReceiverClock1Byte(getHarmonyID(moduleId));
}


void halI2CReceivedByteAcknowledge(
    I2CModule module, bool ack) {
 
    PLIB_I2C_ReceivedByteAcknowledge(getHarmonyID(module), ack);
}


/// ----------------------------------------------------------------------
/// \brief    Crida a la funcio callback de la interrupcio.
/// \param    id: identificacod 'Harmony' del modul.
///
static void doCallback(
    I2C_MODULE_ID id) {
    
    I2CModule module = getEosID(id);    
    I2CInterruptCallback callback = callbacks[module];
    if (callback != NULL)
        callback(module, params[module]);
}


/*************************************************************************
 *
 *       Funcions ISR del modul I2C (Hi una per cada modul)
 * 
 *       Funcio:
 *          void isrI2CxHandler(void)
 *
 *************************************************************************/

void isrI2C1Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_1_MASTER)) {
        doCallback(I2C_ID_1);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_1_MASTER);
    }
}

#ifdef _I2C2
void isrI2C2Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_2_MASTER)) {
        doCallback(I2C_ID_2); 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
    }
}
#endif            

#ifdef _I2C3
void isrI2C3Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_3_MASTER)) {
        doCallback(I2C_ID_3);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_3_MASTER);
    }
}
#endif            

#ifdef _I2C4
void isrI2C4Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_4_MASTER)) {
        doCallback(I2C_ID_4);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_4_MASTER);
    }
}
#endif            

#ifdef _I2C5
void isrI2C5Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_5_MASTER)) {
        doCallback(I2C_ID_5);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_MASTER);
    }
}
#endif            
