#include "eos.h"

#ifdef __PIC32MX


#ifdef EOS_USE_FREERTOS
#include "freertos.h"
#endif


void sysInitialize(void) {


}


void eosCreateTask(void) {

}

void eosSchedule(void) {

#ifdef EOS_USE_FREERTOS
    vTaskStartSchedule();
#endif
}

void eosCreateQueue(void) {

}

void eosDeleteQueue(void) {
    
}


#endif
