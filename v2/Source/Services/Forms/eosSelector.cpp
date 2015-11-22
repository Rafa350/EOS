#include "Services/Forms/eosSelector.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param i2cMasterService: El servei de comunicacions I2C
/// \param addr: Adressa I2C del selector
///
SelectorService::SelectorService(
    I2CMasterServiceHandle _i2cService,
    uint8_t _addr):
    task(taskStackSize, taskPriority, this),
    i2cService(_i2cService),
    addr(_addr),
    evChange(nullptr),
    state(0),
    position(0) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
SelectorService::~SelectorService() {
    
    if (evChange != nullptr)
        delete evChange;
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
///
void SelectorService::run() {
    
    static uint8_t query[1] = { SEL_CMD_GETSTATE };
    uint8_t response[10];
    BinarySemaphore endTransactionNotify;

    while (true) {
        
        Task::delay(25);
        
        if (i2cService->startTransaction(
            addr, 
            query, sizeof(query), 
            response, sizeof(response), 
            (unsigned) -1,
            &endTransactionNotify)) {
            
            if (endTransactionNotify.take((unsigned) - 1)) {
            
                uint8_t newState = response[1];
                int16_t newPosition = (int16_t) ((response[3] << 8) | response[2]);

                if ((state != newState) || (position != newPosition)) {
                    position = newPosition;
                    state = newState;
                    if (evChange != nullptr)
                        evChange->execute(position, state);
                }
            }
        }
    }
}
