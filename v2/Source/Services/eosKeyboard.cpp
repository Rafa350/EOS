#include "Services/eosKeyboard.hpp"
#include "Services/eosI2CMaster.hpp"
#include "../../../MD-KBD01/KBD01Messages.h"


using namespace eos;


static const char *serviceName = "KeyboardService";
static const unsigned taskStackSize = 512;
static const unsigned taskLoopDelay = 50;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param application: Aplicacio a la que pertany.
/// \param i2cService: El servei de comunicacions I2C
/// \param addr: Adressa I2C del selector
///
KeyboardService::KeyboardService(
    Application *application,
    I2CMasterService *_i2cService,
    uint8_t _addr):
    
    Service(application, serviceName, taskStackSize, taskPriority),
    i2cService(_i2cService),
    addr(_addr),
    state(0),
    evNotify(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
KeyboardService::~KeyboardService() {
    
    if (evNotify != nullptr)
        delete evNotify;
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
/// \param task: La tasca actual.
///
void KeyboardService::run(
    Task *task) {
    
    KbdGetStateMessage query;
    query.cmd = KBD_CMD_GETSTATE;
    
    KbdGetStateResponse response;
    
    BinarySemaphore endTransactionNotify;

    while (true) {
        
        Task::delay(taskLoopDelay);
        
        if (i2cService->startTransaction(
            addr, 
            &query, sizeof(query), 
            &response, sizeof(response), 
            (unsigned) -1, 
            &endTransactionNotify)) {
            
            if (endTransactionNotify.take((unsigned) -1)) {
            
                if (response.cmd == KBD_CMD_GETSTATE) {
                    
                    if (state != response.keyState) {
                        state = response.keyState;
                        if (evNotify != nullptr) 
                            evNotify->execute(state);
                    }
                }
            }
        }
    }
}
