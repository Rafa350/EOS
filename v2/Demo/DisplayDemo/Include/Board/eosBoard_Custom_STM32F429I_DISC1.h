#pragma once


#include "Board/eosBoard_STM32F429I_DISC1.h"


#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)

#define DISPLAY_IMAGE_WIDTH       240  // Amplada en pixels
#define DISPLAY_IMAGE_HEIGHT      320  // Alçada en pixels
#define DISPLAY_COLOR_FORMAT      ColorFormat::rgb565  // Format de color
#define DISPLAY_IMAGE_BUFFER      0xD0000000


#define DISPLAY_RST_PORT          HAL_GPIO_PORT_A
#define DISPLAY_RST_PIN			  HAL_GPIO_PIN_5

#define DISPLAY_RS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_RS_PIN            HAL_GPIO_PIN_4

#define DISPLAY_CS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_CS_PIN            HAL_GPIO_PIN_7

#define DISPLAY_CLK_PORT          HAL_GPIO_PORT_F
#define DISPLAY_CLK_PIN           HAL_GPIO_PIN_7
#define DISPLAY_CLK_AF			  HAL_GPIO_AF5_SPI5

#define DISPLAY_MOSI_PORT         HAL_GPIO_PORT_F
#define DISPLAY_MOSI_PIN          HAL_GPIO_PIN_9
#define DISPLAY_MOSI_AF           HAL_GPIO_AF5_SPI5

#define DISPLAY_SPI_ID            HAL_SPI_CHANNEL_5


#endif
