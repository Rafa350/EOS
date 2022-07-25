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


namespace board {

	// -----------------------------------------------------------------------
	// LED1
	// -----------------------------------------------------------------------
	//
	#ifdef USE_LED1

		#define EXIST_LED1

		namespace led1 {

			// Asignacio de pins
			using GPIO_LED = htl::GPIO_I1;

			constexpr bool onState = true;
			constexpr bool offState = !onState;
		};

	#endif

	// -----------------------------------------------------------------------
	// SW1
	// -----------------------------------------------------------------------
	//
	#ifdef USE_SW1

		#define EXIST_SW1

		namespace sw1 {

			// Asignacio de pins
			using GPIO_SW = htl::GPIO_I11;

			constexpr bool onState = true;
			constexpr bool offState = !onState;
		}

	#endif

	// -----------------------------------------------------------------------
	// DISPLAY
	// -----------------------------------------------------------------------
	//
	#ifdef USE_DISPLAY

		#define EXIST_DISPLAY

		#ifndef DISPLAY_COLOR_FORMAT
			#define DISPLAY_COLOR_FORMAT eos::ColorFormat::rgb565
		#endif

		#ifndef DISPLAY_BUFFER
			#define DISPLAY_BUFFER 0xC0000000
		#endif

		#ifndef DISPLAY_DOUBLEBUFFER
			#define DISPLAY_DOUBLEBUFFER true
		#endif

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
			constexpr uint32_t buffer              = DISPLAY_BUFFER;
			constexpr bool useDoubleBuffer         = DISPLAY_DOUBLEBUFFER;
			constexpr eos::ColorFormat colorFormat = DISPLAY_COLOR_FORMAT;
		};

	#endif

	// -----------------------------------------------------------------------
	// TOUCHPAD
	// -----------------------------------------------------------------------
	//
	#ifdef USE_TOUCHPAD

		#define EXIST_TOUCHPAD

		namespace touchpad {

			// Asignacio de pins
			using GPIO_SCL = htl::GPIO_H7;
			using GPIO_SDA = htl::GPIO_H8;
			using GPIO_INT = htl::GPIO_I13;

			// Asignacio de interrupcions externes
			using EXTI_INT = htl::EXTI_13;

			// Asignacio del dispositiu I2C
			using I2C = htl::I2C_3;

			constexpr uint16_t width = 470;      // Amplada del touchpad
			constexpr uint16_t height = 272;     // Alçada del touchpad

			constexpr uint8_t i2cAddr = 0x70;

			constexpr htl::EXTIPort extiPort = htl::EXTIPort::portI;

			constexpr htl::INTVector intVector = htl::INTVector::vEXTI13;
			constexpr htl::INTPriority intVectorPriority = htl::INTPriority::p15;
			constexpr htl::INTSubPriority intVectorSubPriority = htl::INTSubPriority::s0;
		}

	#endif

	// -----------------------------------------------------------------------
	// Arduino expansion conector
	// -----------------------------------------------------------------------

	#ifdef USE_ARDUINO

		#define EXIST_ARDUINO

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

	#endif
}


#endif


