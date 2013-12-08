#include "eos.h"


#ifdef EOS_USE_VARIABLES


#if !defined(EOS_NUM_VARIABLES) || (EOS_NUM_VARIABLES < 1) || (EOS_NUM_VARIABLES > 64)
#error 'EOS_NUM_VARIABLES' ha de estar en el intervalo 1..64
#endif

#ifndef VAR_EEPROM_BASE
#define VAR_EEPROM_BASE     0
#endif

#if (VAR_EEPROM_BASE + (EOS_NUM_VARIABLES * 2) > _EEPROMSIZE) && defined(_PIC18)
#error No hay suficiente EEPROM para almacenar las variables. Modifique 'EOS_NUM_VARIABLES'.
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

#ifdef _PIC18x
void eosVarSave(void) {

    UINT8 var;
    UINT16 addr;

    addr = VAR_EEPROM_BASE;

    eosDisableInterrupts();

    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;

    varId = EOS_NUM_VARIABLES - 1;
    do {

        // Guarda la part baixa de la variable
        //
        EEADR = addr & 0x00FF;
#if _EEPROMSIZE > 256
        EEADRH = (addr >> 8) & 0x03;
#endif
        EEDATA = variables[varId] & 0x00FF;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        while (EECON1bits.WR)
            continue;
        addr++;

        // Guarda la part alta de la variable
        //
        EEADR = addr & 0x00FF;
#if _EEPROMSIZE > 256
        EEADRH = (addr >> 8) & 0x03;
#endif
        EEDATA = variables[varId] >> 8;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        while (EECON1bits.WR)
            continue;
        addr++;

    } while (varId--);

    EECON1bits.WREN = 0;

    eosEnableInterrupts();
}
#endif


/*************************************************************************
 *
 *       Recupera les variables de la EEPROM
 *
 *       Funcio:
 *           void varRestore(void)
 *
 **************************************************************************/

#ifdef _PIC18x
void eosVarRestore(void) {

    UINT8 var;
    UINT16 addr, data;

    addr = VAR_EEPROM_BASE;

    var = EOS_NUM_VARIABLES - 1;
    do {

        // Llegeix el primer byte de la variable
        //
        EEADR = addr & 0x0ff;
#if _EEPROMSIZE > 256
        EEADRH = (addr >> 8) & 0x03;
#endif
        EECON1bits.CFGS = 0;
        EECON1bits.EEPGD = 0;
        EECON1bits.RD = 1;
        NOP();          // Nop may be required for latency at high frequencies
        NOP();          // Nop may be required for latency at high frequencies
        data = EEDATA;
        addr++;

#if sizeof(VARTYPE) > 1

        // Llegeix el segon byte de la variable
        //
        EEADR = addr & 0x0ff;
#if _EEPROMSIZE > 256
        EEADRH = (addr >> 8) & 0x03;
#endif
        EECON1bits.CFGS = 0;
        EECON1bits.EEPGD = 0;
        EECON1bits.RD = 1;
        NOP();          // Nop may be required for latency at high frequencies
        NOP();          // Nop may be required for latency at high frequencies
        data |= (EEDATA << 8);
        addr++;
#endif

        variables[var] =  data;

    } while (var--);
}
#endif


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
