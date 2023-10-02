#ifndef __eosBoard_PIC32_USB_STARTER_KIT_I__
#define __eosBoard_PIC32_USB_STARTER_KIT_I__


// -----------------------------------------------------------------------
// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)



// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------
//
#ifdef USE_LED1
#define EXIST_LED1

#define LED1_Pin             htl::gpio::PinD0
#define LED1_StateON         true
#define LED1_StateOFF        false

#endif // USE_LED1


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------
//
#ifdef USE_LED2
#define EXIST_LED2

#define LED2_Pin             htl::gpio::PinD1
#define LED2_StateON         true
#define LED2_StateOFF        false

#endif // USE_LED2


// -----------------------------------------------------------------------
// LED3
// -----------------------------------------------------------------------
//
#ifdef USE_LED3
#define EXIST_LED3

#define LED3_Pin             htl::gpio::PinD2
#define LED3_StateON         true
#define LED3_StateOFF        false

#endif // USE_LED1



// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinD6
#define SW1_StateON          false
#define SW1_StateOFF         true

#endif // USE_SW1


// -----------------------------------------------------------------------
// SW2
// -----------------------------------------------------------------------
//
#ifdef USE_SW2
#define EXIST_SW2

#define SW2_Pin              htl::gpio::PinD7
#define SW2_StateON          false
#define SW2_StateOFF         true

#endif // USE_SW2


// -----------------------------------------------------------------------
// SW3
// -----------------------------------------------------------------------
//
#ifdef USE_SW3
#define EXIST_SW3

#define SW3_Pin              htl::gpio::PinD13
#define SW3_StateON          false
#define SW3_StateOFF         true

#endif // USE_SW3


#endif // __eosBoard_PIC32_USB_STARTER_KIT_I__
