#ifndef __EOS_FORMSMENUS_H
#define __EOS_FORMSMENUS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/Forms/eosForms.h>
#endif

                                       // Notificacions MSG_NOTIFY
#define EV_MENU_GETVALUE          1    // -Obte el valor del item
#define EV_MENU_PAINT_BACKGROUND  2    // -Dibuixa el fons
#define EV_MENU_PAINT_TITLE       3    // -Dibuixa el titol
#define EV_MENU_PAINT_ITEM        4    // -Dibuixa un item

typedef struct {                       // Parametres de notificacio GETVALUE
    unsigned command;
    char *itemValue;
} eosMenuNotifyGetValue;

typedef struct {                       // Parametres de notificacio PAINT
    char *title;                       // -Titol del menu/item
    unsigned firstItem;                // -Numero del primer item que es dibuixa
    unsigned numItem;                  // -Numero d'item
    unsigned command;                  // -Comanda del item
} eosMenuNotifyPaint;

typedef struct {
    eosFormHandle hParent;
    uint8_t *resource;
} eosMenuParams;


extern eosFormHandle eosFormsCreateMenu(eosFormsServiceHandle hService,  eosMenuParams *params);


#endif
