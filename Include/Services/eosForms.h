#ifndef __EOS_FORMS_H
#define __EOS_FORMS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#define MSG_INITIALIZE         1
#define MSG_PAINT              2
#define MSG_ACTIVATE           3

#define MSG_SELECTOR_UP      100
#define MSG_SELECTOR_DOWN    101
#define MSG_SELECTOR_CLICK   102


typedef struct __eosFormsService *eosHFormsService;
typedef struct __eosForm *eosHForm;

typedef struct {
    unsigned id;
} eosFormsMessage;

typedef struct {
    eosCallback onMessage;
} eosFormParams;

typedef struct {
    eosCallback onMessage;
    unsigned privateDataSize;
} eosFormsServiceParams;


extern eosHFormsService eosFormsServiceInitialize(eosFormsServiceParams *params);
extern void eosFormsServiceTask(eosHFormsService hForms);

extern void eosFormsSendMessage(eosHFormsService hService, eosFormsMessage *message);
extern bool eosFormsGetMessage(eosHFormsService hService, eosFormsMessage *message);

extern eosHForm eosFormsCreateForm(eosFormParams *params);


#endif