#ifndef __board_SMT32F429I_DISC1__
#define __board_SMT32F429I_DISC1__


// ----------------------------------------------------------------------
//
// Hardware: STM32F429I-DISC1
//
// ----------------------------------------------------------------------


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ           80000000
#define CLOCK_PERIPHERICAL_HZ     (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// Indicadors LED
// -----------------------------------------------------------------------

#ifdef USE_LEDS_LED1
#define EXIST_LEDS_LED1
#define LED_LED1_PORT             HAL_GPIO_PORT_G
#define LED_LED1_PIN              HAL_GPIO_PIN_13
#endif // USE_LEDS_LED1

#ifdef USE_LEDS_LED2
#define EXIST_LEDS_LED2
#define LED_LED2_PORT             HAL_GPIO_PORT_G
#define LED_LED2_PIN              HAL_GPIO_PIN_14
#endif // USE_LEDS_LED2


// -----------------------------------------------------------------------
// Switches
// -----------------------------------------------------------------------

#ifdef USE_SWITCHES_SW1
#define EXIST_SWITCHES_SW1
#define SW_SW1_PORT               HAL_GPIO_PORT_A
#define SW_SW1_PIN                HAL_GPIO_PIN_0
#endif // USE_SWITCHES_SW1


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
// Display grafic
// -----------------------------------------------------------------------

#if defined(USE_DISPLAY)
#define EXIST_DISPLAY


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

// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      240  // Amplada en pixels
#define DISPLAY_SCREEN_HEIGHT     320  // Alçada en pixels
#define DISPLAY_COLOR_RGB565           // Format de color RGB565

// Parametres del controlador
//
#define DISPLAY_DRV_ILI9341LTDC        // Driver


// -----------------------------------------------------------------------
// Display grafic ILI9341
// -----------------------------------------------------------------------

#ifdef DISPLAY_DRV_ILI9341

// Control del pin CS (Chip select)
//
#define DISPLAY_CS_PORT      HAL_GPIO_PORT_C
#define DISPLAY_CS_PIN       HAL_GPIO_PIN_2

// Control del pin RS (Register select)
//
#define DISPLAY_RS_PORT      HAL_GPIO_PORT_D
#define DISPLAY_RS_PIN       HAL_GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define DISPLAY_CLK_PORT     HAL_GPIO_PORT_F
#define DISPLAY_CLK_PIN      HAL_GPIO_PIN_7
#define DISPLAY_CLK_AF       HAL_GPIO_AF5_SPI5

// Control del pin MOSI (CPU to Controller)
//
#define DISPLAY_MOSI_PORT    HAL_GPIO_PORT_F
#define DISPLAY_MOSI_PIN     HAL_GPIO_PIN_9
#define DISPLAY_MOSI_AF      HAL_GPIO_AF5_SPI5

// Control del pin MISO (Controller to CPU)
//
#define DISPLAY_MISO_PORT    HAL_GPIO_PORT_F
#define DISPLAY_MISO_PIN     HAL_GPIO_PIN_8
#define DISPLAY_MISO_AF      HAL_GPIO_AF5_SPI5

// Modul SPI a utilitzar
//
#define DISPLAY_SPI_ID       HAL_SPI_ID_5

#endif // DISPLAY_DRV_ILI9341


// -----------------------------------------------------------------------
// Display grafic ILI9341LTDC
// -----------------------------------------------------------------------

#ifdef DISPLAY_DRV_ILI9341LTDC

// Adressa del buffer de video
//
#define DISPLAY_VRAM         0xD0000000

// Parametres fisics de la pantalla
//
#define DISPLAY_HSYNC        9    // Horizontal sync
#define DISPLAY_HBP          29   // Horizontal back Porch
#define DISPLAY_HFP          2    // Horizontal front Porch
#define DISPLAY_VSYNC        1    // Vertical sync
#define DISPLAY_VBP          3    // Vertical back Porch
#define DISPLAY_VFP          2    // Vertical front Porch
#define DISPLAY_HSPOL        0    // HSync active (0=LOW, 1=HIGHT)
#define DISPLAY_VSPOL        0    // VSync active (0=LOW, 1=HIGHT)
#define DISPLAY_DEPOL        0    // DE active (0=LOW, 1=HIGHT)
#define DISPLAY_PCPOL        0    // PC active (0=LOW, 1=HIGHT)

