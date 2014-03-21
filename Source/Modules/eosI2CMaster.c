#include "eos.h"

#ifdef eosUSE_I2CMASTER

#ifndef eosCFG_I2CMASTER_TxBufferSize
#define eofCFG_I2CMASTER_TxBufferSize  32
#endif

#ifndef eosCFG_I2CMASTER_RxBufferSize
#define eosCFG_I2CMASTER_RxBufferSize  32
#endif

#ifndef eosCFG_I2CMASTER_MaxFrameSize
#define eosCFG_I2CMASTER_MaxFrameSize  16
#endif

#if (I2CM_TX_BUFFER < I2CM_MAX_FRAME_SIZE) || \
    (I2CM_RX_BUFFER < I2CM_MAX_FRAME_SIZE)
#error El tamany del buffer cal que sigui major o igual al tamany de trama
#endif

#define I2CM_TX_BUFSIZE      eosCFG_I2CMASTER_TxBufferSize
#define I2CM_RX_BUFSIZE      eosCFG_I2CMASTER_RxBufferSize

#if defined(_12F1822)
#define I2C_SDA_TRIS         TIRSAbits.TRISA2
#define I2C_SCL_TRIS         TRISAbits.TRISA1
#define I2C_SDA_ANSEL        ANSELAbits.ANSA2
#define I2C_SCL_ANSEL        ANSELAbits.ANSA1


#elif defined(_16F1823) || defined(_16F1825)

#define I2C_SDA_TRIS         TRISCbits.TRISC1
#define I2C_SCL_TRIS         TRISCbits.TRISC0
#define I2C_SDA_ANSEL        ANSELCbits.ANSC1
#define I2C_SCL_ANSEL        ANSELCbits.ANSC0

#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKEN            SSP1CON2bits.ACKEN
#define I2C_ACKSTAT          SSP1CON2bits.ACKSTAT
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_CON2             SSP1CON2
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_PEN              SSP1CON2bits.PEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#define I2C_SMP              SSP1STATbits.SMP
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_RCEN             SSP1CON2bits.RCEN
#define I2C_BF               SSP1STATbits.BF
#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF

#elif defined(_16F1829)

#if defined(I2CM_SSP1)
#define I2C_SDA_TRIS         TRISBbits.TRISB4
#define I2C_SCL_TRIS         TRISBbits.TRISB6
#define I2C_SDA_ANSEL        ANSELBbits.ANSB4
#define I2C_SCL_ANSEL        ANSELBbits.ANSB6

#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKEN            SSP1CON2bits.ACKEN
#define I2C_ACKSTAT          SSP1CON2bits.ACKSTAT
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_CON2             SSP1CON2
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_PEN              SSP1CON2bits.PEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#define I2C_SMP              SSP1STATbits.SMP
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_RCEN             SSP1CON2bits.RCEN
#define I2C_BF               SSP1STATbits.BF
#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF

#elif defined(I2CM_SSP2)
#define I2C_SDA_TRIS         TRISBbits.TRISB5
#define I2C_SCL_TRIS         TRISBbits.TRISB7
#define I2C_SDA_ANSEL        ANSELBbits.ANSB5
#define I2C_SCL_ANSEL        ANSELBbits.ANSB7

#define I2C_ADD              SSP2ADD
#define I2C_CKP              SSP2CON1bits.CKP
#define I2C_ACKDT            SSP2CON2bits.ACKDT
#define I2C_ACKEN            SSP2CON2bits.ACKEN
#define I2C_ACKSTAT          SSP2CON2bits.ACKSTAT
#define I2C_STAT             SSP2STAT
#define I2C_BUF              SSP2BUF
#define I2C_CON2             SSP2CON2
#define I2C_SSPM             SSP2CON1bits.SSPM
#define I2C_SSPEN            SSP2CON1bits.SSPEN
#define I2C_SEN              SSP2CON2bits.SEN
#define I2C_PEN              SSP2CON2bits.PEN
#define I2C_DHEN             SSP2CON3bits.DHEN
#define I2C_SMP              SSP2STATbits.SMP
#define I2C_SSPEN            SSP2CON1bits.SSPEN
#define I2C_SSPM             SSP2CON1bits.SSPM
#define I2C_RCEN             SSP2CON2bits.RCEN
#define I2C_BF               SSP2STATbits.BF
#define I2C_IE               SSP2IE
#define I2C_IF               SSP2IF
#endif


