#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigInput.h"


using namespace eos;


static const char *serviceName = "DigInputService";
static const unsigned taskStackSize = 512;
static const TaskPriority taskPriority = TaskPriority::normal;


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: L'aplicacio a la que pertany
/// \param pInfo: Parametres d'inicialitzacio.
///
DigInputService::DigInputService(
    Application *pApplication,
    const DigInputServiceInitializeInfo *pInfo) :
    Service(pApplication, serviceName, taskStackSize, taskPriority) {
}


/// ----------------------------------------------------------------------
/// \brief Afegeix una entrada al servei.
/// \param pInput: L'entrada a afeigir.
///
void DigInputService::add(
    DigInput *pInput) {
    
    eosArgumentIsNotNull(pInput);
    
    eosAssert(pInput != nullptr);
    eosAssert(pInput->pService == nullptr);

    inputs.add(pInput);
    pInput->pService = this;
}


/// ----------------------------------------------------------------------
/// \brieg Elimina una entrada del servei.
/// \param pInput:La entrada a eliminar.
///
void DigInputService::remove(
    DigInput *pInput) {

    eosArgumentIsNotNull(pInput);

    eosAssert(pInput != nullptr);
    eosAssert(pInput->pService == this);

    pInput->pService = nullptr;
    inputs.remove(inputs.indexOf(pInput));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
    
}

/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void DigInputService::onTask() {

    weakTime = Task::getTickCount();
    
    while (true) {
        
        Task::delay(10, weakTime);

        DigInputListIterator iterator(inputs);
        while (iterator.hasNext()) {

            DigInput *input = iterator.current();
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

            if (changed && (input->evChange != nullptr))
                input->evChange->execute(input);

            iterator.next();
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei.
/// \param info: Parametres d'inicialitzacio.
///
DigInput::DigInput(
    DigInputService *pService,
    const DigInputInitializeInfo *pInfo):

    pService(nullptr),
    evChange(nullptr) {
       
    eosArgumentIsNotNull(pInfo);
    
    port = pInfo->port;
    pin = pInfo->pin;

    GPIOOptions options = HAL_GPIO_MODE_INPUT;
    halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);

    state = halGPIOReadPin(port, pin);
    pattern = state ? 0xFFFFFFFF : 0x00000000;

    if (pService != nullptr)
        pService->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigInput::~DigInput() {

    if (pService != nullptr)
        pService->remove(this);

    if (evChange != nullptr)
        delete evChange;
}
