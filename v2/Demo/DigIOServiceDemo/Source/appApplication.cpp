#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
#ifdef EOS_PIC32
#include "HAL/PIC32/halCN.h"
#endif
#include "HAL/halTMR.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"


using namespace eos;
using namespace app;


TMRData digInputTimer;
TMRData digOutputTimer;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    sw1EventCallback(this, &MyApplication::sw1EventHandler)
#ifdef EXIST_SWITCHES_SW2
    , sw2EventCallback(this, &MyApplication::sw2EventHandler)
#endif
#ifdef EXIST_SWITCHES_SW3
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
	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = DigInputService_Timer;
#if defined(EOS_PIC32)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrInfo.period = ((halSYSGetPeripheralClockFrequency() * DigInputService_TimerPeriod) / 64000) - 1; 
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrInfo.prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000L) - 1; // 1MHz
    tmrInfo.period = (1000 * DigInputService_TimerPeriod) - 1;
#else
    //#error CPU no soportada
#endif   
    halTMRInitialize(&digInputTimer, &tmrInfo);

    // Inicialitza el servei d'entrades digitals
	//
    DigInputService::InitParams digInputServiceInit;
    digInputServiceInit.hTimer = &digInputTimer;
    digInputService = new DigInputService(this, digInputServiceInit);
    digInputService->setPriority(Task::Priority::high);

    // Inicialitza les interrupcions
    //
    halINTSetInterruptVectorPriority(DigInputService_TimerInterruptVector, DigInputService_TimerInterruptPriority, DigInputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigInputService_TimerInterruptVector);
    
    DigInput::InitParams digInputInit;
    digInputInit.eventParam = nullptr;
    
    // Inicialitza la entrada corresponent al switch SW1
    //
#ifdef EXIST_SWITCHES_SW1
    halGPIOInitializePin(SWITCHES_SW1_PORT, SWITCHES_SW1_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
#ifdef EOS_PIC32
    halCNInitializeLine(SWITCHES_SW1_CN, HAL_CN_PULL_UP);
#endif

    digInputInit.port = SWITCHES_SW1_PORT;
    digInputInit.pin = SWITCHES_SW1_PIN;
    digInputInit.eventCallback = &sw1EventCallback;
    sw1 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW2
    //
#ifdef EXIST_SWITCHES_SW2
    halGPIOInitializePin(SWITCHES_SW2_PORT, SWITCHES_SW2_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
    halCNInitializeLine(SWITCHES_SW2_CN, HAL_CN_PULL_UP);

    digInputInit.port = SWITCHES_SW2_PORT;
    digInputInit.pin = SWITCHES_SW2_PIN;
    digInputInit.eventCallback = &sw2EventCallback;
    sw2 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW3
    //
#ifdef EXIST_SWITCHES_SW3
    halGPIOInitializePin(SWITCHES_SW3_PORT, SWITCHES_SW3_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
    halCNInitializeLine(SWITCHES_SW3_CN, HAL_CN_PULL_UP);

    digInputInit.port = SWITCHES_SW3_PORT;
    digInputInit.pin = SWITCHES_SW3_PIN;
    digInputInit.eventCallback = &sw3EventCallback;
    sw3 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza el temporitzador pel servei de sortides digitals
    //
	tmrInfo.timer = DigOutputService_Timer;
#if defined(EOS_PIC32)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrInfo.period = ((halSYSGetPeripheralClockFrequency() * DigOutputService_TimerPeriod) / 64000) - 1; 
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrInfo.prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000L) - 1; // 1MHz
    tmrInfo.period = (1000 * DigOutputService_TimerPeriod) - 1;
#else
    //#error CPU no soportada
#endif   
	halTMRInitialize(&digOutputTimer, &tmrInfo);

    // Inicialitza el servei de sortides digitals
    //
    DigOutputService::InitParams digOutputServiceInit;
    digOutputServiceInit.hTimer = &digOutputTimer;
    digOutputService = new DigOutputService(this, digOutputServiceInit);

    // Inicialitza les interrupcions
    //
    halINTSetInterruptVectorPriority(DigOutputService_TimerInterruptVector, DigOutputService_TimerInterruptPriority, DigOutputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigOutputService_TimerInterruptVector);
    
    DigOutput::InitParams digOutputInit;

    // Inicialitza la sortida corresponent al led LED1
    //
#ifdef EXIST_LEDS_LED1
    halGPIOInitializePin(LEDS_LED1_PORT, LEDS_LED1_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);

    digOutputInit.port = LEDS_LED1_PORT;
    digOutputInit.pin = LEDS_LED1_PIN;
    led1 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED2
    //
#ifdef EXIST_LEDS_LED2
    halGPIOInitializePin(LEDS_LED2_PORT, LEDS_LED2_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);

    digOutputInit.port = LEDS_LED2_PORT;
    digOutputInit.pin = LEDS_LED2_PIN;
    led2 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED3
    //
#ifdef EXIST_LEDS_LED3
    halGPIOInitializePin(LEDS_LED3_PORT, LEDS_LED3_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);
    
    digOutputInit.port = LEDS_LED3_PORT;
    digOutputInit.pin = LEDS_LED3_PIN;
    led3 = new DigOutput(digOutputService, digOutputInit);
#endif

}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::sw1EventHandler(
    const DigInput::EventArgs &args) {

    if (sw1->read() == SWITCHES_STATE_ON) {
        led1->pulse(500);
        led2->delayedPulse(250, 500);
#ifdef EXIST_LEDS_LED3
        led3->delayedPulse(500, 500);
#endif
    }
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::sw2EventHandler(
    const DigInput::EventArgs &args) {

    if (sw2->read() == SWITCHES_STATE_ON) {
#ifdef EXIST_LEDS_LED3
        led3->pulse(500);
#endif
#ifdef EXIST_LEDS_LED2
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
#ifdef EXIST_SWITCHES_SW3
void MyApplication::sw3EventHandler(
    const DigInput::EventArgs &args) {

    if (sw3->read() == SWITCHES_STATE_ON) {
        led1->pulse(1000);
#ifdef EXIST_LEDS_LED2
        led2->pulse(2000);
#endif
#ifdef EXIST_LEDS_LED3
        led3->pulse(3000);
#endif
    }
}
#endif


