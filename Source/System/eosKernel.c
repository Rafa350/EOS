#include "eos.h"
#include "Services/eosTick.h"
#include "system/devcon/sys_devcon.h"
#include "system/int/sys_int.h"
#include "HardwareProfile.h"


#ifdef eos_OPTION_FREERTOS
#include "freertos.h"
#endif


SYS_DEVCON_INIT devconInit = {
    .moduleInit = {0},
};


static eosTickServiceHandle hTickService;


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
 *           eosTickServiceHandle eosGetTickServiceHandle(void)
 *
 *       Retorn:
 *           El handler del servei TICK
 *
 *************************************************************************/

eosTickServiceHandle eosGetTickServiceHandle(void) {

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

    // Inicialitza les interrupcions
    //
    SYS_INT_Initialize();
    SYS_INT_Enable();

    // Inicialitza el servei TICK
    //
    eosTickServiceParams tickServiceParams;
    hTickService = eosTickServiceInitialize(&tickServiceParams);

    // Inicialitzacio de l'aplicacio d'usuari
    //
    appSetup();
    
    while (true) {

        // Procesa les tasques del sistema
        //
        eosTickServiceTask(hTickService);

        // Procesa les tasques de l'aplicacio d'usuari
        //
        appLoop();
    }
}
