#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/Usb/eosUsbClient.hpp"
#include "HAL/halUSBDevice.h"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Contructor
///
UsbClientService::UsbClientService():
    task(taskStackSize, taskPriority, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
///
void UsbClientService::run() {
       
    halUSBDeviceSetup();
    
    while (true) {
        halUSBTask();
        
    }
}


/// ----------------------------------------------------------------------
/// \brief Contructor
/// \param service: El servei al que pertany.
///
UsbDevice::UsbDevice(
    UsbClientServiceHandle* service) {
    
}