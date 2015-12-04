#include "eos.hpp"
#include "Services/Forms/eosFormsMenus.hpp"
#include "Services/Forms/eosFormsIncDec.hpp"
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
 
    mainMenuForm = new MenuForm(service, this, (uint8_t*) menuMnuMain);
    mainMenuForm->setEvCommand<MainForm>(this, &MainForm::mainMenuFormEvCommandHandler);
    
    mainMenuForm->activate();
}


MainForm::~MainForm() {
    
    delete mainMenuForm;
}


void MainForm::mainMenuFormEvCommandHandler(
    unsigned command) {

    currentCommand = command;
    
    switch (command) {
        case CMD_SET_XJERK:
            startEdit();
            break;
            
        case CMD_EXIT:
            break;
    }
}

void MainForm::startEdit() {
 
    IncDecFormHandle form = new IncDecForm(getService(), this);
    form->setDelta(infoXJerk.delta);
    form->setMinValue(infoXJerk.minValue);
    form->setMaxValue(infoXJerk.maxValue);
    form->setValue(2400);
    form->setTitle(infoXJerk.title);
    form->setEvSet<MainForm>(this, &MainForm::incDecEvSet);
    form->activate();
    
    editForm = form;
}

void MainForm::endEdit() {

    delete editForm;
}


void MainForm::incDecEvChange(int value) {
    
    switch (currentCommand) {
        case CMD_SET_XJERK:
            break;
    }
}


void MainForm::incDecEvSet(int value) {
    
    mainMenuForm->activate();
}
