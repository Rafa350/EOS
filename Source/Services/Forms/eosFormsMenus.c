#include "Services/eosFormsMenus.h"
#include "DisplayService.h"


#define MAX_LEVELS  10

typedef struct {                       // Informacio d'un menu
    unsigned offset;                   // -Offset al menu
    unsigned numItems;                 // -Numero de items
    unsigned firstItem;                // -Primer item a mostrar
    unsigned currentItem;              // -Item actual
} MenuInfo;

typedef struct {                       // Dades privades
    BYTE *resource;                    // -Recurs del menu
    unsigned level;                    // -Nivell de submenus
    MenuInfo info[MAX_LEVELS];         // -Pila d'informacio del menu
    unsigned showItems;                // -Numero d'items a mostrar
} PrivateData;


static void onMessage(eosHFormsService hService, eosFormsMessage *message);

static void onActivate(eosHForm hForm, eosHForm hInactiveForm);
static void onPaint(eosHForm hForm, axHDisplayService hDisplayService);

static void nextItem(eosHForm hForm);
static void prevItem(eosHForm hForm);
static void firstItem(eosHForm hForm);
static void lastItem(eosHForm hForm);
static void selectItem(eosHForm hForm);


/*************************************************************************
 *
 *       Crea un form de menus
 *
 *       Funcio:
 *           eosHForm eosFormsCreateMenu(
 *               eosHFormsService hService,
 *               eosMenuParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form
 *
 *************************************************************************/

eosHForm eosFormsCreateMenu(
    eosHFormsService hService,
    eosMenuParams *params) {

    PrivateData *data = (PrivateData*) eosAlloc(sizeof(PrivateData));
    data->resource = params->resource;
    data->showItems = 5;
    data->level = 0;
    data->info[0].offset = 0;
    data->info[0].numItems = data->resource[0];
    data->info[0].firstItem = 0;
    data->info[0].currentItem = 0;

    eosFormParams formParams;
    memset(&formParams, 0, sizeof(formParams));
    formParams.hParent = params->hParent;
    formParams.onMessage = (eosCallback) onMessage;
    formParams.privateData = data;
    
    eosHForm hForm = eosFormsCreateForm(hService, &formParams);

    eosFormsSetOnActivate(hForm, hForm, (eosEventMethod) onActivate);
    eosFormsSetOnPaint(hForm, hForm, (eosEventMethod) onPaint);

    return hForm;
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
        case MSG_SELECTOR_DEC:
            prevItem(hForm);
            break;

        case MSG_SELECTOR_INC:
            nextItem(hForm);
            break;

        case MSG_SELECTOR_CLICK: {
            selectItem(hForm);
            break;
        }
    }
}


/*************************************************************************
 *
 *       Procesa l'event OnActivate
 *
 *       Funcio:
 *           void onActivate(
 *               eosHForm hForm,
 *               eosHForm hInactiveForm)
 *
 *       Entrada:
 *           hForm        : El handler del form
 *           hInactiveForm: El form que ha estat desactivat
 *
 *************************************************************************/

static void onActivate(
    eosHForm hForm,
    eosHForm hInactiveForm) {

    eosFormsRefresh(hForm);
}


/*************************************************************************
 *
 *       Procesa l'event OnPaint
 *
 *       Funcio:
 *           void onPaint(
 *               eosHForm hForm,
 *               axHDisplayService hDisplay)
 *
 *       Entrada:
 *           hForm   : Handler del form
 *           hDisplay: Handler del display
 *
 *************************************************************************/

static void onPaint(
    eosHForm hForm,
    axHDisplayService hDisplay) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);

    if (axDisplayBeginCommand(hDisplay)) {

        BYTE *resource = data->resource;
        MenuInfo *info = &data->info[data->level];

        unsigned offset = info->offset;
        unsigned titleLen = resource[offset + 1];
        char *title = &resource[offset + 2];

        axDisplayAddCommandClear(hDisplay);
        axDisplayAddCommandDrawText(hDisplay, 0, 0, title, 0, titleLen);
        axDisplayAddCommandDrawLine(hDisplay, 0, 10, 127, 10);

        unsigned i = info->firstItem;
        unsigned j = min(info->numItems, data->showItems);
        unsigned k = 12;
        while (j--) {

            unsigned itemMapOffset = offset + 2 + titleLen + (i * 2);
            unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

            unsigned itemTitleLen = resource[itemOffset + 1];
            char *itemTitle = &resource[itemOffset + 2];

            if (i == info->currentItem) {
                axDisplayAddCommandFillRectangle(hDisplay, 0, k, 127, k + 8);
                axDisplayAddCommandSetColor(hDisplay, 0, 1);
            }
            axDisplayAddCommandDrawText(hDisplay, 10, k, itemTitle, 0, itemTitleLen);
            axDisplayAddCommandSetColor(hDisplay, 1, 0);

            i += 1;
            k += 10;
        }

        axDisplayAddCommandRefresh(hDisplay);
        axDisplayEndCommand(hDisplay);
    }
}


