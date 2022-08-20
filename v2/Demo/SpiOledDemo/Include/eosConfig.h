#ifndef __eosConfig__
#define __eosConfig__


#if defined(BUILD_SSD1306)
	#define HARDWARE_CUSTOM
	#if defined(EOS_PLATFORM_STM32F7)
		#define HARDWARE_CUSTOM_STM32F746G_DISCO
		#define DISPLAY_ADAFRUIT_SSD1306_128x64_D098
	#elif defined(EOS_PLATFORM_PIC32)
		#define HARDWARE_CUSTOM_PIC32_USB_STARTER_KIT_I
		#define DISPLAY_ADAFRUIT_SSD1306_128x64_D098
	#else
		#error "Hardware no soportado para SSD1306"
	#endif
	#define DISPLAY_DRV_SSD1306

#else
	#error "No se especifico el producto"
#endif


// Opcions generals del sistema
//
#define EOS_COLOR_FORMAT ColorFormat::l8
#define FONT_USE_Tahoma12pt
#define EOS_USE_STD_STRING
#define USE_ARDUINO
#define USE_LED1
#define USE_LED2
#define USE_SW1
#define USE_CUSTOM_DISPLAY


#endif // __eosConfig__
