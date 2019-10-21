#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigInputService.h"


using namespace eos;


static DigInputServiceConfiguration defaultConfiguration = {
    .serviceConfiguration = {
        .serviceName = "DigInputService",
        .stackSize = 512,
        .priority = TaskPriority::normal
    }
};


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea l'objecte amb els parametres per defecte.
/// \param    application: L'aplicacio al que pertany.
///
DigInputService::DigInputService(
    Application *application) :
    
    DigInputService(application, defaultConfiguration) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pApplication: L'aplicacio a la que pertany
/// \param    configuration: Parametres de configuracio.
///
DigInputService::DigInputService(
    Application *application,
    const DigInputServiceConfiguration &configuration) :
    
    Service(application, configuration.serviceConfiguration) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

    while (!inputs.isEmpty()) {
        DigInput *input = inputs.getFirst();
        removeInput(input);       
        delete input;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *input) {

    // Prerequisits
    //
    eosAssert(input != nullptr);
    eosAssert(input->service == nullptr);

    inputs.add(input);
    input->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput *input) {

    // Precondicions
    //
    eosAssert(input != nullptr);
    eosAssert(input->service == this);

    input->service = nullptr;
    inputs.remove(input);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {
    
    while (!inputs.isEmpty())
        removeInput(inputs.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
      
    for (auto input: inputs)
        input->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    weakTime = Task::getTickCount();
    
    while (true) {
        
        Task::delay(10, weakTime);

        for (auto input: inputs) {

            bool changed = false;

            input->pattern <<= 1;
            if (halGPIOReadPin(input->port, input->pin))
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                changed = true;
                input->state = true;
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                changed = true;
                input->state = false;
            }

            if (changed && (input->changeEventCallback != nullptr)) {
                DigInputEventArgs args = {
                    .input = input
                };
                input->changeEventCallback->execute(args);
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    configuration: Parametres de configuracio.
///
DigInput::DigInput(
    DigInputService *service,
    const DigInputConfiguration &configuration):

    service(nullptr),
    changeEventCallback(nullptr) {
       
    port = configuration.port;
    pin = configuration.pin;

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


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la entrada.
///
void DigInput::initialize() {
    
    GPIOOptions options = HAL_GPIO_MODE_INPUT;
    halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);

    state = halGPIOReadPin(port, pin);
    pattern = state ? 0xFFFFFFFF : 0x00000000;
}
