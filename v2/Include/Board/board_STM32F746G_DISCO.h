#ifndef __board_SMT32F746G_DISCO__
#define __board_SMT32F746G_DISCO__


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors LED
// -----------------------------------------------------------------------

#ifdef USE_LEDS_LED1
#define EXIST_LEDS_LED1

#define LED_LED1_PORT             HAL_GPIO_PORT_I
#define LED_LED1_PIN              HAL_GPIO_PIN_1

#endif // USE_LED_LED1


// -----------------------------------------------------------------------
// Display grafic
// -----------------------------------------------------------------------

#ifdef USE_DISPLAY
#define EXIST_DISPLAY

// Tamany de la pantalla
//
#define DISPLAY_IMAGE_WIDTH       480  // Amplada en pixels
#define DISPLAY_IMAGE_HEIGHT      272  // Alçada en pixels

// Tipus de codificacio de color
//
#define DISPLAY_COLOR_RGB565           // Format de color

// Adressa de la memoria de video
//
#define DISPLAY_VRAM_ADDR         0xC0000000

// Controlador
//
#define DISPLAY_DRV_RGBLTDC            // RK043FN48H


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
#define DISPLAY_FDIV              5    // Divisor de fequencia

// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt

// Control del pin DISPLAY_ENABLE
//
#define DISPLAY_LCDE_PORT         HAL_GPIO_PORT_I
#define DISPLAY_LCDE_PIN	      HAL_GPIO_PIN_12

// Control del pin BACKLIGHT_ENABLE
//
#define DISPLAY_BKE_PORT          HAL_GPIO_PORT_K
#define DISPLAY_BKE_PIN           HAL_GPIO_PIN_3

// Control del pin HSYNC (Horizontal sync)
//
#define DISPLAY_HSYNC_PORT        HAL_GPIO_PORT_I
#define DISPLAY_HSYNC_PIN         HAL_GPIO_PIN_10
#define DISPLAY_HSYNC_AF          HAL_GPIO_AF14_LTDC

// Control del pin VSYNC (Vertical sync)
//
#define DISPLAY_VSYNC_PORT        HAL_GPIO_PORT_I
#define DISPLAY_VSYNC_PIN         HAL_GPIO_PIN_9
#define DISPLAY_VSYNC_AF          HAL_GPIO_AF14_LTDC

// Control del pin DE (Display enable)
//
#define DISPLAY_DE_PORT           HAL_GPIO_PORT_K
#define DISPLAY_DE_PIN            HAL_GPIO_PIN_7
#define DISPLAY_DE_AF             HAL_GPIO_AF14_LTDC

// Control del pin DOTCLK (Dot clock)
//
#define DISPLAY_DOTCLK_PORT       HAL_GPIO_PORT_I
#define DISPLAY_DOTCLK_PIN        HAL_GPIO_PIN_14
#define DISPLAY_DOTCLK_AF         HAL_GPIO_AF14_LTDC

// Control del pin R0
//
#define DISPLAY_R0_PORT           HAL_GPIO_PORT_I
#define DISPLAY_R0_PIN            HAL_GPIO_PIN_15
#define DISPLAY_R0_AF             HAL_GPIO_AF14_LTDC

// Control del pin R1
//
#define DISPLAY_R1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R1_PIN            HAL_GPIO_PIN_0
#define DISPLAY_R1_AF             HAL_GPIO_AF14_LTDC

// Control del pin R2
//
#define DISPLAY_R2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R2_PIN            HAL_GPIO_PIN_1
#define DISPLAY_R2_AF             HAL_GPIO_AF14_LTDC

// Control del pin R3
//
#define DISPLAY_R3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R3_PIN            HAL_GPIO_PIN_2
#define DISPLAY_R3_AF             HAL_GPIO_AF14_LTDC

// Control del pin R4
//
#define DISPLAY_R4_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R4_PIN            HAL_GPIO_PIN_3
#define DISPLAY_R4_AF             HAL_GPIO_AF14_LTDC

// Control del pin R5
//
#define DISPLAY_R5_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R5_PIN            HAL_GPIO_PIN_4
#define DISPLAY_R5_AF             HAL_GPIO_AF14_LTDC

// Control del pin R6
//
#define DISPLAY_R6_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R6_PIN            HAL_GPIO_PIN_5
#define DISPLAY_R6_AF             HAL_GPIO_AF14_LTDC

