#ifndef __EOS_FORMS_H
#define __EOS_FORMS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#include "DisplayService.h"


#define MSG_NULL               0
#define MSG_INITIALIZE         1
#define MSG_ACTIVATE           2
#define MSG_DEACTIVATE         3
#define MSG_PAINT              4

#define MSG_SELECTOR         100
#define EV_SELECTOR_INC        1
#define EV_SELECTOR_DEC        2
#define EV_SELECTOR_CLICK      3

#define MSG_KEYBOARD         101
#define EV_KEYBOARD_UP         1
#define EV_KEYBOARD_DOWN       2
#define EV_KEYBOARD_LEFT       3
#define EV_KEYBOARD_RIGHT      4
#define EV_KEYBOARD_OK         5

#define MSG_COMMAND          120
#define MSG_NOTIFY           121


typedef struct __eosFormsService *eosHFormsService;
typedef struct __eosForm *eosHForm;

typedef struct {
    eosHForm hOldActive;
} MsgActivate;

typedef struct {
    unsigned command;
} MsgCommand;

typedef struct {
    eosHForm hNewActive;
} MsgDeactivate;

typedef struct {
    void *privateParams;
    void *privateData;
} MsgInitialize;

typedef struct {
    axHDisplayService hDisplayService;
} MsgPaint;

typedef struct {
    unsigned event;
    int position;
    UINT8 state;
} MsgSelector;

typedef struct {
    eosHForm hForm;
    unsigned id;
    union {
        MsgActivate msgActivate;
        MsgDeactivate msgDeactivate;
        MsgCommand msgCommand;
        MsgInitialize msgInitialize;
        MsgPaint msgPaint;
        MsgSelector msgSelector;
    };
} eosFormsMessage;

typedef void (*eosFormsOnMessageCallback)(eosHFormsService hService, eosFormsMessage *message);

typedef struct {                            // Parametres d'inicialitzacio del form
    eosHForm hParent;                       // -Form pare
    eosFormsOnMessageCallback onMessage;    // -Funcio per gestionar els missatges
    unsigned privateDataSize;               // -Tamany de les dades privates
    void *privateParams;                    // -Parametres d'inicialitzacio privats
} eosFormParams;

typedef struct {                            // Parametres d'inicialitzacio del servei
    axHDisplayService hDisplayService;
    eosFormsOnMessageCallback onMessage;    // -Funcio per procesar els missatges
    void *globalData;                       // -Dades globals a tots els forms
} eosFormsServiceParams;


extern eosHFormsService eosFormsServiceInitialize(eosFormsServiceParams *params);
extern bool eosFormServiceIsReady(eosHFormsService hService);
extern void eosFormsServiceTask(eosHFormsService hForms);
extern void eosFormsSendMessage(eosHFormsService hService, eosFormsMessage *message);
extern void eosFormsPostMessage(eosHFormsService hService, eosFormsMessage *message);

extern eosHForm eosFormsCreateForm(eosHFormsService hService, eosFormParams *params);
extern void eosFormsRefreshForm(eosHForm hForm);

extern eosHForm eosFormsGetActiveForm(eosHFormsService hService);
extern void *eosFormsGetPrivateData(eosHForm hForm);
extern eosHForm eosFormsGetParent(eosHForm hForm);
extern eosHFormsService eosFormsGetService(eosHForm hForm);

extern void eosFormsSetActiveForm(eosHForm hForm);


#endif