#include "Services/Forms/eosSelector.hpp"
#include "../../../MD-SEL01/SEL01Messages.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           SelectorService::SelectorService(
 *               I2CMasterService *i2cService) 
 * 
 *       Entrada:
 *          i2cMasterService: El servei de comunicacions I2C
 *          addr            : Adressa I2C del selector
 *
 *************************************************************************/

SelectorService::SelectorService(
    I2CMasterService *i2cService,
    uint8_t addr):
    task(taskStackSize, taskPriority, this) {
    
    this->i2cService = i2cService;
    this->addr = addr;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void SelectorService::run() 
 *
 *************************************************************************/

void SelectorService::run() {
    
    static uint8_t query[1] = { SEL_CMD_GETSTATE };
    uint8_t response[10];
    BinarySemaphore endTransactionNotify;

    while (true) {
        
        Task::delay(100);
        
        if (i2cService->startTransaction(
            addr, 
            query, sizeof(query), 
            response, sizeof(response), 
            1000,
            &endTransactionNotify)) {
            
            if (endTransactionNotify.take(1000)) {
            
                uint8_t newState = response[0];
                uint16_t newPosition = (uint16_t) ((response[3] << 8) | response[2]);

                if ((state != newState) || (position != newPosition)) {
                    position = newPosition;
                    state = newState;
                }
            }
        }
    }
}