// Control del pin R7
//
#define DISPLAY_R7_PORT           HAL_GPIO_PORT_J
#define DISPLAY_R7_PIN            HAL_GPIO_PIN_6
#define DISPLAY_R7_AF             HAL_GPIO_AF14_LTDC

// Control del pin G0
//
#define DISPLAY_G0_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G0_PIN            HAL_GPIO_PIN_7
#define DISPLAY_G0_AF             HAL_GPIO_AF14_LTDC

// Control del pin G1
//
#define DISPLAY_G1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G1_PIN            HAL_GPIO_PIN_8
#define DISPLAY_G1_AF             HAL_GPIO_AF14_LTDC

// Control del pin G2
//
#define DISPLAY_G2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G2_PIN            HAL_GPIO_PIN_9
#define DISPLAY_G2_AF             HAL_GPIO_AF14_LTDC

// Control del pin G3
//
#define DISPLAY_G3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G3_PIN            HAL_GPIO_PIN_10
#define DISPLAY_G3_AF             HAL_GPIO_AF14_LTDC

// Control del pin G4
//
#define DISPLAY_G4_PORT           HAL_GPIO_PORT_J
#define DISPLAY_G4_PIN            HAL_GPIO_PIN_11
#define DISPLAY_G4_AF             HAL_GPIO_AF14_LTDC

// Control del pin G5
//
#define DISPLAY_G5_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G5_PIN            HAL_GPIO_PIN_0
#define DISPLAY_G5_AF             HAL_GPIO_AF14_LTDC

// Control del pin G6
//
#define DISPLAY_G6_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G6_PIN            HAL_GPIO_PIN_1
#define DISPLAY_G6_AF             HAL_GPIO_AF14_LTDC

// Control del pin G7
//
#define DISPLAY_G7_PORT           HAL_GPIO_PORT_K
#define DISPLAY_G7_PIN            HAL_GPIO_PIN_2
#define DISPLAY_G7_AF             HAL_GPIO_AF14_LTDC

// Control del pin B0
//
#define DISPLAY_B0_PORT           HAL_GPIO_PORT_E
#define DISPLAY_B0_PIN            HAL_GPIO_PIN_4
#define DISPLAY_B0_AF             HAL_GPIO_AF14_LTDC

// Control del pin B1
//
#define DISPLAY_B1_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B1_PIN            HAL_GPIO_PIN_13
#define DISPLAY_B1_AF             HAL_GPIO_AF14_LTDC

// Control del pin B2
//
#define DISPLAY_B2_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B2_PIN            HAL_GPIO_PIN_14
#define DISPLAY_B2_AF             HAL_GPIO_AF14_LTDC

// Control del pin B3
//
#define DISPLAY_B3_PORT           HAL_GPIO_PORT_J
#define DISPLAY_B3_PIN            HAL_GPIO_PIN_15
#define DISPLAY_B3_AF             HAL_GPIO_AF14_LTDC

// Control del pin B4
//
#define DISPLAY_B4_PORT           HAL_GPIO_PORT_G
#define DISPLAY_B4_PIN            HAL_GPIO_PIN_12
#define DISPLAY_B4_AF             HAL_GPIO_AF9_LTDC

// Control del pin B5
//
#define DISPLAY_B5_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B5_PIN            HAL_GPIO_PIN_5
#define DISPLAY_B5_AF             HAL_GPIO_AF14_LTDC

// Control del pin B6
//
#define DISPLAY_B6_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B6_PIN            HAL_GPIO_PIN_6
#define DISPLAY_B6_AF             HAL_GPIO_AF14_LTDC

// Control del pin B7
//
#define DISPLAY_B7_PORT           HAL_GPIO_PORT_K
#define DISPLAY_B7_PIN            HAL_GPIO_PIN_7
#define DISPLAY_B7_AF             HAL_GPIO_AF14_LTDC

#endif // USE_DISPLAY


// -----------------------------------------------------------------------
// Controlador camara DCIM OV9655
// -----------------------------------------------------------------------

// Tamany de la imatge
//
#define CAMERA_IMAGE_WIDTH        0  // Seleccionable per software
#define CAMERA_IMAGE_HEIGHT       0  // Seleccionable per software

// Format de la imatge
//
#define CAMERA_FORMAT        RGB565

