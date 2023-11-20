#pragma once


// -----------------------------------------------------------------------
// External oscilator parameters
// -----------------------------------------------------------------------

#define CLOCK_HSE_FREQUENCY        25000000 // Hz
#define CLOCK_HSE_STARTUP          100      // ms
#define CLOCK_LSE_FREQUENCY        32768    // Hz
#define CLOCK_LSE_STARTUP          5000     // ms


// -----------------------------------------------------------------------
// Green led 1
// -----------------------------------------------------------------------
//
#ifdef USE_LED1
#define EXIST_LED1

#define LED1_Pin             htl::gpio::PinI1
#define LED1_PortID          LED1_Pin::portID
#define LED1_PinID           LED1_Pin::pinID
#define LED1_StateON         true
#define LED1_StateOFF        false

#endif // USE_LED1


// -----------------------------------------------------------------------
// Blue switch 1
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinI11
#define SW1_PortID           SW1_Pin::portID
#define SW1_PinID            SW1_Pin::pinID
#define SW1_PinInterrupt     htl::gpio::PinInterrupX<SW1_Pin::portID, SW1_Pin::pinID>
#define SW1_StateON          true
#define SW1_StateOFF         false

#endif // SW1


// -----------------------------------------------------------------------
// Integrated board display
// -----------------------------------------------------------------------
//
#ifdef USE_DISPLAY
#define EXIST_DISPLAY

#define DISPLAY_BKE_Pin      htl::gpio::PinK3
#define DISPLAY_LCDE_Pin     htl::gpio::PinI12
#define DISPLAY_PC_Pin       htl::gpio::PinI14
#define DISPLAY_HSYNC_Pin    htl::gpio::PinI10
#define DISPLAY_VSYNC_Pin    htl::gpio::PinI9
#define DISPLAY_DE_Pin       htl::gpio::PinK7
#define DISPLAY_R0_Pin       htl::gpio::PinI15
#define DISPLAY_R1_Pin       htl::gpio::PinJ0
#define DISPLAY_R2_Pin       htl::gpio::PinJ1
#define DISPLAY_R3_Pin       htl::gpio::PinJ2
#define DISPLAY_R4_Pin       htl::gpio::PinJ3
#define DISPLAY_R5_Pin       htl::gpio::PinJ4
#define DISPLAY_R6_Pin       htl::gpio::PinJ5
#define DISPLAY_R7_Pin       htl::gpio::PinJ6
#define DISPLAY_G0_Pin       htl::gpio::PinJ7
#define DISPLAY_G1_Pin       htl::gpio::PinJ8
#define DISPLAY_G2_Pin       htl::gpio::PinJ9
#define DISPLAY_G3_Pin       htl::gpio::PinJ10
#define DISPLAY_G4_Pin       htl::gpio::PinJ11
#define DISPLAY_G5_Pin       htl::gpio::PinK0
#define DISPLAY_G6_Pin       htl::gpio::PinK1
#define DISPLAY_G7_Pin       htl::gpio::PinK2
#define DISPLAY_B0_Pin       htl::gpio::PinE4
#define DISPLAY_B1_Pin       htl::gpio::PinJ13
#define DISPLAY_B2_Pin       htl::gpio::PinJ14
#define DISPLAY_B3_Pin       htl::gpio::PinJ15
#define DISPLAY_B4_Pin       htl::gpio::PinG12
#define DISPLAY_B5_Pin       htl::gpio::PinK4
#define DISPLAY_B6_Pin       htl::gpio::PinK5
#define DISPLAY_B7_Pin       htl::gpio::PinK6

#define DISPLAY_WIDTH 		 480            // Amplada de la imatge
#define DISPLAY_HEIGHT		 272            // Alçada de la imatge
#define DISPLAY_HSYNC        41             // Horizontal synchronization
#define DISPLAY_VSYNC        10             // Vertical synchronization
#define DISPLAY_HBP          13             // Horizontal back porch
#define DISPLAY_VBP          2              // Vertical back porch
#define DISPLAY_HFP          32             // Horizontal front porch
#define DISPLAY_VFP          2              // Vertical front porch
#define DISPLAY_HSYNC_POL    htl::ltdc::PinPolarity::activeLow
#define DISPLAY_VSYNC_POL    htl::ltdc::PinPolarity::activeLow
#define DISPLAY_DE_POL       htl::ltdc::PinPolarity::activeLow
#define DISPLAY_PC_POL       htl::ltdc::PinPolarity::activeLow

#define DISPLAY_BUFFER       0xC0000000

#define DISPLAY_CLK_FDIV     5


#endif // USE_DISPLAY


// -----------------------------------------------------------------------
// Integrated display capacitative touchpad
// -----------------------------------------------------------------------
//
#if defined(USE_TOUCHPAD) & defined(USE_DISPLAY)
#define EXIST_TOUCHPAD

#define TOUCHPAD_SCL_Pin     htl::gpio::PinH7
#define TOUCHPAD_SDA_Pin     htl::gpio::PinH8
#define TOUCHPAD_INT_Pin     htl::gpio::PinI13
#define TOUCHPAD_INT_PinInterrupt      htl::gpio::PinInterruptX<htl::gpio::PortID::I, htl::gpio::PinID::_13>
#define TOUCHPAD_INT_IntVector         htl::irq::VectorID::exti13

#define TOUCHPAD_I2C_Device  htl::i2c::I2CMasterDevice3
#define TOUCHPAD_I2C_ADDR    0x70

#define TOUCHPAD_WIDTH       DISPLAY_WIDTH
#define TOUCHPAD_HEIGHT      DISPLAY_HEIGHT


#endif // USE_TOUCHPAD


