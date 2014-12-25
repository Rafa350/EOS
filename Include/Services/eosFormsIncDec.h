#ifndef __EOS_FORMINCDEC_H
#define __EOS_FORMSINCDEC_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_FORMS_H
#include <Services/eosForms.h>
#endif

                                       // Notificacions MSG_NOTIFY
#define EV_INCDEC_CHANGED         1    // -El valor ha canviat
#define EV_INCDEC_END             2    // -Ha finalitzat l'edicio


typedef struct {                       // Parametres d'inicialitzacio
    eosHForm hParent;                  // -Form pare. Es el que reb les notificacions
    char* title;                       // -Titlo
    int minValue;                      // -Valor minim
    int maxValue;                      // -Valor maxim
    int delta;                         // -Increment
    int value;                         // -Valor inicial
} eosIncDecParams;

extern eosHForm eosFormsCreateIncDec(eosHFormsService hService, eosIncDecParams *params);


#endif
