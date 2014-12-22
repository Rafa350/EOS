#ifndef __EOS_FORMS_H
#define __EOS_FORMS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#include "DisplayService.h"


#define MSG_NULL               0
#define MSG_INITIALIZE         1
#define MSG_PAINT              2
#define MSG_ACTIVATE           3
#define MSG_DEACTIVATE         4

#define MSG_SELECTOR_INC     100
#define MSG_SELECTOR_DEC     101
#define MSG_SELECTOR_CLICK   102
//#define MSG_SELECTOR_PRESS   103
//#define MSG_SELECTOR_RELEASE 104

#define MSG_KEYBOARD_CLICK   110
//#define MSG_KEYBOARD_PRESS   111
//#define MSG_KEYBOARD_RELEASE 112
#define MSG_KEYBOARD_UP      113
#define MSG_KEYBOARD_DOWN    114
#define MSG_KEYBOARD_LEFT    115
#define MSG_KEYBOARD_RIGHT   116
#define MSG_KEYBOARD_OK      117

#define MSG_COMMAND          120


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
        struct {
            unsigned command;
        } msgCommand;
    };
} eosFormsMessage;

typedef struct {                  // Parametres d'inicialitzacio del form
    eosHForm hParent;             // -Form pare
    eosCallback onMessage;        // -Funcio per gestionar els missatges
    void *privateData;            // -Dades privades
} eosFormParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    axHDisplayService hDisplayService;
    eosCallback onMessage;        // -Funcio per procesar els missatges
    void *globalData;             // -Dades globals a tots els forms
} eosFormsServiceParams;


extern eosHFormsService eosFormsServiceInitialize(eosFormsServiceParams *params);
extern bool eosFormServiceIsReady(eosHFormsService hService);
extern void eosFormsServiceTask(eosHFormsService hForms);

extern void eosFormsSendMessage(eosHFormsService hService, eosFormsMessage *message);
extern bool eosFormsGetMessage(eosHFormsService hService, eosFormsMessage *message);

extern eosHForm eosFormsCreateForm(eosHFormsService hService, eosFormParams *params);
extern eosHForm eosFormsGetActiveForm(eosHFormsService hService);
extern eosHForm eosFormsSetActiveForm(eosHForm hForm);
extern void eosFormsRefreshForm(eosHForm hForm);

extern void *eosFormsGetPrivateData(eosHForm hForm);
extern eosHForm eosFormsGetParent(eosHForm hForm);
extern eosHFormsService eosFormsGetService(eosHForm hForm);


#endif