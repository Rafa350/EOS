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
    _messageBusEventCallback(*this, &MyApplication::messageBusEventHandler),
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

    // Configura el servei de missatgeria
    //
    _messengerService = new MessengerService(this);

    _messageBus = new MessageBus<ButtonMessage>(10);
    _messageBus->subscribe(_messageBusEventCallback);
    _messengerService->addMessageBus(_messageBus);

    // Configura el servei d'entrades digitals
	//
    _digInputService = new DigInputService(this);
    _digInputService->setPriority(Task::Priority::high);

    // Configura la entrada corresponent al switch SW1
    //
    SW1_GPIO::initInput(GPIOPull::up);
    _sw1 = new DigInput(_digInputService, getGPIO<SW1_GPIO>());
    _sw1->enableChangedEventCallback(_sw1ChangedEventCallback);

    // Configura la entrada corresponent al switch SW2
    //
    #ifdef EXIST_SW2
        SW2_GPIO::initInput(GPIOPull::up);
        _sw2 = new DigInput(_digInputService, getGPIO<SW2_GPIO>());
        _sw2->enableChangedEventCallback(_sw2ChangedEventCallback);
    #endif

    // Configure la entrada corresponent al switch SW3
    //
    #ifdef EXIST_SW3
        SW3_GPIO::initInput(GPIOPull::up);
        _sw3 = new DigInput(_digInputService, getGPIO<SW3_GPIO>());
        _sw3->enableChangedEventCallback(_sw3ChangedEventCallback);
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
    htl::INT_1::setInterruptVectorPriority(
        DigInputService_TimerInterruptVector,
        DigInputService_TimerInterruptPriority,
        DigInputService_TimerInterruptSubPriority);


    // Configura el servei de sortides digitals
    //
    _digOutputService = new DigOutputService(this);

    // Configura la sortida corresponent al led LED1
    //
    LED1_GPIO::initOutput();
    LED1_GPIO::clear();
    _led1 = new DigOutput(_digOutputService, htl::getGPIO<LED1_GPIO>());

    // Configura la sortida corresponent al led LED2
    //
    #ifdef EXIST_LED2
        LED2_GPIO::initOutput();
        LED2_GPIO::clear();
        _led2 = new DigOutput(_digOutputService, htl::getGPIO<LED2_GPIO>());
    #endif

    // Configura la sortida corresponent al led LED3
    //
    #ifdef EXIST_LED3
        LED3_GPIO::initOutput();
        LED3_GPIO::clear();
        _led3 = new DigOutput(_digOutputService, htl::getGPIO<LED3_GPIO>());
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
    INT_1::setInterruptVectorPriority(
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


/// -------------------------------------------------------------------
/// \brief    Procesa els events de MessageBus
// \param     args: Parametres del event.
///
void MyApplication::messageBusEventHandler(
    const ButtonMessage &args) {

}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
void MyApplication::sw1ChangedEventHandler(
    const DigInput::ChangedEventArgs &args) {

    if (args.value == (bool) SW1_ON) {

        ButtonMessage msg;
        msg.id = 1;
        _messageBus->send(msg, 1000);

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

    if (args.value == (bool) SW2_ON) {

        ButtonMessage msg;
        msg.id = 2;
        _messageBus->send(msg, 1000);

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

    if (args.value == (bool) SW3_ON) {

        ButtonMessage msg;
        msg.id = 3;
        _messageBus->send(msg, 1000);

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
