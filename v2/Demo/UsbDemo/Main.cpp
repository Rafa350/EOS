#include "eos.hpp"
#include "System/eosApplication.hpp"
#include "System/Core/eosTask.hpp"
#include "Services/eosAppLoop.hpp"
#include "Services/Usb/eosUsbDevice.hpp"


using namespace eos;


class MyAppLoopService: public AppLoopService {
   
    protected:
        void setup();
        void loop();
};


class MyApplication: public Application {
    private:
        MyAppLoopService *appService;
        UsbDeviceServiceHandle usbService;
        UsbDeviceHandle usbCDCDevice;
        
    public :
        MyApplication();
};


///-----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {
    
    appService = new MyAppLoopService();    

    usbService = new UsbDeviceService();    
    usbCDCDevice = new UsbDeviceCDC(usbService);
}


///-----------------------------------------------------------------------
/// \brief Process d'inicialitzacio. El sistema el crida nomes un cop.
///
void MyAppLoopService::setup() {
    
    initLED1();
    initLED2();
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio. El sistema el crida periodicament.
///
void MyAppLoopService::loop() {
    
    invLED1();
    Task::delay(500);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
int main(void) {
   
    MyApplication *app = new MyApplication();
    app->execute();
    delete app;

    return 0;
}
