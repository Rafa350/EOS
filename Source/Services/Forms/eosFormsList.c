#include "Services/eosFormsList.h"
#include "DisplayService.h"


typedef struct {
    char *title;
    char **items;
    unsigned numItems;
    unsigned selectedIndex;
} PrivateData;


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
    formParams.hParent = params->hParent;
    formParams.privateDataSize = sizeof(PrivateData);
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

        case MSG_ACTIVATE:
            onMsgActivate(message);
            break;

        case MSG_PAINT:
            onMsgPaint(message);
            break;
        
        case MSG_SELECTOR:
            switch (message->msgSelector.event) {
                case EV_SELECTOR_CLICK:
                    onMsgSelectorClick(message);
                    break;
    
                case EV_SELECTOR_INC:
                    onMsgSelectorInc(message);
                    break;

                case EV_SELECTOR_DEC:
                    onMsgSelectorDec(message);
                    break;
            }
            break;
    }
}


static void onMsgCreate(
    eosFormsMessage *message) {

    eosListParams *params = (eosListParams*) message->msgCreate.privateParams;
    PrivateData *data = (PrivateData*) message->msgCreate.privateData;
    data->title = params->title;
    data->items = params->items;
    data->numItems = params->numItems;
    data->selectedIndex = 0;
}


static void onMsgActivate(
    eosFormsMessage *message) {

    eosFormsRefresh(message->hForm);
}


static void onMsgSelectorInc(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->selectedIndex < (data->numItems - 1)) {
        data->selectedIndex++;
        eosFormsRefresh(message->hForm);
        notify(message->hForm, EV_LIST_CHANGED);
    }
}


static void onMsgSelectorDec(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->selectedIndex > 0) {
        data->selectedIndex--;
        eosFormsRefresh(message->hForm);
        notify(message->hForm, EV_LIST_CHANGED);
    }
}


static void onMsgSelectorClick(
    eosFormsMessage *message) {

    notify(message->hForm, EV_LIST_END);
}


static void onMsgPaint(eosFormsMessage *message) {

    eosHForm hForm = message->hForm;
    axHDisplayService hDisplay = message->msgPaint.hDisplayService;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (axDisplayBeginCommand(hDisplay)) {

        axDisplayAddCommandClear(hDisplay);
        if (data->title != NULL)
            axDisplayAddCommandDrawText(hDisplay, 0, 0, data->title, 0, -1);
        axDisplayAddCommandDrawLine(hDisplay, 0, 10, 127, 10);
        axDisplayAddCommandDrawLine(hDisplay, 0, 53, 127, 53);

        if (data->selectedIndex != -1) {
            char *text = data->items[data->selectedIndex];
            axDisplayAddCommandDrawText(hDisplay, 10, 30, text, 0, -1);
        }
        
        axDisplayAddCommandRefresh(hDisplay);
        axDisplayEndCommand(hDisplay);
    }
}


static void notify(
    eosHForm hForm,
    unsigned event) {

    eosFormsMessage message;

    message.id = MSG_NOTIFY;
    message.hForm = eosFormsGetParent(hForm);
    message.msgNotify.hSender = hForm;
    message.msgNotify.event = event;
    message.msgNotify.parameters = NULL;

    eosFormsSendMessage(eosFormsGetService(hForm), &message);
}