#elif defined(_18F23K22) || defined(_18F24K22) || defined(_18F25K22) || defined(_18F26K22) || \
      defined(_18F43K22) || defined(_18F44K22) || defined(_18F45K22) || defined(_18F46K22)
#if defined(I2CM_SSP1)
#define I2C_SDA_TRIS         TRISCbits.TRISC3
#define I2C_SCL_TRIS         TRISCbits.TRISC4
#define I2C_SDA_ANSEL        ANSELCbits.ANSC3
#define I2C_SCL_ANSEL        ANSELCbits.ANSC4

#define I2C_ADD              SSP1ADD
#define I2C_CKP              SSP1CON1bits.CKP
#define I2C_ACKDT            SSP1CON2bits.ACKDT
#define I2C_ACKEN            SSP1CON2bits.ACKEN
#define I2C_ACKSTAT          SSP1CON2bits.ACKSTAT
#define I2C_STAT             SSP1STAT
#define I2C_BUF              SSP1BUF
#define I2C_CON2             SSP1CON2
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SEN              SSP1CON2bits.SEN
#define I2C_PEN              SSP1CON2bits.PEN
#define I2C_DHEN             SSP1CON3bits.DHEN
#define I2C_SMP              SSP1STATbits.SMP
#define I2C_SSPEN            SSP1CON1bits.SSPEN
#define I2C_SSPM             SSP1CON1bits.SSPM
#define I2C_RCEN             SSP1CON2bits.RCEN
#define I2C_BF               SSP1STATbits.BF
#define I2C_IE               SSP1IE
#define I2C_IF               SSP1IF

#elif defined(I2CM_SSP2)
#define I2C_SDA_TRIS         TRISDbits.TRISD1
#define I2C_SCL_TRIS         TRISDbits.TRISD0
#define I2C_SDA_ANSEL        ANSELDbits.ANSD1
#define I2C_SCL_ANSEL        ANSELDbits.ANSD0

#define I2C_ADD              SSP2ADD
#define I2C_CKP              SSP2CON1bits.CKP
#define I2C_ACKDT            SSP2CON2bits.ACKDT
#define I2C_ACKEN            SSP2CON2bits.ACKEN
#define I2C_ACKSTAT          SSP2CON2bits.ACKSTAT
#define I2C_STAT             SSP2STAT
#define I2C_BUF              SSP2BUF
#define I2C_CON2             SSP2CON2
#define I2C_SSPM             SSP2CON1bits.SSPM
#define I2C_SSPEN            SSP2CON1bits.SSPEN
#define I2C_SEN              SSP2CON2bits.SEN
#define I2C_PEN              SSP2CON2bits.PEN
#define I2C_DHEN             SSP2CON3bits.DHEN
#define I2C_SMP              SSP2STATbits.SMP
#define I2C_SSPEN            SSP2CON1bits.SSPEN
#define I2C_SSPM             SSP2CON1bits.SSPM
#define I2C_RCEN             SSP2CON2bits.RCEN
#define I2C_BF               SSP2STATbits.BF
#define I2C_IE               SSP2IE
#define I2C_IF               SSP2IF
#endif
#else
#error CPU no soportada
#endif


typedef enum {
    STATE_Ready,
    STATE_SendADDR,
    STATE_SendLENGTH,
    STATE_SendDATA,
    STATE_SendCHECK,
    STATE_WaitACK,
    STATE_RecvACK,
    STATE_RecvLENGTH,
    STATE_RecvDATA,
    STATE_RecvCHECK,
    STATE_Stop,
    STATE_StopCompleted,
    STATE_StopPause
} STATE;


static STATE state;               // Estat de la maquina
static UINT8 pauseCnt;            // Contador per la pausa despres de STOP
static UINT8 lastError;           // Codi d'error de l'ultima operacio
static BYTE address;              // Adressa del esclau
static UINT8 check;               // Check-sum
static UINT8 count;               // Contador de bytes

static BYTE txBuffer[I2CM_TX_BUFSIZE];  // Buffer de transmissio
static UINT8 txCount;             // Numero de bytes en el buffer
static UINT8 txPutIdx;            // Index per insertar en el buffer
static UINT8 txGetIdx;            // Index per recollir del buffer

