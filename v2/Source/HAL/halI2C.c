#include "HAL/halI2C.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

static I2CInterruptCallback callbacks[I2C_NUMBER_OF_MODULES];
static I2CInterruptParam params[I2C_NUMBER_OF_MODULES];


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


static I2C_MODULE_ID getHarmonyID(unsigned moduleId) {
    
    static I2C_MODULE_ID idTable[I2C_NUMBER_OF_MODULES] = {
        I2C_ID_1, 
#ifdef _I2C2        
        I2C_ID_2,   
#endif        
#ifdef _I2C3        
        I2C_ID_3, 
#endif        
#ifdef _I2C4     
        I2C_ID_4, 
#endif        
#ifdef _I2C5        
        I2C_ID_5
#endif        
    };
    
    return idTable[moduleId];
}


static unsigned getEosID(I2C_MODULE_ID id) {
    
    switch (id) {
        default:
        case I2C_ID_1: 
            return 0;
#ifdef _I2C2
        case I2C_ID_2: 
            return 1;
#endif        
#ifdef _I2C3
        case I2C_ID_3: 
            return 2;
#endif        
#ifdef _I2C4
        case I2C_ID_4: 
            return 3;
#endif        
#ifdef _I2C5
        case I2C_ID_5: 
            return 4;
#endif        
    }
}


void halI2CMasterInitialize(
    unsigned moduleId,
    unsigned baudRate,
    I2CInterruptCallback callback,
    I2CInterruptParam param) {
    
    callbacks[moduleId] = callback;
    params[moduleId] = param;
    
    I2C_MODULE_ID id = getHarmonyID(moduleId);

    // Inicialitzacio general del modul
    //
    PLIB_I2C_SlaveClockStretchingEnable(id);
    PLIB_I2C_SMBDisable(id);
    PLIB_I2C_HighFrequencyDisable(id);
    PLIB_I2C_StopInIdleEnable(id);

    // Selecciona la frequencia de treball
    //
    PLIB_I2C_BaudRateSet(id, CLOCK_PERIPHERICAL_HZ, baudRate);

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


void halI2CMasterStart(unsigned moduleId) {

    PLIB_I2C_MasterStart(getHarmonyID(moduleId));    
}


void halI2CMasterStop(unsigned moduleId) {
 
    PLIB_I2C_MasterStop(getHarmonyID(moduleId));
}


void halI2CMasterStartRepeat(unsigned moduleId) {

    PLIB_I2C_MasterStartRepeat(getHarmonyID(moduleId));
}


bool halI2CIsBusIdle(unsigned moduleId) {
 
    return PLIB_I2C_BusIsIdle(getHarmonyID(moduleId));
}


bool halI2CArbitrationLossHasOccurred(unsigned moduleId) {

    return PLIB_I2C_ArbitrationLossHasOccurred(getHarmonyID(moduleId));
}


void halI2CArbitrationLossClear(unsigned moduleId) {

    PLIB_I2C_ArbitrationLossClear(getHarmonyID(moduleId));
}


void halI2CTransmitterByteSend(unsigned moduleId, uint8_t data) {
    
    PLIB_I2C_TransmitterByteSend(getHarmonyID(moduleId), data);
}


bool halI2CTransmitterByteWasAcknowledged(unsigned moduleId) {
                    
    return PLIB_I2C_TransmitterByteWasAcknowledged(getHarmonyID(moduleId));
}


uint8_t halI2CReceivedByteGet(unsigned moduleId) {

    return PLIB_I2C_ReceivedByteGet(getHarmonyID(moduleId));
}


void halI2CMasterReceiverClock1Byte(unsigned moduleId) {
 
    PLIB_I2C_MasterReceiverClock1Byte(getHarmonyID(moduleId));
}


void halI2CReceivedByteAcknowledge(unsigned moduleId, bool ack) {
 
    PLIB_I2C_ReceivedByteAcknowledge(getHarmonyID(moduleId), ack);
}


/*************************************************************************
 *
 *       Crida al callback adequat a cada modul I2C
 * 
 *       Funcio:
 *           void doCallback(
 *               I2C_MODULE_ID id)
 * 
 *       Entrada:
 *           id: Numero de modul I2C
 *
 *************************************************************************/

static void doCallback(
    I2C_MODULE_ID id) {
    
    unsigned moduleId = getEosID(id);    
    I2CInterruptCallback callback = callbacks[moduleId];
    if (callback != NULL)
        callback(moduleId, params[moduleId]);
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
