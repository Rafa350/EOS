#pragma once


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

#define LED1_Pin             htl::gpio::PinG13
#define LED1_PortID          LED1_Pin::portID
#define LED1_PinID           LED1_Pin::PinID
#define LED1_StateON         true
#define LED1_StateOFF        false

#endif // USE_LED1


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------

#ifdef USE_LED2
#define EXIST_LED2

#define LED2_Pin             htl::gpio::PinG14
#define LED2_PortID          LED2_Pin::portID
#define LED2_PinID           LED2_Pin::PinID
#define LED2_StateON         true
#define LED2_StateOFF        false

#endif // USE_LED2


// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------

#ifdef USE_SW1
#define EXIST_SW1

#define SW1_Pin              htl::gpio::PinA0
#define SW1_PortID           SW1_Pin::portID
#define SW1_PinID            SW!_Pin::pinID
#define SW1_StateON          htl::gpio::PinState::set
#define SW1_StateOFF         htl::gpio::PinState::clear

#endif // USE_SW1


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
#define DISPLAY_TE_PIn            htl::GPIO_D11
#define DISPLAY_RD_Pin            htl::GPIO_D12
#define DISPLAY_WR_Pin            htl::GPIO_D13
#define DISPLAY_TE_Pin            htl::GPIO_D11
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

#define DISPLAY_HSYNC_POL         htl::ltdc::PinPolarity::activeLow;   // HSync polarity
#define DISPLAY_VSYNC_POL         htl::ltdc::PinPolarity::activeLow;   // VSync polarity
#define DISPLAY_DE_POL            htl::ltdc::PinPolarity::activeLow;   // DE polarity
#define DISPLAY_PC_POL            htl::ltdc::PinPolarity::activeLow;   // PC polarity
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
