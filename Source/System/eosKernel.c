#include "eos.h"
#include "Services/eosTick.h"
#include "system/devcon/sys_devcon.h"
#include "peripheral/int/plib_int.h"
#include "HardwareProfile.h"


#ifdef eos_OPTION_FREERTOS
#include "freertos.h"
#endif


SYS_DEVCON_INIT devconInit = {
    .moduleInit = {0},
};


static eosHTickService hTickService;


// Funcions a definir en l'aplicacio del usuari
//
extern void appSetup(void);
extern void appLoop(void);


void eosTaskInitialize(void) {
}


void eosTaskCreate(void) {
}


void eosTaskSchedule(void) {

#ifdef eos_OPTION_FREERTOS
    vTaskStartSchedule();

#else
#endif
}


/*************************************************************************
 *
 *       Obte el handler del servei TICK intern
 *
 *       Funcio:
 *           eosTickService eosGetTickServiceHandle(void)
 *
 *       Retorn:
 *           El handler del servei TICK
 *
 *************************************************************************/

eosHTickService eosGetTickServiceHandle(void) {

    return hTickService;
}


/*************************************************************************
 *
 *       Punt d'entrada del sistema EOS
 *
 *       Funcio:
 *           void eosMain(void)
 *
 *************************************************************************/

void eosMain(void) {

    // Inicialitzacio del sistema
    //
    SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*) &devconInit);
    SYS_DEVCON_PerformanceConfig(CLOCK_SYSTEM_HZ);
    PLIB_INT_MultiVectorSelect(INT_ID_0);

    // Inicialitza el servei TICK
    //
    eosTickServiceParams tickServiceParams;
    eosTickServiceInitialize(&tickServiceParams, &hTickService);

    // Inicialitzacio de l'aplicacio d'usuari
    //
    appSetup();
    
    // Autoritza les interrupcions
    //
    eosEnableInterrupts();

    while (TRUE) {

        // Procesa les tasques del sistema
        //
        eosTickServiceTask(hTickService);

        // Procesa les tasques de l'aplicacio d'usuari
        //
        appLoop();
    }
}