// Control del pin CS (Chip select)
//
#define DISPLAY_CS_PORT      HAL_GPIO_PORT_C
#define DISPLAY_CS_PIN       HAL_GPIO_PIN_2

// Control del pin RS (Register select)
//
#define DISPLAY_RS_PORT      HAL_GPIO_PORT_D
#define DISPLAY_RS_PIN       HAL_GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define DISPLAY_CLK_PORT     HAL_GPIO_PORT_F
#define DISPLAY_CLK_PIN      HAL_GPIO_PIN_7
#define DISPLAY_CLK_AF       HAL_GPIO_AF5_SPI5

// Control del pin MOSI (CPU to controller)
//
#define DISPLAY_MOSI_PORT    HAL_GPIO_PORT_F
#define DISPLAY_MOSI_PIN     HAL_GPIO_PIN_9
#define DISPLAY_MOSI_AF      HAL_GPIO_AF5_SPI5

// Control del pin MISO (Controller to CPU)
//
#define DISPLAY_MISO_PORT    HAL_GPIO_PORT_F
#define DISPLAY_MISO_PIN     HAL_GPIO_PIN_8
#define DISPLAY_MISO_AF      HAL_GPIO_AF5_SPI5

// Control del pin HSYNC (Horizontal sync)
//
#define DISPLAY_HSYNC_PORT   HAL_GPIO_PORT_C
#define DISPLAY_HSYNC_PIN    HAL_GPIO_PIN_6
#define DISPLAY_HSYNC_AF     HAL_GPIO_AF14_LTDC

// Control del pin VSYNC (Vertical sync)
//
#define DISPLAY_VSYNC_PORT   HAL_GPIO_PORT_A
#define DISPLAY_VSYNC_PIN    HAL_GPIO_PIN_4
#define DISPLAY_VSYNC_AF     HAL_GPIO_AF14_LTDC

// Control del pin DE (Display enable)
//
#define DISPLAY_DE_PORT      HAL_GPIO_PORT_F
#define DISPLAY_DE_PIN       HAL_GPIO_PIN_10
#define DISPLAY_DE_AF        HAL_GPIO_AF14_LTDC

// Control del pin DOTCLK (Dot clock)
//
#define DISPLAY_DOTCLK_PORT  HAL_GPIO_PORT_G
#define DISPLAY_DOTCLK_PIN   HAL_GPIO_PIN_7
#define DISPLAY_DOTCLK_AF    HAL_GPIO_AF14_LTDC

// Control del pin R2
//
#define DISPLAY_R2_PORT      HAL_GPIO_PORT_C
#define DISPLAY_R2_PIN       HAL_GPIO_PIN_10
#define DISPLAY_R2_AF        HAL_GPIO_AF14_LTDC

// Control del pin R3
//
#define DISPLAY_R3_PORT      HAL_GPIO_PORT_B
#define DISPLAY_R3_PIN       HAL_GPIO_PIN_0
#define DISPLAY_R3_AF        HAL_GPIO_AF9_LTDC

// Control del pin R4
//
#define DISPLAY_R4_PORT      HAL_GPIO_PORT_A
#define DISPLAY_R4_PIN       HAL_GPIO_PIN_11
#define DISPLAY_R4_AF        HAL_GPIO_AF14_LTDC

// Control del pin R5
//
#define DISPLAY_R5_PORT      HAL_GPIO_PORT_A
#define DISPLAY_R5_PIN       HAL_GPIO_PIN_12
#define DISPLAY_R5_AF        HAL_GPIO_AF14_LTDC

