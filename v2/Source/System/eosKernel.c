#include "eos.h"
#include "system/devcon/sys_devcon.h"
#include "system/int/sys_int.h"
#include "HardwareProfile.h"


SYS_DEVCON_INIT devconInit = {
    .moduleInit = {0},
};

//static eosTickServiceHandle hTickService = NULL;
static SYS_MODULE_OBJ hDevCon;


// Funcions a definir en l'aplicacio del usuari
//
extern void appSetup(void);
extern void appTask(void);


/*************************************************************************
 *
 *       Inicialitza el sistema
 *
 *       Funcio:
 *           void eosSetup() 
 *
 *************************************************************************/

static void eosSetup() {
    
    // Inicialitzacio del sistema
    //
    hDevCon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*) &devconInit);
    SYS_DEVCON_PerformanceConfig(CLOCK_SYSTEM_HZ);

    // Inicialitza les interrupcions
    //
    SYS_INT_Initialize();
    
    // Desactiva els ports analogics
    //
    AD1PCFG = 0xFFFF;
}


/*************************************************************************
 *
 *       Procesa les tasques del sistema
 *
 *       Funcio:
 *           void eosTask()
 * 
 *************************************************************************/

static void eosTask() {

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

    eosSetup();
    appSetup();
    
    while (true) {
        eosTask();
        appTask();
    }
}
