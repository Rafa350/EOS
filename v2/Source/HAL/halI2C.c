#include "HAL/halI2C.h"
#include "HardwareProfile.h"
#include "sys/attribs.h"
#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

static I2CInterruptCallback interruptCallback = NULL;
static void *interruptParam;


extern void __ISR(_I2C_1_VECTOR, IPL2SOFT) isrI2C1Wrapper(void);
extern void __ISR(_I2C_2_VECTOR, IPL2SOFT) isrI2C2Wrapper(void);
extern void __ISR(_I2C_3_VECTOR, IPL2SOFT) isrI2C3Wrapper(void);
extern void __ISR(_I2C_4_VECTOR, IPL2SOFT) isrI2C4Wrapper(void);
extern void __ISR(_I2C_5_VECTOR, IPL2SOFT) isrI2C5Wrapper(void);


static I2C_MODULE_ID getHarmonyID(unsigned moduleId) {
    
    static I2C_MODULE_ID idTable[] = {
        I2C_ID_1, I2C_ID_2, I2C_ID_3, I2C_ID_4, I2C_ID_5
    };
    
    return idTable[moduleId];
}


static unsigned getEosID(I2C_MODULE_ID id) {
    
    switch (id) {
        case I2C_ID_2: return 1;
        case I2C_ID_3: return 2;
        case I2C_ID_4: return 3;
        case I2C_ID_5: return 4;
        default:
        case I2C_ID_1: return 0;
    }
}


void halI2CMasterInitialize(
    unsigned moduleId,
    unsigned baudRate,
    I2CInterruptCallback callback,
    void *param) {
    
    I2C_MODULE_ID id = getHarmonyID(moduleId);
    
    interruptCallback = callback;
    interruptParam = param;
    
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

        case I2C_ID_2:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C2, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C2, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
            break;

        case I2C_ID_3:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C3, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C3, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_3_MASTER);
            break;

        case I2C_ID_4:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C4, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C4, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_4_MASTER);
            break;

        case I2C_ID_5:
            PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_I2C5, intPriority);
            PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_I2C5, intSubPriority);
            PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_I2C_5_MASTER);
            break;
    }

    // Activa el modul
    //
    PLIB_I2C_Enable(id);
}


void halI2CMasterStart(unsigned moduleId) {

    PLIB_I2C_MasterStart(getHarmonyID(moduleId));    
}


bool halI2CMasterIsBufIdle(unsigned moduleId) {
 
    return PLIB_I2C_BusIsIdle(getHarmonyID(moduleId));
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
        if (interruptCallback)
            interruptCallback(getEosID(I2C_ID_1), interruptParam);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_1_MASTER);
    }
}

void isrI2C2Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_2_MASTER)) {
        if (interruptCallback)
            interruptCallback(getEosID(I2C_ID_2), interruptParam);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_2_MASTER);
    }
}

void isrI2C3Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_3_MASTER)) {
        if (interruptCallback)
            interruptCallback(getEosID(I2C_ID_3), interruptParam);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_3_MASTER);
    }
}

void isrI2C4Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_4_MASTER)) {
        if (interruptCallback)
            interruptCallback(getEosID(I2C_ID_4), interruptParam);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_4_MASTER);
    }
}

void isrI2C5Handler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_I2C_5_MASTER)) {
        if (interruptCallback)
            interruptCallback(getEosID(I2C_ID_5), interruptParam);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_MASTER);
    }
}

