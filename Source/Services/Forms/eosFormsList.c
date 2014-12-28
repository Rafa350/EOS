#include "Services/eosFormsList.h"
#include "DisplayService.h"


typedef struct {

} PrivateParams;


static void onMessage(eosHFormsService hServide, eosFormsMessage *message);

static void onMsgActivate(eosFormsMessage *message);
static void onMsgCreate(eosFormsMessage *message);
static void onMsgSelectorInc(eosFormsMessage *message);
static void onMsgSelectorDec(eosFormsMessage *message);
static void onMsgSelectorClick(eosFormsMessage *message);
static void onMsgPaint(eosFormsMessage *message);

static void notify(eosHForm hForm, unsigned event);


eosHForm eosFormsCreateList(
    eosHFormsService hService,
    eosListParams *params) {

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.privateDataSize = sizeof(PrivateParams);
    formParams.privateParams = params;
    formParams.onMessage = onMessage;

    return eosFormsCreateForm(hService, &formParams);
}


static void onMessage(
    eosHFormsService hServide,
    eosFormsMessage *message) {

    switch (message->id) {
        case MSG_CREATE:
            onMsgCreate(message);
            break;

        case MSG_ACTIVATEW:
            onMsgActivate(message);
            break;
    }
}
