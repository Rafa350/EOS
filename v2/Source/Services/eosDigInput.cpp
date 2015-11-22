#include "Services/eosDigInput.hpp"
#include "System/eosTask.hpp"
#include "HAL/halGPIO.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


/// ----------------------------------------------------------------------
/// \brief Constructor
///
DigInputService::DigInputService() :
    task(taskStackSize, taskPriority, this) {
}


/// ----------------------------------------------------------------------
/// \brief Afegeix una entrada
/// \param input: L'entrada a afeigir
///
void DigInputService::add(
    DigInputHandle input) {

    inputs.add(input);
}


/// ----------------------------------------------------------------------
/// \brief Tasca de control del servei
///
void DigInputService::run() {
    
    unsigned tc = Task::getTickCount();

    while (true) {
        
        Task::delayUntil(10, &tc);
        
        DigInputListIterator iterator(inputs);
        while (!iterator.isEnd()) {
            
            DigInputHandle input = iterator.current();
            bool changed = false;
            
            input->pattern <<= 1;
            if (input->pinGet())
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
            
            ++iterator;
        }
    }    
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei.
/// \param pin: El numero de pin.
/// \param inverted: Indica si la senyal va invertida.
///
DigInput::DigInput(
    DigInputServiceHandle _service,
    uint8_t _pin, 
    bool _inverted):
    service(_service),
    pin(_pin),
    inverted(_inverted),
    evChange(nullptr) {
    
    halGPIOPinSetModeInput(pin);
    state = pinGet();
    pattern = state ? 0xFFFFFFFF : 0x00000000;
    
    service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigInput::~DigInput() {
    
    if (evChange != nullptr)
        delete evChange;
}


/// ----------------------------------------------------------------------
/// \brief Lectura del port d'una entrada.
/// \return Valor lleigit del port.
///
bool DigInput::pinGet() const {
    
    bool p = halGPIOPinGetState(pin);
    return inverted ? !p : p;
}
