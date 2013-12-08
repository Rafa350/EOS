#include "eos.h"


#ifdef EOS_USE_VARIABLES


#if !defined(EOS_NUM_VARIABLES) || (EOS_NUM_VARIABLES < 1) || (EOS_NUM_VARIABLES > 64)
#error 'EOS_NUM_VARIABLES' ha de estar en el intervalo 1..64
#endif


static VARTYPE variables[EOS_NUM_VARIABLES];



/*************************************************************************
 *
 *       Inicialitza la gestio de les variables
 *
 *       Funcio:
 *           void sysVarInitialize(void)
 *
 *************************************************************************/

void sysVarInitialize(void) {

    UINT8 varId = EOS_NUM_VARIABLES - 1;
    do {
        variables[varId] = 0;
    } while (varId--);
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
    __halVarSave((BYTE*) variables, sizeof(variables));
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
    __halVarRestore((BYTE*) variables, sizeof(variables));
    eosEnableInterrupts();
}


/*************************************************************************
 *
 *       Obte el valor d'una variable
 *
 *       Funcio:
 *           VARTYPE eosVarGet(UINT8 varId)
 *
 *       Entrada:
 *           varId: Numero de la variable
 *
 *       Retorn:
 *           El valor de la variable
 *
 *       Notes:
 *           Les variables inexistens retornen 0
 *
 *************************************************************************/

VARTYPE eosVarGet(UINT8 varId) {

    if (varId < EOS_NUM_VARIABLES)
        return variables[varId];
    else
        return 0;
}


/*************************************************************************
 *
 *       Assigna un valor a una variable
 *
 *       Funcio:
 *           void eosVarSet(UINT8 varId, VARTYPE value)
 *
 *       Entrada:
 *           varId: El numero de la variable
 *           value: El valor
 *
 *************************************************************************/

void eosVarSet(UINT8 varId, VARTYPE value) {

    if (varId < EOS_NUM_VARIABLES)
        variables[varId] = value;
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
