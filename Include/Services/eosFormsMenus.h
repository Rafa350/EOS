#ifndef __EOS_FORMSMENUS_H
#define __EOS_FORMSMENUS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif


typedef struct {
    BYTE *resource;
} eosMenuParams;

extern eosHForm eosFormsCreateMenu(eosHFormsService hService, eosMenuParams *params);


#endif
