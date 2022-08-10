#pragma once
#ifndef __board_SMT32F746G_DISCO__
#define __board_SMT32F746G_DISCO__


#ifdef __cplusplus

#include "HTL/htlGPIO.h"
#include "HTL/htlI2C.h"
#include "HTL/htlINT.h"
#include "HTL/htlSPI.h"
#include "HTL/htlUART.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/Graphics/eosColor.h"


// -----------------------------------------------------------------------
// LED1
// -----------------------------------------------------------------------
//
#ifdef USE_LED1
#define EXIST_LED1

namespace board {
	namespace led1 {

		// Asignacio de pins
		using GPIO_LED = htl::GPIO_I1;

		constexpr bool onState = true;
		constexpr bool offState = !onState;
	}
}

#endif // USE_LED1


// -----------------------------------------------------------------------
// SW1
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

namespace board {
	namespace sw1 {

		// Asignacio de pins
		using GPIO_SW = htl::GPIO_I11;

		constexpr bool onState = true;
		constexpr bool offState = !onState;
	}
}

#endif // SW1


// -----------------------------------------------------------------------
// DISPLAY
// -----------------------------------------------------------------------
//
#ifdef USE_DISPLAY
#define EXIST_DISPLAY

namespace board {
	namespace display {

		// Asignacio de pins
		using GPIO_BKE = htl::GPIO_K3;
		using GPIO_LCDE = htl::GPIO_I12;
		using GPIO_PC = htl::GPIO_I14;
		using GPIO_HSYNC = htl::GPIO_I10;
		using GPIO_VSYNC = htl::GPIO_I9;
		using GPIO_DE = htl::GPIO_K7;
		using GPIO_R0 = htl::GPIO_I15;
		using GPIO_R1 = htl::GPIO_J0;
		using GPIO_R2 = htl::GPIO_J1;
		using GPIO_R3 = htl::GPIO_J2;
		using GPIO_R4 = htl::GPIO_J3;
		using GPIO_R5 = htl::GPIO_J4;
		using GPIO_R6 = htl::GPIO_J5;
		using GPIO_R7 = htl::GPIO_J6;
		using GPIO_G0 = htl::GPIO_J7;
		using GPIO_G1 = htl::GPIO_J8;
		using GPIO_G2 = htl::GPIO_J9;
		using GPIO_G3 = htl::GPIO_J10;
		using GPIO_G4 = htl::GPIO_J11;
		using GPIO_G5 = htl::GPIO_K0;
		using GPIO_G6 = htl::GPIO_K1;
		using GPIO_G7 = htl::GPIO_K2;
		using GPIO_B0 = htl::GPIO_E4;
		using GPIO_B1 = htl::GPIO_J13;
		using GPIO_B2 = htl::GPIO_J14;
		using GPIO_B3 = htl::GPIO_J15;
		using GPIO_B4 = htl::GPIO_G12;
		using GPIO_B5 = htl::GPIO_K4;
		using GPIO_B6 = htl::GPIO_K5;
		using GPIO_B7 = htl::GPIO_K6;

		// Configuracio del LTDC
		constexpr uint16_t width = 480;      // Amplada de la imatge
		constexpr uint16_t height = 272;     // Alçada de la imatge
		constexpr uint16_t hSync = 41;       // Horizontal synchronization
		constexpr uint16_t vSync = 10;       // Vertical synchronization
		constexpr uint16_t hBP = 13;         // Horizontal back porch
		constexpr uint16_t vBP = 2;          // Vertical back porch
		constexpr uint16_t hFP = 32;         // Horizontal front porch
		constexpr uint16_t vFP = 2;          // Vertical front porch
		constexpr htl::LTDCPolarity hSyncPol  = htl::LTDCPolarity::activeLow;
		constexpr htl::LTDCPolarity vSyncPol  = htl::LTDCPolarity::activeLow;
		constexpr htl::LTDCPolarity dePol     = htl::LTDCPolarity::activeLow;
		constexpr htl::LTDCPolarity pcPol     = htl::LTDCPolarity::activeLow;

		// Configuracio del rellotge del LTDC
		constexpr uint32_t fdiv = 5;         // Divisor de frequencia

