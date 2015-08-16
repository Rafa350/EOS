#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosDigOutput.h"


static void task1(void *params) {

    TRISDbits.TRISD0 = 0;
    while (true) {
        PORTDbits.RD0 = !LATDbits.LATD0;
        eosTaskDelay(300);
    }
}

static void task2(void *params) {
   
    TRISDbits.TRISD1 = 0;
    while (true) {
        PORTDbits.RD1 = !LATDbits.LATD1;
        eosTaskDelay(200);
    }
}


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           void appSetup(void)
 *
 *************************************************************************/

void appSetup(void) {
    
    eosTaskCreate(0, 512, task1, NULL);
    eosTaskCreate(0, 512, task2, NULL);
    
    eosDigOutputServiceInitialize(NULL);
}


/*************************************************************************
 *
 *       Bucle principal de l'aplicacio
 *
 *       Funcio:
 *           void usrTask(void)
 *
 *************************************************************************/

void appTask(void) {

    eosTaskRun();
}
