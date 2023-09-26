#pragma once
#ifndef __eosBoard_NUCLEO_G031K8__
#define __eosBoard_NUCLEO_G031K8__


// -----------------------------------------------------------------------
// External oscilator parameters
// -----------------------------------------------------------------------

#define CLOCK_HSE_FREQUENCY        8000000 // Hz
#define CLOCK_HSE_STARTUP          100     // ms
#define CLOCK_HSE_BYPASS           1       // Bypass enabled
#define CLOCK_LSE_FREQUENCY        32768   // Hz
#define CLOCK_LSE_STARTUP          5000    // ms


// -----------------------------------------------------------------------
// LED1 (Green led)
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

#define LED1_Pin             htl::gpio::PinC6
#define LED1_StateON         true
#define LED1_StateOFF        false

#define LED1_Initialize()    LED1_Pin::getHandler()->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium)
#define LED1_On()            LED1_Pin::getHandler()->set()
#define LED1_Off()           LED1_Pin::getHandler()->clear()
#define LED1_Toggle()        LED1_Pin::getHandler()->toggle()

#endif // USE_LED1


// -----------------------------------------------------------------------
// SW1 (Blue button)
// -----------------------------------------------------------------------

#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinF2
#define SW1_StateON          true
#define SW1_StateOFF         false

#define SW1_Initialize()     SW1_Pin::getandler()->initInput()
#define SW1_Read()           SW1_Pin::getHandler()->read()

#endif // USE_SW1


// -----------------------------------------------------------------------
// CN3 expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_CN3
#define EXIST_CN3

#define CN3_1_Pin            htl::gpio::PinB6
#define CN3_2_Pin            htl::gpio::PinB7
#define CN3_3_Pin            htl::gpio::PinF2
#define CN3_5_Pin            htl::gpio::PinA15
#define CN3_6_Pin            htl::gpio::PinB1
#define CN3_7_Pin            htl::gpio::PinA10
#define CN3_8_Pin            htl::gpio::PinA9
#define CN3_9_Pin            htl::gpio::PinB0
#define CN3_10_Pin           htl::gpio::PinB2
#define CN3_11_Pin           htl::gpio::PinB8
#define CN3_12_Pin           htl::gpio::PinA8
#define CN3_13_Pin           htl::gpio::PinB9
#define CN3_14_Pin           htl::gpio::PinB5
#define CN3_15_Pin           htl::gpio::PinB4

#endif // USE_CN3


// -----------------------------------------------------------------------
// CN4 expansion connector
// -----------------------------------------------------------------------

#ifdef USE_CN4
#define EXIST_CN4

#define CN4_3_Pin            htl::gpio::PinF2
#define CN4_5_Pin            htl::gpio::PinA7
#define CN4_6_Pin            htl::gpio::PinA6
#define CN4_7_Pin            htl::gpio::PinA11
#define CN4_8_Pin            htl::gpio::PinA12
#define CN4_9_Pin            htl::gpio::PinA5
#define CN4_10_Pin           htl::gpio::PinA5
#define CN4_11_Pin           htl::gpio::PinA1
#define CN4_12_Pin           htl::gpio::PinA0
#define CN4_15_Pin           htl::gpio::PinB3

#endif // USE_CN4


// -----------------------------------------------------------------------
// Arduino expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_D0_Pin       htl::gpio::PinB6
#define ARDUINO_D1_Pin       htl::gpio::PinB7
#define ARDUINO_D2_Pin       htl::gpio::PinA15
#define ARDUINO_D3_Pin       htl::gpio::PinB1
#define ARDUINO_D4_Pin       htl::gpio::PinA10
#define ARDUINO_D5_Pin       htl::gpio::PinA9
#define ARDUINO_D6_Pin       htl::gpio::PinB0
#define ARDUINO_D7_Pin       htl::gpio::PinB2
#define ARDUINO_D8_Pin       htl::gpio::PinB8
#define ARDUINO_D9_Pin       htl::gpio::PinA8
#define ARDUINO_D10_Pin      htl::gpio::PinB9
#define ARDUINO_D11_Pin      htl::gpio::PinB5
#define ARDUINO_D12_Pin      htl::gpio::PinB4
#define ARDUINO_D13_Pin      htl::gpio::PinB3

#define ARDUINO_UART         htl::uart::UARTDevice1
#define ARDUINO_RX_Pin       htl::gpio::PinB6  // D0
#define ARDUINO_TX_Pin       htl::gpio::PinB7  // D1

#define ARDUINO_I2CMaster    htl::i2c::I2CMasterDevice1
#define ARDUINO_I2CSlave     htl::i2c::I2CSlaveDevice1
#define ARDUINO_SCL_Pin      htl::gpio::PinA9  // D5
#define ARDUINO_SDA_Pin      htl::gpio::PinA10 // D4

#define ARDUINO_SPI          htl::spi::SPIDevice1
#define ARDUINO_SCK_Pin      htl::gpio::PinB3  // D13
#define ARDUINO_MISO_Pin     htl::gpio::PinB4  // D12
#define ARDUINO_MOSI_Pin     htl::gpio::PinB5  // D11

#endif // USE_ARDUINO


#endif // __eosBoard_NUCLERO_G031K8__

