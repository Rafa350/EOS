#pragma once


#define EOS_HARDWARE_NUCLEO_G071RB


// -----------------------------------------------------------------------
// External oscilator parameters
// -----------------------------------------------------------------------

#define CLOCK_HSE_FREQUENCY       8000000 // Hz
#define CLOCK_HSE_STARTUP         100     // ms
#define CLOCK_HSE_BYPASS          1       // Bypass enabled
#define CLOCK_LSE_FREQUENCY       32768   // Hz
#define CLOCK_LSE_STARTUP         5000    // ms


// -----------------------------------------------------------------------
// LED1 (Green led)
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

#define LED1_Pin             htl::gpio::PinA5
#define LED1_StateON         true
#define LED1_StateOFF        false

#define LED1_Initialize()    LED1_Pin::pInst->initOutput(htl::gpio::OutDriver::pushPull)
#define LED1_On()            LED1_Pin::pInst->set()
#define LED1_Off()           LED1_Pin::pInst->clear()
#define LED1_Toggle()        LED1_Pin::pInst->toggle()

#endif // USE_LED1


// -----------------------------------------------------------------------
// SW1 (Blue button)
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinC13;
#define SW1_PinInterrupt     htl::gpio::PinInterruptX<SW1_Pin::portID, SW1_Pin::pinID>
#define SW1_StateON          true
#define SW1_StateOF          false

#endif // USE_SW1


// -----------------------------------------------------------------------
// CN7 expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_CN7
#define EXISTS_CN7

#define CN7_1_Pin            htl::gpio::PinC10
#define CN7_2_Pin            htl::gpio::PinC11
#define CN7_3_Pin            htl::gpio::PinC12
#define CN7_4_Pin            htl::gpio::PinD2
#define CN7_7_Pin            htl::gpio::PinA14
#define CN7_9_Pin            htl::gpio::PinD0
#define CN7_11_Pin           htl::gpio::PinD3
#define CN7_13_Pin			 htl::gpio::PinA13
#define CN7_15_Pin  		 htl::gpio::PinD4
#define CN7_17_Pin  		 htl::gpio::PinA15
#define CN7_21_Pin  		 htl::gpio::PinB7
#define CN7_23_Pin  		 htl::gpio::PinC13
#define CN7_25_Pin  		 htl::gpio::PinC14
#define CN7_26_Pin  		 htl::gpio::PinD5
#define CN7_27_Pin  		 htl::gpio::PinC15
#define CN7_29_Pin  		 htl::gpio::PinF0
#define CN7_31_Pin  		 htl::gpio::PinF1
#define CN7_35_Pin  		 htl::gpio::PinC2
#define CN7_37_Pin  		 htl::gpio::PinC3

#ifndef USE_ARDUINO
#define CN7_10_Pin           htl::gpio::PinD1
#define CN7_28_Pin  		 htl::gpio::PinA0
#define CN7_30_Pin  		 htl::gpio::PinA1
#define CN7_32_Pin  		 htl::gpio::PinA4
#define CN7_34_Pin  		 htl::gpio::PinB1
#define CN7_36_Pin  		 htl::gpio::PinB11
#define CN7_38_Pin  		 htl::gpio::PinB12
#endif

#endif // USE_CN7


// -----------------------------------------------------------------------
// CN10 expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_CN10
#define EXISTS_CN10

#define CN10_1_Pin  		 htl::gpio::PinC9
#define CN10_2_Pin  		 htl::gpio::PinC8
#define CN10_4_Pin  		 htl::gpio::PinC6
#define CN10_6_Pin  		 htl::gpio::PinA3
#define CN10_10_Pin  		 htl::gpio::PinD6
#define CN10_12_Pin  		 htl::gpio::PinA12
#define CN10_14_Pin  		 htl::gpio::PinA11
#define CN10_16_Pin  		 htl::gpio::PinC1
#define CN10_18_Pin  		 htl::gpio::PinC0
#define CN10_22_Pin  		 htl::gpio::PinB2
#define CN10_24_Pin  		 htl::gpio::PinB6
#define CN10_26_Pin  		 htl::gpio::PinB15
#define CN10_28_Pin  		 htl::gpio::PinB10
#define CN10_30_Pin  		 htl::gpio::PinB13
#define CN10_34_Pin  		 htl::gpio::PinA2
#define CN10_36_Pin  		 htl::gpio::PinD8
#define CN10_38_Pin  		 htl::gpio::PinD9

