#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"


/// ----------------------------------------------------------------------
/// \brief Constructor.
///

eos::AppLoopService::AppLoopService():
    task(512, eos::TaskPriority::normal, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
///

void eos::AppLoopService::run() {
    
/*    appSetup();
    while (true)
        appLoop();*/
}
