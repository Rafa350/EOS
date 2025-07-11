#pragma once
#ifndef __eosBoard_STM32F429I_DISC1__
#define __eosBoard_STM32F429I_DISC1__


#define EOS_HARDWARE_STM32F429I_DISC1


// -----------------------------------------------------------------------
// External oscilator parameters
// -----------------------------------------------------------------------

#define CLOCK_HSE_FREQUENCY        8000000 // Hz
#define CLOCK_HSE_STARTUP          100     // ms
#define CLOCK_HSE_BYPASS           0       // Bypass disabled
#define CLOCK_LSE_FREQUENCY        32768   // Hz
#define CLOCK_LSE_STARTUP          5000    // ms


// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

#define LED1_PortID          htl::gpio::PortID::portG
#define LED1_PinID           htl::gpio::PinID::pin13
#define LED1_Pin             htl::gpio::PinDeviceX<LED1_PortID, LED1_PinID>
#define LED1_Instance        LED1_Pin::pInst
#define LED1_StateON         true
#define LED1_StateOFF        false

#define LED1_Initialize()    LED1_Instance->initOutput(htl::gpio::OutputType::pushPull, htl::gpio::PullUpDown::none, htl::gpio::Speed::low, false)
#define LED1_On()            LED1_Instance->set()
#define LED1_Off()           LED1_Instance->clear()
#define LED1_Toggle()        LED1_Instance->toggle()

#endif // USE_LED1


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------

#ifdef USE_LED2
#define EXIST_LED2

#define LED2_Pin             htl::gpio::PinG14
#define LED2_Instance        LED2_Pin::pInst
#define LED2_StateON         true
#define LED2_StateOFF        false

#define LED2_Initialize()    LED2_Instance->initOutput(htl::gpio::OutputType::pushPull, htl::gpio::PullUpDown::none, htl::gpio::Speed::low, false)
#define LED2_On()            LED2_Instance->set()
#define LED2_Off()           LED2_Instance->clear()
#define LED2_Toggle()        LED2_Instance->toggle()

#endif // USE_LED2


// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------

#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinA0
#define SW1_PortID           SW1_Pin::portID
#define SW1_PinID            SW1_Pin::pinID
#define SW1_StateON          true
#define SW1_StateOFF         false

#endif // USE_SW1


// -----------------------------------------------------------------------
// SIO (Comunicacio serie a traver del depurador)
// -----------------------------------------------------------------------
//
#ifdef USE_SIO
#define EXIST_SIO

#define SIO_UART_Device           htl::uart::UARTDevice1
#define SIO_UART_InterruptHandler USART1_IRQHandler
#define SIO_UART_IrqVector        htl::irq::VectorID::uart1
#define SIO_TX_Pin                htl::gpio::PinA9
#define SIO_RX_Pin                htl::gpio::PinA10

#endif // USE_SIO


// -----------------------------------------------------------------------
// USB FS (OTG1)
// -----------------------------------------------------------------------

#if defined(USE_USB_DEVICE0) || defined(USE_USB_HOST0)
#define USB_USB0_DP_PORT          HAL_GPIO_PORT_A
#define USB_USB0_DP_PIN           HAL_GPIO_PIN_12
#define USB_USB0_DP_AF            HAL_GPIO_AF10_OGT1_FS

#define USB_USB0_DM_PORT          HAL_GPIO_PORT_A
#define USB_USB0_DM_PIN           HAL_GPIO_PIN_11
#define USB_USB0_DM_AF            HAL_GPIO_AF10_OGT1_FS

#define USB_USB0_ID_PORT          HAL_GPIO_PORT_A
#define USB_USB0_ID_PIN           HAL_GPIO_PIN_10
#define USB_USB0_ID_AF            HAL_GPIO_AF10_OGT1_FS

#define USB_USB0_VBUS_PORT        HAL_GPIO_PORT_A
#define USB_USB0_VBUS_PIN         HAL_GPIO_PIN_9
#define USB_USB0_VBUS_AF          HAL_GPIO_AF10_OGT1_FS

//#define USB_USB0_VBUSEN_PORT      HAL_GPIO_PORT_C
//#define USB_USB0_VBUSEN_PIN       HAL_GPIO_PIN_0
//#define USB_USB0_VBUSEN_AF        HAL_GPIO_AF_NONE
#endif // USE_USB_DEVICE0 || USE_USB_HOST0


// -----------------------------------------------------------------------
// USB HS (OTG2 Full speed mode)
// -----------------------------------------------------------------------

#if defined(USE_USB_DEVICE1) || defined(USE_USB_HOST1)
#define USB_USB1_DP_PORT          HAL_GPIO_PORT_B
#define USB_USB1_DP_PIN           HAL_GPIO_PIN_15
#define USB_USB1_DP_AF            HAL_GPIO_AF12_OGT2_HS

#define USB_USB1_DM_PORT          HAL_GPIO_PORT_B
#define USB_USB1_DM_PIN           HAL_GPIO_PIN_14
#define USB_USB1_DM_AF            HAL_GPIO_AF12_OGT2_FS

