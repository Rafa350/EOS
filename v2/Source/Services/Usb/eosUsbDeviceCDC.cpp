#include "eos.h"
#include "Services/Usb/eosUsbDevice.h"
#include "HAL/halUSBDevice.h"


using namespace eos;


extern "C" void APP_Initialize(void);
extern "C" void APP_Tasks(void);


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
    
    halUSBDeviceCDCSetup(nullptr, nullptr);
}


/// ---------------------------------------------------------------------
/// \brief Procesament de les tasques de control.
///
void UsbDeviceCDC::process() {    

    halUSBDeviceCDCTask();
}
