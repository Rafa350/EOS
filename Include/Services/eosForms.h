#ifndef __EOS_FORMS_H
#define __EOS_FORMS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#include "DisplayService.h"


#define MSG_INITIALIZE         1
#define MSG_PAINT              2
#define MSG_ACTIVATE           3
#define MSG_DEACTIVATE         4

#define MSG_SELECTOR_UP      100
#define MSG_SELECTOR_DOWN    101
#define MSG_SELECTOR_CLICK   102


typedef struct __eosFormsService *eosHFormsService;
typedef struct __eosForm *eosHForm;

typedef struct {
    eosHForm hForm;
    unsigned id;
    union {
        struct {
            void *hHandle;
            unsigned param1;
            unsigned param2;
        };
        struct {
            axHDisplayService hDisplayService;
        } msgPaint;
    };
} eosFormsMessage;

typedef struct {
    eosCallback onMessage;
    unsigned privateDataSize;
} eosFormParams;

typedef struct {
    axHDisplayService hDisplayService;
    eosCallback onMessage;
} eosFormsServiceParams;


extern eosHFormsService eosFormsServiceInitialize(eosFormsServiceParams *params);
extern void eosFormsServiceTask(eosHFormsService hForms);

extern void eosFormsSendMessage(eosHFormsService hService, eosFormsMessage *message);
extern bool eosFormsGetMessage(eosHFormsService hService, eosFormsMessage *message);

extern eosHForm eosFormsCreateForm(eosHFormsService hService, eosFormParams *params);
extern eosHForm eosFormsGetActiveForm(eosHFormsService hService);
extern eosHForm eosFormsSetActiveForm(eosHFormsService hService, eosHForm hForm);
extern void eosFormsRefresh(eosHFormsService hService, eosHForm hForm);

extern void *eosFormsGetPrivateData(eosHForm hForm);


#endif