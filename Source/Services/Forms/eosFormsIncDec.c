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

static void valueInc(eosHForm hForm);
static void valueDec(eosHForm hForm);
static void draw(eosHForm hForm, axHDisplayService hDisplay);


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

    PrivateData *data = (PrivateData*) eosAlloc(sizeof(PrivateData));
    data->minValue = 0;
    data->maxValue = 99999;
    data->value = 0;
    data->delta = 1;

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.onMessage = (eosCallback) onMessage;
    formParams.privateData = data;
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

    eosHForm hForm = message->hForm;

    switch (message->id) {
        case MSG_INITIALIZE:
            break;

        case MSG_ACTIVATE:
            eosFormsRefresh(hForm);
            break;

        case MSG_PAINT:
            draw(hForm, message->msgPaint.hDisplayService);
            break;

        case MSG_SELECTOR_INC:
            valueInc(hForm);
            break;

        case MSG_SELECTOR_DEC:
            valueDec(hForm);
            break;
    }
}


static void draw(
    eosHForm hForm,
    axHDisplayService hDisplay) {

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

static void valueInc(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (data->value + data->delta < data->maxValue) {
        data->value += data->delta;
        eosFormsRefresh(hForm);
    }
}


static void valueDec(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (data->value - data->delta > data->minValue) {
        data->value -= data->delta;
        eosFormsRefresh(hForm);
    }
}
