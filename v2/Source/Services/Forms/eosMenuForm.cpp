#include "eos.h"
#include "eosMacros.h"
#include "Services/Forms/eosMenuForm.h"
#include "Controllers/Display/eosColor.h"


using namespace eos;


extern VisualScheme visualScheme;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param service: El servei
/// \param parent: El form pare
/// \param resource: El recurs del menu
///
MenuForm::MenuForm(
    FormsService *service, 
    Form *parent,
    uint8_t *_resource):
    
    Form(service, parent),
    resource(_resource),
    evSelectItem(nullptr),
    evClickItem(nullptr),
    evDrawItem(nullptr) {
    
    refreshBackground = true;
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
    
    if (evSelectItem != nullptr)
        delete evSelectItem;
    
    if (evClickItem != nullptr)
        delete evClickItem;
    
    if (evDrawItem != nullptr)
        delete evDrawItem;
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant cal repintar la pantalla.
/// \param display: El handler de visualitzacio.
///
void MenuForm::onPaint(
    FormsDisplay *display) {
    
    MenuInfo *info = &this->info[level];
    unsigned offset = info->offset;
    unsigned titleLen = resource[offset + 1];
    char *title = (char*) &resource[offset + 2];
    
    if (refreshBackground) {
        
        // Dibuixa el fons
        //
        display->clear(visualScheme.menuBackgroundColor);

        // Dibuixa el marc
        //
        display->setColor(visualScheme.menuBorderColor);
        display->drawRectangle(0, 0, 240, 320);
        display->drawLine(0, 20, 239, 20);

        // Dibuixa el titol
        //
        display->setColor(visualScheme.menuTitleTextColor);
        display->drawText(4, 16, title, 0, titleLen);    
        
        refreshBackground = false;
    }
    
    unsigned i = info->firstItem;
    unsigned j = min(info->numItems, showItems);
    unsigned k = 25;
    while (j--) {

        unsigned itemMapOffset = offset + 2 + titleLen + (i * 2);
        unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;
        
        unsigned itemTitleLen = resource[itemOffset + 1];
        char *itemTitle = (char*) &resource[itemOffset + 2];
        unsigned itemId = resource[itemOffset + 2 + itemTitleLen];

        if (i == info->currentItem) {
            display->setColor(visualScheme.menuSelectedBackgroundColor);
            display->fillRectangle(4, k, 232, visualScheme.menuItemHeight);
            display->setColor(visualScheme.menuSelectedBorderColor);
            display->drawRectangle(4, k, 232, visualScheme.menuItemHeight);
            display->setColor(visualScheme.menuSelectedTextColor);
        }
        else {
            display->setColor(visualScheme.menuBackgroundColor);
            display->fillRectangle(4, k, 232, visualScheme.menuItemHeight);
            display->setColor(visualScheme.menuNormalTextColor);
        }

        onDrawItem(itemId, itemTitle, display, 4, k + 15, 0, 0);
        display->drawText(4, k + 15, itemTitle, 0, itemTitleLen);
        
        i += 1;
        k += visualScheme.menuItemHeight;
    }
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou
/// \param delta: Desplaçament.
///
#ifdef eosFormsService_UseSelector
void MenuForm::onSelectorInc(
    uint16_t delta) {
    
    nextItem();
    Form::onSelectorInc(delta);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant el selector es mou
/// \param delta: Desplaçament.
///
#ifdef eosFormsService_UseSelector
void MenuForm::onSelectorDec(
    uint16_t delta) {
    
    prevItem();
    Form::onSelectorDec(delta);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es prem el boto del selector.
///
#ifdef eosFormsService_UseSelector
void MenuForm::onSelectorPress() {
    
    clickItem();
    
    Form::onSelectorPress();
}
#endif


/// ----------------------------------------------------------------------
/// \bried Es crida quant es prem una tecla.
/// \param key: Codi de la tecla.
///
#ifdef eosFormsService_UseKeyboard
void MenuForm::onKeyPress(
    KeyCode keyCode) {
    
    switch (keyCode) {
        case KeyCode::up:
            prevItem();
            break;
            
        case KeyCode::down:
            nextItem();
            break;
            
        case KeyCode::left:
            backItem();
            break;
            
        case KeyCode::enter:
        case KeyCode::right:
            clickItem();
            break;
    }
    
    Form::onKeyPress(keyCode);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Es crida quant es clica el item.
/// \param itemId: El identificador del item.
///
void MenuForm::onClickItem(
    uint16_t itemId) {
    
    if (evClickItem != nullptr)
        evClickItem->execute(this, itemId);
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant es selecciona el item.
/// \param itemId: El identificador del item.
///
void MenuForm::onSelectItem(
    uint16_t itemId) {
    
    if (evSelectItem != nullptr)
        evSelectItem->execute(this, itemId);
}


/// ----------------------------------------------------------------------
/// \brief Es crida quant cal dibuixae el item.
/// \param itemId: El identificador del item
///
void MenuForm::onDrawItem(
    ItemId itemId, 
    const char *title, 
    FormsDisplay *display, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    if (evDrawItem != nullptr) {
        DrawItemEventParams params;
        params.itemId = itemId;
        params.title = title;
        params.display = display;
        params.x = x;
        params.y = y;
        params.width = width;
        params.height = height;
        evDrawItem->execute(this, &params);
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
        //onSelectItem;
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
        //onSelectItem;
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
        //onSelectItem;
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
        //onSelectItem;
    }
}


/// ----------------------------------------------------------------------
/// \brier Mou el selector al menu entrior. 
///
void MenuForm::backItem() {

    if (level > 0)  {
        level--;
        refreshBackground = true;
        refresh();
    }   
}
 

/// ----------------------------------------------------------------------
/// \brief Selecciona el item actual.
///
void MenuForm::clickItem() {
    
    MenuInfo *info = &this->info[level];

    unsigned offset = info->offset;
    unsigned currentItem = info->currentItem;
    unsigned itemMapOffset = offset + 2 + resource[offset + 1] + (currentItem * 2);
    unsigned itemOffset = resource[itemMapOffset] + resource[itemMapOffset + 1] * 256;

    switch (resource[itemOffset] & 0x03) {
        case 0x00: { // commandItem 
                uint16_t itemId = resource[itemOffset + 2 + resource[itemOffset + 1]];
                onClickItem(itemId);
            }
            break;

        case 0x01: // menuItem
            if (level < MAX_LEVELS) {
                level++;
                MenuInfo *info = &this->info[level];
                info->offset = itemOffset + 2 + resource[itemOffset + 1];
                info->numItems = resource[info->offset];
                info->firstItem = 0;
                info->currentItem = 0;
                refreshBackground = true;
                refresh();
            }
            break;

        case 0x02: // backItem
            backItem();
            break;
    }
}
