#ifndef __board_PIC32_USB_STARTER_KIT_I__
#define __board_PIC32_USB_STARTER_KIT_I__


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
#define LED_LED1_PORT        HAL_GPIO_PORT_D
#define LED_LED1_PIN         HAL_GPIO_PIN_0
#endif

#ifdef USE_LEDS_LED2
#define EXIST_LEDS_LED2
#define LED_LED2_PORT        HAL_GPIO_PORT_D
#define LED_LED2_PIN         HAL_GPIO_PIN_1
#endif

#ifdef USE_LEDS_LED3
#define EXIST_LEDS_LED3
#define LED_LED3_PORT        HAL_GPIO_PORT_D
#define LED_LED3_PIN         HAL_GPIO_PIN_2
#endif


// -----------------------------------------------------------------------
// SWITCHES
//
#ifdef USE_SWITCHES_SW1
#define EXIST_SWITCHES_SW1
#define SW_SW1_PORT          HAL_GPIO_PORT_D
#define SW_SW1_PIN           HAL_GPIO_PIN_6
#endif

#ifdef USE_SWITCHES_SW2
#define EXIST_SWITCHES_SW2
#define SW_SW2_PORT          HAL_GPIO_PORT_D
#define SW_SW2_PIN           HAL_GPIO_PIN_7
#endif

#ifdef USE_SWITCHES_SW3
#define EXIST_SWITCHES_SW3
#define SW_SW3_PORT          HAL_GPIO_PORT_D
#define SW_SW3_PIN           HAL_GPIO_PIN_13
#endif


#endif // __board_PIC32_USB_STARTER_KIT_I__