// -----------------------------------------------------------------------
// Arduino expansion conector
// -----------------------------------------------------------------------
/*
#ifdef USE_ARDUINO
#define EXISTS_ARDUINO

#define ARDUINO_D0_PORT           HAL_GPIO_PORT_C
#define ARDUINO_D0_PIN            HAL_GPIO_PIN_7

#define ARDUINO_D1_PORT           HAL_GPIO_PORT_C
#define ARDUINO_D1_PIN            HAL_GPIO_PIN_6

#define ARDUINO_D2_PORT           HAL_GPIO_PORT_G
#define ARDUINO_D2_PIN            HAL_GPIO_PIN_6

#define ARDUINO_D3_PORT           HAL_GPIO_PORT_B
#define ARDUINO_D3_PIN            HAL_GPIO_PIN_4

#define ARDUINO_D4_PORT           HAL_GPIO_PORT_G
#define ARDUINO_D4_PIN            HAL_GPIO_PIN_7

#define ARDUINO_D5_PORT           HAL_GPIO_PORT_I
#define ARDUINO_D5_PIN            HAL_GPIO_PIN_0

#define ARDUINO_D6_PORT           HAL_GPIO_PORT_H
#define ARDUINO_D6_PIN            HAL_GPIO_PIN_6

#define ARDUINO_D7_PORT           HAL_GPIO_PORT_I
#define ARDUINO_D7_PIN            HAL_GPIO_PIN_3

#define ARDUINO_D8_PORT           HAL_GPIO_PORT_I
#define ARDUINO_D8_PIN            HAL_GPIO_PIN_2

#define ARDUINO_D9_PORT           HAL_GPIO_PORT_A
#define ARDUINO_D9_PIN            HAL_GPIO_PIN_15

#define ARDUINO_D10_PORT          HAL_GPIO_PORT_A
#define ARDUINO_D10_PIN           HAL_GPIO_PIN_8

#define ARDUINO_D11_PORT          HAL_GPIO_PORT_B
#define ARDUINO_D11_PIN           HAL_GPIO_PIN_15

#define ARDUINO_D12_PORT          HAL_GPIO_PORT_B
#define ARDUINO_D12_PIN           HAL_GPIO_PIN_14

#define ARDUINO_D13_PORT          HAL_GPIO_PORT_I
#define ARDUINO_D13_PIN           HAL_GPIO_PIN_1

#define ARDUINO_D14_PORT          HAL_GPIO_PORT_B
#define ARDUINO_D14_PIN           HAL_GPIO_PIN_9

#define ARDUINO_D15_PORT          HAL_GPIO_PORT_B
#define ARDUINO_D15_PIN           HAL_GPIO_PIN_8

#define ARDUINO_SPI_SCK_PORT      HAL_GPIO_PORT_I
#define ARDUINO_SPI_SCK_PIN       HAL_GPIO_PIN_1
#define ARDUINO_SPI_SCK_AF        HAL_GPIO_AF_5

#define ARDUINO_SPI_MOSI_PORT     HAL_GPIO_PORT_B
#define ARDUINO_SPI_MOSI_PIN      HAL_GPIO_PIN_15
#define ARDUINO_SPI_MOSI_AF       HAL_GPIO_AF_5

#define ARDUINO_SPI_MISO_PORT     HAL_GPIO_PORT_B
#define ARDUINO_SPI_MISO_PIN      HAL_GPIO_PIN_14
#define ARDUINO_SPI_MISO_AF       HAL_GPIO_AF_5

#define ARDUINO_I2C_SCL_PORT      HAL_GPIO_PORT_B
#define ARDUINO_I2C_SCL_PIN       HAL_GPIO_PIN_8
#define ARDUINO_I2C_SCL_AF        HAL_GPIO_AF_4

#define ARDUINO_I2C_SDA_PORT      HAL_GPIO_PORT_B
#define ARDUINO_I2C_SDA_PIN       HAL_GPIO_PIN_9
#define ARDUINO_I2C_SDA_AF        HAL_GPIO_AF_4

#define ARDUINO_I2C_CHANNEL       HAL_I2C_CHANNEL_1


#endif // USE_ARDUINO
*/

