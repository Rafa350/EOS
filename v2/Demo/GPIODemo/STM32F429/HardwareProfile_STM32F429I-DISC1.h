#ifndef __HARDWARE_PROFILE_STM32F429I_DISC1_H
#define __HARDWARE_PROFILE_STM32F429I_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


#define LEDS_LD1_PORT        HAL_GPIO_PORT_G
#define LEDS_LD1_PIN         HAL_GPIO_PIN_13

#define LEDS_LD2_PORT        HAL_GPIO_PORT_G
#define LEDS_LD2_PIN         HAL_GPIO_PIN_14


#endif
