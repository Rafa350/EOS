#include "eos.hpp"
#include "Services/Forms/eosFormsMenus.hpp"
#include "Services/Forms/eosFormsIncDec.hpp"
#include "appMainForm.hpp"
#include "MnuMain.h"


using namespace eos;
using namespace app;

extern const uint8_t menuMnuMain[];


MainForm::MainForm(
    FormsServiceHandle service):
    Form(service, nullptr) {
 
    mainMenuForm = new MenuForm(service, this, (uint8_t*) menuMnuMain);
    mainMenuForm->setEvCommand<MainForm>(this, &MainForm::mainMenuFormEvCommandHandler);
    
    mainMenuForm->activate();
}


MainForm::~MainForm() {
    
    delete mainMenuForm;
}


void MainForm::mainMenuFormEvCommandHandler(
    unsigned command) {
    
    int a = 0;
    switch (command) {
        case CMD_SET_XJERK:
            doSetXJerk();
            break;
            
        case CMD_EXIT:
            break;
    }
}

void MainForm::doSetXJerk() {
 
    IncDecFormHandle form = new IncDecForm(getService(), this);
    form->setDelta(5);
    form->setMinValue(100);
    form->setMaxValue(200);
    form->setValue(2400);
    form->setTitle("X-Motor Jerk");
    form->setEvSet<MainForm>(this, &MainForm::incDecEvSet);
    form->activate();
}


void MainForm::incDecEvChange(int value) {
    
}


void MainForm::incDecEvSet(int value) {
    
    mainMenuForm->activate();
}
