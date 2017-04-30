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


ExtInterrupt::ExtInterrupt(
    ExtInterruptService *service):
    
    service(service) {
    
    if (service != nullptr)
        service->add(this);   
}


ExtInterrupt::~ExtInterrupt() {
    
    if (service != nullptr)
        service->remove(this);
}