// -----------------------------------------------------------------------
// Display
// -----------------------------------------------------------------------
/*
#ifdef USE_DISPLAY
#define EXIST_DISPLAY

// Parametres del display
//
#define DISPLAY_IMAGE_WIDTH       480            // Amplada de la pantalla
#define DISPLAY_IMAGE_HEIGHT      272            // Alçada de la pantalla
#define DISPLAY_IMAGE_BUFFER      0xC0000000     // Adressa de la ram de video
#define DISPLAY_DRV_RGBLTDC                      // Driver


// Parametres de temporitzacio i sincronitzacio
//
#define DISPLAY_HSYNC             41   // Horizontal synchronization
#define DISPLAY_HBP               13   // Horizontal back porch
#define DISPLAY_HFP               32   // Horizontal front porch
#define DISPLAY_VSYNC             10   // Vertical synchronization
#define DISPLAY_VBP               2    // Vertical back porch
#define DISPLAY_VFP               2    // Vertical front porch
#define DISPLAY_HSPOL             0    // HSync active (0=LOW, 1=HIGHT)
#define DISPLAY_VSPOL             0    // VSync active (0=LOW, 1=HIGHT)
#define DISPLAY_DEPOL             0    // DE active (0=LOW, 1=HIGHT)
#define DISPLAY_PCPOL             0    // PC active (0=LOW, 1=HIGHT)
#define DISPLAY_FDIV              5    // Divisor de frequencia

// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt
#define FONT_USE_Tahoma10pt
#define FONT_USE_Tahoma12pt

// Control del pin DISPLAY_ENABLE
//
#define DISPLAY_LCDE_PORT         HAL_GPIO_PORT_I
#define DISPLAY_LCDE_PIN	      HAL_GPIO_PIN_12
#define GPIO_LCDE_TYPE            htl::GPIO_I12

// Control del pin BACKLIGHT_ENABLE
//
#define DISPLAY_BKE_PORT          HAL_GPIO_PORT_K
#define DISPLAY_BKE_PIN           HAL_GPIO_PIN_3
#define GPIO_BKE_TYPE             htl::GPIO_K3

// Control del pin HSYNC (Horizontal sync)
//
#define DISPLAY_HSYNC_PORT        HAL_GPIO_PORT_I
#define DISPLAY_HSYNC_PIN         HAL_GPIO_PIN_10
#define DISPLAY_HSYNC_AF          HAL_GPIO_AF_14
#define GPIO_HSYNC_TYPE           htl::GPIO_I10

// Control del pin VSYNC (Vertical sync)
//
#define DISPLAY_VSYNC_PORT        HAL_GPIO_PORT_I
#define DISPLAY_VSYNC_PIN         HAL_GPIO_PIN_9
#define DISPLAY_VSYNC_AF          HAL_GPIO_AF_14
#define GPIO_VSYNC_TYPE           htl::GPIO_I9

// Control del pin DE (Display enable)
//
#define DISPLAY_DE_PORT           HAL_GPIO_PORT_K
#define DISPLAY_DE_PIN            HAL_GPIO_PIN_7
#define DISPLAY_DE_AF             HAL_GPIO_AF_14
#define GPIO_DE_TYPE              htl::GPIO_K7

// Control del pin DOTCLK (Dot clock)
//
#define DISPLAY_DOTCLK_PORT       HAL_GPIO_PORT_I
#define DISPLAY_DOTCLK_PIN        HAL_GPIO_PIN_14
#define DISPLAY_DOTCLK_AF         HAL_GPIO_AF_14
#define GPIO_DOTCLK_TYPE          htl::GPIO_I14

// Control del pin R0
//
#define DISPLAY_R0_PORT           HAL_GPIO_PORT_I
#define DISPLAY_R0_PIN            HAL_GPIO_PIN_15
#define DISPLAY_R0_AF             HAL_GPIO_AF_14
#define GPIO_R0_TYPE              htl::GPIO_I15

// Control del pin R1
//
#define DISPLAY_R1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R1_PIN            HAL_GPIO_PIN_0
#define DISPLAY_R1_AF             HAL_GPIO_AF_14
#define GPIO_R1_TYPE              htl::GPIO_J0

// Control del pin R2
//
#define DISPLAY_R2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R2_PIN            HAL_GPIO_PIN_1
#define DISPLAY_R2_AF             HAL_GPIO_AF_14
#define GPIO_R2_TYPE              htl::GPIO_J1

// Control del pin R3
//
#define DISPLAY_R3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R3_PIN            HAL_GPIO_PIN_2
#define DISPLAY_R3_AF             HAL_GPIO_AF_14
#define GPIO_R3_TYPE              htl::GPIO_J2

// Control del pin R4
//
#define DISPLAY_R4_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R4_PIN            HAL_GPIO_PIN_3
#define DISPLAY_R4_AF             HAL_GPIO_AF_14
#define GPIO_R4_TYPE              htl::GPIO_J3

// Control del pin R5
//
#define DISPLAY_R5_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R5_PIN            HAL_GPIO_PIN_4
#define DISPLAY_R5_AF             HAL_GPIO_AF_14
#define GPIO_R5_TYPE              htl::GPIO_J4

// Control del pin R6
//
#define DISPLAY_R6_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R6_PIN            HAL_GPIO_PIN_5
#define DISPLAY_R6_AF             HAL_GPIO_AF_14
#define GPIO_R6_TYPE              htl::GPIO_J5

// Control del pin R7
//
#define DISPLAY_R7_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R7_PIN            HAL_GPIO_PIN_6
#define DISPLAY_R7_AF             HAL_GPIO_AF_14
#define GPIO_R7_TYPE              htl::GPIO_J6

// Control del pin G0
//
#define DISPLAY_G0_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G0_PIN            HAL_GPIO_PIN_7
#define DISPLAY_G0_AF             HAL_GPIO_AF_14
#define GPIO_G0_TYPE              htl::GPIO_J7

// Control del pin G1
//
#define DISPLAY_G1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G1_PIN            HAL_GPIO_PIN_8
#define DISPLAY_G1_AF             HAL_GPIO_AF_14
#define GPIO_G1_TYPE              htl::GPIO_J8

// Control del pin G2
//
#define DISPLAY_G2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G2_PIN            HAL_GPIO_PIN_9
#define DISPLAY_G2_AF             HAL_GPIO_AF_14
#define GPIO_G2_TYPE              htl::GPIO_J9

// Control del pin G3
//
#define DISPLAY_G3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G3_PIN            HAL_GPIO_PIN_10
#define DISPLAY_G3_AF             HAL_GPIO_AF_14
#define GPIO_G3_TYPE              htl::GPIO_J10

// Control del pin G4
//
#define DISPLAY_G4_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G4_PIN            HAL_GPIO_PIN_11
#define DISPLAY_G4_AF             HAL_GPIO_AF_14
#define GPIO_G4_TYPE              htl::GPIO_J11

// Control del pin G5
//
#define DISPLAY_G5_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G5_PIN            HAL_GPIO_PIN_0
#define DISPLAY_G5_AF             HAL_GPIO_AF_14
#define GPIO_G5_TYPE              htl::GPIO_K0

// Control del pin G6
//
#define DISPLAY_G6_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G6_PIN            HAL_GPIO_PIN_1
#define DISPLAY_G6_AF             HAL_GPIO_AF_14
#define GPIO_G6_TYPE              htl::GPIO_K1

// Control del pin G7
//
#define DISPLAY_G7_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G7_PIN            HAL_GPIO_PIN_2
#define DISPLAY_G7_AF             HAL_GPIO_AF_14
#define GPIO_G7_TYPE              htl::GPIO_K2

// Control del pin B0
//
#define DISPLAY_B0_PORT           HAL_GPIO_PORT_E
#define DISPLAY_B0_PIN            HAL_GPIO_PIN_4
#define DISPLAY_B0_AF             HAL_GPIO_AF_14
#define GPIO_B0_TYPE              htl::GPIO_E4

// Control del pin B1
//
#define DISPLAY_B1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B1_PIN            HAL_GPIO_PIN_13
#define DISPLAY_B1_AF             HAL_GPIO_AF_14
#define GPIO_B1_TYPE              htl::GPIO_J13

// Control del pin B2
//
#define DISPLAY_B2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B2_PIN            HAL_GPIO_PIN_14
#define DISPLAY_B2_AF             HAL_GPIO_AF_14
#define GPIO_B2_TYPE              htl::GPIO_J14

// Control del pin B3
//
#define DISPLAY_B3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B3_PIN            HAL_GPIO_PIN_15
#define DISPLAY_B3_AF             HAL_GPIO_AF_14
#define GPIO_B3_TYPE              htl::GPIO_J15

// Control del pin B4
//
#define DISPLAY_B4_PORT           HAL_GPIO_PORT_G
#define DISPLAY_B4_PIN            HAL_GPIO_PIN_12
#define DISPLAY_B4_AF             HAL_GPIO_AF_9
#define GPIO_B4_TYPE              htl::GPIO_G12

// Control del pin B5
//
#define DISPLAY_B5_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B5_PIN            HAL_GPIO_PIN_4
#define DISPLAY_B5_AF             HAL_GPIO_AF_14
#define GPIO_B5_TYPE              htl::GPIO_K4

// Control del pin B6
//
#define DISPLAY_B6_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B6_PIN            HAL_GPIO_PIN_5
#define DISPLAY_B6_AF             HAL_GPIO_AF_14
#define GPIO_B6_TYPE              htl::GPIO_K5

// Control del pin B7
//
#define DISPLAY_B7_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B7_PIN            HAL_GPIO_PIN_6
#define DISPLAY_B7_AF             HAL_GPIO_AF_14
#define GPIO_B7_TYPE              htl::GPIO_K6

#endif // USE_DISPLAY
*/

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

