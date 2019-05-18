#ifndef __board_CUSTOM__
#define __board_CUSTOM__


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ           80000000
#define CLOCK_PERIPHERICAL_HZ     (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors LED
// -----------------------------------------------------------------------

#define LED_LED1_PORT             HAL_GPIO_PORT_G
#define LED_LED1_PIN              HAL_GPIO_PIN_6

#define LED_LED2_PORT             HAL_GPIO_PORT_D
#define LED_LED2_PIN              HAL_GPIO_PIN_1

#define LED_LED3_PORT             HAL_GPIO_PORT_D
#define LED_LED3_PIN              HAL_GPIO_PIN_1



#endif // __board_CUSTOM__