#include "eos.h"


#ifdef EOS_USE_VARIABLES


#if !defined(EOS_NUM_VARIABLES) || (EOS_NUM_VARIABLES < 1) || (EOS_NUM_VARIABLES > 64)
#error 'EOS_NUM_VARIABLES' ha de estar en el intervalo 1..64
#endif


static unsigned variables[EOS_NUM_VARIABLES];



/*************************************************************************
 *
 *       Inicialitza la gestio de les variables
 *
 *       Funcio:
 *           void sysVarInitialize(void)
 *
 *************************************************************************/

void sysVarInitialize(void) {

    UINT8 id = EOS_NUM_VARIABLES - 1;
    do {
        variables[id] = 0;
    } while (id--);
}


/*************************************************************************
 *
 *       Salva les variables en EEPROM
 *
 *       Funcio:
 *           void varSave(void)
 *
 **************************************************************************/

void eosVarSave(void) {

    eosDisableInterrupts();
    __halVarSave((void*) variables, sizeof(variables));
    eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Recupera les variables de la EEPROM
 *
 *       Funcio:
 *           void varRestore(void)
 *
 **************************************************************************/

void eosVarRestore(void) {

    eosDisableInterrupts();
    __halVarRestore((void*) variables, sizeof(variables));
    eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Obte el valor d'una variable
 *
 *       Funcio:
 *           unsigned eosVarGet(UINT8 id)
 *
 *       Entrada:
 *           id: Numero de la variable
 *
 *       Retorn:
 *           El valor de la variable
 *
 *       Notes:
 *           Les variables inexistens retornen 0
 *
 *************************************************************************/

unsigned eosVarGet(UINT8 id) {

    if (id < EOS_NUM_VARIABLES)
        return variables[id];
    else
        return 0;
}


/*************************************************************************
 *
 *       Assigna un valor a una variable
 *
 *       Funcio:
 *           void eosVarSet(UINT8 id, unsigned value)
 *
 *       Entrada:
 *           id   : El numero de la variable
 *           value: El valor
 *
 *************************************************************************/

void eosVarSet(UINT8 id, unsigned value) {

    if (id < EOS_NUM_VARIABLES)
        variables[id] = value;
}


/*************************************************************************
 *
 *       Assigna valors a variables a partir d'una taula
 *
 *       Funcio:
 *           void eosVarSetTable(VARINIT *data, UINT8 dataLen)
 *           void eosVarSetTableROM(VARINIT const *data, UINT8 dataLen)
 *
 *       Entrada:
 *           data: Taula d'inicialitzacio
 *           size: Numero d'elements en la taula
 *
 *************************************************************************/

void eosVarSetTable(VARINIT *data, UINT8 dataLen) {

    while (dataLen--)
        eosVarSet(data[dataLen].varId, data[dataLen].value);
}

#ifdef _PIC18
void varSetTableROM(VARINIT const *data, UINT8 dataLen) {

    while (dataLen--)
        eosVarSet(data[dataLen].varId, data[dataLen].value);
}
#endif


#endif
