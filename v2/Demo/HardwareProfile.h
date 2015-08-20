#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


// Configurarcio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// Configuracio dels leds indicadors
//
#define LED_1_CHN       PORTS_CHANNEL_D
#define LED_1_POS       PORT_BIT_POS_0

#define LED_2_CHN       PORTS_CHANNEL_D
#define LED_2_POS       PORT_BIT_POS_1

#define LED_3_CHN       PORTS_CHANNEL_D
#define LED_3_POS       PORT_BIT_POS_2

#define SW_1_CHN        PORTS_CHANNEL_D
#define SW_1_POS        PORT_BIT_POS_6

#define SW_2_CHN        PORTS_CHANNEL_D
#define SW_2_POS        PORT_BIT_POS_7

#define SW_3_CHN        PORTS_CHANNEL_D
#define SW_3_POS        PORT_BIT_POS_13


#endif