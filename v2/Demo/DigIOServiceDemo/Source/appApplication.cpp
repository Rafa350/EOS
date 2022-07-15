#include "eos.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
#include "HAL/halTMR.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"


using namespace eos;
using namespace app;


halTMRData digInputTimer;
halTMRData digOutputTimer;


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

    // Inicialitza el temporitzador pel servei d'entrades digitals
    //
    /*hal::TMR tmr(DigInputService_Timer);
#if defined(EOS_PIC32)
    tmr.setClockSource(hal::TMR::ClockSource::pclk);
    tmr.setClockDivider(hal::TMR::ClockDivider::div64);
    tmr.setResolution(hal::TMR::Resolution::res32);
    tmr.setPeriod((halSYSGetPeripheralClockFrequency() * DigInputService_TimerPeriod) / 64000) - 1,
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
#endif
*/
	halTMRSettings tmrSettings;
	tmrSettings.timer = DigInputService_Timer;
#if defined(EOS_PIC32)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrSettings.period = ((halSYSGetPeripheralClockFrequency() * DigInputService_TimerPeriod) / 64000) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrSettings.prescaler = (halSYSGetTimerClock1Frequency() / 1000000L) - 1; // 1MHz
    tmrSettings.period = (1000 * DigInputService_TimerPeriod) - 1;
#else
    //#error CPU no soportada
#endif
    halTMRHandler hDigInputServiceTimer = halTMRInitialize(&digInputTimer, &tmrSettings);

    // Inicialitza les interrupcions
    //
    halINTSetInterruptVectorPriority(DigInputService_TimerInterruptVector, DigInputService_TimerInterruptPriority, DigInputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigInputService_TimerInterruptVector);

    // Inicialitza el servei d'entrades digitals
	//
    DigInputService::Settings digInputServiceSettings;
    digInputServiceSettings.hTimer = hDigInputServiceTimer;
    _digInputService = new DigInputService(this, digInputServiceSettings);
    _digInputService->setPriority(Task::Priority::high);

    // Inicialitza la entrada corresponent al switch SW1
    //
#ifdef EXIST_SW1
    GPIO_SW1::initInput(htl::GPIOPull::up);
    sw1 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW1>());
    sw1->setCallback(sw1EventCallback, nullptr);
#endif

    // Inicialitza la entrada corresponent al switch SW2
    //
#ifdef EXIST_SW2
    GPIO_SW2::initInput(htl::GPIOPull::up);
    sw2 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW2>());
    sw2->setCallback(sw2EventCallback, nullptr);
#endif

    // Inicialitza la entrada corresponent al switch SW3
    //
#ifdef EXIST_SW3
    GPIO_SW3::initInput(htl::GPIOPull::up);
    sw3 = new DigInput(_digInputService, htl::getAdapter<GPIO_SW3>());
    sw3->setCallback(sw3EventCallback, nullptr);
#endif

    // Inicialitza el temporitzador pel servei de sortides digitals
    //
	tmrSettings.timer = DigOutputService_Timer;
#if defined(EOS_PIC32)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrSettings.period = ((halSYSGetPeripheralClockFrequency() * DigOutputService_TimerPeriod) / 64000) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrSettings.prescaler = (halSYSGetTimerClock1Frequency() / 1000000L) - 1; // 1MHz
    tmrSettings.period = (1000 * DigOutputService_TimerPeriod) - 1;
#else
    //#error CPU no soportada
#endif
	halTMRHandler hDigOutputServiceTimer = halTMRInitialize(&digOutputTimer, &tmrSettings);

    // Inicialitza les interrupcions
    //
    halINTSetInterruptVectorPriority(DigOutputService_TimerInterruptVector, DigOutputService_TimerInterruptPriority, DigOutputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigOutputService_TimerInterruptVector);

    // Inicialitza el servei de sortides digitals
    //
    DigOutputService::Settings digOutputServiceSettings;
    digOutputServiceSettings.hTimer = hDigOutputServiceTimer;
    _digOutputService = new DigOutputService(this, digOutputServiceSettings);

    // Inicialitza la sortida corresponent al led LED1
    //
#ifdef EXIST_LED1
    GPIO_LED1::initOutput();
    GPIO_LED1::clear();
    led1 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED1>());
#endif

    // Inicialitza la sortida corresponent al led LED2
    //
#ifdef EXIST_LED2
    GPIO_LED2::initOutput();
    GPIO_LED2::clear();
    led2 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED2>());
#endif

    // Inicialitza la sortida corresponent al led LED3
    //
#ifdef EXIST_LED3
    GPIO_LED3::initOutput();
    GPIO_LED3::clear();
    led3 = new DigOutput(_digOutputService, htl::getAdapter<GPIO_LED3>());
#endif

    _timerService = new TimerService(this);
    TimerCounter *timer = new TimerCounter(_timerService, nullptr);
    timer->start(10000);
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SW1
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
#endif


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