#ifndef USE_ARDUINO
#define CN10_3_Pin  		 htl::gpio::PinB8
#define CN10_5_Pin  		 htl::gpio::PinB9
#define CN10_11_Pin  		 htl::gpio::PinA5
#define CN10_13_Pin  		 htl::gpio::PinA6
#define CN10_15_Pin  		 htl::gpio::PinA7
#define CN10_17_Pin  		 htl::gpio::PinB0
#define CN10_19_Pin  		 htl::gpio::PinC7
#define CN10_21_Pin  		 htl::gpio::PinA9
#define CN10_23_Pin  		 htl::gpio::PinA8
#define CN10_25_Pin  		 htl::gpio::PinB14
#define CN10_27_Pin  		 htl::gpio::PinB4
#define CN10_29_Pin  		 htl::gpio::PinB5
#define CN10_31_Pin  		 htl::gpio::PinB3
#define CN10_33_Pin  		 htl::gpio::PinA10
#define CN10_35_Pin  		 htl::gpio::PinC4
#define CN10_37_Pin  		 htl::gpio::PinC5
#endif

#endif // USE_CN10


// -----------------------------------------------------------------------
// Arduino expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_A0_Pin       htl::gpio::PinA0
#define ARDUINO_A1_Pin       htl::gpio::PinA1
#define ARDUINO_A2_Pin       htl::gpio::PinA4
#define ARDUINO_A3_Pin       htl::gpio::PinB1
#define ARDUINO_A4_Pin       htl::gpio::PinB11
#define ARDUINO_A5_Pin       htl::gpio::PinB12

#define ARDUINO_D0_Pin       htl::gpio::PinC5
#define ARDUINO_D1_Pin       htl::gpio::PinC4
#define ARDUINO_D2_Pin       htl::gpio::PinA10
#define ARDUINO_D3_Pin       htl::gpio::PinB3
#define ARDUINO_D4_Pin       htl::gpio::PinB5
#define ARDUINO_D5_Pin       htl::gpio::PinB4
#define ARDUINO_D6_Pin       htl::gpio::PinB14
#define ARDUINO_D7_Pin       htl::gpio::PinA8

#define ARDUINO_D8_Pin       htl::gpio::PinA9
#define ARDUINO_D9_Pin       htl::gpio::PinC7
#define ARDUINO_D10_Pin      htl::gpio::PinB0
#define ARDUINO_D11_Pin      htl::gpio::PinA7
#define ARDUINO_D12_Pin      htl::gpio::PinA6
#define ARDUINO_D13_Pin      htl::gpio::PinA5
#define ARDUINO_D14_Pin      htl::gpio::PinB9
#define ARDUINO_D15_Pin      htl::gpio::PinB8

#define ARDUINO_RX_Pin       htl::gpio::PinC5 // ARDUINO_D0
#define ARDUINO_TX_Pin       htl::gpio::PinC4 // ARDUINO_D1

#define ARDUINO_SCL_Pin      htl::gpio::PinB8 // ARDUINO_D15
#define ARDUINO_SDA_Pin      htl::gpio::PinB9 // ARDUINO_D14

#define ARDUINO_SCK_Pin      htl::gpio::PinA5 // ARDUINO_D13
#define ARDUINO_MISO_Pin     htl::gpio::PinA6 // ARDUINO_D12
#define ARDUINO_MOSI_Pin     htl::gpio::PinA7 // ARDUINO_D11

#endif // USE_ARDUINO
