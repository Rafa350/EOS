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
/// \param    pApplication: L'aplicacio al que pertany.
///
DigInputService::DigInputService(
    Application *pApplication) :
    
    DigInputService(pApplication, defaultConfiguration) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pApplication: L'aplicacio a la que pertany
/// \param    configuration: Parametres de configuracio.
///
DigInputService::DigInputService(
    Application *pApplication,
    const DigInputServiceConfiguration &configuration) :
    
    Service(pApplication, configuration.serviceConfiguration) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {
   
    // Elimina totes les entrades.
    //
    removeInputs();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    pInput: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *pInput) {

    // Prerequisits
    //
    eosAssert(pInput != nullptr);
    eosAssert(pInput->pService == nullptr);

    inputs.add(pInput);
    pInput->pService = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    pInput: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput *pInput) {

    // Precondicions
    //
    eosAssert(pInput != nullptr);
    eosAssert(pInput->pService == this);

    pInput->pService = nullptr;
    inputs.remove(pInput);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {
    
    while (!inputs.isEmpty())
        inputs.remove(inputs.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
    
    for (DigInputListIterator it(inputs); it.hasNext(); it.next())
        it.current()->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    weakTime = Task::getTickCount();
    
    while (true) {
        
        Task::delay(10, weakTime);

        for (DigInputListIterator it(inputs); it.hasNext(); it.next()) {

            DigInput *pInput = it.current();
            bool changed = false;

            pInput->pattern <<= 1;
            if (halGPIOReadPin(pInput->port, pInput->pin))
                pInput->pattern |= 1;

            if ((pInput->pattern & PATTERN_MASK) == PATTERN_ON) {
                changed = true;
                pInput->state = true;
            }
            else if ((pInput->pattern & PATTERN_MASK) == PATTERN_OFF) {
                changed = true;
                pInput->state = false;
            }

            if (changed && (pInput->pChangeEventCallback != nullptr)) {
                DigInputEventArgs args = {
                    .pDigInput = pInput
                };
                pInput->pChangeEventCallback->execute(args);
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pService: El servei.
/// \param    configuration: Parametres de configuracio.
///
DigInput::DigInput(
    DigInputService *pService,
    const DigInputConfiguration &configuration):

    pService(nullptr),
    pChangeEventCallback(nullptr) {
       
    port = configuration.port;
    pin = configuration.pin;

    if (pService != nullptr)
        pService->addInput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInput::~DigInput() {

    if (pService != nullptr)
        pService->removeInput(this);
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
