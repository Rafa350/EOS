#include "eos.h"
#include "System/eosTask.h"


extern void setup(void);
extern void loop(void);


static void task(void *params);



static void task(
    void *params) {
    
    setup();
    while (true)
        loop();
}