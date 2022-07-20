#ifndef __eosBoard_PIC32_USB_STARTER_KIT_I__
#define __eosBoard_PIC32_USB_STARTER_KIT_I__


// -----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


#ifdef __cplusplus


#include "HTL/htlGPIO.h"


namespace board {

	// -----------------------------------------------------------------------
	// LED1
	// -----------------------------------------------------------------------
	//
	#ifdef USE_LED1

		#define EXIST_LED1

		namespace led1 {

			// Asignacio de pins
			using GPIO_LED = htl::GPIO_D0;

			constexpr bool onState = true;
			constexpr bool offState = false;
		};

	#endif // USE_LED1

    // -----------------------------------------------------------------------
	// LED2
	// -----------------------------------------------------------------------
	//
	#ifdef USE_LED2

		#define EXIST_LED2

		namespace led2 {

			// Asignacio de pins
			using GPIO_LED = htl::GPIO_D1;

			constexpr bool onState = true;
			constexpr bool offState = false;
		};

	#endif // USE_LED2

	// -----------------------------------------------------------------------
	// LED3
	// -----------------------------------------------------------------------
	//
	#ifdef USE_LED3

		#define EXIST_LED3

		namespace led3 {

			// Asignacio de pins
			using GPIO_LED = htl::GPIO_D2;

			constexpr bool onState = true;
			constexpr bool offState = false;
		};

	#endif // USE_LED3

	// -----------------------------------------------------------------------
	// SW1
	// -----------------------------------------------------------------------
	//
	#ifdef USE_SW1

		#define EXIST_SW1

		namespace sw1 {

			// Asignacio de pins
			using GPIO_SW = htl::GPIO_D6;

			constexpr bool onState = true;
			constexpr bool offState = false;
		}

	#endif // USE_SW1

	// -----------------------------------------------------------------------
	// SW2
	// -----------------------------------------------------------------------
	//
	#ifdef USE_SW2

		#define EXIST_SW2

		namespace sw2 {

			// Asignacio de pins
			using GPIO_SW = htl::GPIO_D7;

			constexpr bool onState = true;
			constexpr bool offState = false;
		}

	#endif // USE_SW2

    // -----------------------------------------------------------------------
	// SW3
	// -----------------------------------------------------------------------
	//
	#ifdef USE_SW3

		#define EXIST_SW3

		namespace sw3 {

			// Asignacio de pins
			using GPIO_SW = htl::GPIO_D13;

			constexpr bool onState = true;
			constexpr bool offState = false;
		}

	#endif // USE_SW3

}


#endif // __cplusplus


#endif // __eosBoard_PIC32_USB_STARTER_KIT_I__
