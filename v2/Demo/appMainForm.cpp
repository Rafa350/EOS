#include "eos.hpp"
#include "Services/Forms/eosMenuForm.hpp"
#include "Services/Forms/eosNumericEditorForm.hpp"
#include "appMainForm.hpp"
#include "MnuMain.h"


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
    menuForm->setClickItemEvent<MainForm>(this, &MainForm::menuClickItemEventHandler);   
    menuForm->activate();
}


MainForm::~MainForm() {
    
    menuForm->destroy();
}


void MainForm::menuClickItemEventHandler(
    MenuFormHandle menuForm,
    unsigned itemId) {

    currentCommand = itemId;
    
    switch (command) {
        case CMD_SET_XJERK:
            startEdit();
            break;
            
        case CMD_EXIT:
            break;
    }
}

void MainForm::startEdit() {
 
    NumericEditorFormHandle form = new NumericEditorForm(getService(), this);
    form->setDelta(infoXJerk.delta);
    form->setMinValue(infoXJerk.minValue);
    form->setMaxValue(infoXJerk.maxValue);
    form->setValue(2400);
    form->setTitle(infoXJerk.title);    
    form->setEvSet<MainForm>(this, &MainForm::incDecEvSet);
    form->activate();
    
    editorForm = form;
}


void MainForm::endEdit() {

    editorForm->destroy();
}


void MainForm::incDecEvChange(int value) {
    
    switch (currentCommand) {
        case CMD_SET_XJERK:
            break;
    }
}


void MainForm::incDecEvSet(int value) {

    endEdit();    
    menuForm->activate();
}
