#ifndef __board_SMT32F746G_DISC__
#define __board_SMT32F746G_DISC__


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors lED
// -----------------------------------------------------------------------

#define LED_LED1_PORT             HAL_GPIO_PORT_I
#define LED_LED1_PIN              HAL_GPIO_PIN_1


// -----------------------------------------------------------------------
// Display grafic RK043FN48H
// -----------------------------------------------------------------------

// Parametres de la pantalla
//
#define  RGBDIRECT_SCREEN_WIDTH   480  // LCD PIXEL WIDTH
#define  RGBDIRECT_SCREEN_HEIGHT  272  // LCD PIXEL HEIGHT

// Parametres de temporitzacio i sincronitzacio
//
#define  RGBDIRECT_HSYNC          41   // Horizontal synchronization
#define  RGBDIRECT_HBP            13   // Horizontal back porch
#define  RGBDIRECT_HFP            32   // Horizontal front porch
#define  RGBDIRECT_VSYNC          10   // Vertical synchronization
#define  RGBDIRECT_VBP            2    // Vertical back porch
#define  RGBDIRECT_VFP            2    // Vertical front porch


// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt

// Tipus de codificacio de color
//
#define DISPLAY_COLOR_565


// -----------------------------------------------------------------------
// Controlador del display RGBDirect
// -----------------------------------------------------------------------

// Punter a la memoria de video
//
#define RGBDIRECT_VRAM            ((uint32_t)0xC0000000)

// Format de color del controlador
//
#define RGBDIRECT_COLORMODE_565

// Control del pin DISPLAY_ENABLE
//
#define RGBDIRECT_LCDE_PORT       HAL_GPIO_PORT_I
#define RGBDIRECT_LCDE_PIN	      HAL_GPIO_PIN_12

// Control del pin BACKLIGHT_ENABLE
#define RGBDIRECT_BKE_PORT        HAL_GPIO_PORT_K
#define RGBDIRECT_BKE_PIN         HAL_GPIO_PIN_3


// Control del pin HSYNC (Horizontal sync)
//
#define RGBDIRECT_HSYNC_PORT      HAL_GPIO_PORT_I
#define RGBDIRECT_HSYNC_PIN       HAL_GPIO_PIN_10
#define RGBDIRECT_HSYNC_AF        HAL_GPIO_AF14_LTDC

// Control del pin VSYNC (Vertical sync)
//
#define RGBDIRECT_VSYNC_PORT      HAL_GPIO_PORT_I
#define RGBDIRECT_VSYNC_PIN       HAL_GPIO_PIN_9
#define RGBDIRECT_VSYNC_AF        HAL_GPIO_AF14_LTDC

// Control del pin DE (Display enable)
//
#define RGBDIRECT_DE_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_DE_PIN          HAL_GPIO_PIN_7
#define RGBDIRECT_DE_AF           HAL_GPIO_AF14_LTDC

// Control del pin DOTCLK (Dot clock)
//
#define RGBDIRECT_DOTCLK_PORT     HAL_GPIO_PORT_I
#define RGBDIRECT_DOTCLK_PIN      HAL_GPIO_PIN_14
#define RGBDIRECT_DOTCLK_AF       HAL_GPIO_AF14_LTDC

// Control del pin R0
//
#define RGBDIRECT_R0_PORT         HAL_GPIO_PORT_I
#define RGBDIRECT_R0_PIN          HAL_GPIO_PIN_15
#define RGBDIRECT_R0_AF           HAL_GPIO_AF14_LTDC

// Control del pin R1
//
#define RGBDIRECT_R1_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R1_PIN          HAL_GPIO_PIN_0
#define RGBDIRECT_R1_AF           HAL_GPIO_AF14_LTDC

// Control del pin R2
//
#define RGBDIRECT_R2_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R2_PIN          HAL_GPIO_PIN_1
#define RGBDIRECT_R2_AF           HAL_GPIO_AF14_LTDC

// Control del pin R3
//
#define RGBDIRECT_R3_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R3_PIN          HAL_GPIO_PIN_2
#define RGBDIRECT_R3_AF           HAL_GPIO_AF14_LTDC

// Control del pin R4
//
#define RGBDIRECT_R4_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R4_PIN          HAL_GPIO_PIN_3
#define RGBDIRECT_R4_AF           HAL_GPIO_AF14_LTDC

// Control del pin R5
//
#define RGBDIRECT_R5_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R5_PIN          HAL_GPIO_PIN_4
#define RGBDIRECT_R5_AF           HAL_GPIO_AF14_LTDC

// Control del pin R6
//
#define RGBDIRECT_R6_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R6_PIN          HAL_GPIO_PIN_5
#define RGBDIRECT_R6_AF           HAL_GPIO_AF14_LTDC

// Control del pin R7
//
#define RGBDIRECT_R7_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_R7_PIN          HAL_GPIO_PIN_6
#define RGBDIRECT_R7_AF           HAL_GPIO_AF14_LTDC

