#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


// Configurarcio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// Configuracio dels leds indicadors
//
#define LED1_CHN        PORT_D
#define LED1_POS        1

#define LED2_CHN        3
#define LED2_POS        2

#define LED3_CHN        3
#define LED3_POS        0

#endif