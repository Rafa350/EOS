#ifndef __eosBoard_PIC32_ETH_STARTER_KIT__
#define __eosBoard_PIC32_ETH_STARTER_KIT__


#define EOS_HARDWARE_PIC32_ETH_STARTER_KIT


// -----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------
//
#ifdef USE_LED1
#define EXIST_LED1

#define LED1_Pin             htl::gpio::PinD0

#define LED1_StateON         true
#define LED1_StateOFF        false

#endif


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------
//
#ifdef USE_LED2
#define EXIST_LED2

#define LED2_Pin             htl::gpio::PinD1

#define LED1_StateON         true
#define LED1_StateOFF        false

#endif


// -----------------------------------------------------------------------
// LED3
// -----------------------------------------------------------------------
//
#ifdef USE_LED3
#define EXIST_LED3

#define LED3_Pin             htl::gpio::PinD3

#define LED1_StateON         true
#define LED1_StateOFF        false

#endif


// -----------------------------------------------------------------------
// SWITCHES
//
#ifdef USE_SWITCHES_SW1
#define EXIST_SWITCHES_SW1
#define SWITCHES_SW1_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW1_PIN     HAL_GPIO_PIN_6
#define SWITCHES_SW1_CN      HAL_CN_LINE_15
#endif

#ifdef USE_SWITCHES_SW2
#define EXIST_SWITCHES_SW2
#define SWITCHES_SW2_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW2_PIN     HAL_GPIO_PIN_7
#define SWITCHES_SW2_CN      HAL_CN_LINE_16
#endif

#ifdef USE_SWITCHES_SW3
#define EXIST_SWITCHES_SW3
#define SWITCHES_SW3_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW3_PIN     HAL_GPIO_PIN_13
#define SWITCHES_SW3_CN      HAL_CN_LINE_19
#endif

#define SWITCHES_STATE_ON    0
#define SWITCHES_STATE_OFF   1


#endif // __eosBoard_PIC32_ETH_STARTER_KIT__
