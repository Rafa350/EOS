#ifndef __HARDWARE_PROFILE_SMT32F429_DISC1_H
#define __HARDWARE_PROFILE_SMT32F429_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors lED
// -----------------------------------------------------------------------

#define LEDS_LD1_PORT        HAL_GPIO_PORT_G
#define LEDS_LD1_PIN         HAL_GPIO_PIN_13

#define LEDS_LD2_PORT        HAL_GPIO_PORT_G
#define LEDS_LD2_PIN         HAL_GPIO_PIN_14


// -----------------------------------------------------------------------
// Display grafic
// -----------------------------------------------------------------------

// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt

// Tipus de pantalla
//
#define DISPLAY_STM32F429I_DISC1

// Tipus de codificacio de color
//
#define DISPLAY_COLOR_565


// -----------------------------------------------------------------------
// Controlador del display ILI9341
// -----------------------------------------------------------------------

#define ILI9341_COLORMODE_565
//#define ILI9341_COLORMODE_666

#define ILI9341_INTERFACE_WRITEONLY

//#define ILI9341_IO_TYPE_PIO8
//#define ILI9342_IO_SUBTYPE_PIO8_HAL
//#define ILI9342_IO_SUBTYPE_PIO8_DIRECT

//#define ILI9341_IO_TYPE_PMP8

#define ILI9341_IO_TYPE_SIO
#define ILI9341_IO_SUBTYPE_SIO_HAL
//#define ILI9341_IO_SUBTYPE_SIO_DIRECT

//#define ILI9341_IO_TYPE_SPI
//#define ILI9341_IO_SUBTYPE_SPI_HAL
//define ILI9341_IO_SUBTYPE_SPI_DIRECT


// Control del pin CS (Chip select)
//
#define ILI9341_CS_PORT      HAL_GPIO_PORT_C
#define ILI9341_CS_PIN       HAL_GPIO_PIN_2

// Control del pin RS (Register select)
//
#define ILI9341_RS_PORT      HAL_GPIO_PORT_D
#define ILI9341_RS_PIN       HAL_GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define ILI9341_CLK_PORT     HAL_GPIO_PORT_F
#define ILI9341_CLK_PIN      HAL_GPIO_PIN_7

// Control del pin MOSI (CPU to Controller)
//
#define ILI9341_MOSI_PORT    HAL_GPIO_PORT_F
#define ILI9341_MOSI_PIN     HAL_GPIO_PIN_9

// Control del pin MISO (Controller to CPU)
//
#define ILI9341_MISO_PORT    HAL_GPIO_PORT_F
#define ILI9341_MISO_PIN     HAL_GPIO_PIN_8

// Modul SPI a utilitzar
//
#define ILI9341_SPI_MODULE   HAL_SPI_MODULE_5
#define ILI9341_GPIO_AF_SPI  HAL_GPIO_AF_SPI5


// -----------------------------------------------------------------------
// Controlador de display ILI9341LTDC
// -----------------------------------------------------------------------

// Parametres del controlador
//
#define ILI9341LTDC_VRAM          0xD0000000

#define ILI9341LTDC_COLORMODE_565
//#define ILI9341LTDC_COLORMODE_666


// Control del pin CS (Chip select)
//
#define ILI9341LTDC_CS_PORT       HAL_GPIO_PORT_C
#define ILI9341LTDC_CS_PIN        HAL_GPIO_PIN_2

// Control del pin RS (Register select)
//
#define ILI9341LTDC_RS_PORT       HAL_GPIO_PORT_D
#define ILI9341LTDC_RS_PIN        HAL_GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define ILI9341LTDC_CLK_PORT      HAL_GPIO_PORT_F
#define ILI9341LTDC_CLK_PIN       HAL_GPIO_PIN_7

// Control del pin MOSI (CPU to controller)
//
#define ILI9341LTDC_MOSI_PORT     HAL_GPIO_PORT_F
#define ILI9341LTDC_MOSI_PIN      HAL_GPIO_PIN_9

