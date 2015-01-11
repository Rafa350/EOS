#ifndef __EOS_FORMS_H
#define __EOS_FORMS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#include "DisplayService.h"


#define MSG_NULL               0
#define MSG_CREATE             1       // Creacio del form
#define MSG_DESTROY            2       // Destruccio del form
#define MSG_ACTIVATE           3       // Activacio del form
#define MSG_DEACTIVATE         4       // Desactivacio del form
#define MSG_PAINT              5       // Redibuix del form

#define MSG_SELECTOR         100       // Event del selector
#define EV_SELECTOR_INC        1       // -Increment del selector
#define EV_SELECTOR_DEC        2       // -Decrement del selector
#define EV_SELECTOR_CLICK      3       // -Click del boto

#define MSG_KEYBOARD         101       // Event del teclat
#define EV_KEYBOARD_UP         1       // -Tecla UP
#define EV_KEYBOARD_DOWN       2       // -Tecla DOWN
#define EV_KEYBOARD_LEFT       3       // -Tecla LEFT
#define EV_KEYBOARD_RIGHT      4       // -Tecla RIGHT
#define EV_KEYBOARD_OK         5       // -Tecla OK

#define MSG_COMMAND          102       // Comanda
#define MSG_NOTIFY           103       // Event de nofificacio d'un altre form


typedef struct __eosFormsService *eosFormsServiceHandle;
typedef struct __eosForm *eosFormHandle;

typedef struct {
    eosFormHandle hOldActive;
} MsgActivate;

typedef struct {
    unsigned command;
} MsgCommand;

typedef struct {
    void *privateParams;
    void *privateData;
} MsgCreate;

typedef struct {
    eosFormHandle hNewActive;
} MsgDeactivate;

typedef struct {
    eosFormHandle hSender;
    unsigned event;
    void *params;
} MsgNotify;

typedef struct {
    axDisplayServiceHandle hDisplayService;
} MsgPaint;

typedef struct {
    unsigned event;
    int position;
    UINT8 state;
} MsgSelector;

typedef struct {
    eosFormHandle hForm;
    unsigned id;
    union {
        MsgActivate msgActivate;
        MsgDeactivate msgDeactivate;
        MsgCommand msgCommand;
        MsgCreate msgCreate;
        MsgNotify msgNotify;
        MsgPaint msgPaint;
        MsgSelector msgSelector;
    };
} eosFormsMessage;

typedef void (*eosFormsOnMessageCallback)(eosFormsServiceHandle hService, eosFormsMessage *message);

typedef struct {                            // Parametres d'inicialitzacio del form
    eosFormHandle hParent;                  // -Form pare
    eosFormsOnMessageCallback onMessage;    // -Funcio per gestionar els missatges
    unsigned privateDataSize;               // -Tamany de les dades privates
    void *privateParams;                    // -Parametres d'inicialitzacio privats
} eosFormParams;

typedef struct {                            // Parametres d'inicialitzacio del servei
    axDisplayServiceHandle hDisplayService;
    eosFormsOnMessageCallback onMessage;    // -Funcio per procesar els missatges
    void *globalData;                       // -Dades globals a tots els forms
} eosFormsServiceParams;


extern eosFormsServiceHandle eosFormsServiceInitialize(eosFormsServiceParams *params);
extern bool eosFormServiceIsReady(eosFormsServiceHandle hService);
extern void eosFormsServiceTask(eosFormsServiceHandle hForms);
extern void eosFormsSendMessage(eosFormsServiceHandle hService, eosFormsMessage *message);
extern void eosFormsPostMessage(eosFormsServiceHandle hService, eosFormsMessage *message);

extern eosFormHandle eosFormsCreateForm(eosFormsServiceHandle hService, eosFormParams *params);
extern void eosFormsDestroyForm(eosFormHandle hForm);
extern void eosFormsRefreshForm(eosFormHandle hForm);

extern eosFormHandle eosFormsGetActiveForm(eosFormsServiceHandle hService);
extern void *eosFormsGetPrivateData(eosFormHandle hForm);
extern eosFormHandle eosFormsGetParent(eosFormHandle hForm);
extern eosFormsServiceHandle eosFormsGetService(eosFormHandle hForm);

extern void eosFormsSetActiveForm(eosFormHandle hForm);


#endif