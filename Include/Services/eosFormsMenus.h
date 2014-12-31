#ifndef __EOS_FORMSMENUS_H
#define __EOS_FORMSMENUS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif

                                       // Notificacions MSG_NOTIFY
#define EV_MENU_GETVALUE          1    // -Obte el valor del item

typedef struct {                       // Parametres del missatge de notificacio
    unsigned command;
    char *itemValue;
} eosMenuNotifyGetValue;


typedef struct {
    eosHForm hParent;
    BYTE *resource;
} eosMenuParams;

extern eosHForm eosFormsCreateMenu(eosHFormsService hService, eosMenuParams *params);


#endif
