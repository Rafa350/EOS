#include "eos.h"
#include "Services/Usb/eosUsbDevice.h"
#include "HAL/halUSBDeviceCDC.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param service: El servei al que pertany.
///
UsbDeviceCDC::UsbDeviceCDC(UsbDeviceService *service):

    UsbDevice(service) {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void UsbDeviceCDC::initialize() {
    
    USBDeviceCDCInitializeInfo info;
    
    info.callback = nullptr;
    info.param = nullptr;    
    halUSBDeviceCDCInitialize(&info);
}


/// ---------------------------------------------------------------------
/// \brief Procesament de les tasques de control.
///
void UsbDeviceCDC::process() {    

    halUSBDeviceCDCTask();
}
