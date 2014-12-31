#ifndef __EOS_FORMSLIST_H
#define __EOS_FORMSLIST_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif


typedef struct {
    eosHForm hParent;
    char *title;
    char **items;
} eosListParams;

extern eosHForm eosFormsCreateList(eosHFormsService hService, eosListParams *params);


#endif
