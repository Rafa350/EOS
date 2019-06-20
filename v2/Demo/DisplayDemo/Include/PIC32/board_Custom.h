#ifndef __board_CUSTOM__
#define __board_CUSTOM__


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
#define LED_LED1_PIN              HAL_GPIO_PIN_6
#endif

#ifdef USE_LEDS_LED2
#define EXIST_LEDS_LED2
#define LED_LED2_PORT             HAL_GPIO_PORT_D
#define LED_LED2_PIN              HAL_GPIO_PIN_1
#endif


// -----------------------------------------------------------------------
// Display grafic
// -----------------------------------------------------------------------

#ifdef USE_DISPLAY
#define EXIST_DISPLAY


//   ILI9341             PINGUINO      GPIO     
//   -------             --------      ----  
//        10     RST     CON1-13       RD11
//        35     RD      CON1-1        RC14     
//        36     WR      CON1-15       RD7      
//        37     RS      CON1-2        RC13     
//        38     CS      CON1-14       RD8      
//               DATA    CON1-3..10    RE0..7   


// Tipus de pantalla
//
#define DISPLAY_ER_TFT028_4

// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      240  // Amplada en pixels
#define DISPLAY_SCREEN_HEIUGHT    320  // Alçada en pixels
#define DISPLAY_COLOR_RGB565           // Codificacio de color RGB565

// Parametres de controlador
//
#define DISPLAY_DRV_ILI9341            // Driver a utilitzar

// Tipus de lletra disponibles 
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt

// Tipus d'interficie amb el controlador
//
#define DISPLAY_IO_TYPE_PIO8


// Control del pin RST (Reset) CON1-13
//
#define DISPLAY_RST_PORT     HAL_GPIO_PORT_D
#define DISPLAY_RST_PIN      HAL_GPIO_PIN_11

// Control del pin CS (Chip select) CON1-14
//
#define DISPLAY_CS_PORT      HAL_GPIO_PORT_D
#define DISPLAY_CS_PIN       HAL_GPIO_PIN_8

// Control del pin RS (Register select) CON1-2
//
#define DISPLAY_RS_PORT      HAL_GPIO_PORT_C
#define DISPLAY_RS_PIN       HAL_GPIO_PIN_13

// Control de pin WR (Write) D7 CON1-15
//
#define DISPLAY_WR_PORT      HAL_GPIO_PORT_D
#define DISPLAY_WR_PIN       HAL_GPIO_PIN_7

// Control del pin RD (Read) CON1-1
//
//#define DISPLAY_RD_PORT      HAL_GPIO_PORT_C
//#define DISPLAY_RD_PIN       HAL_GPIO_PIN_14

// Control del port DATA (I/O paralel port) CON1-3..10
//
#define DISPLAY_DATA_PORT    HAL_GPIO_PORT_E

#endif


#endif // __board_CUSTOM__