// Control del pin G0
//
#define RGBDIRECT_G0_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_G0_PIN          HAL_GPIO_PIN_7
#define RGBDIRECT_G0_AF           HAL_GPIO_AF14_LTDC

// Control del pin G1
//
#define RGBDIRECT_G1_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_G1_PIN          HAL_GPIO_PIN_8
#define RGBDIRECT_G1_AF           HAL_GPIO_AF14_LTDC

// Control del pin G2
//
#define RGBDIRECT_G2_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_G2_PIN          HAL_GPIO_PIN_9
#define RGBDIRECT_G2_AF           HAL_GPIO_AF14_LTDC

// Control del pin G3
//
#define RGBDIRECT_G3_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_G3_PIN          HAL_GPIO_PIN_10
#define RGBDIRECT_G3_AF           HAL_GPIO_AF14_LTDC

// Control del pin G4
//
#define RGBDIRECT_G4_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_G4_PIN          HAL_GPIO_PIN_11
#define RGBDIRECT_G4_AF           HAL_GPIO_AF14_LTDC

// Control del pin G5
//
#define RGBDIRECT_G5_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_G5_PIN          HAL_GPIO_PIN_0
#define RGBDIRECT_G5_AF           HAL_GPIO_AF14_LTDC

// Control del pin G6
//
#define RGBDIRECT_G6_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_G6_PIN          HAL_GPIO_PIN_1
#define RGBDIRECT_G6_AF           HAL_GPIO_AF14_LTDC

// Control del pin G7
//
#define RGBDIRECT_G7_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_G7_PIN          HAL_GPIO_PIN_2
#define RGBDIRECT_G7_AF           HAL_GPIO_AF14_LTDC

// Control del pin B0
//
#define RGBDIRECT_B0_PORT         HAL_GPIO_PORT_E
#define RGBDIRECT_B0_PIN          HAL_GPIO_PIN_4
#define RGBDIRECT_B0_AF           HAL_GPIO_AF14_LTDC

// Control del pin B1
//
#define RGBDIRECT_B1_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_B1_PIN          HAL_GPIO_PIN_13
#define RGBDIRECT_B1_AF           HAL_GPIO_AF14_LTDC

// Control del pin B2
//
#define RGBDIRECT_B2_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_B2_PIN          HAL_GPIO_PIN_14
#define RGBDIRECT_B2_AF           HAL_GPIO_AF14_LTDC

// Control del pin B3
//
#define RGBDIRECT_B3_PORT         HAL_GPIO_PORT_J
#define RGBDIRECT_B3_PIN          HAL_GPIO_PIN_15
#define RGBDIRECT_B3_AF           HAL_GPIO_AF14_LTDC

// Control del pin B4
//
#define RGBDIRECT_B4_PORT         HAL_GPIO_PORT_G
#define RGBDIRECT_B4_PIN          HAL_GPIO_PIN_12
#define RGBDIRECT_B4_AF           HAL_GPIO_AF9_LTDC

// Control del pin B5
//
#define RGBDIRECT_B5_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_B5_PIN          HAL_GPIO_PIN_5
#define RGBDIRECT_B5_AF           HAL_GPIO_AF14_LTDC

// Control del pin B6
//
#define RGBDIRECT_B6_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_B6_PIN          HAL_GPIO_PIN_6
#define RGBDIRECT_B6_AF           HAL_GPIO_AF14_LTDC

// Control del pin B7
//
#define RGBDIRECT_B7_PORT         HAL_GPIO_PORT_K
#define RGBDIRECT_B7_PIN          HAL_GPIO_PIN_7
#define RGBDIRECT_B7_AF           HAL_GPIO_AF14_LTDC


// -----------------------------------------------------------------------
// Controlador de touchpad FT5336
// -----------------------------------------------------------------------

#define FT5336_I2C_ADDR           0x70

#define FT5336_PAD_WIDTH          480
#define FT5336_PAD_HEIGHT         270

// Control del pin SCL
//
#define FT5336_SCL_PORT           HAL_GPIO_PORT_H
#define FT5336_SCL_PIN            HAL_GPIO_PIN_7
#define FT5336_SCL_AF		      HAL_GPIO_AF4_I2C3

// Control del pin SDA
//
#define FT5336_SDA_PORT           HAL_GPIO_PORT_H
#define FT5336_SDA_PIN            HAL_GPIO_PIN_8
#define FT5336_SDA_AF             HAL_GPIO_AF4_I2C3

// Control del pin INT
//
//#define FT5336_INT_PORT           HAL_GPIO_PORT_I
//#define FT5336_INT_PIN            HAL_GPIO_PIN_13

// IRQ asignada al pin INT
//#define FT5336_IRQ                EXTI15_10_IRQn

// Modul I2C de comunicacions
#define FT5336_I2C_MODULE         HAL_I2C_ID_3

#endif // __board_SMT32F746G_DISC__

