#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/Usb/eosUsbClient.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


extern "C" void usbSetup(void);
extern "C" void usbLoop(void);


/// ----------------------------------------------------------------------
/// \brief Contructor
///
UsbClientService::UsbClientService() :
    task(taskStackSize, taskPriority, this) {
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
///
void UsbClientService::run() {
       
    usbSetup();
    while (true)
        usbLoop();
}