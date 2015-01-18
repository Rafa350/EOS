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


typedef struct {                       // Parametres de notificacion CHANGED
    int value;
} eosIncDecNotifyChanged;

typedef struct {                       // Parametres de notificacion END
    int value;
} eosIncDecNotifyEnd;

typedef struct {                       // Parametres d'inicialitzacio
    eosFormHandle hParent;             // -Form pare. Es el que reb les notificacions
    char* title;                       // -Titol
    int minValue;                      // -Valor minim
    int maxValue;                      // -Valor maxim
    int delta;                         // -Increment
    int value;                         // -Valor inicial
    char *prefix;                      // -Texte del prefix
    char *suffix;                      // -Texte del sufix
} eosIncDecParams;

extern eosFormHandle eosFormsCreateIncDec(eosIncDecParams *params);

extern void eosFormsIncDecSetMinValue(eosFormHandle hForm, int minValue);
extern void eosFormsIncDecSetMaxValue(eosFormHandle hForm, int maxValue);
extern void eosFormsIncDecSetValue(eosFormHandle hForm, int value);
extern void eosFormsIncDecSetDelta(eosFormHandle hForm, int delta);
extern void eosFormsIncDecSetTitle(eosFormHandle hForm, char *title);
extern void eosFormsIncDecSetPrefix(eosFormHandle hForm, char *prefix);
extern void eosFormsIncDecSetSuffix(eosFormHandle hForm, char *suffix);
extern int  eosFormsIncDecGetValue(eosFormHandle hForm);


#endif
