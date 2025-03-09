#pragma once
#ifndef __eosBoard_NUCLEO_F030R8__
#define __eosBoard_NUCLEO_F030R8__


#define EOS_HARDWARE_NUCLEO_F030R8


// -----------------------------------------------------------------------
// Board information
// -----------------------------------------------------------------------

#define EOS_BOARD_NAME            "NUCLEO F030R8"
#define EOS_BOARD_MANUFACTURER    "ST-Microelectronics"

// -----------------------------------------------------------------------
// External oscilator parameters
// -----------------------------------------------------------------------

#define CLOCK_HSE_FREQUENCY        8000000 // Hz
#define CLOCK_HSE_STARTUP          100     // ms
#define CLOCK_HSE_BYPASS           0       // Bypass enabled
#define CLOCK_LSE_FREQUENCY        32768   // Hz
#define CLOCK_LSE_STARTUP          5000    // ms


// -----------------------------------------------------------------------
// LED1 (Green led)
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

#define LED1_PortID          htl::gpio::PortID::portA
#define LED1_PinID           htl::gpio::PinID::pin5
#define LED1_Pin             htl::gpio::PinX<LED1_PortID, LED1_PinID>
#define LED1_StateON         true
#define LED1_StateOFF        false

#define LED1_Initialize()    LED1_Pin::pInst->initOutput(htl::gpio::OutputMode::pushPull)
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

#define SW1_PortID           htl::gpio::PortID::portC
#define SW1_PinID            htl::gpio::PinID::pin13
#define SW1_Pin              htl::gpio::PinX<SW1_PortID, SW1_PinID>
#define SW1_FastPin          htl::gpio::FastPinX<SW1_PortID, SW1_PinID>
#define SW1_PinInterrupt     htl::gpio::PinInterruptX<SW1_PortID, SW1_PinID>
#define SW1_PinInitialize    htl::gpio::pInst->initInput(htl::gpio::InputMode::floating)
#define SW1_StateON          true
#define SW1_StateOF          false

#define SW1_Initialize()
#define SW1_Read()


#endif // SW1


// -----------------------------------------------------------------------
// SIO (Comunicacio serie a traver del depurador)
// -----------------------------------------------------------------------
//
#ifdef USE_SIO
#define EXIST_SIO

#define SIO_Device         htl::uart::UARTDevice2
#define SIO_IRQVector      htl::interrupts::VectorID::usart2
#define SIO_TX_Pin         htl::gpio::PinA2
#define SIO_RX_Pin         htl::gpio::PinA3

#endif // USE_SIO

// -----------------------------------------------------------------------
// Arduino expansion connector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_D0_Pin       htl::gpio::PinA3    // Conflicte amb SIO RX
#define ARDUINO_D1_Pin       htl::gpio::PinA2    // Conflicte amb SIO TX
#define ARDUINO_D2_Pin       htl::gpio::PinA10
#define ARDUINO_D3_Pin       htl::gpio::PinB3
#define ARDUINO_D4_Pin       htl::gpio::PinB5
#define ARDUINO_D5_Pin       htl::gpio::PinB4
#define ARDUINO_D6_Pin       htl::gpio::PinB10
#define ARDUINO_D7_Pin       htl::gpio::PinA8
#define ARDUINO_D8_Pin       htl::gpio::PinA9
#define ARDUINO_D9_Pin       htl::gpio::PinC7
#define ARDUINO_D10_Pin      htl::gpio::PinB6
#define ARDUINO_D11_Pin      htl::gpio::PinA7
#define ARDUINO_D12_Pin      htl::gpio::PinA6
#define ARDUINO_D13_Pin      htl::gpio::PinA5    // Conflicte amb LED1
#define ARDUINO_D14_Pin      htl::gpio::PinB9
#define ARDUINO_D15_Pin      htl::gpio::PinB8

#define ARDUINO_UART         htl::uart::UARTDevice2
#define ARDUINO_RX_Pin       htl::gpio::PinA3 // D0
#define ARDUINO_TX_Pin       htl::gpio::PinA2 // D1

#define ARDUINO_I2C          htl::i2c::I2CMasterDevice
#define ARDUINO_SCL_Pin      htl::gpio::PinB8 // D15
#define ARDUINO_SDA_Pin      htl::gpio::PinB9 // D14

#define ARDUINO_SPI          htl::spi::SPIDevice1
#define ARDUINO_SCK_Pin      htl::gpio::PinA5 // D13
#define ARDUINO_MISO_Pin     htl::gpio::PinA6 // D12
#define ARDUINO_MOSI_Pin     htl::gpio::PinA7 // D11

#endif // USE_ARDUINO


#endif // __eosBoard_NUCLEO_F030R8__

