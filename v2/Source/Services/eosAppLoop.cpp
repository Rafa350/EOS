#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
AppLoopService::AppLoopService():
    task(512, eos::TaskPriority::normal, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
///
void AppLoopService::run() {
    
    setup();
    while (true)
        loop();
}


void AppLoopService::setup() {
    
}


void AppLoopService::loop() {
    
}

