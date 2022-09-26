#include "eos.h"
#include "HAL/halSYS.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"
#include "htl/htlINT.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"
#include "appApplication.h"



using namespace eos;
using namespace htl;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    _sw1ChangedEventCallback(*this, &MyApplication::sw1ChangedEventHandler)
    #ifdef EXIST_SW2
        , _sw2ChangedEventCallback(*this, &MyApplication::sw2ChangedEventHandler)
    #endif
    #ifdef EXIST_SW3
        , _sw3ChangedEventCallback(*this, &MyApplication::sw3ChangedEventHandler)
    #endif
{
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Configura el servei d'entrades digitals
	//
    _digInputService = new DigInputService(this);
    _digInputService->setPriority(Task::Priority::high);

    // Configura la entrada corresponent al switch SW1
    //
    PinSW1::initInput(GPIOPull::up);
    _sw1 = new DigInput(_digInputService, getGPIOWrapper<PinSW1>());
    _sw1->enableChangedEventCallback(_sw1ChangedEventCallback);

    // COnfigura la entrada corresponent al switch SW2
    //
    #ifdef EXIST_SW2
        PinSW2::initInput(GPIOPull::up);
        _sw2 = new DigInput(_digInputService, getGPIOWrapper<PinSW2>());
        _sw2->enableChangedEventCallback(_sw2ChangedEventCallback);
    #endif

    // Configure la entrada corresponent al switch SW3
    //
    #ifdef EXIST_SW3
        PinSW3::initInput(GPIOPull::up);
        _sw3 = new DigInput(_digInputService, getGPIOWrapper<PinSW3>());
        _sw3->enableChangedEventCallback(_sw3ChangedEventCallback);
    #endif

    // Configura el temporitzador pel servei d'entrades digitals
    //
    TMR_INP::init();
    TMR_INP::setClockSource(TMRClockSource::pclk);
    TMR_INP::setResolution(TMRResolution::_16);
    TMR_INP::setClockDivider(TMRClockDivider::_64);
    TMR_INP::setPeriod(((halSYSGetPeripheralClockFrequency() * config::digInputService::timerPeriod) / 64000) - 1);
    TMR_INP::setInterruptFunction(tmrInpInterruptFunction, _digInputService);

    // Configura les interrupcions pel servei d'entrades digitals
    //
    htl::INT_1::setInterruptVectorPriority(
        DigInputService_TimerInterruptVector,
        DigInputService_TimerInterruptPriority,
        DigInputService_TimerInterruptSubPriority);


    // Configura el servei de sortides digitals
    //
    _digOutputService = new DigOutputService(this);

    // Configura la sortida corresponent al led LED1
    //
    PinLED1::initOutput();
    PinLED1::clear();
    _led1 = new DigOutput(_digOutputService, htl::getGPIOWrapper<PinLED1>());

    // COnfigura la sortida corresponent al led LED2
    //
    #ifdef EXIST_LED2
        PinLED2::initOutput();
        PinLED2::clear();
        _led2 = new DigOutput(_digOutputService, htl::getGPIOWrapper<PinLED2>());
    #endif

    // COnfigura la sortida corresponent al led LED3
    //
    #ifdef EXIST_LED3
        PinLED3::initOutput();
        PinLED3::clear();
        _led3 = new DigOutput(_digOutputService, htl::getGPIOWrapper<PinLED3>());
    #endif

    // Configura el temporitzador pel servei de sortides digitals
    //
    TMR_OUT::init();
    TMR_OUT::setClockSource(TMRClockSource::pclk);
    TMR_OUT::setResolution(TMRResolution::_16);
    TMR_OUT::setClockDivider(TMRClockDivider::_64);
    TMR_OUT::setPeriod(((halSYSGetPeripheralClockFrequency() * config::digOutputService::timerPeriod) / 64000) - 1);
    TMR_OUT::setInterruptFunction(tmrOutInterruptFunction, _digOutputService);

    // Configura les interrupcions
    //
    INT_1::setInterruptVectorPriority(
        DigOutputService_TimerInterruptVector,
        DigOutputService_TimerInterruptPriority,
        DigOutputService_TimerInterruptSubPriority);

    // Inicia el temporitzador del servei d'entrades digitals
    //
    TMR_INP::enableInterrupt(TMREvent::update);
    TMR_INP::start();

    // Inicia el temporitzador del servei de sortides digitals
    //
    TMR_OUT::enableInterrupt(TMREvent::update);
    TMR_OUT::start();
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
void MyApplication::sw1ChangedEventHandler(
    const DigInput::ChangedEventArgs &args) {

    if (args.value == SW1_ON) {
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
    const DigInput::ChangedEventArgs &args) {

    if (args.value == SW2_ON) {
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
    const DigInput::ChangedEventArgs &args) {

    if (args.value == SW3_ON) {
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
void MyApplication::tmrInpInterruptFunction(
    htl::TMREvent event,
    htl::TMRInterruptParam param) {

    DigInputService *service = reinterpret_cast<DigInputService*>(param);
    service->tmrInterruptFunction();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzados del servei
///           de sortides digitals.
///
void MyApplication::tmrOutInterruptFunction(
    htl::TMREvent event,
    htl::TMRInterruptParam param) {

    DigOutputService *service = reinterpret_cast<DigOutputService*>(param);
    service->tmrInterruptFunction();
}
