#include "eos.h"
#include "osal/osal.h"
#include "osal/osalThread.h"
#include "osal/osalMsgQueue.h"



/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #1
/// \param parameter: Parametre opcional.
///
static void task1(void *parameter) {
    
    while (true) {
        
        osalDelay(250);
        
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #2
/// \param parameter: Parametre opcional.
///
static void task2(void *parameter) {
    
    while (true) {
    
        osalDelay(350);
        
    }
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {
    
    TaskInitializeInfo info;

    // Inicialitza els parametres comuns
    //
    info.options = OSAL_TASK_PRIORITY_NORMAL;
    info.stackSize = 512;    

    // Inicialitza la tasca #1
    //
    info.name = "task1";
    info.function = task1;
    info.params = (void*) 0;
    osalTaskCreate(&info);

    // Inicialitza la tasca #2
    //
    info.name = "task2";
    info.function = task2;
    info.params = (void*)0;
    osalTaskCreate(&info);
    
    osalStartScheduler();
}
