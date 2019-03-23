#include "eos.h"
#include "HAL/halGPIO.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"
#include "Services/eosAppLoop.h"
#include "Controllers/Usb/eosUsb.h"
#include "Controllers/Usb/eosUsbDevice.h"


using namespace eos;


class LedService: public AppLoopService {

    public:
        LedService(Application *application): AppLoopService(application) {}

    protected:
        void onSetup();
        void onLoop();
};


class UsbService: public AppLoopService {

	private:
		UsbDevice *usbDevice;

    public:
        UsbService(Application *application): AppLoopService(application) {}

    protected:
        void onSetup();
        void onLoop();
};


class MyApplication: public Application {
    private:
        LedService *ledService;
        UsbService *usbService;


    public :
        MyApplication();
};


///-----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {

    ledService = new LedService(this);
    usbService = new UsbService(this);
}


///-----------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void LedService::onSetup() {

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
void LedService::onLoop() {

    halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
    Task::delay(500);
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void UsbService::onSetup() {

	usbDevice = new UsbDeviceCDC(HAL_USB_PORT_0);
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void UsbService::onLoop() {

}


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

    MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
