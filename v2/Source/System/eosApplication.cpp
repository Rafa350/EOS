#include "System/eosApplication.hpp"
#include "HAL/halSYS.h"
#include "FreeRTOS.h"
#include "task.h"


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           eos::Application::Application() 
 *
 *************************************************************************/

eos::Application::Application() {
    
    halSYSInitialize();
}


/*************************************************************************
 *
 *       Inicia el planificador de tasques
 * 
 *       Funcio:
 *           void eos::Application::execute() 
 *
 *************************************************************************/

void eos::Application::execute() {
        
    vTaskStartScheduler();
}
