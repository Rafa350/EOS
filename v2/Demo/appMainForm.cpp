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
        case CMD_EXIT:
            a++;
            break;
    }
}