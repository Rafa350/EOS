#include "Services/eosExtInterrupt.h"


using namespace eos;


static const char *serviceName = "ExtInterruptService";
static const unsigned taskStackSize = 512;
static const TaskPriority taskPriority = TaskPriority::normal;


ExtInterruptService::ExtInterruptService(
    Application *application):
        
    Service(application, serviceName, taskStackSize, taskPriority) {
    
}


void ExtInterruptService::add(
    ExtInterrupt* extInterrupt) {
    
    if ((extInterrupt != nullptr) && (extInterrupt->service == nullptr)) {
        extInterrupts.add(extInterrupt);
        extInterrupt->service = this;
    }
}


void ExtInterruptService::remove(
    ExtInterrupt* extInterrupt) {

    if ((extInterrupt != nullptr) && (extInterrupt->service == this)) {
        extInterrupt->service = nullptr;
        extInterrupts.remove(extInterrupts.indexOf(extInterrupt));
    }
    
}


void ExtInterruptService::run(
    Task* task) {
    
    halCNEnable();
    
    while (true) {
        
    }
}


ExtInterrupt::ExtInterrupt(
    ExtInterruptService *service,
    CNPin pin):
    
    service(service),
    pin(pin) {
    
    halCNInitialize(pin, HAL_CN_ENABLE_ON | HAL_CN_PULLUP_UP, interruptCallback, this);
    
    if (service != nullptr)
        service->add(this);   
}


ExtInterrupt::~ExtInterrupt() {
    
    halCNInitialize(pin, HAL_CN_ENABLE_OFF | HAL_CN_PULLUP_OFF, nullptr, nullptr);

    if (service != nullptr)
        service->remove(this);
}


void ExtInterrupt::interruptCallback(
    CNPin pin, 
    void *param) {
    
}

