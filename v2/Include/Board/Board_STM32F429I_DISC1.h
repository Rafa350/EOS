#ifndef __board_SMT32F429I_DISC1__
#define __board_SMT32F429I_DISC1__


// ----------------------------------------------------------------------
//
//     Hardware: STM32F429I-DISC1
//
// ----------------------------------------------------------------------


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ           80000000
#define CLOCK_PERIPHERICAL_HZ     (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors LED
// -----------------------------------------------------------------------

#define LED_LED1_PORT             HAL_GPIO_PORT_G
#define LED_LED1_PIN              HAL_GPIO_PIN_13

#define LED_LED2_PORT             HAL_GPIO_PORT_G
#define LED_LED2_PIN              HAL_GPIO_PIN_14


// -----------------------------------------------------------------------
// Switches
// -----------------------------------------------------------------------

#define SW_SW1_PORT               HAL_GPIO_PORT_A
#define SW_SW1_PIN                HAL_GPIO_PIN_0


// -----------------------------------------------------------------------
// USB FS (OTG1)
// -----------------------------------------------------------------------

#define USB_USB0_DP_PORT          HAL_GPIO_PORT_A
#define USB_USB0_DP_PIN           HAL_GPIO_PIN_12
#define USB_USB0_DP_AF            HAL_GPIO_AF10_OGT1_FS

#define USB_USB0_DM_PORT          HAL_GPIO_PORT_A
#define USB_USB0_DM_PIN           HAL_GPIO_PIN_11
#define USB_USB0_DM_AF            HAL_GPIO_AF10_OGT1_FS

#define USB_USB0_ID_PORT          HAL_GPIO_PORT_A
#define USB_USB0_ID_PIN           HAL_GPIO_PIN_10
#define USB_USB0_ID_AF            HAL_GPIO_AF10_OGT1_FS


// -----------------------------------------------------------------------
// USB HS (OTG2 Full speed mode)
// -----------------------------------------------------------------------

#define USB_USB1_DP_PORT          HAL_GPIO_PORT_B
#define USB_USB1_DP_PIN           HAL_GPIO_PIN_15
#define USB_USB1_DP_AF            HAL_GPIO_AF12_OGT2_FS

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


// -----------------------------------------------------------------------
// USB HS (OTG2 External PHY high speed mode)
// -----------------------------------------------------------------------


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
// Parametres de configuracio controlador de display ILI9341
// -----------------------------------------------------------------------

// Opcions de codificacio del color
#define ILI9341_COLORMODE_565

// Opcions de comunicacio amb el controlodor ILI9341
//
#define ILI9341_IO_TYPE_SPI

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
#define ILI9341_CLK_AF       HAL_GPIO_AF5_SPI5

// Control del pin MOSI (CPU to Controller)
//
#define ILI9341_MOSI_PORT    HAL_GPIO_PORT_F
#define ILI9341_MOSI_PIN     HAL_GPIO_PIN_9
#define ILI9341_MOSI_AF      HAL_GPIO_AF5_SPI5

// Control del pin MISO (Controller to CPU)
//
#define ILI9341_MISO_PORT    HAL_GPIO_PORT_F
#define ILI9341_MISO_PIN     HAL_GPIO_PIN_8
#define ILI9341_MISO_AF      HAL_GPIO_AF5_SPI5

// Modul SPI a utilitzar
//
#define ILI9341_SPI_ID       HAL_SPI_ID_5


// -----------------------------------------------------------------------
// Parametres de configuracio del controlador de display ILI9341LTDC
// -----------------------------------------------------------------------

// Punter a la memoria de video
//
#define ILI9341LTDC_VRAM          ((uint32_t)0xD0000000)

// Format de color del controlador
//
#define ILI9341LTDC_COLORMODE_565

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
#define ILI9341LTDC_CLK_AF        HAL_GPIO_AF5_SPI5

// Control del pin MOSI (CPU to controller)
//
#define ILI9341LTDC_MOSI_PORT     HAL_GPIO_PORT_F
#define ILI9341LTDC_MOSI_PIN      HAL_GPIO_PIN_9
#define ILI9341LTDC_MOSI_AF       HAL_GPIO_AF5_SPI5

// Control del pin MISO (Controller to CPU)
//
#define ILI9341LTDC_MISO_PORT     HAL_GPIO_PORT_F
#define ILI9341LTDC_MISO_PIN      HAL_GPIO_PIN_8
#define ILI9341LTDC_MISO_AF       HAL_GPIO_AF5_SPI5

// Control del pin HSYNC (Horizontal sync)
//
#define ILI9341LTDC_HSYNC_PORT    HAL_GPIO_PORT_C
#define ILI9341LTDC_HSYNC_PIN     HAL_GPIO_PIN_6
#define ILI9341LTDC_HSYNC_AF      HAL_GPIO_AF14_LTDC

// Control del pin VSYNC (Vertical sync)
//
#define ILI9341LTDC_VSYNC_PORT    HAL_GPIO_PORT_A
#define ILI9341LTDC_VSYNC_PIN     HAL_GPIO_PIN_4
#define ILI9341LTDC_VSYNC_AF      HAL_GPIO_AF14_LTDC

