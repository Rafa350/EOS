#ifndef __STM32_halGPIO_AF__
#define __STM32_halGPIO_AF__


#include "HAL/halGPIO.h"


#if defined(EOS_STM32F4)


// Funcions alternatives del port F
#define HAL_GPIO_AF_F7_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_F7_SPI5_SCK             HAL_GPIO_AF_5

#define HAL_GPIO_AF_F9_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_F9_SPI5_MOSI            HAL_GPIO_AF_5


#elif defined(STM32F7)
    
// Funcions alternatives del port B
#define HAL_GPIO_AF_B8_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_B8_I2C1_SCL             HAL_GPIO_AF_4

#define HAL_GPIO_AF_B9_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_B9_I2C1_SDA             HAL_GPIO_AF_4

#define HAL_GPIO_AF_B14_NONE                HAL_GPIO_AF_0
#define HAL_GPIO_AF_B14_SPI2_MISO           HAL_GPIO_AF_5

#define HAL_GPIO_AF_B15_NONE                HAL_GPIO_AF_2
#define HAL_GPIO_AF_B15_SPI2_MOSI           HAL_GPIO_AF_5

// Funcions alternatives del port I
#define HAL_GPIO_AF_I1_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_I1_SPI2_SCK             HAL_GPIO_AF_5

#define HAL_GPIO_AF_I9_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_I9_LTDC_VSYNC           HAL_GPIO_AF_14

#define HAL_GPIO_AF_I10_NONE                HAL_GPIO_AF_0
#define HAL_GPIO_AF_I10_LTDC_HSYNC          HAL_GPIO_AF_14

#define HAL_GPIO_AF_I14_NONE                HAL_GPIO_AF_0
#define HAL_GPIO_AF_I14_LTDC_DOTCLK         HAL_GPIO_AF_14

#define HAL_GPIO_AF_I15_NONE                HAL_GPIO_AF_0
#define HAL_GPIO_AF_I15_LTDC_R0             HAL_GPIO_AF_14

// Funcions alternatives del port J
#define HAL_GPIO_AF_J0_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J0_LTDC_R1              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J1_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J1_LTDC_R2              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J2_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J2_LTDC_R3              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J3_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J3_LTDC_R4              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J4_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J4_LTDC_R5              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J5_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J5_LTDC_R6              HAL_GPIO_AF_14

#define HAL_GPIO_AF_J6_NONE                 HAL_GPIO_AF_0
#define HAL_GPIO_AF_J6_LTDC_R7              HAL_GPIO_AF_14

// Funcions alternatives del port K


#else
#error "Hardware no soportado."
#endif
    
#endif // __STM32_halGPIO_AF__
