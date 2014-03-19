#include "eos.h"

#include "peripheral/ports/plib_ports.h"
#include "peripheral/tmr/plib_tmr.h"


static PORTS_CHANNEL outPortChannel[eosPLC_NumOutputs] = {
    PORT_CHANNEL_D,
    PORT_CHANNEL_D,
    //PORT_CHANNEL_PORT_D
};

static PORTS_BIT_POS outPortBit[eosPLC_NumOutputs] = {
    PORTS_BIT_POS_0,
    PORTS_BIT_POS_1,
    //PORTS_BIT_POS_2
};

static PORTS_CHANNEL inpPortChannel[eosPLC_NumInputs] =  {
    PORT_CHANNEL_D,
    PORT_CHANNEL_D,
    PORT_CHANNEL_D
};

static PORTS_BIT_POS inpPortBit[eosPLC_NumInputs] = {
    PORTS_BIT_POS_6,
    PORTS_BIT_POS_7,
    PORTS_BIT_POS_13
};

static int inpPullUpChannel[eosPLC_NumInputs] = {
    CN15,
    CN16,
    CN19
};


/*************************************************************************
 *
 *       Inicialitza el hardware
 *
 *       Funcio:
 *           void halInitialize(void)
 *
 *************************************************************************/

void halInitialize(void) {

    extern unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);

    unsigned i;

    // Configura el sistema
    //
    SYSTEMConfigPerformance(GetSystemClock());

    // Configura el temporitzador per que generi interrupcions TICK cada 1ms
    //
    PLIB_TMR_Stop(TMR_ID_2);
    PLIB_TMR_ClockSourceSelect(TMR_ID_2, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_2, TMR_PRESCALE_VALUE_64);
    PLIB_TMR_Mode16BitEnable(TMR_ID_2);
    PLIB_TMR_Counter16BitClear(TMR_ID_2);
    PLIB_TMR_Period16BitSet(TMR_ID_2, GetPeriphericalClock() / 64 / 1000);

    // Configura les interrupcions
    //
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T2, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T2, INT_SUBPRIORITY_LEVEL0);
    PLIB_INT_MultiVectorSelect(INT_ID_0);

    // Activa el temporitzador i comença a generar interrupcions TICK
    //
    PLIB_TMR_Start(TMR_ID_2);
}


/*************************************************************************
 *
 *     Inicialitza el modul de sortides digitals
 *
 *     Funcio:
 *         void halOutInitialize(void)
 *
 *************************************************************************/

void halOutInitialize(void) {

    unsigned i;

    // Inicialitza els ports de sortida
    //
    for (i = 0; i < eosPLC_NumOutputs; i++)
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, outPortChannel[i], outPortBit[i]);
}


/*************************************************************************
 *
 *       Escriu en un port de sortida
 *
 *       Funcio:
 *           void halOutPortWrite(UINT8 id, BOOL state)
 *
 *       Entrada:
 *           id   : Identificador del port
 *           state: Esl nou estat
 *
 *************************************************************************/

void halOutPortWrite(UINT8 id, BOOL state) {
    
    if (state)
        PLIB_PORTS_PinSet(PORTS_ID_0, outPortChannel[id], outPortBit[id]);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, outPortChannel[id], outPortBit[id]);
}


/*************************************************************************
 *
 *     Inicialitza el modul d'entrades digitals
 *
 *     Funcio:
 *         void halInpInitialize(void)
 *
 *************************************************************************/

void halInpInitialize(void) {

    unsigned i;

    // Inicialitza els ports d'entrada
    //
    for (i = 0; i < eosPLC_NumInputs; i++) {
        PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, inpPortChannel[i], inpPortBit[i]);
        PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, inpPullUpChannel[i]);
    }
}


/*************************************************************************
 *
 *       Llegeix un port d'entrada
 *
 *       Funcio:
 *           BOOL halInpPortRead(UINT8 inpupId)
 *
 *       Entrada:
 *           inputId: Identificador del port
 *
 *       Retorn:
 *           Estat del port
 *
 *************************************************************************/

BOOL halInpPortRead(UINT8 id) {

    return !PLIB_PORTS_PinGet(PORTS_ID_0, inpPortChannel[id], inpPortBit[id]);
}


/*************************************************************************
 *
 *     Inicialitza el modul
 *
 *     Funcio:
 *         void halLedInitialize(void)
 *
 *************************************************************************/

void halLedInitialize(void) {

    // Inicialitza el led
    //
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);
}


/*************************************************************************
 *
 *       Escriu en el port del led
 *
 *       Funcio:
 *           void halLedPortWrite(BOOL state)
 *
 *       Entrada:
 *           state: El nou estat
 *
 *************************************************************************/

void halLedPortWrite(BOOL state) {

    if (state)
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);
}


void halVarSave(void *data, unsigned dataSize) {
}

void halVarRestore(void *data, unsigned dataSize) {
}


/*************************************************************************
 *
 *       Interrupcio del temporitzador
 *
 *       Funcio:
 *           void TickHandler(void)
 *
 *************************************************************************/

void  __attribute__((interrupt(ipl2), vector(_TIMER_2_VECTOR))) TickHandler(void) {

    eosTickInterrupt();
    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
}
