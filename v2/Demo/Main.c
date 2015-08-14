#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosTick.h"


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

static void task3(void *params) {

    eosTickServiceParams serviceParams;
    eosTickServiceHandle hService = eosTickServiceInitialize(&serviceParams);
    while (true) {
        eosTickServiceTask(hService);
        eosTaskDelay(100);
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
    
    static eosTaskParams taskParams[3] = {
        {
            .name = "task 1",
            .function = task1,
            .params = NULL,
            .stackSize = 1024                    
        },
        {
            .name = "task 2",
            .function = task2,
            .params = NULL,
            .stackSize = 1024                    
        },
        {
            .name = "task 3",
            .function = task3,
            .params = NULL,
            .stackSize = 1024                    
        }
    };

    unsigned i;
    for (i = 0; i < sizeof(taskParams) / sizeof(taskParams[0]); i++)
        eosTaskCreate(&taskParams[i]);
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
