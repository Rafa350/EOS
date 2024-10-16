#include "eos.h"
#include "Controllers/Pin/Drivers/GPIO/eosPinDriver_GPIO.h"
#include "HAL/halSYS.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"
#include "htl/htlINT.h"
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
    _sw1ChangedEvent(*this, &MyApplication::sw1ChangedEventHandler)
    #ifdef EXIST_SW2
        , _sw2ChangedEvent(*this, &MyApplication::sw2ChangedEventHandler)
    #endif
    #ifdef EXIST_SW3
        , _sw3ChangedEvent(*this, &MyApplication::sw3ChangedEventHandler)
    #endif
{
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Configura el servei d'entrades digitals
	//
    _digInputService = new DigInputService();
    addService(_digInputService, Task::Priority::high, 512, "INPUTS");

    // Configura la entrada corresponent al switch SW1
    //
    _pinSW1->initInput(gpio::InputMode::pullUp);
    _sw1 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW1));
    _sw1->setChangedEvent(_sw1ChangedEvent);

    // Configura la entrada corresponent al switch SW2
    //
    #ifdef EXIST_SW2
    _pinSW2->initInput(gpio::InputMode::pullUp);
    _sw2 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW2));
    _sw2->setChangedEvent(_sw2ChangedEvent);
    #endif

    // Configure la entrada corresponent al switch SW3
    //
    #ifdef EXIST_SW3
    _pinSW3->initInput(gpio::InputMode::pullUp);
    _sw3 = new DigInput(_digInputService, new PinDriver_GPIO(_pinSW3));
    _sw3->setChangedEvent(_sw3ChangedEvent);
    #endif

    // Configura el temporitzador pel servei d'entrades digitals
    //
    INPSRV_TMR::init();
    INPSRV_TMR::setClockSource(TMRClockSource::pclk);
    INPSRV_TMR::setResolution(TMRResolution::_16);
    INPSRV_TMR::setClockDivider(TMRClockDivider::_64);
    INPSRV_TMR::setPeriod(((halSYSGetPeripheralClockFrequency() * config::digInputService::timerPeriod) / 64000) - 1);
    INPSRV_TMR::setInterruptFunction(digInputServiceTMRInterruptFunction, _digInputService);

    // Configura les interrupcions pel servei d'entrades digitals
    //
    irq::setInterruptVectorPriority(
        DigInputService_TimerInterruptVector,
        DigInputService_TimerInterruptPriority,
        DigInputService_TimerInterruptSubPriority);


    // Configura el servei de sortides digitals
    //
    _digOutputService = new DigOutputService();
    addService(_digOutputService, Task::Priority::normal, 512, "OUTPUTS");

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

    // Configura el temporitzador pel servei de sortides digitals
    //
    OUTSRV_TMR::init();
    OUTSRV_TMR::setClockSource(TMRClockSource::pclk);
    OUTSRV_TMR::setResolution(TMRResolution::_16);
    OUTSRV_TMR::setClockDivider(TMRClockDivider::_64);
    OUTSRV_TMR::setPeriod(((halSYSGetPeripheralClockFrequency() * config::digOutputService::timerPeriod) / 64000) - 1);
    OUTSRV_TMR::setInterruptFunction(digOutputServiceTMRInterruptFunction, _digOutputService);

    // Configura les interrupcions
    //
    irq::setInterruptVectorPriority(
        DigOutputService_TimerInterruptVector,
        DigOutputService_TimerInterruptPriority,
        DigOutputService_TimerInterruptSubPriority);

    // Inicia el temporitzador del servei d'entrades digitals
    //
    INPSRV_TMR::enableInterrupt(TMRInterrupt::update);
    INPSRV_TMR::start();

    // Inicia el temporitzador del servei de sortides digitals
    //
    OUTSRV_TMR::enableInterrupt(TMRInterrupt::update);
    OUTSRV_TMR::start();
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
void MyApplication::sw1ChangedEventHandler(
    const eos::DigInput *sender,
    const DigInput::ChangedEventArgs &args) {

    if (args.pinState == SW1_StateON) {

        _led1->pulse(500);
        _led2->delayedPulse(250, 500);
        #ifdef EXIST_LED3
            _led3->delayedPulse(500, 500);
        #endif
    }
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SW2
void MyApplication::sw2ChangedEventHandler(
    const eos::DigInput *sender,
    const DigInput::ChangedEventArgs &args) {

    if (args.pinState == SW2_StateON) {

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


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 3.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SW3
void MyApplication::sw3ChangedEventHandler(
    const eos::DigInput *sender,
    const DigInput::ChangedEventArgs &args) {

    if (args.pinState == SW3_StateON) {

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


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzados del servei
///           d'entrades digitals.
///
void MyApplication::digInputServiceTMRInterruptFunction(
    htl::TMRInterruptParam param) {

    if (INPSRV_TMR::getFlag(TMRFlag::update)) {
        INPSRV_TMR::clearFlag(TMRFlag::update);

        DigInputService *service = reinterpret_cast<DigInputService*>(param);
        service->tmrInterruptFunction();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzados del servei
///           de sortides digitals.
///
void MyApplication::digOutputServiceTMRInterruptFunction(
    htl::TMRInterruptParam param) {

    if (OUTSRV_TMR::getFlag(TMRFlag::update)) {
        OUTSRV_TMR::clearFlag(TMRFlag::update);

        DigOutputService *service = reinterpret_cast<DigOutputService*>(param);
        service->tmrInterruptFunction();
    }
}