// Control del pin R6
//
#define DISPLAY_R6_PORT      HAL_GPIO_PORT_B
#define DISPLAY_R6_PIN       HAL_GPIO_PIN_1
#define DISPLAY_R6_AF        HAL_GPIO_AF9_LTDC

// Control del pin R7
//
#define DISPLAY_R7_PORT      HAL_GPIO_PORT_G
#define DISPLAY_R7_PIN       HAL_GPIO_PIN_6
#define DISPLAY_R7_AF        HAL_GPIO_AF14_LTDC

// Control del pin G2
//
#define DISPLAY_G2_PORT      HAL_GPIO_PORT_A
#define DISPLAY_G2_PIN       HAL_GPIO_PIN_6
#define DISPLAY_G2_AF        HAL_GPIO_AF14_LTDC

// Control del pin G3
//
#define DISPLAY_G3_PORT      HAL_GPIO_PORT_G
#define DISPLAY_G3_PIN       HAL_GPIO_PIN_10
#define DISPLAY_G3_AF        HAL_GPIO_AF9_LTDC

// Control del pin G4
//
#define DISPLAY_G4_PORT      HAL_GPIO_PORT_B
#define DISPLAY_G4_PIN       HAL_GPIO_PIN_10
#define DISPLAY_G4_AF        HAL_GPIO_AF14_LTDC

// Control del pin G5
//
#define DISPLAY_G5_PORT      HAL_GPIO_PORT_B
#define DISPLAY_G5_PIN       HAL_GPIO_PIN_11
#define DISPLAY_G5_AF        HAL_GPIO_AF14_LTDC

// Control del pin G6
//
#define DISPLAY_G6_PORT      HAL_GPIO_PORT_C
#define DISPLAY_G6_PIN       HAL_GPIO_PIN_7
#define DISPLAY_G6_AF        HAL_GPIO_AF14_LTDC

// Control del pin G7
//
#define DISPLAY_G7_PORT      HAL_GPIO_PORT_D
#define DISPLAY_G7_PIN       HAL_GPIO_PIN_3
#define DISPLAY_G7_AF        HAL_GPIO_AF14_LTDC

// Control del pin B2
//
#define DISPLAY_B2_PORT      HAL_GPIO_PORT_D
#define DISPLAY_B2_PIN       HAL_GPIO_PIN_6
#define DISPLAY_B2_AF        HAL_GPIO_AF14_LTDC

// Control del pin B3
//
#define DISPLAY_B3_PORT      HAL_GPIO_PORT_G
#define DISPLAY_B3_PIN       HAL_GPIO_PIN_11
#define DISPLAY_B3_AF        HAL_GPIO_AF14_LTDC

// Control del pin B4
//
#define DISPLAY_B4_PORT      HAL_GPIO_PORT_G
#define DISPLAY_B4_PIN       HAL_GPIO_PIN_12
#define DISPLAY_B4_AF        HAL_GPIO_AF9_LTDC

// Control del pin B5
//
#define DISPLAY_B5_PORT      HAL_GPIO_PORT_A
#define DISPLAY_B5_PIN       HAL_GPIO_PIN_3
#define DISPLAY_B5_AF        HAL_GPIO_AF14_LTDC

// Control del pin B6
//
#define DISPLAY_B6_PORT      HAL_GPIO_PORT_B
#define DISPLAY_B6_PIN       HAL_GPIO_PIN_8
#define DISPLAY_B6_AF        HAL_GPIO_AF14_LTDC

// Control del pin B7
//
#define DISPLAY_B7_PORT      HAL_GPIO_PORT_B
#define DISPLAY_B7_PIN       HAL_GPIO_PIN_9
#define DISPLAY_B7_AF        HAL_GPIO_AF14_LTDC

// Control del modul SPI
//
#define DISPLAY_SPI_ID       HAL_SPI_ID_5

#endif // DISPLAY_DRV_ILI9341LTDC

#endif // USE_DISPLAY


#endif // __board_SMT32F429I_DISC1__

