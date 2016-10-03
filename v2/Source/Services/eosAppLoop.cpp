#include "Services/eosAppLoop.hpp"


using namespace eos;


static const char *serviceName = "AppLoopService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
AppLoopService::AppLoopService(
    Application *application):
    
    Service(application, serviceName, stackSize, priority) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
///
void AppLoopService::run(
    Task *task) {
    
    setup();
    while (true) {
        loop();
        
#if configUSE_TIME_SLICING == 0
        Task::delay(100); 
#endif        
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

