#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif


extern eosResult eosInputsInitialize(unsigned maxInputs, eosHandle *hService);
extern eosResult eosInputsTerminate(eosHandle hService);
extern eosResult eosInputsTask(eosHandle hService);

extern void eosInputsISRTick(void *context);



#endif	

