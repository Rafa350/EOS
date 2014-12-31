#ifndef __EOS_FORMSLIST_H
#define __EOS_FORMSLIST_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif

                                       // Notificacions MSG_NOTIFY
#define EV_LIST_CHANGED           1    // -El valor ha canviat
#define EV_LIST_END               2    // -Ha finalitzat l'edicio


typedef struct {
    eosHForm hParent;
    char *title;
    char **items;
    unsigned numItems;
} eosListParams;

extern eosHForm eosFormsCreateList(eosHFormsService hService, eosListParams *params);


#endif
