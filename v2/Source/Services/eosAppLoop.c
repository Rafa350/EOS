#include "eos.h"
#include "System/eosTask.h"
#include "Services/eosAppLoop.h"


extern void appSetup(void);
extern void appLoop(void);


static void task(void *params);


static void task(
    void *params) {
    
    appSetup();
    while (true)
        appLoop();
}