static BYTE rxBuffer[I2CM_TX_BUFSIZE];  // Buffer de recepcio
static UINT8 rxCount;             // Numero de bytes en el buffer
static UINT8 rxPutIdx;            // Index per insertar en el buffer
static UINT8 rxGetIdx;            // Index per recollir del buffer


/*************************************************************************
 *
 *       Escriu un byte en el buffer de transmissio
 *
 *       Funcio:
 *           BYTE txPut(BYTE b)
 *
 *       Entrada:
 *           b: El byte a escriure
 *
 *       Retorn:
 *           El byte escrit
 *
 *       Notes:
 *          La funcio ajusta txCount, i txPut, pero no far cap
 *          tipus de verificacio que impedeixi sobreescriure
 *          les dades de buffer
 *
 *************************************************************************/

static BYTE txPut(BYTE b) {

    txBuffer[txPutIdx++] = b;
    if (txPutIdx == sizeof(txBuffer))
        txPutIdx = 0;
    txCount++;

    return b;
}


/*************************************************************************
 *
 *       Llegeix un byte del buffer de transmissio
 *
 *       Funcio:
 *           BYTE txGet(void)
 * 
 *       Retorn:
 *           El byte lleigit
 *
 *       Notes:
 *          La funcio ajusta txCount, i txGet, pero no far cap
 *          tipus de verificacio que impedeixi tornar a lleigir
 *          dades antigues
 *
 *************************************************************************/

static BYTE txGet(void) {

    BYTE b = txBuffer[txGetIdx++];
    if (txGetIdx == sizeof(txBuffer))
        txGetIdx = 0;
    txCount--;

    return b;
}


/*************************************************************************
 *
 *       Escriu un byte en el buffer de recepcio
 *
 *       Funcio:
 *           BYTE rxPut(BYTE b)
 *
 *       Entrada:
 *           b: El byte a escriure
 *
 *       Retorn:
 *           El byte escrit
 *
 *       Notes:
 *          La funcio ajusta rxCount, i rxPut, pero no far cap
 *          tipus de verificacio que impedeixi sobreescriure
 *          les dades de buffer
 *
 *************************************************************************/

static BYTE rxPut(BYTE b) {

    rxBuffer[rxPutIdx++] = b;
    if (rxPutIdx == sizeof(rxBuffer))
        rxPutIdx = 0;
    rxCount++;

    return b;
}


/*************************************************************************
 *
 *       Llegeix un byte del buffer de recepcio
 *
 *       Funcio:
 *           BYTE rxGet(void)
 *
 *       Retorn:
 *           El byte lleigit
 *
 *       Notes:
 *          La funcio ajusta rxCount, i rxGet, pero no far cap
 *          tipus de verificacio que impedeixi tornar a lleigir
 *          dades antigues
 *
 *************************************************************************/

static BYTE rxGet(void) {

    BYTE b = rxBuffer[rxGetIdx++];
    if (rxGetIdx == sizeof(rxBuffer))
        rxGetIdx = 0;
    rxCount--;

    return b;
}


/*************************************************************************
 *
 *       Inicia l'escriptura
 *
 *       Funcio:
 *           void startWrite(UINT8 addr)
 *
 *       Entrada:
 *           addr: L'adressa del esclau
 *
 *************************************************************************/

static void startWrite(UINT8 addr) {

    lastError = I2CM_OK;
    address = addr & 0xFE;        // Posa el bit R/W a 0
    state = STATE_SendADDR;
    I2C_SEN = 1;
}


/*************************************************************************
 *
 *       Inicia la lecture
 *
 *       Funcio:
 *           void startRead(UINT8 addr)
 *
 *       Entrada:
 *           addr   : L'adressa del esclau
 *
 *************************************************************************/

static void startRead(UINT8 addr) {

    lastError = I2CM_OK;
    address = addr | 0x01;        // Posa el bit R/W a 1
    state = STATE_SendADDR;
    I2C_SEN = 1;
}


/*************************************************************************
 *
 *       Inicialitza la gestio de les comunicacions I2C
 *
 *       Funcio:
 *           void i2cMasterInitialize(void)
 *
 *************************************************************************/

