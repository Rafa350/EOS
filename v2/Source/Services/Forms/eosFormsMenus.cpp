#include "eos.hpp"
#include "Services/Forms/eosFormsMenus.hpp"
#include "Services/Forms/eosDisplay.hpp"


using namespace eos;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           MenuForm::MenuForm
 *               FormsServiceHandle service,
 *               FormHandle parent,
 *               IMenuOwner *owner,
 *               uint8_t *esource)
 *
 *       Entrada:
 *           service : El servei
 *           parent  : El form pare
 *           owner   : El propietari del menu
 *           resource: El recurs del menu
 *
 *************************************************************************/

MenuForm::MenuForm(
    FormsServiceHandle service, 
    FormHandle parent,
    IMenuOwner *_owner,
    uint8_t *_resource):
    Form(service, parent),
    owner(_owner),
    resource(_resource) {
    
    showItems = 5;
    level = 0;
    info[0].offset = 0;
    info[0].numItems = resource[0];
    info[0].firstItem = 0;
    info[0].currentItem = 0;
}


/*************************************************************************
 *
 *       Procesa els missatges que arribin al form
 *
 *       Funcio:
 *           void MenuForm::dispatchMessage(
 *               Message &message)
 *
 *       Entrada:
 *           message : El missatge a procesar
 *
 **************************************************************************/

void MenuForm::dispatchMessage(
    Message &message) {

    switch (message.id) {
        case MSG_KEYBOARD:
            switch (message.msgKeyboard.event) {
                case EV_KEYBOARD_UP:
                    prevItem();
                    break;

                case EV_KEYBOARD_DOWN:
                    nextItem();
                    break;

                case EV_KEYBOARD_OK:
                    selectItem();
                    break;
                    
                case EV_KEYBOARD_LEFT:
                    //backMenu();
                    break;
            }
            break;

        case MSG_SELECTOR:
            switch (message.msgSelector.event) {
                case EV_SELECTOR_DEC:
                    prevItem();
                    break;

                case EV_SELECTOR_INC:
                    nextItem();
                    break;

                case EV_SELECTOR_CLICK: 
                    selectItem();
                    break;
            }
            break;
            
        default:
            Form::dispatchMessage(message);
            break;
    }
}


/*************************************************************************
 *
 *       Procesa el event onActivate
 *
 *       Funcio:
 *           void Menuform::onActivate(
 *               Form *deactivatedForm,
 *
 *       Entrada:
 *           deactivatedForm: El form desactivat
 *
 *************************************************************************/

void MenuForm::onActivate(
    Form *deactivateForm) {

    refresh();
}


/*************************************************************************
 *
 *       Procesa el event ON_PAINT
 *
 *       Funcio:
 *           void MenuForm::onPaint(
 *               DisplayServiceHandle displayService) 
 *
 *       Entrada:
 *           displayService: Servei de pantalla
 *
 *************************************************************************/

void MenuForm::onPaint(
    DisplayServiceHandle displayService) {

    if (displayService->beginCommand()) {

        uint8_t *resource = resource;
        MenuInfo *info = &info[level];

        unsigned offset = info->offset;
        unsigned titleLen = resource[offset + 1];
        char *title = (char*) &resource[offset + 2];

        displayService->addCommandClear();
        displayService->addCommandDrawText(0, 0, title, 0, titleLen);
        displayService->addCommandDrawLine(0, 10, 127, 10);

        unsigned i = info->firstItem;
        unsigned j = eosMin(info->numItems, showItems);
        unsigned k = 12;
        while (j--) {

            unsigned itemMapOffset = offset + 2 + titleLen + (i * 2);
            unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

            unsigned itemTitleLen = resource[itemOffset + 1];
            char *itemTitle = (char*) &resource[itemOffset + 2];

            if (i == info->currentItem) {
                displayService->addCommandFillRectangle(0, k, 127, k + 8);
                displayService->addCommandSetColor(0, 1);
            }
            displayService->addCommandDrawText(10, k, itemTitle, 0, itemTitleLen);

            /*
            eosMenuNotifyGetValue notifyParams;
            notifyParams.command = resource[itemOffset + 2 + itemTitleLen];
            notifyParams.itemValue = NULL;
            notify(hForm, EV_MENU_GETVALUE, &notifyParams);
            if (notifyParams.itemValue != NULL)
                eosDisplayAddCommandDrawText(hDisplay, 60, k, notifyParams.itemValue, 0, -1);
            */
            displayService->addCommandSetColor(1, 0);

            i += 1;
            k += 10;
        }

        displayService->addCommandRefresh();
        displayService->endCommand();
    }
}


/*************************************************************************
 *
 *       Mou el selector al primer item del menu
 *
 *       Funcio:
 *           void MenuForm::firstItem()
 *
 *************************************************************************/

void MenuForm::firstItem() {

    MenuInfo *info = &info[level];

    if (info->currentItem != 0) {
        info->currentItem = 0;
        info->firstItem = 0;
        refresh();
    }
}


/*************************************************************************
 *
 *       Mou el selector a l'ultim item del menu
 *
 *       Funcio:
 *           void MenuForm::lastItem()
 *
 *************************************************************************/

void MenuForm::lastItem() {

    MenuInfo *info = &info[level];

    if (info->currentItem <= info->numItems - 1) {
        info->currentItem = info->numItems - 1;
        info->firstItem = info->numItems - showItems;
        refresh();
    }
}


/*************************************************************************
 *
 *       Mou el selector al seguent item del menu
 *
 *       Funcio:
 *           void MenuForm::nextItem()
 *
 *************************************************************************/

void MenuForm::nextItem() {
    
    MenuInfo *info = &info[level];

    if (info->currentItem < info->numItems - 1) {
        info->currentItem++;
        if (info->firstItem + showItems <= info->currentItem)
            info->firstItem++;
        refresh();
    }
}
 

/*************************************************************************
 *
 *       Mou el selector a l'anterior item del menu
 *
 *       Funcio:
 *           void MenuForm::prevItem()
 *
 *************************************************************************/

void MenuForm::prevItem() {

    MenuInfo *info = &info[level];

    if (info->currentItem > 0) {
        info->currentItem--;
        if (info->firstItem > info->currentItem)
            info->firstItem--;
        refresh();
    }
}


/*************************************************************************
 *
 *       Selecciona el item actual
 *
 *       Funcio:
 *           void MenuForm::selectItem()
 *
 *************************************************************************/

void MenuForm::selectItem() {
    
    MenuInfo *info = &info[level];

    unsigned offset = info[level].offset;
    unsigned currentItem = info[level].currentItem;
    unsigned itemMapOffset = offset + 2 + resource[offset + 1] + (currentItem * 2);
    unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

    switch (resource[itemOffset] & 0x03) {
        case 0: {
            if (owner != nullptr) {
                unsigned command = resource[itemOffset + 2 +  resource[itemOffset + 1]];
                owner->onCommand(command);
            }
            break;
        }

        case 0x01:
            if (level < MAX_LEVELS) {
                level++;
                MenuInfo *info = &info[level];
                info->offset = itemOffset + 2 + resource[itemOffset + 1];
                info->numItems = resource[info->offset];
                info->firstItem = 0;
                info->currentItem = 0;
                refresh();
            }
            break;

        case 0x02:
            if (level > 0)  {
                level--;
                refresh();
            }
            break;
    }
}
