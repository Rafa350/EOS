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


eosHForm eosFormsCreateIncDec(
    eosHFormsService hService,
    eosIncDecParams *params) {

    PrivateData *data = (PrivateData*) eosAlloc(sizeof(PrivateData));

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.onMessage = (eosCallback) onMessage;
    formParams.privateData = data;
    return eosFormsCreateForm(hService, &formParams);
}


static void onMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    eosHForm hForm = message->hForm;
    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    switch (message->id) {
        case MSG_INITIALIZE:
            break;

        case MSG_ACTIVATE:
            eosFormsRefresh(hForm);
            break;

        case MSG_PAINT:
            break;

        case MSG_SELECTOR_INC:
            valueInc(hForm);
            break;

        case MSG_SELECTOR_DEC:
            valueDec(hForm);
            break;
    }
}


static void valueInc(eosHForm hForm){

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (data->value + data->delta < data->maxValue) {
        data->value += data->delta;
        eosFormsRefresh(hForm);
    }
}


static void valueDec(eosHForm hForm){

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (data->value - data->delta > data->minValue) {
        data->value -= data->delta;
        eosFormsRefresh(hForm);
    }
}
