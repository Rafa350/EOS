#include "eos.h"
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
/// \param application: L'aplicacio a la que pertany
/// \param info: Parametres d'inicialitzacio.
///
DigInputService::DigInputService(
    Application *application,
    const DigInputServiceInitializeInfo *info) :
    Service(application, serviceName, taskStackSize, taskPriority) {
}


/// ----------------------------------------------------------------------
/// \brief Afegeix una entrada al servei.
/// \param input: L'entrada a afeigir.
///
void DigInputService::add(
    DigInput *input) {

    if ((input != nullptr) && (input->service == nullptr)) {
        inputs.add(input);
        input->service = this;
    }
}


/// ----------------------------------------------------------------------
/// \brieg Elimina una entrada del servei.
/// \param La entrada a eliminar.
void DigInputService::remove(
    DigInput *input) {
    
    if ((input != nullptr) && (input->service == this)) {
        input->service = nullptr;
        inputs.remove(inputs.indexOf(input));
    }
}


/// ----------------------------------------------------------------------
/// \brief Tasca de control del servei.
/// \param task: La tasca que s'esta executant.
///
void DigInputService::run(
    Task *task) {
    
    unsigned tc = Task::getTickCount();

    while (true) {
        
        Task::delayUntil(10, &tc);
        
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
    DigInputService *service,
    const DigInputInitializeInfo *info):

    service(nullptr),
    port(info->port),
    pin(info->pin),
    evChange(nullptr) {
    
    GPIOInitializePinInfo pinInfo;
    pinInfo.port = info->port;
    pinInfo.pin = info->pin;
    pinInfo.options = HAL_GPIO_MODE_INPUT;
    halGPIOInitializePin(&pinInfo);
    
    state = halGPIOReadPin(port, pin);
    pattern = state ? 0xFFFFFFFF : 0x00000000;
    
    if (service != nullptr)
        service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigInput::~DigInput() {
    
    if (service != nullptr)
        service->remove(this);
    
    if (evChange != nullptr)
        delete evChange;
}
