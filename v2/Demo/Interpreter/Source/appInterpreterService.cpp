#include "eos.h"
#include "appInterpreterService.h"


using namespace eos;
using namespace app;

#define LIT      0x10
#define DROP     0x20
#define ADD      0x21
#define AND      0x22
#define END      0x00


static const uint8_t __program[] = {
    LIT, 10,
    LIT, 20,
    LIT, 30,
    ADD,
    ADD,
    DROP,
    END    
};


InterpreterService::InterpreterService(
    Application* application):
    
    AppLoopService(application) {
    
}


void InterpreterService::onSetup() {
    
    ip = __program;
    sp = stack;
}


void InterpreterService::onLoop() {
    
    while (*ip)    
        switch (*ip) {
            case ADD: add(); break;
            case DROP: drop(); break;
            case LIT: lit(); break;
            case END: break;
        }
}

void InterpreterService::add() {

    uint8_t tmp1 = *--sp;
    uint8_t tmp2 = *--sp;
    *sp++ = tmp1 + tmp2;
    ip++;
}


void InterpreterService::drop() {
    
    sp--;
    ip++;
}


void InterpreterService::lit() {
    
    *sp++ = *++ip;
    ip++;
}

