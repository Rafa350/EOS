#include "eos.hpp"
#include "Services/Forms/eosFormsMenus.hpp"
#include "Controllers/eosDisplay.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param service: El servei
/// \param parent: El form pare
/// \param resource: El recurs del menu
///
MenuForm::MenuForm(
    FormsServiceHandle service, 
    FormHandle parent,
    uint8_t *_resource):
    Form(service, parent),
    resource(_resource),
    evCommand(nullptr) {
    
    showItems = 5;
    level = 0;
    info[0].offset = 0;
    info[0].numItems = resource[0];
    info[0].firstItem = 0;
    info[0].currentItem = 0;
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
MenuForm::~MenuForm() {
    
    if (evCommand != nullptr)
        delete evCommand;
}


/// ----------------------------------------------------------------------
/// \brief Procesa els missatges que arribin al form
/// \param message: El missatge a procesar
///
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
                    prevMenu();
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


/// ----------------------------------------------------------------------
/// \brief Notifica l'activacio del form.
/// \param deactivatedForm: El form desactivat.
///
void MenuForm::onActivate(
    FormHandle deactivateForm) {

    refresh();
}


/// ----------------------------------------------------------------------
/// \brief Notifica que cal repintar la pantalla.
/// \param displayController: Controlador de pantalla.
///
void MenuForm::onPaint(
    DisplayControllerHandle displayController) {

    if (displayController->beginCommand()) {

        MenuInfo *info = &this->info[level];

        unsigned offset = info->offset;
        unsigned titleLen = resource[offset + 1];
        char *title = (char*) &resource[offset + 2];

        displayController->addCommandClear();
        displayController->addCommandDrawText(0, 0, title, 0, titleLen);
        displayController->addCommandDrawLine(0, 10, 127, 10);

        unsigned i = info->firstItem;
        unsigned j = eosMin(info->numItems, showItems);
        unsigned k = 12;
        while (j--) {

            unsigned itemMapOffset = offset + 2 + titleLen + (i * 2);
            unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

            unsigned itemTitleLen = resource[itemOffset + 1];
            char *itemTitle = (char*) &resource[itemOffset + 2];

            if (i == info->currentItem) {
                displayController->addCommandFillRectangle(0, k, 127, k + 8);
                displayController->addCommandSetColor(0, 1);
            }
            // TODO: event onItemDraw
            displayController->addCommandDrawText(10, k, itemTitle, 0, itemTitleLen);
            displayController->addCommandSetColor(1, 0);

            i += 1;
            k += 10;
        }

        displayController->addCommandRefresh();
        displayController->endCommand();
    }
}


/// ----------------------------------------------------------------------
/// \brief Mou el selector al primer item del menu.
///
void MenuForm::firstItem() {

    MenuInfo *info = &this->info[level];

    if (info->currentItem != 0) {
        info->currentItem = 0;
        info->firstItem = 0;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \bried Mou el selector a l'ultim item del menu.
///
void MenuForm::lastItem() {

    MenuInfo *info = &this->info[level];

    if (info->currentItem <= info->numItems - 1) {
        info->currentItem = info->numItems - 1;
        info->firstItem = info->numItems - showItems;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Mou el selector al seguent item del menu.
///
void MenuForm::nextItem() {
    
    MenuInfo *info = &this->info[level];

    if (info->currentItem < info->numItems - 1) {
        info->currentItem++;
        if (info->firstItem + showItems <= info->currentItem)
            info->firstItem++;
        refresh();
    }
}
 

/// ----------------------------------------------------------------------
/// \brief Mou el selector a l'anterior item del menu.
///
void MenuForm::prevItem() {

    MenuInfo *info = &this->info[level];

    if (info->currentItem > 0) {
        info->currentItem--;
        if (info->firstItem > info->currentItem)
            info->firstItem--;
        refresh();
    }
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el item actual.
///
void MenuForm::selectItem() {
    
    MenuInfo *info = &this->info[level];

    unsigned offset = info->offset;
    unsigned currentItem = info->currentItem;
    unsigned itemMapOffset = offset + 2 + resource[offset + 1] + (currentItem * 2);
    unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

    switch (resource[itemOffset] & 0x03) {
        case 0x00: // commandItem
            if (evCommand != nullptr) {
                unsigned command = resource[itemOffset + 2 + resource[itemOffset + 1]];
                evCommand->execute(command);
            }
            break;

        case 0x01: // menuItem
            // nextMenu();
            if (level < MAX_LEVELS) {
                level++;
                MenuInfo *info = &this->info[level];
                info->offset = itemOffset + 2 + resource[itemOffset + 1];
                info->numItems = resource[info->offset];
                info->firstItem = 0;
                info->currentItem = 0;
                refresh();
            }
            break;

        case 0x02: // exitItem
            prevMenu();
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief Avança al seguent menu
///
void MenuForm::nextMenu() {

    // TODO 
}
  

/// ----------------------------------------------------------------------
/// \brief Retorna al menu anterior
///
void MenuForm::prevMenu() {

    if (level > 0)  {
        level--;
        refresh();
    }   
}    