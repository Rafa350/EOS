#include "eos.h"

#ifdef eosUSE_I2CSLAVE


#ifndef I2CS_RX_BUFSIZE
#define I2CS_RX_BUFSIZE      16    // Tamany del buffer de recepcio
#endif

#ifndef I2CS_TX_BUFSIZE
#define I2CS_TX_BUFSIZE      16    // Tamany del buffer de transmisio
#endif


#if defined(_12F1822)
#if defined(I2CS_SSP1)
#define I2C_SDA_TRIS         TRISAbits.TRISA2
#define I2C_SCL_TRIS         TRISAbits.TRISA1
#define I2C_SDA_ANSEL        ANSELAbits.ANSA2
#define I2C_SCL_ANSEL        ANSELAbits.ANSA1

#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF
#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKTIM           SSP1CON3bits.ACKTIM
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#else
#error Modulo SSP no soportado
#endif


#elif defined(_16F1823) || defined(_16F1825)
#if defined(I2CS_SSP1)
#define I2C_SDA_TRIS         TRISCbits.TRISC1
#define I2C_SCL_TRIS         TRISCbits.TRISC0
#define I2C_SDA_ANSEL        ANSELCbits.ANSC1
#define I2C_SCL_ANSEL        ANSELCbits.ANSC0

#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF
#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKTIM           SSP1CON3bits.ACKTIM
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#else
#error Modulo SSP no soportado
#endif


#elif defined(_16F1829)
#if defined(I2CS_SSP1)
#define I2C_SDA_TRIS         TRISBbits.TRISB4
#define I2C_SCL_TRIS         TRISBbits.TRISB6
#define I2C_SDA_ANSEL        ANSELBbits.ANSB4
#define I2C_SCL_ANSEL        ANSELBbits.ANSB6

#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF
#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKTIM           SSP1CON3bits.ACKTIM
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#elif defined(I2CS_SSP2)
#define I2C_IE               SSP2IE
#define I2C_IF               SSP2IF
#define I2C_ADD              SSP2ADD
#define I2C_CKP              SSP2CON1bits.CKP
#define I2C_ACKDT            SSP2CON2bits.ACKDT
#define I2C_ACKTIM           SSP2CON3bits.ACKTIM
#define I2C_STAT             SSP2STAT
#define I2C_BUF              SSP2BUF
#define I2C_SSPM             SSP2CON1bits.SSPM
#define I2C_SSPEN            SSP2CON1bits.SSPEN
#define I2C_SEN              SSP2CON2bits.SEN
#define I2C_DHEN             SSP2CON3bits.DHEN
#else
#error No se definio I2CS_SSPx
#endif


#elif defined(_18F23K22) || defined(_18F24K22) || defined(_18F25K22) || defined(_18F26K22) || \
      defined(_18F43K22) || defined(_18F44K22) || defined(_18F45K22) || defined(_18F46K22)
#if defined(I2CS_SSP1)
#define I2C_SDA_TRIS         TRISCbits.TRISC4
#define I2C_SCL_TRIS         TRISCbits.TRISC3
#define I2C_SDA_ANSEL        ANSELCbits.ANSC4
#define I2C_SCL_ANSEL        ANSELCbits.ANSC3

#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF
#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKTIM           SSP1CON3bits.ACKTIM
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#else
#error No se definio I2CS_SSPx
#endif

#else
#error CPU no soportada
#endif

typedef enum {
    STATE_WaitLength,
    STATE_WaitData,
    STATE_WaitCheck
} STATE;

static STATE state;                // Estat de la comunicacio
static UINT8 count;                // Contador de bytes
static UINT8 check;                // Check-sum
static UINT8 lastError;            // Ultim error

static BYTE rxBuffer[I2CS_RX_BUFSIZE];  // Buffer de recepcio
static UINT8 rxCount;              // Numero de bytes en el buffer
static UINT8 rxGetIdx;             // Punter de lectura
static UINT8 rxPutIdx;             // Punter de escriptura

static UINT8 txBuffer[I2CS_TX_BUFSIZE]; // Buffer de transmissio
static UINT8 txCount;              // Numero de bytes en el buffer
static UINT8 txGetIdx;             // Punter de lectura
static UINT8 txPutIdx;             // Punter de escriptura


