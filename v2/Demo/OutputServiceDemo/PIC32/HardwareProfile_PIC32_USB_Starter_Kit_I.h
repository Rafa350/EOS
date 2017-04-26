#ifndef __HARDWARE_PROFILE_PIC32_USB_STARTER_KIT_I_H
#define __HARDWARE_PROFILE_PIC32_USB_STARTER_KIT_I_H


// -----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LEDS
//
#define LEDS_LD1_PORT        HAL_GPIO_PORT_D
#define LEDS_LD1_PIN         HAL_GPIO_PIN_0

#define LEDS_LD2_PORT        HAL_GPIO_PORT_D
#define LEDS_LD2_PIN         HAL_GPIO_PIN_1

#define LEDS_LD3_PORT        HAL_GPIO_PORT_D
#define LEDS_LD3_PIN         HAL_GPIO_PIN_2


// -----------------------------------------------------------------------
// SWITCH
//
#define SW_SW1_PORT          HAL_GPIO_PORT_D
#define SW_SW1_PIN           HAL_GPIO_PIN_6

#define SW_SW2_PORT          HAL_GPIO_PORT_D
#define SW_SW2_PIN           HAL_GPIO_PIN_7

#define SW_SW3_PORT          HAL_GPIO_PORT_D
#define SW_SW3_PIN           HAL_GPIO_PIN_13


#endif