#include "eos.h"


#ifdef EOS_USE_VARIABLES


#if !defined(EOS_NUM_VARIABLES) || (EOS_NUM_VARIABLES < 1) || (EOS_NUM_VARIABLES > 64)
#error 'EOS_NUM_VARIABLES' ha de estar en el intervalo 1..32
#endif

#ifndef VAR_EEPROM_BASE
#define VAR_EEPROM_BASE     0
#endif

#if (VAR_EEPROM_BASE + (NUM_VARIABLES * 2) > _EEPROMSIZE)
#error No hay suficiente EEPROM para almacenar las variables. Modifique 'EOS_NUM_VARIABLES'.
#endif

static UINT16 variables[EOS_NUM_VARIABLES];



/*************************************************************************
 *
 *       Inicialitza la gestio de les variables
 *
 *       Funcio:
 *           void eosVarInitialize(void)
 *
 *************************************************************************/

void eosVarInitialize(void) {

    UINT8 var = EOS_NUM_VARIABLES - 1;
    do {
        variables[var] = 0;
    } while (var--);
}


/*************************************************************************
 *
 *       Salva les variables en EEPROM
 *
 *       Funcio:
 *           void varSave(void)
 *
 **************************************************************************/

void varSave(void) {

    UINT8 var;
    UINT16 addr;

    addr = VAR_EEPROM_BASE;

    di();
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;

    var = NUM_VARIABLES - 1;
    do {

        // Guarda la part baixa de la variable
        //
        EEADR = addr & 0x00FF;
        EEADRH = (addr >> 8) & 0x03;
        EEDATA = variables[var] & 0x00FF;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        while (EECON1bits.WR)
            continue;
        addr++;

        // Guarda la part alta de la variable
        //
        EEADR = addr & 0x00FF;
        EEADRH = (addr >> 8) & 0x03;
        EEDATA = variables[var] >> 8;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        while (EECON1bits.WR)
            continue;
        addr++;

    } while (var--);

    EECON1bits.WREN = 0;
    ei();
}


/*************************************************************************
 *
 *       Recupera les variables de la EEPROM
 *
 *       Funcio:
 *           void varRestore(void)
 *
 **************************************************************************/

void varRestore(void) {

    UINT8 var;
    UINT16 addr, data;

    addr = VAR_EEPROM_BASE;

    var = NUM_VARIABLES - 1;
    do {

        // Llegeix la part baixa de la variable
        //
        EEADR = addr & 0x0ff;
        EEADRH = (addr >> 8) & 0x03;
        EECON1bits.CFGS = 0;
        EECON1bits.EEPGD = 0;
        EECON1bits.RD = 1;
        NOP();          // Nop may be required for latency at high frequencies
        NOP();          // Nop may be required for latency at high frequencies
        data = EEDATA;
        addr++;

        // Llegeix la part alta de la variable
        //
        EEADR = addr & 0x0ff;
        EEADRH = (addr >> 8) & 0x03;
        EECON1bits.CFGS = 0;
        EECON1bits.EEPGD = 0;
        EECON1bits.RD = 1;
        NOP();          // Nop may be required for latency at high frequencies
        NOP();          // Nop may be required for latency at high frequencies
        variables[var] = (EEDATA << 8) | data;
        addr++;

    } while (var--);
}


/*************************************************************************
 *
 *       Obte el valor d'una variable
 *
 *       Funcio:
 *           UINT16 varGet(UINT8 var)
 *
 *       Entrada:
 *           var: Numero de la variable
 *
 *       Retorn:
 *           El valor de la variable
 *
 *       Notes:
 *           Les variables inexistens retornen 0
 *
 *************************************************************************/

UINT16 varGet(UINT8 var) {

#ifdef MODE_MASTER
    UINT8 addr;
    BYTE data[5];
#endif

    if (var < NUM_VARIABLES)
        return variables[var];

#ifdef MODE_MASTER
    else {
        data[0] = CMD_VAR_GET | (var & 0b00011111);
        data[1] = CalcCheckSum((BYTE*) data, 1);
        addr = var & 0b11100000;
        if (masterSendCommand(addr, (BYTE*) data, 2)) {
            if (masterGetResponse(addr, (BYTE*) data, sizeof(data)))
                return (data[0] << 8) | data[1];
            else
                return 0;
        }
        else
            return 0;
    }
#else
    else
        return 0;
#endif
}


/*************************************************************************
 *
 *       Assigna un valor a una variable
 *
 *       Funcio:
 *           void varSet(UINT8 var, UINT16 value)
 *
 *       Entrada:
 *           var  : El numero de la variable
 *           value: El valor
 *
 *************************************************************************/

void varSet(UINT8 var, UINT16 value) {

    BYTE data[4];

    if (var < NUM_VARIABLES)
        variables[var] = value;

#ifdef MODE_MASTER
    else {
        data[0] = CMD_VAR_SET | (var & 0b00011111);
        data[1] = value >> 8;
        data[2] = value & 0xFF;
        data[3] = CalcCheckSum((BYTE*) data, sizeof(data) - 1);
        masterSendCommand(var & 0b11100000, (BYTE*) data, sizeof(data));
    }
#endif
}


/*************************************************************************
 *
 *       Assigna valors a variables a partir d'una taula
 *
 *       Funcio:
 *           void varSetTable(VARINIT *data, UINT8 size)
 *           void varSetTableROM(VARINIT const *data, UINT8 size)
 *
 *       Entrada:
 *           data: Taula d'inicialitzacio
 *           size: Numero d'elements en la taula
 *
 *************************************************************************/

void varSetTable(VARINIT *data, UINT8 size) {

    while (size--)
        varSet(data[size].var, data[size].value);
}

void varSetTableROM(VARINIT const *data, UINT8 size) {

    while (size--)
        varSet(data[size].var, data[size].value);
}


#endif