// Control del pin MISO (Controller to CPU)
//
#define ILI9341LTDC_MISO_PORT     HAL_GPIO_PORT_F
#define ILI9341LTDC_MISO_PIN      HAL_GPIO_PIN_8

// Control del pin HSYNC (Horizontal sync)
//
#define ILI9341LTDC_HSYNC_PORT    HAL_GPIO_PORT_C
#define ILI9341LTDC_HSYNC_PIN     HAL_GPIO_PIN_6

// Control del pin VSYNC (Vertical sync)
//
#define ILI9341LTDC_VSYNC_PORT    HAL_GPIO_PORT_A
#define ILI9341LTDC_VSYNC_PIN     HAL_GPIO_PIN_4

// Control del pin DE (Display enable)
//
#define ILI9341LTDC_DE_PORT       HAL_GPIO_PORT_F
#define ILI9341LTDC_DE_PIN        HAL_GPIO_PIN_10

// Control del pin DOTCLK (Dot clock)
//
#define ILI9341LTDC_DOTCLK_PORT   HAL_GPIO_PORT_G
#define ILI9341LTDC_DOTCLK_PIN    HAL_GPIO_PIN_7

// Control del pin R2
//
#define ILI9341LTDC_R2_PORT       HAL_GPIO_PORT_C
#define ILI9341LTDC_R2_PIN        HAL_GPIO_PIN_10

// Control del pin R3
//
#define ILI9341LTDC_R3_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_R3_PIN        HAL_GPIO_PIN_0

// Control del pin R4
//
#define ILI9341LTDC_R4_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_R4_PIN        HAL_GPIO_PIN_11

// Control del pin R5
//
#define ILI9341LTDC_R5_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_R5_PIN        HAL_GPIO_PIN_12

// Control del pin R6
//
#define ILI9341LTDC_R6_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_R6_PIN        HAL_GPIO_PIN_1

// Control del pin R7
//
#define ILI9341LTDC_R7_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_R7_PIN        HAL_GPIO_PIN_6

// Control del pin G2
//
#define ILI9341LTDC_G2_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_G2_PIN        HAL_GPIO_PIN_6

// Control del pin G3
//
#define ILI9341LTDC_G3_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_G3_PIN        HAL_GPIO_PIN_10

// Control del pin G4
//
#define ILI9341LTDC_G4_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_G4_PIN        HAL_GPIO_PIN_10

// Control del pin G5
//
#define ILI9341LTDC_G5_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_G5_PIN        HAL_GPIO_PIN_11

// Control del pin G6
//
#define ILI9341LTDC_G6_PORT       HAL_GPIO_PORT_C
#define ILI9341LTDC_G6_PIN        HAL_GPIO_PIN_7

// Control del pin G7
//
#define ILI9341LTDC_G7_PORT       HAL_GPIO_PORT_D
#define ILI9341LTDC_G7_PIN        HAL_GPIO_PIN_3

// Control del pin B2
//
#define ILI9341LTDC_B2_PORT       HAL_GPIO_PORT_D
#define ILI9341LTDC_B2_PIN        HAL_GPIO_PIN_6

// Control del pin B3
//
#define ILI9341LTDC_B3_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_B3_PIN        HAL_GPIO_PIN_11

// Control del pin B4
//
#define ILI9341LTDC_B4_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_B4_PIN        HAL_GPIO_PIN_12

// Control del pin B5
//
#define ILI9341LTDC_B5_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_B5_PIN        HAL_GPIO_PIN_3

// Control del pin B6
//
#define ILI9341LTDC_B6_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_B6_PIN        HAL_GPIO_PIN_8

// Control del pin B7
//
#define ILI9341LTDC_B7_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_B7_PIN        HAL_GPIO_PIN_9

// Control del modul SPI
//
#define ILI9341LTDC_SPI_MODULE    HAL_SPI_MODULE_5
#define ILI9341LTDC_GPIO_AF_SPI   HAL_GPIO_AF_SPI5


#endif