/*************************************************************************
 *
 *      Obte un byte del buffer de recepcio
 *
 *      Funcio:
 *          BYTE rxGet(void)
 *
 *      Retorn:
 *          El byte lleigit
 *
 *      Notes:
 *          ATENCIO: No hi ha cap tipus de comprovacio de limits
 *
 *************************************************************************/

static BYTE rxGet(void) {

    BYTE d = rxBuffer[rxGetIdx++];
    if (rxGetIdx == sizeof(rxBuffer))
        rxGetIdx = 0;
    rxCount--;

    return d;
}


/*************************************************************************
 *
 *       Escriu un byte en el buffer de recepcio
 *
 *       Funcio:
 *           BYTE rxPut(BYTE d) 
 *
 *       Entrada:
 *           d: EL byte a escriure
 *
 *       Retorn:
 *           d: El byte escrit
 *
 *       Notes:
 *           ATENCIO: No es realitza cap comprovacio de limits
 *
 *************************************************************************/

static BYTE rxPut(BYTE d) {

    rxBuffer[rxPutIdx++] = d;
    if (rxPutIdx == sizeof(rxBuffer))
        rxPutIdx = 0;
    rxCount++;

    return d;
}


/*************************************************************************
 *
 *      Obte un byte del buffer de transmisio
 *
 *      Funcio:
 *          BYTE txGet(void)
 *
 *      Retorn:
 *          El byte lleigit
 *
 *      Notes:
 *          ATENCIO: No hi ha cap tipus de comprovacio de limits
 *
 *************************************************************************/

static BYTE txGet(void) {

    BYTE d = txBuffer[txGetIdx++];
    if (txGetIdx == sizeof(txBuffer))
        txGetIdx = 0;
    txCount--;

    return d;
}


/*************************************************************************
 *
 *       Escriu un byte en el buffer de transmisio
 *
 *       Funcio:
 *           BYTE txPut(BYTE d)
 *
 *       Entrada:
 *           d: EL byte a escriure
 *
 *       Retorn:
 *           d: El byte escrit
 *
 *       Notes:
 *           ATENCIO: No es realitza cap comprovacio de limits
 *
 *************************************************************************/

static BYTE txPut(BYTE d) {

    txBuffer[txPutIdx++] = d;
    if (txPutIdx == sizeof(txBuffer))
        txPutIdx = 0;
    txCount++;

    return d;
}


/*************************************************************************
 *
 *       Inicialitza el dispositiu I2C 
 *
 *       Funcio:
 *           void i2cSlaveInitialize(UINT8 addr)
 *
 *       Entrada:
 *           addr: Adressa
 *
 *************************************************************************/
 
void i2cSlaveInitialize(UINT8 addr) {

    // Configura la direccio dels ports
    //
    I2C_SCL_TRIS = 1;                  // SCL entrada digital
    I2C_SCL_ANSEL = 0;
    I2C_SDA_TRIS = 1;                  // SDA entrada digital
    I2C_SDA_ANSEL = 0;

    // Configura el modul de comunicacions
    //
    I2C_ADD = addr;                    // Selecciona l'adressa
    I2C_SSPM = 6;                      // I2C esclau
    I2C_SSPEN = 1;                     // Modul activat
    I2C_CKP = 1;                       // CLK actiu
    I2C_SEN = 1;                       // Clock Stretching Activat
    I2C_DHEN = 1;                      // Data hold enabled
    I2C_IF = 0;                        // Borra el indicador d'interrupcio
    I2C_IE = 1;                        // Activa les interrupcions SSP

    // Inicialitza els buffers de recepcio i de transmissio
    //
    rxCount = 0;
    rxGetIdx = 0;
    rxPutIdx = 0;

    txCount = 0;
    txGetIdx = 0;
    txPutIdx = 0;
}


/*************************************************************************
 *
 *       Purga els buffers i els deixa com acabat d'inicialitzar
 *
 *       Funcio:
 *           void i2cSlavePurge(void) 
 *
 *************************************************************************/

void i2cSlavePurge(void) {

    di();

    rxCount = 0;
    rxGetIdx = 0;
    rxPutIdx = 0;

    txCount = 0;
    txGetIdx = 0;
    txPutIdx = 0;

    ei();
}