// -----------------------------------------------------------------------
// Arduino expansion conector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_D0_Pin       htl::gpio::PinC7
#define ARDUINO_D1_Pin       htl::gpio::PinC6
#define ARDUINO_D2_Pin       htl::gpio::PinG6
#define ARDUINO_D3_Pin       htl::gpio::PinB4
#define ARDUINO_D4_Pin       htl::gpio::PinG7
#define ARDUINO_D5_Pin       htl::gpio::PinI0
#define ARDUINO_D6_Pin       htl::gpio::PinH6
#define ARDUINO_D7_Pin       htl::gpio::PinI3
#define ARDUINO_D8_Pin       htl::gpio::PinI2
#define ARDUINO_D9_Pin       htl::gpio::PinA15
#define ARDUINO_D10_Pin      htl::gpio::PinA8
#define ARDUINO_D11_Pin      htl::gpio::PinB15
#define ARDUINO_D12_Pin      htl::gpio::PinB14
#define ARDUINO_D13_Pin      htl::gpio::PinI1
#define ARDUINO_D14_Pin      htl::gpio::PinB9
#define ARDUINO_D15_Pin      htl::gpio::PinB8

#define ARDUINO_UART_Device  htl::uart::UARTDevice6
#define ARDUINO_RX_Pin       htl::gpio::PinC7
#define ARDUINO_TX_Pin       htl::gpio::PinC6

#define ARDUINO_I2C_Device   htl::i2c::I2CMasterDevice1
#define ARDUINO_SCL_Pin      htl::gpio::PinB8
#define ARDUINO_SDA_Pin      htl::gpio::PinB9

#define ARDUINO_SPI_Device   htl::spi::SPIDevice2
#define ARDUINO_SCK_Pin      htl::gpio::PinI1
#define ARDUINO_MISO_Pin     htl::gpio::PinB14
#define ARDUINO_MOSI_Pin     htl::gpio::PinB15

#endif // USE_ARDUINO


// -----------------------------------------------------------------------
// Camara DCIM OV9655
// -----------------------------------------------------------------------

#ifdef USE_CAMERA
#define EXIST_CAMERA

// Tamany de la imatge
//
#define CAMERA_IMAGE_WIDTH        0  // Seleccionable per software
#define CAMERA_IMAGE_HEIGHT       0  // Seleccionable per software

// Format de la imatge
//
#define CAMERA_FORMAT             RGB565

#define CAMERA_PIXCK_PORT         HAL_GPIO_PORT_A
#define CAMERA_PIXCK_PIN          HAL_GPIO_PIN_6
#define CAMERA_PIXCH_AF           HAL_GPIO_AF13

#define CAMERA_HSYNC_PORT         HAL_GPIO_PORT_A
#define CAMERA_HSYNC_PIN          HAL_GPIO_PIN_4
#define CAMERA_HSYNC_AF           HAL_GPIO_AF13

#define CAMERA_VSYNC_PORT         HAL_GPIO_PORT_G
#define CAMERA_VSYNC_PIN          HAL_GPIO_PIN_9
#define CAMERA_VSYNC_AF           HAL_GPIO_AF13

#define CAMERA_D0_PORT            HAL_GPIO_PORT_H
#define CAMERA_D0_PIN             HAL_GPIO_PIN_9
#define CAMERA_D0_AF              HAL_GPIO_AF13

#define CAMERA_D1_PORT            HAL_GPIO_PORT_H
#define CAMERA_D1_PIN             HAL_GPIO_PIN_10
#define CAMERA_D1_AF              HAL_GPIO_AF13

#define CAMERA_D2_PORT            HAL_GPIO_PORT_H
#define CAMERA_D2_PIN             HAL_GPIO_PIN_11
#define CAMERA_D2_AF              HAL_GPIO_AF13

#define CAMERA_D3_PORT            HAL_GPIO_PORT_H
#define CAMERA_D3_PIN             HAL_GPIO_PIN_12
#define CAMERA_D3_AF              HAL_GPIO_AF13

#define CAMERA_D4_PORT            HAL_GPIO_PORT_H
#define CAMERA_D4_PIN             HAL_GPIO_PIN_14
#define CAMERA_D4_AF              HAL_GPIO_AF13

#define CAMERA_D5_PORT            HAL_GPIO_PORT_D
#define CAMERA_D5_PIN             HAL_GPIO_PIN_3
#define CAMERA_D5_AF              HAL_GPIO_AF13

#define CAMERA_D6_PORT            HAL_GPIO_PORT_E
#define CAMERA_D6_PIN             HAL_GPIO_PIN_5
#define CAMERA_D6_AF              HAL_GPIO_AF13

#define CAMERA_D7_PORT            HAL_GPIO_PORT_E
#define CAMERA_D7_PIN             HAL_GPIO_PIN_6
#define CAMERA_D7_AF              HAL_GPIO_AF13

#define CAMERA_PE_PORT            HAL_GPIO_PORT_H
#define CAMERA_PE_PIN             HAL_GPIO_PIN_13


#endif // USE_CAMERA


// -----------------------------------------------------------------------
// Controlador SD
// -----------------------------------------------------------------------

#ifdef USE_SD
#define EXIST_SD

#define SD_PRESENT_PORT           HAL_GPIO_PORT_C
#define SD_PRESENT_PIN            HAL_GPIO_PIN_13

#define SD_DMA_RX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_RX_STREAM          DMA2_Stream3
#define SD_DMA_RX_IRQ             DMA2_Stream3_IRQn

#define SD_DMA_TX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_TX_STREAM          DMA2_Stream6
#define SD_DMA_TX_IRQ             DMA2_Stream6_IRQn

#define SD_MODULE                 SDMMC1

#endif // USE_SD
