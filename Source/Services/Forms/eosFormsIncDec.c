#include <stdio.h>
#include "Services/eosFormsIncDec.h"
#include "DisplayService.h"


typedef struct {
    char *title;
    int minValue;
    int maxValue;
    int delta;
    int value;
} PrivateData;


static void onMessage(eosHFormsService hService, eosFormsMessage *message);
static void onMsgActivate(eosFormsMessage *message);
static void onMsgCreate(eosFormsMessage *message);
static void onMsgSelectorInc(eosFormsMessage *message);
static void onMsgSelectorDec(eosFormsMessage *message);
static void onMsgSelectorClick(eosFormsMessage *message);
static void onMsgPaint(eosFormsMessage *message);

static void notify(eosHForm hForm, unsigned event);


/*************************************************************************
 *
 *       Crea un form de increment/decrement
 *
 *       Funcio:
 *           eosHForm eosFormsCreateIncDec(
 *               eosHFormsService hService,
 *               eosIncDecParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form
 *
 *************************************************************************/

eosHForm eosFormsCreateIncDec(
    eosHFormsService hService,
    eosIncDecParams *params) {

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.hParent = params->hParent;
    formParams.privateParams = params;
    formParams.privateDataSize = sizeof(PrivateData);
    formParams.onMessage = onMessage;
    
    return eosFormsCreateForm(hService, &formParams);
}


/*************************************************************************
 *
 *       Procesa els missatges que arribin al form
 *
 *       Funcio:
 *           void onMessage(
 *               eosHFormsService hService,
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del sevei
 *           message : El missatge a procesar
 *
 **************************************************************************/

static void onMessage(
    eosHFormsService hService,
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
                case EV_SELECTOR_INC:
                    onMsgSelectorInc(message);
                    break;

                case EV_SELECTOR_DEC:
                    onMsgSelectorDec(message);
                    break;

                case EV_SELECTOR_CLICK:
                    onMsgSelectorClick(message);
                    break;
            }
            break;
    }
}


/*************************************************************************
 *
 *       Procesa el missatge MSG_ACTIVATE
 *
 *       Funcio:
 *           void onMsgActivate(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgActivate(
    eosFormsMessage *message) {

    eosFormsRefresh(message->hForm);
}


static void onMsgCreate(
    eosFormsMessage *message) {

    eosIncDecParams *params = (eosIncDecParams*) message->msgCreate.privateParams;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    data->title = params->title;
    data->minValue = params->minValue;
    data->maxValue = params->maxValue;
    data->value = params->value;
    data->delta = params->delta;
}


static void onMsgPaint(
    eosFormsMessage *message) {

    eosHForm hForm = message->hForm;
    axHDisplayService hDisplay = message->msgPaint.hDisplayService;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (axDisplayBeginCommand(hDisplay)) {

        axDisplayAddCommandClear(hDisplay);
        if (data->title != NULL)
            axDisplayAddCommandDrawText(hDisplay, 0, 0, data->title, 0, -1);
        axDisplayAddCommandDrawLine(hDisplay, 0, 10, 127, 10);
        axDisplayAddCommandDrawLine(hDisplay, 0, 53, 127, 53);

        char text[20];
        sprintf(text, "%d", data->value);

        axDisplayAddCommandDrawText(hDisplay, 10, 30, text, 0, -1);
        axDisplayAddCommandRefresh(hDisplay);
        axDisplayEndCommand(hDisplay);
    }

}


static void onMsgSelectorInc(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->value + data->delta < data->maxValue) {
        data->value += data->delta;
        eosFormsRefresh(message->hForm);
        notify(message->hForm, EV_INCDEC_CHANGED);
    }
}


static void onMsgSelectorDec(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->value - data->delta > data->minValue) {
        data->value -= data->delta;
        eosFormsRefresh(message->hForm);
        notify(message->hForm, EV_INCDEC_CHANGED);
    }
}

static void onMsgSelectorClick(
    eosFormsMessage *message) {

    notify(message->hForm, EV_INCDEC_END);
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
