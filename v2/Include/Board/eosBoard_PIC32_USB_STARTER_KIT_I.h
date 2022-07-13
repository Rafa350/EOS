#ifndef __eosBoard_PIC32_USB_STARTER_KIT_I__
#define __eosBoard_PIC32_USB_STARTER_KIT_I__


// -----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LEDS
//
#ifdef USE_LEDS_LED1
#define EXIST_LEDS_LED1
#define LEDS_LED1_PORT       HAL_GPIO_PORT_D
#define LEDS_LED1_PIN        HAL_GPIO_PIN_0
#define LEDS_LED1_TYPE       htl::GPIO_D0
#endif

#ifdef USE_LEDS_LED2
#define EXIST_LEDS_LED2
#define LEDS_LED2_PORT       HAL_GPIO_PORT_D
#define LEDS_LED2_PIN        HAL_GPIO_PIN_1
#define LEDS_LED2_TYPE       htl::GPIO_D1
#endif

#ifdef USE_LEDS_LED3
#define EXIST_LEDS_LED3
#define LEDS_LED3_PORT       HAL_GPIO_PORT_D
#define LEDS_LED3_PIN        HAL_GPIO_PIN_2
#define LEDS_LED3_TYPE       htl::GPIO_D2
#endif

#define LEDS_STATE_ON        1
#define LEDS_STATE_OFF       0


// -----------------------------------------------------------------------
// SWITCHES
//
#ifdef USE_SWITCHES_SW1
#define EXIST_SWITCHES_SW1
#define SWITCHES_SW1_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW1_PIN     HAL_GPIO_PIN_6
#define SWITCHES_SW1_CN      HAL_CN_LINE_15
#define SWITCHES_SW1_TYPE    htl::GPIO_D6
#endif

#ifdef USE_SWITCHES_SW2
#define EXIST_SWITCHES_SW2
#define SWITCHES_SW2_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW2_PIN     HAL_GPIO_PIN_7
#define SWITCHES_SW2_CN      HAL_CN_LINE_16
#define SWITCHES_SW2_TYPE    htl::GPIO_D7
#endif

#ifdef USE_SWITCHES_SW3
#define EXIST_SWITCHES_SW3
#define SWITCHES_SW3_PORT    HAL_GPIO_PORT_D
#define SWITCHES_SW3_PIN     HAL_GPIO_PIN_13
#define SWITCHES_SW3_CN      HAL_CN_LINE_19
#define SWITCHES_SW3_TYPE    htl::GPIO_D13
#endif

#define SWITCHES_STATE_ON    0
#define SWITCHES_STATE_OFF   1


#endif // __eosBoard_PIC32_USB_STARTER_KIT_I__
