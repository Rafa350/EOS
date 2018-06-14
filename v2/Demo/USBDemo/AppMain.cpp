#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Services/Usb/eosUsbDevice.h"


using namespace eos;



class MyAppLoopService: public AppLoopService {
   
    public:
        MyAppLoopService(Application *application): AppLoopService(application) {}
        
    protected:
        void setup();
        void loop();
};


class MyApplication: public Application {
    private:
        MyAppLoopService *appService;
        UsbDeviceService *usbService;
        UsbDevice *usbCDCDevice;
        
    public :
        MyApplication();
};


///-----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {
    
    appService = new MyAppLoopService(this);    

    usbService = new UsbDeviceService(this);    
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
void AppMain() {
   
    MyApplication *app = new MyApplication();
    app->execute();
    delete app;
}
