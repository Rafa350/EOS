#ifndef __EOS_FORMINCDEC_H
#define __EOS_FORMSINCDEC_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif


typedef struct {
} eosIncDecParams;

extern eosHForm eosFormsCreateIncDec(eosHFormsService hService, eosIncDecParams *params);


#endif
