#include "Modules/Plc/eosPlc.h"


#ifdef eosUSE_VARIABLES


#if !defined(eosCFG_VARIABLES_NumVariables) || (eosCFG_VARIABLES_NumVariables < 1) || (eosCFG_VARIABLES_NumVariables > 64)
#error 'eosPLC_NumVariables' ha de estar en el intervalo 1..64
#endif


static unsigned variables[eosCFG_VARIABLES_NumVariables];

extern void halVarSave(void *data, unsigned dataSize);
extern void halVarRestore(void *data, unsigned dataSize);


/*************************************************************************
 *
 *       Inicialitza la gestio de les variables
 *
 *       Funcio:
 *           void sysVarInitialize(void)
 *
 *************************************************************************/

void sysVarInitialize(void) {

    UINT8 id = eosCFG_VARIABLES_NumVariables - 1;
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
    halVarSave((void*) variables, sizeof(variables));
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
    halVarRestore((void*) variables, sizeof(variables));
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

    if (id < eosCFG_VARIABLES_NumVariables)
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

    if (id < eosCFG_VARIABLES_NumVariables)
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
