#ifndef __board_PINGUINO__
#define __board_PINGUINO__


// ----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LEDS
//
#ifdef USE_LEDS_LED1
#define EXISTS_LEDS_LED1
#define LEDS_LED1_PORT       HAL_GPIO_PORT_G
#define LEDS_LED1_PIN        HAL_GPIO_PIN_6
#endif

#ifdef USE_LEDS_LED2
#define EXISTS_LEDS_LED2
#define LEDS_LED1_PORT       HAL_GPIO_PORT_D
#define LEDS_LED1_PIN        HAL_GPIO_PIN_1
#endif

#define LEDS_STATE_ON        1
#define LEDS_STATE_OFF       0


//------------------------------------------------------------------------
// SWITCHES
//

#define SWITCHES_STATE_ON    0
#define SWITCHES_STATE_OFF   1


#endif // __eosBoard_PINGUINO__