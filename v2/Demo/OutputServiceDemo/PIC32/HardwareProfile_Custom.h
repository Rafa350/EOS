#ifndef __HARDWARE_PROFILE_CUSTOM_H
#define __HARDWARE_PROFILE_CUSTOM_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)

// -----------------------------------------------------------------------
// LEDS
// -----------------------------------------------------------------------

#define LEDS_LD1_PORT        HAL_GPIO_PORT_G
#define LEDS_LD1_PIN         HAL_GPIO_PIN_6

#define LEDS_LD2_PORT        HAL_GPIO_PORT_D
#define LEDS_LD2_PIN         HAL_GPIO_PIN_1

#define LEDS_LD3_PORT        HAL_GPIO_PORT_D
#define LEDS_LD3_PIN         HAL_GPIO_PIN_1



#endif