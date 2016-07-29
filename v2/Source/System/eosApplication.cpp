#include "System/eosApplication.hpp"
#include "HAL/halSYS.h"
#include "FreeRTOS.h"
#include "task.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
Application::Application() {
    
    halSYSInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Executa l'aplicacio.
///
void Application::execute() {
        
    onInitialize();
    vTaskStartScheduler();
    onTerminate();
}