void i2cMasterInitialize(void) {

    I2C_SDA_TRIS = 1;        // SDA i SCL son entrades digitals
    I2C_SDA_ANSEL = 0;
    I2C_SCL_TRIS = 1;
    I2C_SCL_ANSEL = 0;
    I2C_SMP = 1;             // Slew rate control disabled
    I2C_SSPEN = 1;           // I2C enabled
    I2C_SSPM = 8;            // I2C master mode
    //I2C_ADD = 0x9F;          // 100Khz @ 64Mhz Fosc
    I2C_ADD = 0x4F;          // 100Khz @ 32Mhz Fosc

    pauseCnt = 0;
    state = STATE_Ready;

    // Inicialitza el buffer de transmissio
    //
    txCount = 0;
    txGetIdx = 0;
    txPutIdx = 0;

    // Inicialitza el buffer de recepcio
    //
    rxCount = 0;
    rxGetIdx = 0;
    rxPutIdx = 0;

    I2C_IF = 0;
    I2C_IE = 1;
}


/*************************************************************************
 *
 *       Buida els buffers de transmissio i recepcio
 *
 *       Funcio:
 *           void i2cMasterPurge(void)
 *
 **************************************************************************/

void i2cMasterPurge(void) {

    di();

    txCount = 0;
    txGetIdx = 0;
    txPutIdx = 0;

    rxCount = 0;
    rxGetIdx = 0;
    rxPutIdx = 0;

    pauseCnt = 0;
    state = STATE_Ready;

    I2C_PEN = 1;
    while (I2C_PEN)
        continue;

    ei();
}


/*************************************************************************
 *
 *       Procesa les interrupcions del temporitzador cada 1ms
 *
 *       Funcio:
 *           void i2cMasterTMRInterrupt(void)
 *
 *************************************************************************/

void i2cMasterTMRInterrupt(void) {

    if (pauseCnt && (state == STATE_StopPause)) {
        pauseCnt--;
        if (!pauseCnt)
            state = STATE_Ready;
    }
}


/*************************************************************************
 *
 *       Procesa les interrupcions de SSP
 *
 *       Funcio:
 *           void i2cMasterInterrupt(void)
 *
 *************************************************************************/

void i2cMasterInterrupt(void) {

    UINT8 data;

    switch (state) {

        // Estat SendADDR
        // Arriba aqui al finalitzar la condicio START. Envia l'adressa
        //
        case STATE_SendADDR:
            I2C_BUF = address;
            if ((address & 1) == 0) {
                check = address;
                count = (txCount > I2C_MAX_FRAMESIZE) ? I2C_MAX_FRAMESIZE : txCount;
                state = STATE_SendLENGTH;
            }
            else
                state = STATE_WaitACK;
            break;

        // Estat SendXXXX
        // Si ha rebut ACK del esclau, envia el seguent byte de dades. Si
        // acaba d'enviar l'ultim byte, genera la condicio STOP en el bus
        //
        case STATE_SendLENGTH:
        case STATE_SendDATA:
        case STATE_SendCHECK:
            if (I2C_ACKSTAT == 0) {
                switch (state) {
                    case STATE_SendLENGTH: 
                        data = count;
                        check += count;
                        if (count)
                            state = STATE_SendDATA;
                        else
                            state = STATE_SendCHECK;
                        break;
               
                    case STATE_SendDATA:
                        data = txGet();
                        check += data;
                        count -= 1;
                        if (!count)
                            state = STATE_SendCHECK;
                        break;

                    case STATE_SendCHECK:
                        data = check;
                        state = STATE_Stop;
                        break;
                }
                I2C_BUF = data;
            }
            else {
                I2C_PEN = 1;
                state = STATE_StopCompleted;
            }
            break;

        // Estat WaitACK
        // Si ha generat ACK del esclau, ja pot començar la recepcio de dades,
        // en cas contrari genera la condicio STOP en el bus
        //
        case STATE_WaitACK:
            if (I2C_ACKSTAT == 0) {
                I2C_RCEN = 1;
                state = STATE_RecvLENGTH;
            }
            else {
                I2C_PEN = 1;
                state = STATE_StopCompleted;
            }
            break;

        // Estat RecvACK
        // El mestre ha acabat de generar el ACK, ja pot rebre el seguent
        // byte de dades
        //
        case STATE_RecvACK:
            I2C_RCEN = 1;
            if (count)
                state = STATE_RecvDATA;
            else
                state = STATE_RecvCHECK;
            break;

        // Estat RecvXXXX
        // S'ha rebut un byte, el carrega i es prepara per rebre el seguent
        //
        case STATE_RecvLENGTH:
        case STATE_RecvDATA:
        case STATE_RecvCHECK:
            data = I2C_BUF;
            switch (state) {
                case STATE_RecvLENGTH:
                    count = data;
                    if (count > (sizeof(rxBuffer) - rxCount)) {
                        I2C_ACKDT = 1;                // NACK (ACK = 1)
                        state = STATE_Stop;
                    }
                    else {
                        check = address + data;
                        I2C_ACKDT = 0;                // ACK (ACK = 0)
                        state = STATE_RecvACK;
                    }
                    break;
                        
                case STATE_RecvDATA:
                    rxPut(data);
                    check += data;
                    count -= 1;
                    I2C_ACKDT = 0;                    // ACK (ACK = 0)
                    state = STATE_RecvACK;
                    break;
                        
                case STATE_RecvCHECK:
                    if ((data != 0xFF) && (data != check))
                        lastError = I2CM_ERR_CHECKSUM;
                    I2C_ACKDT = 1;                    // NACK (ACK = 1)
                    state = STATE_Stop;
                    break;
            }
            I2C_ACKEN = 1;     // Genera la sequencia ACK
            break;

        // Estat Stop
        // Inicia la condicio STOP en el bus
        //
        case STATE_Stop:
            I2C_PEN = 1;
            state = STATE_StopCompleted;
            break;

        // Estat StopCompleted
        // Ha finalitzat la condicio STOP del bus. Transmissio finalitzada
        //
        case STATE_StopCompleted:
            pauseCnt = 6;
            state = STATE_StopPause;
            break;
    }
}