#define CAMERA_PIXCK_PORT         HAL_GPIO_PORT_A
#define CAMERA_PIXCK_PIN          HAL_GPIO_PIN_6
#define CAMERA_PIXCH_AF           HAL_GPIO_AF13_DCMI

#define CAMERA_HSYNC_PORT         HAL_GPIO_PORT_A
#define CAMERA_HSYNC_PIN          HAL_GPIO_PIN_4
#define CAMERA_HSYNC_AF           HAL_GPIO_AF13_DCMI

#define CAMERA_VSYNC_PORT         HAL_GPIO_PORT_G
#define CAMERA_VSYNC_PIN          HAL_GPIO_PIN_9
#define CAMERA_VSYNC_AF           HAL_GPIO_AF13_DCMI

#define CAMERA_D0_PORT            HAL_GPIO_PORT_H
#define CAMERA_D0_PIN             HAL_GPIO_PIN_9
#define CAMERA_D0_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D1_PORT            HAL_GPIO_PORT_H
#define CAMERA_D1_PIN             HAL_GPIO_PIN_10
#define CAMERA_D1_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D2_PORT            HAL_GPIO_PORT_H
#define CAMERA_D2_PIN             HAL_GPIO_PIN_11
#define CAMERA_D2_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D3_PORT            HAL_GPIO_PORT_H
#define CAMERA_D3_PIN             HAL_GPIO_PIN_12
#define CAMERA_D3_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D4_PORT            HAL_GPIO_PORT_H
#define CAMERA_D4_PIN             HAL_GPIO_PIN_14
#define CAMERA_D4_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D5_PORT            HAL_GPIO_PORT_D
#define CAMERA_D5_PIN             HAL_GPIO_PIN_3
#define CAMERA_D5_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D6_PORT            HAL_GPIO_PORT_E
#define CAMERA_D6_PIN             HAL_GPIO_PIN_5
#define CAMERA_D6_AF              HAL_GPIO_AF13_DCMI

#define CAMERA_D7_PORT            HAL_GPIO_PORT_E
#define CAMERA_D7_PIN             HAL_GPIO_PIN_6
#define CAMERA_D7_AF              HAL_GPIO_AF13_DCMI


// -----------------------------------------------------------------------
// Controlador SD-IO
// -----------------------------------------------------------------------

#define SD_PRESENT_PORT           HAL_GPIO_PORT_C
#define SD_PRESENT_PIN            HAL_GPIO_PIN_13

#define SD_DMA_RX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_RX_STREAM          DMA2_Stream3
#define SD_DMA_RX_IRQ             DMA2_Stream3_IRQn

#define SD_DMA_TX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_TX_STREAM          DMA2_Stream6
#define SD_DMA_TX_IRQ             DMA2_Stream6_IRQn

#define SD_MODULE                 SDMMC1


// -----------------------------------------------------------------------
// Controlador de touchpad FT5336
// -----------------------------------------------------------------------

#ifdef USE_TOUCHPAD_FT5336

#define TOUCHPAD_MAX_POINTS         5

#define TOUCHPAD_I2C_ADDR           0x70

#define TOUCHPAD_PAD_WIDTH          480
#define TOUCHPAD_PAD_HEIGHT         270

// Control del pin SCL
//
#define TOUCHPAD_SCL_PORT           HAL_GPIO_PORT_H
#define TOUCHPAD_SCL_PIN            HAL_GPIO_PIN_7
#define TOUCHPAD_SCL_AF		      HAL_GPIO_AF4_I2C3

// Control del pin SDA
//
#define TOUCHPAD_SDA_PORT           HAL_GPIO_PORT_H
#define TOUCHPAD_SDA_PIN            HAL_GPIO_PIN_8
#define TOUCHPAD_SDA_AF             HAL_GPIO_AF4_I2C3

// Control del pin INT
//
//#define TOUCHPAD_INT_PORT           HAL_GPIO_PORT_I
//#define TOUCHPAD_INT_PIN            HAL_GPIO_PIN_13

// IRQ asignada al pin INT
//#define TOUCHPAD_IRQ                EXTI15_10_IRQn

// Modul I2C de comunicacions
#define TOUCHPAD_I2C_MODULE         HAL_I2C_ID_3

#endif // USE_TOUCHPAD_FT5336


#endif // __board_SMT32F746G_DISCO__