#define USB_USB1_ID_PORT          HAL_GPIO_PORT_B
#define USB_USB1_ID_PIN           HAL_GPIO_PIN_12
#define USB_USB1_ID_AF            HAL_GPIO_AF12_OGT2_FS

#define USB_USB1_VBUS_PORT        HAL_GPIO_PORT_B
#define USB_USB1_VBUS_PIN         HAL_GPIO_PIN_13
#define USB_USB1_VBUS_AF          HAL_GPIO_AF12_OGT2_FS

#define USB_USB1_VBUSEN_PORT      HAL_GPIO_PORT_C
#define USB_USB1_VBUSEN_PIN       HAL_GPIO_PIN_4
#define USB_USB1_VBUSEN_AF        HAL_GPIO_AF12_OGT2_FS
#endif // USE_USB_DEVICE1 || USE_USB_HOST1


// -----------------------------------------------------------------------
// DISPLAY
// -----------------------------------------------------------------------

#ifdef USE_DISPLAY
#define EXIST_DISPLAY

#define DISPLAY_IM0_Pin           htl::gpio::PinD2
#define DISPLAY_IM1_Pin           htl::gpio::PinD4
#define DISPLAY_IM2_Pin           htl::gpio::PinD5
#define DISPLAY_IM3_Pin           htl::gpio::PinD7

// SPI interface
#if defined(DISPLAY_INTERFACE_SPI) || \
	defined(DISPLAY_INTERFACE_RGB)
#define DISPLAY_CS_Pin            htl::gpio::PinC2
#define DISPLAY_RS_Pin            htl::gpio::PinD13
#define DISPLAY_SCK_Pin           htl::gpio::PinF7
#define DISPLAY_MOSI_Pin          htl::gpio::PinF9
#define DISPLAY_SPI_Device        htl::spi::SPIDevice5
#endif
#if defined(DISPLAY_INTERFACE_SPI)
#define DISPLAY_TE_Pin            htl::gpio::PinD11
#endif

// 8080 interface
#if defined(DISPLAY_INTERFACE_8080)
#define DISPLAY_TE_PIn            htl::gpio::PinD11
#define DISPLAY_RD_Pin            htl::gpio::PinD12
#define DISPLAY_WR_Pin            htl::gpio::PinD13
#define DISPLAY_TE_Pin            htl::gpio::PinD11
#endif

// RGB interface
#if defined(DISPLAY_INTERFACE_RGB)
#define DISPLAY_HSYNC_Pin         htl::gpio::PinC6
#define DISPLAY_VSYNC_Pin         htl::gpio::PinA4
#define DISPLAY_DE_Pin            htl::gpio::PinF10
#define DISPLAY_PC_Pin            htl::gpio::PinG7
#define DISPLAY_R2_Pin            htl::gpio::PinC10
#define DISPLAY_R3_Pin            htl::gpio::PinB0
#define DISPLAY_R4_Pin            htl::gpio::PinA11
#define DISPLAY_R5_Pin            htl::gpio::PinA12
#define DISPLAY_R6_Pin            htl::gpio::PinB1
#define DISPLAY_R7_Pin            htl::gpio::PinG6
#define DISPLAY_G2_Pin            htl::gpio::PinA6
#define DISPLAY_G3_Pin            htl::gpio::PinG10
#define DISPLAY_G4_Pin            htl::gpio::PinB10
#define DISPLAY_G5_Pin            htl::gpio::PinB11
#define DISPLAY_G6_Pin            htl::gpio::PinC7
#define DISPLAY_G7_Pin            htl::gpio::PinD3
#define DISPLAY_B2_Pin            htl::gpio::PinD6
#define DISPLAY_B3_Pin            htl::gpio::PinG11
#define DISPLAY_B4_Pin            htl::gpio::PinG12
#define DISPLAY_B5_Pin            htl::gpio::PinA3
#define DISPLAY_B6_Pin            htl::gpio::PinB8
#define DISPLAY_B7_Pin            htl::gpio::PinB9

#define DISPLAY_HSYNC_POL         htl::ltdc::PinPolarity::activeLow  // HSync polarity
#define DISPLAY_VSYNC_POL         htl::ltdc::PinPolarity::activeLow  // VSync polarity
#define DISPLAY_DE_POL            htl::ltdc::PinPolarity::activeLow  // DE polarity
#define DISPLAY_PC_POL            htl::ltdc::PinPolarity::activeLow  // PC polarity
#endif

#define DISPLAY_WIDTH  		      240            // Amplada fisica de la pantalla
#define DISPLAY_HEIGHT            320            // Alçada fisica de la pantall
#define DISPLAY_HSYNC             9              // Horizontal sync
#define DISPLAY_VSYNC             1              // Vertical sync
#define DISPLAY_HBP               29             // Horizontal back Porch
#define DISPLAY_VBP               3              // Vertical back Porch
#define DISPLAY_HFP               2              // Horizontal front Porch
#define DISPLAY_VFP               2              // Vertical front Porch

#define DISPLAY_BUFFER            0xD0000000;

#endif // USE_DISPLAY


#endif // __eosBoard_STM32F429I_DISC1__
