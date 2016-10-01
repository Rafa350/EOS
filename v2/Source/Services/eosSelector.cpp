#include "Services/eosSelector.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"


using namespace eos;


static const char *serviceName = "SelectorService";
static const unsigned taskStackSize = 512;
static const unsigned taskLoopDelay = 25;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param application: Aplicacio a la que pertany.
/// \param i2cService: El servei de comunicacions I2C
/// \param addr: Adressa I2C del selector
///
SelectorService::SelectorService(
    Application *application,
    I2CMasterService *_i2cService,
    uint8_t _addr):
    
    Service(application, serviceName, taskStackSize, taskPriority),
    i2cService(_i2cService),
    addr(_addr),
    evNotify(nullptr),
    state(0),
    position(0) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
SelectorService::~SelectorService() {
    
    if (evNotify != nullptr)
        delete evNotify;
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
/// \param task: La tasca actual.
///
void SelectorService::run(
    Task *task) {
    
    static uint8_t query[1] = { SEL_CMD_GETSTATE };
    uint8_t response[10];
    BinarySemaphore endTransactionNotify;

    while (true) {
        
        Task::delay(taskLoopDelay);
        
        if (i2cService->startTransaction(
            addr, 
            query, sizeof(query), 
            response, sizeof(response), 
            (unsigned) -1,
            &endTransactionNotify)) {
            
            if (endTransactionNotify.take((unsigned) - 1)) {
            
                SelectorState newState = response[1];
                SelectorPosition newPosition = (int16_t) ((response[3] << 8) | response[2]);

                if ((state != newState) || (position != newPosition)) {
                    position = newPosition;
                    state = newState;
                    if (evNotify != nullptr)
                        evNotify->execute(position, state);
                }
            }
        }
    }
}
