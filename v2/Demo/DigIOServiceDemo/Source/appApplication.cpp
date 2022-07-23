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
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    sw1EventCallback(this, &MyApplication::sw1EventHandler)
    #ifdef EXIST_SW2
        , sw2EventCallback(this, &MyApplication::sw2EventHandler)
    #endif
    #ifdef EXIST_SW3
        , sw3EventCallback(this, &MyApplication::sw3EventHandler)
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
    GPIO_SW1::initInput(htl::GPIOPull::up);
    sw1 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW1>());
    sw1->setCallback(sw1EventCallback, nullptr);

    // COnfigura la entrada corresponent al switch SW2
    //
    #ifdef EXIST_SW2
        GPIO_SW2::initInput(htl::GPIOPull::up);
        sw2 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW2>());
        sw2->setCallback(sw2EventCallback, nullptr);
    #endif

    // Configure la entrada corresponent al switch SW3
    //
    #ifdef EXIST_SW3
        GPIO_SW3::initInput(htl::GPIOPull::up);
        sw3 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW3>());
        sw3->setCallback(sw3EventCallback, nullptr);
    #endif

    // Configura el temporitzador pel servei d'entrades digitals
    //
    TMR_INP::init();
    TMR_INP::setClockSource(htl::TMRClockSource::pclk);
    TMR_INP::setResolution(htl::TMRResolution::res16);
    TMR_INP::setClockDivider(htl::TMRClockDivider::div64);
    TMR_INP::setPeriod(((halSYSGetPeripheralClockFrequency() * DigInputService_TimerPeriod) / 64000) - 1);
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
    GPIO_LED1::initOutput();
    GPIO_LED1::clear();
    led1 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED1>());

    // COnfigura la sortida corresponent al led LED2
    //
    #ifdef EXIST_LED2
        GPIO_LED2::initOutput();
        GPIO_LED2::clear();
        led2 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED2>());
    #endif

    // COnfigura la sortida corresponent al led LED3
    //
    #ifdef EXIST_LED3
        GPIO_LED3::initOutput();
        GPIO_LED3::clear();
        led3 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED3>());
    #endif

    // Configura el temporitzador pel servei de sortides digitals
    //
    TMR_OUT::init();
    TMR_OUT::setClockSource(htl::TMRClockSource::pclk);
    TMR_OUT::setResolution(htl::TMRResolution::res16);
    TMR_OUT::setClockDivider(htl::TMRClockDivider::div64);
    TMR_OUT::setPeriod(((halSYSGetPeripheralClockFrequency() * DigOutputService_TimerPeriod) / 64000) - 1);
    TMR_OUT::setInterruptFunction(tmrOutInterruptFunction, _digOutputService);

    // Configura les interrupcions
    //
    htl::INT_1::setInterruptVectorPriority(
        DigOutputService_TimerInterruptVector,
        DigOutputService_TimerInterruptPriority,
        DigOutputService_TimerInterruptSubPriority);

    // Inicia el temporitzador del servei d'entrades digitals
    //
    TMR_INP::enableInterrupt(htl::TMREvent::update);
    TMR_INP::start();

    // Inicia el temporitzador del servei de sortides digitals
    //
    TMR_OUT::enableInterrupt(htl::TMREvent::update);
    TMR_OUT::start();
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
void MyApplication::sw1EventHandler(
    const DigInput::EventArgs &args) {

    if (sw1->read()) {
        led1->pulse(500);
        led2->delayedPulse(250, 500);
        #ifdef EXIST_LED3
            led3->delayedPulse(500, 500);
        #endif
    }
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SW2
void MyApplication::sw2EventHandler(
    const DigInput::EventArgs &args) {

    if (sw2->read()) {
        #ifdef EXIST_LED3
            led3->pulse(500);
        #endif
        #ifdef EXIST_LED2
            led2->delayedPulse(250, 500);
        #endif
            led1->delayedPulse(500, 500);
    }
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 3.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SW3
void MyApplication::sw3EventHandler(
    const DigInput::EventArgs &args) {

    if (sw3->read()) {
        led1->pulse(1000);
        #ifdef EXIST_LED2
            led2->pulse(2000);
        #endif
        #ifdef EXIST_LED3
            led3->pulse(3000);
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
