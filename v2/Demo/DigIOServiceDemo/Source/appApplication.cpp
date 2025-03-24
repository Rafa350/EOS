#include "eos.h"
#include "Controllers/Pin/Drivers/GPIO/eosPinDriver_GPIO.h"
#include "HAL/halSYS.h"
#include "HTL/htlGPIO.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosRTOSApplication.h"
#include "appApplication.h"


using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    _digInputNotifyEvent(*this, &MyApplication::digInputNotifyEventHandler)
{
}


/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void MyApplication::onExecute() {

    // Configura el servei d'entrades digitals
	//
    _digInputService = new DigInputService();
    _digInputService->setNotifyEvent(_digInputNotifyEvent);
    addService(_digInputService);

    // Configura la entrada corresponent al switch SW1
    //
    _pinSW1->initInput(gpio::InputMode::pullUp);
    _sw1 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW1));

    // Configura la entrada corresponent al switch SW2
    //
    #ifdef EXIST_SW2
    _pinSW2->initInput(gpio::InputMode::pullUp);
    _sw2 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW2));
    #endif

    // Configure la entrada corresponent al switch SW3
    //
    #ifdef EXIST_SW3
    _pinSW3->initInput(gpio::InputMode::pullUp);
    _sw3 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW3));
    #endif

    // Configura el servei de sortides digitals
    //
    _digOutputService = new DigOutputService();
    addService(_digOutputService);

    // Configura la sortida corresponent al led LED1
    //
    _pinLED1->initOutput(gpio::OutputMode::pushPull);
    _pinLED1->clear();
    _led1 = new DigOutput(_digOutputService, new PinDriver_GPIO(_pinLED1));

    // Configura la sortida corresponent al led LED2
    //
    #ifdef EXIST_LED2
    _pinLED2->initOutput(gpio::OutputMode::pushPull);
    _pinLED2->clear();
    _led2 = new DigOutput(_digOutputService, new PinDriver_GPIO(_pinLED2));
    #endif

    // Configura la sortida corresponent al led LED3
    //
    #ifdef EXIST_LED3
    _pinLED3->initOutput(gpio::OutputMode::pushPull);
    _pinLED3->clear();
    _led3 = new DigOutput(_digOutputService, new PinDriver_GPIO(_pinLED3));
    #endif
   
    // Bucle d'execucio
    //
    while (true)
        eos::Task::delay(1000);
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
void MyApplication::digInputNotifyEventHandler(
    DigInputService::NotifyID id,
    DigInputService::NotifyEventArgs * const args) {

    if (args->changed.input == _sw1) {
        
        if (_sw1->read() == SW1_StateON) {
        _led1->pulse(500);
         _led2->delayedPulse(250, 500);
 #ifdef EXIST_LED3
        _led3->delayedPulse(500, 500);
 #endif
        }
    }

#ifdef EXIST_SW2
    else if (args->changed.input == _sw2) {
        
        if (_sw2->read() == SW2_StateON) {
 #ifdef EXIST_LED3
            _led3->pulse(500);
 #endif
 #ifdef EXIST_LED2
            _led2->delayedPulse(250, 500);
 #endif
            _led1->delayedPulse(500, 500);
        }
    }
#endif

#ifdef EXIST_SW3
    if (args->changed.input == _sw3) {
       if (_sw3->read() == SW3_StateON) {

            _led1->pulse(1000);
#ifdef EXIST_LED2
            _led2->pulse(2000);
#endif
 #ifdef EXIST_LED3
            _led3->pulse(3000);
#endif
        }
    }
#endif
}
