#ifndef __board_Custom_SMT32F429I_DISC1__
#define __board_Custom_SMT32F429I_DISC1__


#include "Board/eosBoard_STM32F429I_DISC1.h"


#define DISPLAY_DRV_SSD1306


#define DISPLAY_RS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_RS_PIN            HAL_GPIO_PIN_4
#define DISPLAY_RS_AF

#define DISPLAY_CS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_CS_PIN            HAL_GPIO_PIN_7
#define DISPLAY_CS_AF

#define DISPLAY_CLK_PORT          HAL_GPIO_PORT_F
#define DISPLAY_CLK_PIN           HAL_GPIO_PIN_7
#define DISPLAY_CLK_AF			  HAL_GPIO_AF5_SPI5

#define DISPLAY_MOSI_PORT         HAL_GPIO_PORT_F
#define DISPLAY_MOSI_PIN          GPIO_PIN_9
#define DISPLAY_MOSI_AF           HAL_GPIO_AF5_SPI5

#define DISPLAY_MISO_PORT         HAL_GPIO_PORT_F
#define DISPLAY_MISO_PIN          HAL_GPIO_PIN_8
#define DISPLAY_MISO_AF           HAL_GPIO_AF5_SPI5


#define DISPLAY_SPI_ID            HAL_SPI_CHANNEL_5


#endif // __board_Custom_STM32F429I_DISC1__

