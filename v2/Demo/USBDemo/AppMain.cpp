#include "eos.h"
#include "hal/halGPIO.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Services/Usb/eosUsbDevice.h"


using namespace eos;



class MyAppLoopService: public AppLoopService {
   
    public:
        MyAppLoopService(Application *application): AppLoopService(application) {}
        
    protected:
        void onSetup();
        void onLoop();
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
/// \brief Inicialitzacio.
///
void MyAppLoopService::onSetup() {
    
    halGPIOInitializePin(
        LED_LED1_PORT, 
        LED_LED1_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 
        HAL_GPIO_AF_NONE);
    
    halGPIOInitializePin(
        LED_LED2_PORT, 
        LED_LED2_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 
        HAL_GPIO_AF_NONE);
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio
///
void MyAppLoopService::onLoop() {

    halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
    Task::delay(500);
}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {
   
    MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
