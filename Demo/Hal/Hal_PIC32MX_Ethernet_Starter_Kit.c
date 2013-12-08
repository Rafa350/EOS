#include "eos.h"


static IoPortId outPortIds[EOS_NUM_OUTPUTS] = {
    IOPORT_D,
    IOPORT_D,
    //IOPORT_D
};

static unsigned outPortBits[EOS_NUM_OUTPUTS] = {
    BIT_0,
    BIT_1,
    //BIT_2
};

static IoPortId inpPortIds[EOS_NUM_INPUTS] =  {
    IOPORT_D,
    IOPORT_D,
    IOPORT_D
};

static unsigned inpPortBits[EOS_NUM_INPUTS] = {
    BIT_6,
    BIT_7,
    BIT_13
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

    unsigned i;

    // Configura el sistema
    //
    SYSTEMConfigPerformance(GetSystemClock());

    // Configura el temporitzador per que generi interrupcions TICK cada 1ms
    //
    OpenTimer5(T5_INT_ON | T5_SOURCE_INT | T5_PS_1_256, GetSystemClock() / 256 / 1000);
    ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_2);

    // Inicialitza els ports de sortida
    //
    for (i = 0; i < EOS_NUM_OUTPUTS; i++)
        PORTSetPinsDigitalOut(outPortIds[i], outPortBits[i]);

    // Inicialitza els ports d'entrada
    //
    for (i = 0; i < EOS_NUM_INPUTS; i++)
        PORTSetPinsDigitalIn(inpPortIds[i], inpPortBits[i]);

    // Inicialitza el led
    //
    mPORTDSetPinsDigitalOut(BIT_2);

    // Configura les interrupcions
    //
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
}


/*************************************************************************
 *
 *       Escriu en un port de sortida
 *
 *       Funcio:
 *           void halOutPortWrite(UINT8 outputId, BOOL state)
 *
 *       Entrada:
 *           outputId: Identificador del port
 *           state   : Esl nou estat
 *
 *************************************************************************/

void halOutPortWrite(UINT8 outputId, BOOL state) {
    
    if (state)
        PORTSetBits(outPortIds[outputId], outPortBits[outputId]);
    else
        PORTClearBits(outPortIds[outputId], outPortBits[outputId]);
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

BOOL halInpPortRead(UINT8 inputId) {

    return PORTReadBits(inpPortIds[inputId], inpPortBits[inputId]) == 0;
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
        mPORTDSetBits(BIT_2);
    else
        mPORTDClearBits(BIT_2);
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

void __ISR(_TIMER_5_VECTOR, ipl2) TickHandler(void) {

    eosTickInterrupt();
    
    mT5ClearIntFlag();
}
