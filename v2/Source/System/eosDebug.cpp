#include "eos.h"

#ifdef EOS_DEBUG


#include "System/eosDebug.h"


using namespace eos;


void Debug::initialize() {

	//ITM->LAR = 0xC5ACCE55;
    //ITM->TCR |= 1 << ITM_TCR_ITMENA_Pos;
    //ITM->TER = 1U;
}


void Debug::print(const char *msg) {

	for (const char *p = msg; *p != '\0'; p++)
      	ITM_SendChar(*p);
}


#endif
