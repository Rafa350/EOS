#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/Usb/eosUsbClient.hpp"



using namespace eos;

const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


UsbClientService::UsbClientService() :
    task(taskStackSize, taskPriority, this) {
    
}


void UsbClientService::run() {
    
}