/*************************************************************************
 *
 *       Reb un bloc de bytes
 *
 *       Funcio:
 *           UINT8 i2cMasterRead(UINT8 addr, BYTE *data, UINT8 dataSize)
 *
 *       Entrada:
 *           addr   : Adressa del escalu
 *           data   : Bloc de dades
 *           dataSze: Tamany del bloc de dades
 *
 *       Retorn:
 *           Numero de bytes lleigits
 *
 *************************************************************************/

UINT8 i2cMasterRead(UINT8 addr, BYTE *data, UINT8 dataSize) {

    UINT8 i;

    di();
    if (!rxCount) {
        if (state != STATE_Ready) {
            ei();
            return 0;
        }
        else
            startRead(addr);
    }

    i = 0;
    while ((rxCount > 0) && (i < dataSize)) {
        if (rxCount)
            data[i++] = rxGet();
    }
    ei();

    return i;
}


/*************************************************************************
 *
 *       Transfereix un bloc de bytes a l'adresa especificada
 *
 *       Funcio:
 *           UINT8 i2cMasterWrite(UINT8 addr, BYTE *data, UINT8 dataLen)
 *
 *       Entrada:
 *           addr   : Addresa del dispositiu del esclau
 *           data   : Bloc de dades
 *           dataLen: Numero de bytes en les dades
 *
 *       Retorn:
 *           Numero de bytes transmessos
 *
 *************************************************************************/

UINT8 i2cMasterWrite(UINT8 addr, BYTE *data, UINT8 dataLen) {

    UINT8 i;

    di();
    if (state != STATE_Ready) {
        ei();
        return 0;
    }

    // Transfereix les dades al buffer de transmissio
    //
    for (i = 0; (i < dataLen) && (txCount < sizeof(txBuffer)); i++)
        txPut(data[i]);

    // Inicia la comunicacio. A partir d'aquest moment es realitza tot
    // el proces per interrupcions
    //
    startWrite(addr);

    ei();
   
    return i;
}



UINT8 i2cMasterWritePending(void) {

    UINT8 pending;

    di();
    pending = txCount;
    ei();

    return pending;
}


UINT8 i2cMasterReadPending(void) {

    UINT8 pending;

    di();
    pending = rxCount;
    ei();

    return pending;
}


UINT8 i2cMasterLastError(void) {

    return lastError;
}


#endif