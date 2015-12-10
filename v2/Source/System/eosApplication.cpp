#include "System/eosApplication.hpp"
#include "HAL/halSYS.h"
#include "FreeRTOS.h"
#include "task.h"


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
eos::Application::Application() {
    
    halSYSInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Executa l'aplicacio.
///
void eos::Application::execute() {
        
    onInitialize();
    onExecute();
    vTaskStartScheduler();
    onTerminate();
}
