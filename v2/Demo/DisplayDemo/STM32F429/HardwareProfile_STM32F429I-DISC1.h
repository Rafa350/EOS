#ifndef __HARDWARE_PROFILE_SMT32F429_DISC1_H
#define __HARDWARE_PROFILE_SMT32F429_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LEDS
// -----------------------------------------------------------------------

#define LEDS_LD1_PORT        HAL_GPIO_PORT_G
#define LEDS_LD1_PIN         HAL_GPIO_PIN_13

#define LEDS_LD2_PORT        HAL_GPIO_PORT_G
#define LEDS_LD2_PIN         HAL_GPIO_PIN_14


// -----------------------------------------------------------------------
// Controlador del display ILI9341
// -----------------------------------------------------------------------

// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt

#define DISPLAY_STM32F429I_DISC1
#define DISPLAY_COLOR_565

#define ILI9341_COLORMODE_565
//#define ILI9341_COLORMODE_666

#define ILI9341_INTERFACE_MODE_HAL_GPIO
//#define ILI9341_INTERFACE_MODE_PIC32_GPIO
//#define ILI9341_INTERFACE_MODE_PIC32_PMP
//#define ILI9341_INTERFACE_MODE_STM32_GPIO

//#define ILI9341_INTERFACE_TYPE_PARALEL_8BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_9BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_16BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_18BIT
#define ILI9341_INTERFACE_TYPE_SERIAL_8BIT

#define ILI9341_INTERFACE_WRITEONLY


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

// Control del pin MOSI (Serial data output to controller)
//
#define ILI9341_MOSI_PORT    HAL_GPIO_PORT_F
#define ILI9341_MOSI_PIN     HAL_GPIO_PIN_9


// -----------------------------------------------------------------------
// Controlador de display ILI9341LTDC
// -----------------------------------------------------------------------

// Control del pin CS (Chip select)
//
#define ILI9341LTDC_CS_PORT      HAL_GPIO_PORT_C
#define ILI9341LTDC_CS_PIN       HAL_GPIO_PIN_2

// Control del pin RS (Register select)
//
#define ILI9341LTDC_RS_PORT      HAL_GPIO_PORT_D
#define ILI9341LTDC_RS_PIN       HAL_GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define ILI9341LTDC_CLK_PORT     HAL_GPIO_PORT_F
#define ILI9341LTDC_CLK_PIN      HAL_GPIO_PIN_7

// Control del pin MOSI (Serial data output to controller)
//
#define ILI9341LTDC_MOSI_PORT    HAL_GPIO_PORT_F
#define ILI9341LTDC_MOSI_PIN     HAL_GPIO_PIN_9

// Control del pin HSYNC (Horizontal sync)
//
#define ILI9341LTDC_HSYNC_PORT   HAL_GPIO_PORT_C
#define ILI9341LTDC_HSYNC_PIN    HAL_GPIO_PIN_6

// Control del pin VSYNC (Vertical sync)
//
#define ILI9341LTDC_VSYNC_PORT   HAL_GPIO_PORT_A
#define ILI9341LTDC_VSYNC_PIN    HAL_GPIO_PIN_4

// Control del pin DOTCLK (Dot clock)
//
#define ILI9341LTDC_DOTCLK_PORT  HAL_GPIO_PORT_G
#define ILI9341LTDC_DOTCLK_PIN   HAL_GPIO_PIN_7

// Control el pin R2
//
#define ILI9341LTDC_R2_PORT      HAL_GPIO_PORT_C
#define ILI9341LTDC_R2_PIN       HAL_GPIO_PIN_10

// Control el pin R3
//
#define ILI9341LTDC_R3_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_R3_PIN       HAL_GPIO_PIN_0

// Control el pin R4
//
#define ILI9341LTDC_R4_PORT      HAL_GPIO_PORT_A
#define ILI9341LTDC_R4_PIN       HAL_GPIO_PIN_11

// Control el pin R5
//
#define ILI9341LTDC_R5_PORT      HAL_GPIO_PORT_A
#define ILI9341LTDC_R5_PIN       HAL_GPIO_PIN_12

// Control el pin R6
//
#define ILI9341LTDC_R6_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_R6_PIN       HAL_GPIO_PIN_1

// Control el pin R7
//
#define ILI9341LTDC_R7_PORT      HAL_GPIO_PORT_G
#define ILI9341LTDC_R7_PIN       HAL_GPIO_PIN_6

// Control el pin G2
//
#define ILI9341LTDC_G2_PORT      HAL_GPIO_PORT_A
#define ILI9341LTDC_G2_PIN       HAL_GPIO_PIN_6

// Control el pin G3
//
#define ILI9341LTDC_G3_PORT      HAL_GPIO_PORT_G
#define ILI9341LTDC_G3_PIN       HAL_GPIO_PIN_10

// Control el pin G4
//
#define ILI9341LTDC_G4_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_G4_PIN       HAL_GPIO_PIN_10

// Control el pin G5
//
#define ILI9341LTDC_G5_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_G5_PIN       HAL_GPIO_PIN_11

// Control el pin G6
//
#define ILI9341LTDC_G6_PORT      HAL_GPIO_PORT_C
#define ILI9341LTDC_G6_PIN       HAL_GPIO_PIN_7

// Control el pin G7
//
#define ILI9341LTDC_G7_PORT      HAL_GPIO_PORT_D
#define ILI9341LTDC_G7_PIN       HAL_GPIO_PIN_3

// Control el pin B2
//
#define ILI9341LTDC_B2_PORT      HAL_GPIO_PORT_D
#define ILI9341LTDC_B2_PIN       HAL_GPIO_PIN_6

// Control el pin B3
//
#define ILI9341LTDC_B3_PORT      HAL_GPIO_PORT_G
#define ILI9341LTDC_B3_PIN       HAL_GPIO_PIN_11

// Control el pin B4
//
#define ILI9341LTDC_B4_PORT      HAL_GPIO_PORT_G
#define ILI9341LTDC_B4_PIN       HAL_GPIO_PIN_12

// Control el pin B5
//
#define ILI9341LTDC_B5_PORT      HAL_GPIO_PORT_A
#define ILI9341LTDC_B5_PIN       HAL_GPIO_PIN_3

// Control el pin B6
//
#define ILI9341LTDC_B6_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_B6_PIN       HAL_GPIO_PIN_8

// Control el pin B7
//
#define ILI9341LTDC_B7_PORT      HAL_GPIO_PORT_B
#define ILI9341LTDC_B7_PIN       HAL_GPIO_PIN_9


#endif
