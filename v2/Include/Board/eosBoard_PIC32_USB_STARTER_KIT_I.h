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

#define LED1_GPIO            htl::GPIO_D0
#define LED1_ON              htl::GPIOState::set
#define LED1_OFF             htl::GPIOState::clear

#endif // USE_LED1


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------
//
#ifdef USE_LED2
#define EXIST_LED2

#define LED2_GPIO            htl::GPIO_D1
#define LED2_ON              htl::GPIOState::set
#define LED2_OFF             htl::GPIOState::clear

#endif // USE_LED2


// -----------------------------------------------------------------------
// LED3
// -----------------------------------------------------------------------
//
#ifdef USE_LED3
#define EXIST_LED3

#define LED3_GPIO            htl::GPIO_D2
#define LED3_ON              htl::GPIOState::set
#define LED3_OFF             htl::GPIOState::clear

#endif // USE_LED1



// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_GPIO             htl::GPIO_D6
#define SW1_ON               htl::GPIOState::clear
#define SW1_OFF              htl::GPIOState::set

#endif // USE_SW1


// -----------------------------------------------------------------------
// SW2
// -----------------------------------------------------------------------
//
#ifdef USE_SW2
#define EXIST_SW2

#define SW2_GPIO             htl::GPIO_D7
#define SW2_ON               htl::GPIOState::clear
#define SW2_OFF              htl::GPIOState::set

#endif // USE_SW2


// -----------------------------------------------------------------------
// SW3
// -----------------------------------------------------------------------
//
#ifdef USE_SW3
#define EXIST_SW3

#define SW3_GPIO             htl::GPIO_D13
#define SW3_ON               htl::GPIOState::clear
#define SW3_OFF              htl::GPIOState::set

#endif // USE_SW3


#endif // __eosBoard_PIC32_USB_STARTER_KIT_I__
