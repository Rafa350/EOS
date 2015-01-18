#include <stdio.h>
#include "Services/eosFormsIncDec.h"
#include "DisplayService.h"


typedef struct {             // Dades privades del form
    char *title;             // -Titol
    char *prefix;            // -Prefix del valor
    char *suffix;            // -Sufix del valor
    int minValue;            // -Valor minim
    int maxValue;            // -Valor maxim
    int delta;               // -Quantitat per incrementar o decrementar
    int value;               // -Valor actual
} PrivateData;


static void onMessage(eosFormsMessage *message);
static void onMsgActivate(eosFormsMessage *message);
static void onMsgCreate(eosFormsMessage *message);
static void onMsgSelectorInc(eosFormsMessage *message);
static void onMsgSelectorDec(eosFormsMessage *message);
static void onMsgSelectorClick(eosFormsMessage *message);
static void onMsgPaint(eosFormsMessage *message);

static void notifyChanged(eosFormHandle hForm);
static void notifyEnd(eosFormHandle hForm);


/*************************************************************************
 *
 *       Crea un form de increment/decrement
 *
 *       Funcio:
 *           eosFormHandle eosFormsCreateIncDec(
 *               eosIncDecParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form
 *
 *************************************************************************/

eosFormHandle eosFormsCreateIncDec(
    eosIncDecParams *params) {

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.hParent = params->hParent;
    formParams.privateParams = params;
    formParams.privateDataSize = sizeof(PrivateData);
    formParams.onMessage = onMessage;
    
    return eosFormsCreateForm(&formParams);
}


void eosFormsIncDecSetMinValue(
    eosFormHandle hForm,
    int minValue) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->minValue = minValue;
    data->value = max(data->value, data->minValue);
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetMaxValue(
    eosFormHandle hForm,
    int maxValue) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->maxValue = maxValue;
    data->value = min(data->value, data->maxValue);
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetValue(
    eosFormHandle hForm,
    int value) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->value = min(max(data->value, data->minValue), data->maxValue);
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetDelta(
    eosFormHandle hForm,
    int delta) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->delta = delta;
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetPrefix(
    eosFormHandle hForm,
    char *prefix) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->prefix = prefix ? prefix : "";
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetSuffix(
    eosFormHandle hForm,
    char *suffix) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->suffix = suffix ? suffix : "";
    eosFormsRefresh(hForm);
}


void eosFormsIncDecSetTitle(
    eosFormHandle hForm,
    char *title) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    data->title = title ? title : "";
    eosFormsRefresh(hForm);
}


int eosFormsIncDecGetValue(eosFormHandle hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    return data->value;
}


/*************************************************************************
 *
 *       Procesa els missatges que arribin al form
 *
 *       Funcio:
 *           void onMessage(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del sevei
 *           message : El missatge a procesar
 *
 **************************************************************************/

static void onMessage(
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


/*************************************************************************
 *
 *       Procesa el missatge MSG_CREATE
 *
 *       Funcio:
 *           void onMsgCreate(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgCreate(
    eosFormsMessage *message) {

    eosIncDecParams *params = (eosIncDecParams*) message->msgCreate.privateParams;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    // Inicialitza les dades privades
    //
    data->title = params->title;
    data->minValue = params->minValue;
    data->maxValue = params->maxValue;
    data->value = min(max(params->value, params->minValue), params->maxValue);
    data->delta = params->delta;
    data->prefix = params->prefix ? params->prefix : "";
    data->suffix = params->suffix ? params->suffix : "";
}


/*************************************************************************
 *
 *       Procesa el missatge MSG_PAINT
 *
 *       Funcio:
 *           void onMsgPaint(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgPaint(
    eosFormsMessage *message) {

    eosFormHandle hForm = message->hForm;
    axDisplayServiceHandle hDisplay = message->msgPaint.hDisplayService;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (axDisplayBeginCommand(hDisplay)) {

        axDisplayAddCommandClear(hDisplay);
        if (data->title != NULL)
            axDisplayAddCommandDrawText(hDisplay, 0, 0, data->title, 0, -1);
        axDisplayAddCommandDrawLine(hDisplay, 0, 10, 127, 10);
        axDisplayAddCommandDrawLine(hDisplay, 0, 53, 127, 53);

        char text[40];
        sprintf(text, "%s%d%s", data->prefix, data->value, data->suffix);

        axDisplayAddCommandDrawText(hDisplay, 10, 30, text, 0, -1);
        axDisplayAddCommandRefresh(hDisplay);
        axDisplayEndCommand(hDisplay);
    }

}


/*************************************************************************
 *
 *       Procesa el missatge MSG_SELECTOR/EV_SELECTOR_INC
 *
 *       Funcio:
 *           void onMsgSelectorInc(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgSelectorInc(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->value + data->delta < data->maxValue) {
        data->value += data->delta;
        eosFormsRefresh(message->hForm);
        notifyChanged(message->hForm);
    }
}


/*************************************************************************
 *
 *       Procesa el missatge MSG_SELECTOR/EV_SELECTOR_DEC
 *
 *       Funcio:
 *           void onMsgSelectorDec(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgSelectorDec(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->value - data->delta > data->minValue) {
        data->value -= data->delta;
        eosFormsRefresh(message->hForm);
        notifyChanged(message->hForm);
    }
}


/*************************************************************************
 *
 *       Procesa el missatge MSG_SELECTOR/EV_SELECTOR_CLICK
 *
 *       Funcio:
 *           void onMsgSelectorClick(
 *               eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge a procesar
 *
 *************************************************************************/

static void onMsgSelectorClick(
    eosFormsMessage *message) {

    notifyEnd(message->hForm);
}

/*************************************************************************
 *
 *       Envia un missatge de notificacio CHANGED al form pare
 *
 *       Funcio:
 *           void notifyChanged(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: Handler del form
 *
 *************************************************************************/

static void notifyChanged(
    eosFormHandle hForm) {

    eosIncDecNotifyChanged params;

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    params.value = data->value;

    eosFormsSendNotify(hForm, EV_INCDEC_CHANGED, &params);
}


/*************************************************************************
 *
 *       Envia un missatge de notificacio END al form pare
 *
 *       Funcio:
 *           void notifyEnd(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: Handler del form
 *
 *************************************************************************/

static void notifyEnd(
    eosFormHandle hForm) {

    eosIncDecNotifyEnd params;

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    params.value = data->value;

    eosFormsSendNotify(hForm, EV_INCDEC_END, &params);
}
