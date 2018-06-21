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
#define LED_LED1_PORT        HAL_GPIO_PORT_D
#define LED_LED1_PIN         HAL_GPIO_PIN_0

#define LED_LED2_PORT        HAL_GPIO_PORT_D
#define LED_LED2_PIN         HAL_GPIO_PIN_1

#define LED_LED3_PORT        HAL_GPIO_PORT_D
#define LED_LED3_PIN         HAL_GPIO_PIN_2


// -----------------------------------------------------------------------
// SWITCHES
//
#define SW_SW1_PORT          HAL_GPIO_PORT_D
#define SW_SW1_PIN           HAL_GPIO_PIN_6

#define SW_SW2_PORT          HAL_GPIO_PORT_D
#define SW_SW2_PIN           HAL_GPIO_PIN_7

#define SW_SW3_PORT          HAL_GPIO_PORT_D
#define SW_SW3_PIN           HAL_GPIO_PIN_13


#endif // __board_PIC32_USB_STARTER_KIT_I__
