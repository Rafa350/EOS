#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
AppLoopService::AppLoopService():
    task(taskStackSize, taskPriority, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
///
void AppLoopService::run() {
    
    setup();
    while (true) {
        loop();
        //Task::delay(100); // TIME_SLICING 
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio d'inicialitzacio.
///
void AppLoopService::setup() {
    
}


/// ----------------------------------------------------------------------
/// \brief Funcio del bucle d'execucio.
///
void AppLoopService::loop() {
    
}

