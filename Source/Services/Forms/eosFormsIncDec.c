#include <stdio.h>
#include "Services/eosFormsIncDec.h"
#include "DisplayService.h"


typedef struct {
    int minValue;
    int maxValue;
    int delta;
    int value;
} PrivateData;


static void onMessage(eosHFormsService hService, eosFormsMessage *message);
static void onMsgActivate(eosFormsMessage *message);
static void onMsgInitialize(eosFormsMessage *message);
static void onMsgSelectorInc(eosFormsMessage *message);
static void onMsgSelectorDec(eosFormsMessage *message);
static void onMsgSelectorClick(eosFormsMessage *message);
static void onMsgPaint(eosFormsMessage *message);


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
        case MSG_INITIALIZE:
            onMsgInitialize(message);
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


static void onMsgInitialize(
    eosFormsMessage *message) {

    PrivateData *data = eosFormsGetPrivateData(message->hForm);
    data->minValue = 0;
    data->maxValue = 99999;
    data->value = 0;
    data->delta = 1;
}


static void onMsgPaint(
    eosFormsMessage *message) {

    eosHForm hForm = message->hForm;
    axHDisplayService hDisplay = message->msgPaint.hDisplayService;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (axDisplayBeginCommand(hDisplay)) {

        char text[20];
        sprintf(text, "%d", data->value);

        axDisplayAddCommandClear(hDisplay);
        axDisplayAddCommandDrawText(hDisplay, 0, 0, text, 0, -1);
        axDisplayAddCommandDrawLine(hDisplay, 0, 10, 127, 10);
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
    }
}


static void onMsgSelectorDec(
    eosFormsMessage *message) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(message->hForm);

    if (data->value - data->delta > data->minValue) {
        data->value -= data->delta;
        eosFormsRefresh(message->hForm);
    }
}
