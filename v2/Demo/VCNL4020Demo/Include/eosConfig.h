#ifndef __eosConfig__
#define __eosConfig__


#if defined(BUILD_VCNL4020)
	#define HARDWARE_CUSTOM
	#if defined(EOS_STM32F4)
		#define HARDWARE_CUSTOM_STM32F429I_DISC1
	#elif defined(EOS_STM32F7)
		#define HARDWARE_CUSTOM_STM32F746G_DISCO
	#elif defined(EOS_PIC32)
		#define HARDWARE_CUSTOM_PIC32_USB_STARTER_KIT_I
	#else
		#error "Hardware no soportado para VCNL4020"
	#endif

#else
	#error "No se especifico el producto"
#endif


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_SWITCHES_SW1
#define USE_ARDUINO


#endif // __eosConfig__
