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

#define LED1_GPIO            htl::GPIO_C6
#define LED1_ON              htl::GPIOState::set
#define LED1_OFF             htl::GPIOState::clear

#define LED1_Initialize()    LED1_GPIO::initOutput(htl::GPIODriver::pushPull)
#define LED1_On()            LED1_GPIO::set()
#define LED1_Off()           LED1_GPIO::clear()
#define LED1_Toggle()        LED1_GPIO::toggle()

#endif // USE_LED1


// -----------------------------------------------------------------------
// SW1 (Blue button)
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_GPIO             htl::GPIO_F2
#define SW1_ON               htl::GPIOState::set
#define SW1_OFF              htl::GPIOState::clear

#endif // SW1


// -----------------------------------------------------------------------
// Arduino expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_D0_GPIO      htl::GPIO_B6
#define ARDUINO_D1_GPIO      htl::GPIO_B7
#define ARDUINO_D2_GPIO      htl::GPIO_A15
#define ARDUINO_D3_GPIO      htl::GPIO_B1
#define ARDUINO_D4_GPIO      htl::GPIO_A10
#define ARDUINO_D5_GPIO      htl::GPIO_A9
#define ARDUINO_D6_GPIO      htl::GPIO_B0
#define ARDUINO_D7_GPIO      htl::GPIO_B2
#define ARDUINO_D8_GPIO      htl::GPIO_B8
#define ARDUINO_D9_GPIO      htl::GPIO_A8
#define ARDUINO_D10_GPIO     htl::GPIO_B9
#define ARDUINO_D11_GPIO     htl::GPIO_B5
#define ARDUINO_D12_GPIO     htl::GPIO_B4
#define ARDUINO_D13_GPIO     htl::GPIO_B3

#define ARDUINO_UART         htl::UART_1
#define ARDUINO_RX_GPIO      htl::GPIO_B6  // D0
#define ARDUINO_TX_GPIO      htl::GPIO_B7  // D1

#define ARDUINO_I2C          htl::I2CMaster_1
#define ARDUINO_SCL_GPIO     htl::GPIO_A9  // D5
#define ARDUINO_SDA_GPIO     htl::GPIO_A10 // D4

#define ARDUINO_SPI          htl::SPI_1
#define ARDUINO_SCK_GPIO     htl::GPIO_B3  // D13
#define ARDUINO_MISO_GPIO    htl::GPIO_B4  // D12
#define ARDUINO_MOSI_GPIO    htl::GPIO_B5  // D11

#endif // USE_ARDUINO


#endif // __eosBoard_NUCLERO_G031K8__