// Control del pin DE (Display enable)
//
#define ILI9341LTDC_DE_PORT       HAL_GPIO_PORT_F
#define ILI9341LTDC_DE_PIN        HAL_GPIO_PIN_10
#define ILI9341LTDC_DE_AF         HAL_GPIO_AF14_LTDC

// Control del pin DOTCLK (Dot clock)
//
#define ILI9341LTDC_DOTCLK_PORT   HAL_GPIO_PORT_G
#define ILI9341LTDC_DOTCLK_PIN    HAL_GPIO_PIN_7
#define ILI9341LTDC_DOTCLK_AF     HAL_GPIO_AF14_LTDC

// Control del pin R2
//
#define ILI9341LTDC_R2_PORT       HAL_GPIO_PORT_C
#define ILI9341LTDC_R2_PIN        HAL_GPIO_PIN_10
#define ILI9341LTDC_R2_AF         HAL_GPIO_AF14_LTDC

// Control del pin R3
//
#define ILI9341LTDC_R3_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_R3_PIN        HAL_GPIO_PIN_0
#define ILI9341LTDC_R3_AF         HAL_GPIO_AF9_LTDC

// Control del pin R4
//
#define ILI9341LTDC_R4_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_R4_PIN        HAL_GPIO_PIN_11
#define ILI9341LTDC_R4_AF         HAL_GPIO_AF14_LTDC

// Control del pin R5
//
#define ILI9341LTDC_R5_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_R5_PIN        HAL_GPIO_PIN_12
#define ILI9341LTDC_R5_AF         HAL_GPIO_AF14_LTDC

// Control del pin R6
//
#define ILI9341LTDC_R6_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_R6_PIN        HAL_GPIO_PIN_1
#define ILI9341LTDC_R6_AF         HAL_GPIO_AF9_LTDC

// Control del pin R7
//
#define ILI9341LTDC_R7_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_R7_PIN        HAL_GPIO_PIN_6
#define ILI9341LTDC_R7_AF         HAL_GPIO_AF14_LTDC

// Control del pin G2
//
#define ILI9341LTDC_G2_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_G2_PIN        HAL_GPIO_PIN_6
#define ILI9341LTDC_G2_AF         HAL_GPIO_AF14_LTDC

// Control del pin G3
//
#define ILI9341LTDC_G3_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_G3_PIN        HAL_GPIO_PIN_10
#define ILI9341LTDC_G3_AF         HAL_GPIO_AF9_LTDC

// Control del pin G4
//
#define ILI9341LTDC_G4_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_G4_PIN        HAL_GPIO_PIN_10
#define ILI9341LTDC_G4_AF         HAL_GPIO_AF14_LTDC

// Control del pin G5
//
#define ILI9341LTDC_G5_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_G5_PIN        HAL_GPIO_PIN_11
#define ILI9341LTDC_G5_AF         HAL_GPIO_AF14_LTDC

// Control del pin G6
//
#define ILI9341LTDC_G6_PORT       HAL_GPIO_PORT_C
#define ILI9341LTDC_G6_PIN        HAL_GPIO_PIN_7
#define ILI9341LTDC_G6_AF         HAL_GPIO_AF14_LTDC

// Control del pin G7
//
#define ILI9341LTDC_G7_PORT       HAL_GPIO_PORT_D
#define ILI9341LTDC_G7_PIN        HAL_GPIO_PIN_3
#define ILI9341LTDC_G7_AF         HAL_GPIO_AF14_LTDC

// Control del pin B2
//
#define ILI9341LTDC_B2_PORT       HAL_GPIO_PORT_D
#define ILI9341LTDC_B2_PIN        HAL_GPIO_PIN_6
#define ILI9341LTDC_B2_AF         HAL_GPIO_AF14_LTDC

// Control del pin B3
//
#define ILI9341LTDC_B3_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_B3_PIN        HAL_GPIO_PIN_11
#define ILI9341LTDC_B3_AF         HAL_GPIO_AF14_LTDC

// Control del pin B4
//
#define ILI9341LTDC_B4_PORT       HAL_GPIO_PORT_G
#define ILI9341LTDC_B4_PIN        HAL_GPIO_PIN_12
#define ILI9341LTDC_B4_AF         HAL_GPIO_AF9_LTDC

// Control del pin B5
//
#define ILI9341LTDC_B5_PORT       HAL_GPIO_PORT_A
#define ILI9341LTDC_B5_PIN        HAL_GPIO_PIN_3
#define ILI9341LTDC_B5_AF         HAL_GPIO_AF14_LTDC

// Control del pin B6
//
#define ILI9341LTDC_B6_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_B6_PIN        HAL_GPIO_PIN_8
#define ILI9341LTDC_B6_AF         HAL_GPIO_AF14_LTDC

// Control del pin B7
//
#define ILI9341LTDC_B7_PORT       HAL_GPIO_PORT_B
#define ILI9341LTDC_B7_PIN        HAL_GPIO_PIN_9
#define ILI9341LTDC_B7_AF         HAL_GPIO_AF14_LTDC

// Control del modul SPI
//
#define ILI9341LTDC_SPI_ID        HAL_SPI_ID_5


#endif // __board_SMT32F429I_DISC1__

