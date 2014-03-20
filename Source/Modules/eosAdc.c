#include "eos.h"


#ifdef eosUSE_ADC


typedef struct {
    UINT8 chanel;
    UINT16 value;
} ANALOGIC;

static ANALOGIC analogic[EOS_NUM_ANALOGIC];
static UINT8 channel;



/*************************************************************************
 *
 *       Inicialitza les entrades analoguiques
 *
 *       Funcio:
 *           void anaInitialize(void)
 *
 *************************************************************************/

void anaInitialize(void) {

    PHY_ANA0_TRIS = 1;
    PHY_ANA0_ANSEL = 1;
    analogic[0].chanel = PHY_ANA0_Ch;
    analogic[0].value = 0;

#if NUM_ANALOGIC > 1
    PHY_ANA1_TRIS = 1;
    PHY_ANA1_ANSEL = 1;
    analogic[1].chanel = PHY_ANA1_Ch;
    analogic[1].value = 0;
#endif

#if NUM_ANALOGIC > 2
    PHY_ANA2_TRIS = 1;
    PHY_ANA2_ANSEL = 1;
    analogic[2].chanel = PHY_ANA2_Ch;
    analogic[2].value = 0;
#endif

#if NUM_ANALOGIC > 3
    PHY_ANA3_TRIS = 1;
    PHY_ANA3_ANSEL = 1;
    analogic[3].chanel = PHY_ANA3_Ch;
    analogic[3].value = 0;
#endif

    // Configura el conversor AD
    //
#if defined(_16F1823) || defined(_16F1825) || defined(_16F1829)
    ADCON1bits.ADPREF = 0;        // Referencia de voltatge VCC
    ADCON1bits.ADCS = 2;          // Divisor del rellotge Fosc/32
    ADCON1bits.ADFM = 1;          // Aliniacio per la dreta

#elif defined(_18F46K22)
    ADCON1bits.PVCFG = 0;         // +Vref = VDD
    ADCON1bits.NVCFG = 0;         // -Vref = VSS
    ADCON2bits.ADCS = 3;          // Oscilador intern 600KHz
    ADCON2bits.ACQT = 0;          // Adquisition time
    ADCON2bits.ADFM = 1;          // Aliniacio per la dreta
#else
#error "CPU no soportada"
#endif

    ADIE = 0;                     // No genera interrupcions
    ADIF = 0;                     // Borra el flag d'interrupcio

    channel = 0;                  // Numero de canal a procesar
}


/*************************************************************************
 *
 *       Tasca de control de les entrades analogiques. Es crida en
 *       cada cicle
 *
 *       Funcio:
 *           void anaService(void)
 *
 *************************************************************************/

void anaService(void) {

    unsigned delay;
    UINT8 inp;

    for (inp = 0; inp < NUM_ANALOGIC; inp++) {
        ADCON0bits.CHS = analogic[inp].chanel;
        ADCON0bits.ADON = 1;                // Activa el conversor

        // Retard pel canvi de canal
        //
        for (delay = 0; delay < 1000; delay++)
            NOP();

#if defined(_16F1823) || defined(_16F1825) || defined(_16F1829)
        ADCON0bits.ADGO = 1;                // Inicia la conversio
        while (ADCON0bits.ADGO)             // Espera que finalitzi
            continue;

#elif defined(_18F46K22)
        ADCON0bits.GODONE = 1;              // Inicia la conversio
        while (ADCON0bits.GODONE)           // Espera que finalitzi
            continue;
#else
#error "CPU no soportada"
#endif

        analogic[inp].value = ((UINT16) ADRESH << 8) | ADRESL;
    }
}


/*************************************************************************
 *
 *       Tasca de control de les entrades analogiques. Es crida
 *       cada 1ms
 *
 *       Funcio:
 *           void anaTMRInterupt(void)
 *
 *************************************************************************/

void anaTMRInterrupt(void) {

}


/*************************************************************************
 *
 *       Tasca de control de les entrades analogiques. Es crida
 *       al produir-se una interrupcio del conversor AD
 *
 *       Funcio:
 *           void anaADCInterupt(void)
 *
 *************************************************************************/

void anaADCInterrupt(void) {

}


/*************************************************************************
 *
 *       Llegeix el valor d'una entrada analogica
 *
 *       Funcio:
 *           UNIT16 outGet(UINT8 inp)
 *
 *       Entrada:
 *           inp: Numero d'entrada analoguique
 *
 *       Retorn:
 *           El valor de l'entrada analogica (0..1024)
 *
 *************************************************************************/

UINT16 anaGet(UINT8 inp) {

    if (inp < NUM_ANALOGIC)
        return analogic[inp].value;
    else
        return 0;
}


#endif