/*************************************************************************
 *
 *       Tasques de gestio del I2C. Cal executar periodicament o 
 *       per mitja d'interrupcions del MSSP
 *
 *       Funcio:
 *           void i2cSlaveInterrupt(void)
 *
 *************************************************************************/

void i2cSlaveInterrupt() {

    BYTE flags; 
    BYTE data;
        
    // Obte l'estat del SSP1. Nomes son utils
    // els bits DA, S, RW i BF
    //  
    flags = I2C_STAT & 0b00101101;
            
    // Estat 1: Operacio d'escriptura, l'ultim byte en una adressa
    // DA=0, S=1, RW=0, BF=1
    //  
    if (flags == 0b00001001) {
        data = SSP1BUF; 
        check = data;
        lastError = I2CS_OK;
        state = STATE_WaitLength;
    }

    // Estat 2: Operacio d'escriptura, l'ultim byte es una dada
    // DA=1, S=1, RW=0, BF=1
    //  
    else if (flags == 0b00101001) { 
        if (I2C_ACKTIM == 1) { // Comprova si es el 8e CLK
            data = I2C_BUF;
            switch (state) {
                case STATE_WaitLength:
                    count = data;
                    check += data;
                    I2C_ACKDT = 0;  // ACK
                    if (count)
                        state = STATE_WaitData;
                    else
                        state = STATE_WaitCheck;
                    break;

                case STATE_WaitData:
                    count -= 1;
                    check += data;
                    if (rxCount < sizeof(rxBuffer))                        
                        rxPut(data);
                    else
                        lastError = I2CS_ERR_FULL;
                    I2C_ACKDT = 0;  // ACK
                    if (!count)
                        state = STATE_WaitCheck;
                    break;

                case STATE_WaitCheck:
                    if (data != 0xFF || data != check)
                        lastError = I2CS_ERR_CHECKSUM;
                    I2C_ACKDT = 0;  // ACK
                    break;
            }
        }
    }

    // Estat 3: Operacio de lectura, l'ultim byte en una adressa
    // DA=0, S=1, RW=1, BF=1
    //  
    else if (flags == 0b00001101) {
        check = I2C_BUF;    // Llegeix l'adressa
        count = txCount;
        check += count;
        I2C_BUF = count;    // Transmiteix el numero de bytes
    }

    // Estat 4: Operacio de lectura, l'ultim byte es una dada
    // DA=1, S=1, RW=1, BF=0
    // CKP=0
    //  
    else if (flags == 0b00101100 && (I2C_CKP == 0)) {

        if (count) {
            data = txGet();
            check += data;
            I2C_BUF = data;  // Transmiteix les dades
            count -= 1;
        }
        else
            I2C_BUF = check; // Transmiteix el digit de control
    }

    I2C_CKP = 1;
}


/*************************************************************************
 *
 *       Obte les rebudes
 *
 *       Funcio:
 *           UINT8 i2cSlaveRead(BYTE *data, UINT8 dataSize)
 *
 *       Entrada:
 *           data    : Punter al buffer de dades
 *           dataSize: Tamany en bytes del buffer
 *
 *       Retorn:
 *          Numero de bytes lleigits
 *
 *************************************************************************/

UINT8 i2cSlaveRead(BYTE *data, UINT8 dataSize) {

    UINT8 i;

    // Desactiva les interrupcions
    //
    di();

    // Llegeix les dades del buffer de recepcio
    //
    for (i = 0; (i < dataSize) && rxCount; i++)
        data[i] = rxGet();

    // Activa les interrupcions
    //
    ei();

    return i;
}


/*************************************************************************
 *
 *       Escriu una trama
 *
 *       Funcio:
 *           UINT8 i2cSlaveWrite(BYTE *data, UINT8 dataLen)
 *
 *       Entrada:
 *           data   : Buffer de dades
 *           dataLen: Numero de bytes en el buffer
 *
 *       Retorn:
 *           Numero de bites lleigits
 *
 *************************************************************************/

UINT8 i2cSlaveWrite(BYTE *data, UINT8 dataLen) {

    UINT8 i;

    // Desactiva les interrupcions
    //
    di();

    // Escriu les dades al buffer de transmisio
    //
    for (i = 0; (i < dataLen) && (txCount < sizeof(txBuffer)); i++)
        txPut(data[i]);

    // Activa les interrupcions
    //
    ei();

    return i;
}


#endif