#ifdef USE_TOUCHPAD
#define EXIST_TOUCHPAD

#define TOUCHPAD_DRV_FT5336

#define TOUCHPAD_MAX_POINTS         5

//#define TOUCHPAD_I2C_ADDR           0x70

//#define TOUCHPAD_PAD_WIDTH          480
//#define TOUCHPAD_PAD_HEIGHT         272

// Control del pin SCL
//
#define TOUCHPAD_SCL_PORT           HAL_GPIO_PORT_H
#define TOUCHPAD_SCL_PIN            HAL_GPIO_PIN_7
#define TOUCHPAD_SCL_AF		        HAL_GPIO_AF_4
#define TOUCHPAD_SCL_TYPE           htl::GPIO_H7

// Control del pin SDA
//
#define TOUCHPAD_SDA_PORT           HAL_GPIO_PORT_H
#define TOUCHPAD_SDA_PIN            HAL_GPIO_PIN_8
#define TOUCHPAD_SDA_AF             HAL_GPIO_AF_4
#define TOUCHPAD_SDA_TYPE           htl::GPIO_H8

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

// Modul I2C de comunicacions
#define TOUCHPAD_I2C_CHANNEL        HAL_I2C_CHANNEL_3
#define TOUCHPAD_I2C_TYPE           htl::I2C_3


#endif // USE_TOUCHPAD


#endif // __board_SMT32F746G_DISCO__
