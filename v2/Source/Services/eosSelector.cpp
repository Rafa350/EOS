#include "Services/eosSelector.h"
#include "Services/eosI2CMaster.h"
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
    uint8_t addr):
    
    Service(application, serviceName, taskStackSize, taskPriority),
    i2cService(_i2cService),
    addr(addr),
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
    
    SelGetStateMessage query;
    query.cmd = SEL_CMD_GETSTATE;
    
    SelGetStateResponse response;
    
    BinarySemaphore endTransactionNotify;

    while (true) {
        
        Task::delay(taskLoopDelay);
        
        if (i2cService->startTransaction(
            addr, 
            &query, sizeof(query), 
            &response, sizeof(response), 
            (unsigned) -1,
            &endTransactionNotify)) {
            
            if (endTransactionNotify.take((unsigned) - 1)) {
                
                if (response.cmd == SEL_CMD_GETSTATE) {

                    if ((state != response.state) || (position != response.position)) {
                        position = response.position;
                        state = response.state;
                        if (evNotify != nullptr)
                            evNotify->execute(position, state);
                    }
                }
            }
        }
    }
}
