#pragma once
#ifndef __eosBoard_SMT32F429I_DISC1__
#define __eosBoard_SMT32F429I_DISC1__


// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

#define LED1_GPIO            htl::GPIO_G13
#define LED1_ON              htl::GPIOState::set
#define LED1_OFF             htl::GPIOState::clear

#endif // USE_LED1


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------

#ifdef USE_LED2
#define EXIST_LED2

#define LED2_GPIO            htl::GPIO_G14
#define LED2_ON              htl::GPIOState::set
#define LED2_OFF             htl::GPIOState::clear

#endif // USE_LED2


// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------

#ifdef USE_SW1
#define EXIST_SW1

#define SW1_GPIO             htl::GPIO_A0
#define SW1_ON               htl::GPIOState::set
#define SW1_OFF              htl::GPIOState::clear

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

#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt
#define FONT_USE_Tahoma12pt
#define FONT_USE_Tahoma14pt

#define DISPLAY_IM0_GPIO     htl::GPIO_D2
#define DISPLAY_IM1_GPIO     htl::GPIO_D4
#define DISPLAY_IM2_GPIO     htl::GPIO_D5
#define DISPLAY_IM3_GPIO     htl::GPIO_D7

// SPI interface
#if defined(DISPLAY_INTERFACE_SPI) || defined(DISPLAY_INTERFACE_RGB)
#define DISPLAY_CS_GPIO      htl::GPIO_C2
#define DISPLAY_RS_GPIO      htl::GPIO_D13
#define DISPLAY_SCK_GPIO     htl::GPIO_F7
#define DISPLAY_MOSI_GPIO    htl::GPIO_F9
#define DISPLAY_SPI          htl::SPI_5
#endif
#if defined(DISPLAY_INTERFACE_SPI)
#define DISPLAY_TE_GPIO      htl::GPIO_D11
#endif

// 8080 interface
#if defined(DISPLAY_INTERFACE_8080)
#define DISPLAY_TE_GPIO      htl::GPIO_D11
#define DISPLAY_RD_GPIO	     htl::GPIO_D12
#define DISPLAY_WR_GPIO      htl::GPIO_D13
#define DISPLAY_TE_GPIO      htl::GPIO_D11
#endif

// RGB interface
#ifdef DISPLAY_INTERFACE_RGB
#define DISPLAY_HSYNC_GPIO   htl::GPIO_C6
#define DISPLAY_VSYNC_GPIO   htl::GPIO_A4
#define DISPLAY_DE_GPIO      htl::GPIO_F10
#define DISPLAY_PC_GPIO      htl::GPIO_G7
#define DISPLAY_R2_GPIO      htl::GPIO_C10
#define DISPLAY_R3_GPIO      htl::GPIO_B0
#define DISPLAY_R4_GPIO      htl::GPIO_A11
#define DISPLAY_R5_GPIO      htl::GPIO_A12
#define DISPLAY_R6_GPIO      htl::GPIO_B1
#define DISPLAY_R7_GPIO      htl::GPIO_G6
#define DISPLAY_G2_GPIO      htl::GPIO_A6
#define DISPLAY_G3_GPIO      htl::GPIO_G10
#define DISPLAY_G4_GPIO      htl::GPIO_B10
#define DISPLAY_G5_GPIO      htl::GPIO_B11
#define DISPLAY_G6_GPIO      htl::GPIO_C7
#define DISPLAY_G7_GPIO      htl::GPIO_D3
#define DISPLAY_B2_GPIO      htl::GPIO_D6
#define DISPLAY_B3_GPIO      htl::GPIO_G11
#define DISPLAY_B4_GPIO      htl::GPIO_G12
#define DISPLAY_B5_GPIO      htl::GPIO_A3
#define DISPLAY_B6_GPIO      htl::GPIO_B8
#define DISPLAY_B7_GPIO      htl::GPIO_B9

#define DISPLAY_HSYNC_POL    htl::LTDCPolarity::activeLow;   // HSync polarity
#define DISPLAY_VSYNC_POL    htl::LTDCPolarity::activeLow;   // VSync polarity
#define DISPLAY_DE_POL       htl::LTDCPolarity::activeLow;   // DE polarity
#define DISPLAY_PC_POL       htl::LTDCPolarity::activeLow;   // PC polarity
#endif

#define DISPLAY_WIDTH  		 240            // Amplada fisica de la pantalla
#define DISPLAY_HEIGHT       320            // Alçada fisica de la pantall
#define DISPLAY_HSYNC        9              // Horizontal sync
#define DISPLAY_VSYNC        1              // Vertical sync
#define DISPLAY_HBP          29             // Horizontal back Porch
#define DISPLAY_VBP          3              // Vertical back Porch
#define DISPLAY_HFP          2              // Horizontal front Porch
#define DISPLAY_VFP          2              // Vertical front Porch

#define DISPLAY_BUFFER       0xD0000000;

#endif // USE_DISPLAY


#endif // __eosBoard_SMT32F429I_DISC1__

