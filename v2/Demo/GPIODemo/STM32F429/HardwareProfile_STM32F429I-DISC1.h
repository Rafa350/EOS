#ifndef __HARDWARE_PROFILE_STM32F429I_DISC1_H
#define __HARDWARE_PROFILE_STM32F429I_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


#define LED1_PORT         GPIO_PORT_G
#define LED1_PIN          GPIO_PIN_13

#define LED2_PORT         GPIO_PORT_G
#define LED2_PIN          GPIO_PIN_14


#endif