		// Configuracio del buffer d'imatge
		constexpr uint32_t buffer = 0xC0000000;
	}
}

#endif // USE_DISPLAY


// -----------------------------------------------------------------------
// TOUCHPAD
// -----------------------------------------------------------------------
//
#ifdef USE_TOUCHPAD
#define EXIST_TOUCHPAD

namespace board {
	namespace touchpad {

		// Asignacio de pins
		using GPIO_SCL = htl::GPIO_H7;
		using GPIO_SDA = htl::GPIO_H8;
		using GPIO_INT = htl::GPIO_I13;

		// Asignacio de interrupcions externes
		using EXTI_INT = htl::EXTI_13;

		// Asignacio del dispositiu I2C
		using I2C = htl::I2CMaster_3;

		constexpr uint16_t width = 470;      // Amplada del touchpad
		constexpr uint16_t height = 272;     // Alçada del touchpad

		constexpr uint8_t i2cAddr = 0x70;

		constexpr htl::GPIOPort extiPort = htl::GPIOPort::portI;

		constexpr htl::INTVector intVector = htl::INTVector::vEXTI13;
		constexpr htl::INTPriority intVectorPriority = htl::INTPriority::p15;
		constexpr htl::INTSubPriority intVectorSubPriority = htl::INTSubPriority::s0;

		constexpr bool useInterruption = true;
	}
}

#endif // USE_TOUCHPAD


// -----------------------------------------------------------------------
// Arduino expansion conector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

namespace board {
	namespace arduino {

		// Asignacio de pins
		using GPIO_D0 = htl::GPIO_C7;
		using GPIO_D1 = htl::GPIO_C6;
		using GPIO_D2 = htl::GPIO_G6;
		using GPIO_D3 = htl::GPIO_B4;
		using GPIO_D4 = htl::GPIO_G7;
		using GPIO_D5 = htl::GPIO_I0;
		using GPIO_D6 = htl::GPIO_H6;
		using GPIO_D7 = htl::GPIO_I3;
		using GPIO_D8 = htl::GPIO_I2;
		using GPIO_D9 = htl::GPIO_A15;
		using GPIO_D10 = htl::GPIO_A8;
		using GPIO_D11 = htl::GPIO_B15;
		using GPIO_D12 = htl::GPIO_B14;
		using GPIO_D13 = htl::GPIO_I1;
		using GPIO_D14 = htl::GPIO_B9;
		using GPIO_D15 = htl::GPIO_B8;

		using GPIO_TX = htl::GPIO_C6;
		using GPIO_RX = htl::GPIO_C7;
		using UART = htl::UART_6;

		using GPIO_SCL = htl::GPIO_B8;
		using GPIO_SDA = htl::GPIO_B9;
		using I2C = htl::I2C_1;

		using GPIO_SCK = htl::GPIO_I1;
		using GPIO_MISO = htl::GPIO_B14;
		using GPIO_MOSI = htl::GPIO_B15;
		using SPI = htl::SPI_2;
	}
}

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


// -----------------------------------------------------------------------
// Touchpad
// -----------------------------------------------------------------------

#ifdef USE_TOUCHPADxx
#define EXIST_TOUCHPAD

#define TOUCHPAD_DRV_FT5336

#define TOUCHPAD_MAX_POINTS         5

// Control del pin INT
//
#define TOUCHPAD_INT_PORT           HAL_GPIO_PORT_I
#define TOUCHPAD_INT_PIN            HAL_GPIO_PIN_13
#define TOUCHPAD_INT_TYPE           htl::GPIO_I13
#define TOUCHPAD_INT_EXTI_LINE      HAL_EXTI_LINE_13
#define TOUCHPAD_INT_EXTI_PORT      HAL_EXTI_PORT_I
#define TOUCHPAD_INT_EXTI_TYPE      htl::EXTI_13
#define TOUCHPAD_INT_IRQ            htl::INTVector::vEXTI13
#define TOUCHPAD_INT_PRIORITY       htl::INTPriority::p15
#define TOUCHPAD_INT_SUBPRIORITY    htl::INTSubPriority::s0


#endif // USE_TOUCHPAD

#endif // __cplusplus


#endif // __board_SMT32F746G_DISCO__
