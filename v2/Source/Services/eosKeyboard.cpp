#include "Services/eosKeyboard.hpp"
#include "../../../MD-KBD01/KBD01Messages.h"


using namespace eos;


const unsigned taskStackSize = 512;
const unsigned taskLoopDelay = 50;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param i2cMasterService: El servei de comunicacions I2C
/// \param addr: Adressa I2C del selector
///
KeyboardService::KeyboardService(
    Application *application,
    I2CMasterServiceHandle _i2cService,
    uint8_t _addr):
    
    Service(application, "KeyboardService", taskStackSize, taskPriority),
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
///
void KeyboardService::run() {
    
    static uint8_t query[1] = { KBD_CMD_GETSTATUS };
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
            
                KeyboardState newState = response[1];

                if (state != newState) {
                    state = newState;
                    if (evNotify != nullptr) 
                        evNotify->execute(state);
                }
            }
        }
    }
}
