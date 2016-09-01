#include "eos.hpp"
#include "Services/Forms/eosMenuForm.hpp"
#include "Services/Forms/eosNumericEditorForm.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "appMainForm.hpp"
#include "MnuMain.h"
#include <stdio.h>


using namespace eos;
using namespace app;


extern const uint8_t menuMnuMain[];


struct IncDecInfo {
    const char *title;
    int minValue;
    int maxValue;
    int delta;
};

struct ListInfo {
    const char *title;
};


const IncDecInfo infoXJerk =  { "X-Motor Jerk",   10, 2000,  5 };
const IncDecInfo infoXAccel = { "X-Motor Accel",  10, 2000,  5 };
const IncDecInfo infoXSpeed = { "X-Motor Speed",  10, 2000,  5 };


MainForm::MainForm(
    FormsServiceHandle service):
    Form(service, nullptr) {
 
    menuForm = new MenuForm(service, this, (uint8_t*) menuMnuMain);
    //menuForm->setClickItemEvent<MainForm>(this, &MainForm::menuClickItemEventHandler);   
} 


/// ----------------------------------------------------------------------
/// \brief Destructor
///
MainForm::~MainForm() {
    
    menuForm->destroy();
}


void MainForm::onSelectorPress() {

    menuForm->activate();
}


void MainForm::onSelectorMove(
    int16_t position, 
    SelectorDirection direction) {
}


void MainForm::onKeyPress(
    KeyCode keyCode) {

    if (keyCode == KeyCode::enter)
        menuForm->activate();
}


void MainForm::onPaint(
    FormsDisplayHandle display) {
    
    display->clear(RGB(0, 0, 32));
    
    display->setColor(RGB(0, 0, 128));
    display->drawRectangle(0, 0, 240, 320);
    display->drawLine(0, 20, 239, 20);
    display->drawText(4, 16, "EOS Forms Demo v1.0", 0, -1);
    
    uint8_t k = 0;
    for (int j = 0; j < 8; j++)
        for (int i = 0; i < 8; i++) {
        
            int x = ((240 - (20 * 8)) / 2) + (20 * i);
            int y = 20 + (((340 - 20) - 20 * 8) / 2) + (20 * j);
            Color c = RGB(k, k, k);
            display->setColor(c);
            display->fillRectangle(x, y, 15, 15);
            
            k += 4;
        }    
}


void MainForm::menuClickItemEventHandler(
    MenuFormHandle menuForm,
    uint16_t itemId) {

    currentCommand = itemId;
    
    switch (itemId) {
        case CMD_SET_XJERK:
            startEdit();
            break;
            
        case CMD_EXIT:
            break;
    }
}

void MainForm::editorSelectorPressEventHandler(
    FormHandle form) {

    endEdit();    
    menuForm->activate();
}


void MainForm::startEdit() {
 
    NumericEditorFormHandle form = new NumericEditorForm(getService(), this);
    form->setDelta(infoXJerk.delta);
    form->setMinValue(infoXJerk.minValue);
    form->setMaxValue(infoXJerk.maxValue);
    form->setValue(2400);
    form->setTitle(infoXJerk.title);   
#ifdef eosFormsService_UseSelector    
    form->setSelectorPressEvent<MainForm>(this, &MainForm::editorSelectorPressEventHandler);
#endif    
    form->activate();
    
    editorForm = form;
}

void MainForm::endEdit() {

    editorForm->destroy();
}
