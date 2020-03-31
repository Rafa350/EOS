#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "Services/eosDigInputService.h"


using namespace eos;


#define PATTERN_mask     0xFF
#define PATTERN_ON       0xFF
#define PATTERN_OFF      0x00
#define PATTERN_POSEDGE  0x7F
#define PATTERN_NEGEDGE  0x80


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany
///
DigInputService::DigInputService(
    Application* application):
    
    Service(application) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

    Task::enterCriticalSection();
    
    while (!inputs.isEmpty()) {
        DigInput* input = inputs.getFirst();
        removeInput(input);       
        delete input;
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    Task::enterCriticalSection();
    
    if (input->service == nullptr) {
        inputs.add(input);
        input->service = this;
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    Task::enterCriticalSection();
    
    if (input->service == this) {
        input->service = nullptr;
        inputs.remove(input);
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {
    
    Task::enterCriticalSection();
    
    while (!inputs.isEmpty())
        removeInput(inputs.getFirst());
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
      
    for (DigInputListIterator it(inputs); it.hasNext(); it.next()) {
        
        DigInput* input = it.getCurrent();

        input->options &= ~HAL_GPIO_MODE_mask;
        input->options |= HAL_GPIO_MODE_INPUT;
        halGPIOInitializePin(input->port, input->pin, input->options, HAL_GPIO_AF_NONE);

        input->state = halGPIOReadPin(input->port, input->pin);
        input->pattern = input->state ? PATTERN_ON : PATTERN_OFF;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    weakTime = Task::getTickCount();
    
    while (true) {
        
        Task::delay(10, weakTime);

        for (DigInputListIterator it(inputs); it.hasNext(); it.next()) {
            DigInput* input = it.getCurrent();

            bool changed = false;

            input->pattern <<= 1;
            if (halGPIOReadPin(input->port, input->pin))
                input->pattern |= 1;

            if ((input->pattern & PATTERN_mask) == PATTERN_POSEDGE) {
                changed = true;
                input->state = true;
            }
            else if ((input->pattern & PATTERN_mask) == PATTERN_NEGEDGE) {
                changed = true;
                input->state = false;
            }

            if (changed && (input->eventCallback != nullptr)) {
                DigInput::EventArgs args;
                args.input = input;
                input->eventCallback->execute(args);
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    port: El port.
/// \param    pin: El numero de pin.
/// \param    options: Opcions del pin.
///
DigInput::DigInput(
    DigInputService* service,
    GPIOPort port, 
    GPIOPin pin, 
    GPIOOptions options) :

    service(nullptr),
    port(port),
    pin(pin),
    options(options),
    eventCallback(nullptr) {
    
    if (service != nullptr)
        service->addInput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInput::~DigInput() {

    if (service != nullptr)
        service->removeInput(this);
}