/*************************************************************************
 *
 *       Mou el selector al primer item del menu
 *
 *       Funcio:
 *           void firstItem(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *************************************************************************/

static void firstItem(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    MenuInfo *info = &data->info[data->level];

    if (info->currentItem != 0) {
        info->currentItem = 0;
        info->firstItem = 0;
        eosFormsRefresh(hForm);
    }
}


/*************************************************************************
 *
 *       Mou el selector a l'ultim item del menu
 *
 *       Funcio:
 *           void lastItem(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: Handler del form
 *
 *************************************************************************/

static void lastItem(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    MenuInfo *info = &data->info[data->level];

    if (info->currentItem <= info->numItems - 1) {
        info->currentItem = info->numItems - 1;
        info->firstItem = info->numItems - data->showItems;
        eosFormsRefresh(hForm);
    }
}


/*************************************************************************
 *
 *       Mou el selector el seguent item del menu
 *
 *       Funcio:
 *           void nextItem(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: Handler del form
 *
 *************************************************************************/

static void nextItem(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    MenuInfo *info = &data->info[data->level];

    if (info->currentItem < info->numItems - 1) {
        info->currentItem++;
        if (info->firstItem + data->showItems <= info->currentItem)
            info->firstItem++;
        eosFormsRefresh(hForm);
    }
}


/*************************************************************************
 *
 *       Mou el selector a l'anterior item del menu
 *
 *       Funcio:
 *           void prevItem(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: Handler del form
 *
 *************************************************************************/

static void prevItem(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    MenuInfo *info = &data->info[data->level];

    if (info->currentItem > 0) {
        info->currentItem--;
        if (info->firstItem > info->currentItem)
            info->firstItem--;
        eosFormsRefresh(hForm);
    }
}


/*************************************************************************
 *
 *       Selecciona el item actual
 *
 *       Funcio:
 *           void selectItem(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: Hander del form
 *
 *       Retorn:
 *           Comanda seleccionada
 *
 *************************************************************************/

static void selectItem(
    eosHForm hForm) {

    PrivateData *data = (PrivateData*) eosFormsGetPrivateData(hForm);
    BYTE *resource = data->resource;

    unsigned offset = data->info[data->level].offset;
    unsigned currentItem = data->info[data->level].currentItem;
    unsigned itemMapOffset = offset + 2 + resource[offset + 1] + (currentItem * 2);
    unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

    switch (resource[itemOffset] & 0x03) {
        case 0: {
            unsigned command = resource[itemOffset + 2 +  resource[itemOffset + 1]];
            if (command != 0) {
                eosHFormsService hService = eosFormsGetService(hForm);
                eosHForm hParent = eosFormsGetParent(hForm);
                if (hParent != NULL) {
                    eosFormsMessage cmdMessage;
                    cmdMessage.id = MSG_COMMAND;
                    cmdMessage.hForm = hParent;
                    cmdMessage.msgCommand.command = command;
                    eosFormsSendMessage(hService, &cmdMessage);
                }
            }
            break;
        }

        case 0x01:
            if (data->level < MAX_LEVELS) {
                data->level++;
                MenuInfo *info = &data->info[data->level];
                info->offset = itemOffset + 2 + resource[itemOffset + 1];
                info->numItems = resource[info->offset];
                info->firstItem = 0;
                info->currentItem = 0;
                eosFormsRefresh(hForm);
            }
            break;

        case 0x02:
            if (data->level > 0)  {
                data->level--;
                eosFormsRefresh(hForm);
            }
            break;
    }
}
