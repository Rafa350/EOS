#pragma once
#ifndef __board_SMT32F429I_DISC1__
#define __board_SMT32F429I_DISC1__


#ifdef __cplusplus

#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/STM32/htlLTDC.h"


// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------

#ifdef USE_LED1
#define EXIST_LED1

namespace board {
	namespace led1 {

		using GPIO_LED = htl::GPIO_G13;

		constexpr bool onState = true;
		constexpr bool offState = !onState;
	}
}
#endif


// -----------------------------------------------------------------------
// LED2
// -----------------------------------------------------------------------

#ifdef USE_LED2
#define EXIST_LED2

namespace board {
	namespace led2 {

		using GPIO_LED = htl::GPIO_G14;

		constexpr bool onState = true;
		constexpr bool offState = !onState;
	}
}

#endif


// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------

#ifdef USE_SW1
#define EXIST_SW1

namespace board {
	namespace sw1 {

		using GPIO_SW1 = htl::GPIO_A0;

		constexpr bool onState = true;
		constexpr bool offState = !onState;
	}
}

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

namespace board {
	namespace display {

		using GPIO_CS = htl::GPIO_C2;
		using GPIO_RS = htl::GPIO_D13;
		using GPIO_SCK = htl::GPIO_F7;
		using GPIO_MOSI = htl::GPIO_F9;
		using SPI = htl::SPI_5;

		using GPIO_HSYNC = htl::GPIO_C6;
		using GPIO_VSYNC = htl::GPIO_A4;
		using GPIO_DE = htl::GPIO_F10;
		using GPIO_PC = htl::GPIO_G7;
		using GPIO_R2 = htl::GPIO_C10;
		using GPIO_R3 = htl::GPIO_B0;
		using GPIO_R4 = htl::GPIO_A11;
		using GPIO_R5 = htl::GPIO_A12;
		using GPIO_R6 = htl::GPIO_B1;
		using GPIO_R7 = htl::GPIO_G6;
		using GPIO_G2 = htl::GPIO_A6;
		using GPIO_G3 = htl::GPIO_G10;
		using GPIO_G4 = htl::GPIO_B10;
		using GPIO_G5 = htl::GPIO_B11;
		using GPIO_G6 = htl::GPIO_C7;
		using GPIO_G7 = htl::GPIO_D3;
		using GPIO_B2 = htl::GPIO_D6;
		using GPIO_B3 = htl::GPIO_G11;
		using GPIO_B4 = htl::GPIO_G12;
		using GPIO_B5 = htl::GPIO_A3;
		using GPIO_B6 = htl::GPIO_B8;
		using GPIO_B7 = htl::GPIO_B9;

		constexpr uint16_t width = 240;     // Amplada fisica de la pantalla
		constexpr uint16_t height = 320;    // Alçada fisica de la pantalla
		constexpr uint16_t hSync= 9;        // Horizontal sync
		constexpr uint16_t vSync = 1;       // Vertical sync
		constexpr uint16_t hBP = 29;        // Horizontal back Porch
		constexpr uint16_t vBP = 3;         // Vertical back Porch
		constexpr uint16_t hFP = 2;         // Horizontal front Porch
		constexpr uint16_t vFP = 2;         // Vertical front Porch
		constexpr htl::LTDCPolarity hSyncPol = htl::LTDCPolarity::activeLow;   // HSync polarity
		constexpr htl::LTDCPolarity vSyncPol = htl::LTDCPolarity::activeLow;   // VSync polarity
		constexpr htl::LTDCPolarity dePol    = htl::LTDCPolarity::activeLow;   // DE polarity
		constexpr htl::LTDCPolarity pcPol    = htl::LTDCPolarity::activeLow;   // PC polarity

		constexpr uint32_t buffer = 0xD0000000;
	}
}

#endif // USE_DISPLAY


#endif // __cplusplus

#endif // __board_SMT32F429I_DISC1__

