#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosAppLoop.hpp"


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::AppLoopService::AppLoopService()
 *
 *************************************************************************/

eos::AppLoopService::AppLoopService():
    task(512, eos::TaskPriority::normal, this) {
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eos::AppLoopService::run()
 *
 *************************************************************************/

void eos::AppLoopService::run() {
    
/*    appSetup();
    while (true)
        appLoop();*/
}
