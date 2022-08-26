#pragma once
#ifndef __board_SMT32F746G_DISCO__
#define __board_SMT32F746G_DISCO__


// -----------------------------------------------------------------------
// Green led 1
// -----------------------------------------------------------------------
//
#ifdef USE_LED1
#define EXIST_LED1

#define LED1_GPIO            htl::GPIO_I1
#define LED1_ON              true
#define LED1_OFF             false

#endif // USE_LED1


// -----------------------------------------------------------------------
// Blue switch 1
// -----------------------------------------------------------------------
//
#ifdef USE_SW1
#define EXIST_SW1

#define SW1_GPIO             htl::GPIO_I11
#define SW1_ON               true
#define SW1_OFF              false

#endif // SW1


// -----------------------------------------------------------------------
// Integrated board display
// -----------------------------------------------------------------------
//
#ifdef USE_DISPLAY
#define EXIST_DISPLAY

#define DISPLAY_BKE_GPIO     htl::GPIO_K3
#define DISPLAY_LCDE_GPIO    htl::GPIO_I12
#define DISPLAY_PC_GPIO      htl::GPIO_I14
#define DISPLAY_HSYNC_GPIO   htl::GPIO_I10
#define DISPLAY_VSYNC_GPIO   htl::GPIO_I9
#define DISPLAY_DE_GPIO      htl::GPIO_K7
#define DISPLAY_R0_GPIO      htl::GPIO_I15
#define DISPLAY_R1_GPIO      htl::GPIO_J0
#define DISPLAY_R2_GPIO      htl::GPIO_J1
#define DISPLAY_R3_GPIO      htl::GPIO_J2
#define DISPLAY_R4_GPIO      htl::GPIO_J3
#define DISPLAY_R5_GPIO      htl::GPIO_J4
#define DISPLAY_R6_GPIO      htl::GPIO_J5
#define DISPLAY_R7_GPIO      htl::GPIO_J6
#define DISPLAY_G0_GPIO      htl::GPIO_J7
#define DISPLAY_G1_GPIO      htl::GPIO_J8
#define DISPLAY_G2_GPIO      htl::GPIO_J9
#define DISPLAY_G3_GPIO      htl::GPIO_J10
#define DISPLAY_G4_GPIO      htl::GPIO_J11
#define DISPLAY_G5_GPIO      htl::GPIO_K0
#define DISPLAY_G6_GPIO      htl::GPIO_K1
#define DISPLAY_G7_GPIO      htl::GPIO_K2
#define DISPLAY_B0_GPIO      htl::GPIO_E4
#define DISPLAY_B1_GPIO      htl::GPIO_J13
#define DISPLAY_B2_GPIO      htl::GPIO_J14
#define DISPLAY_B3_GPIO      htl::GPIO_J15
#define DISPLAY_B4_GPIO      htl::GPIO_G12
#define DISPLAY_B5_GPIO      htl::GPIO_K4
#define DISPLAY_B6_GPIO      htl::GPIO_K5
#define DISPLAY_B7_GPIO      htl::GPIO_K6

#define DISPLAY_WIDTH 		 480            // Amplada de la imatge
#define DISPLAY_HEIGHT		 272            // Alçada de la imatge
#define DISPLAY_HSYNC        41             // Horizontal synchronization
#define DISPLAY_VSYNC        10             // Vertical synchronization
#define DISPLAY_HBP          13             // Horizontal back porch
#define DISPLAY_VBP          2              // Vertical back porch
#define DISPLAY_HFP          32             // Horizontal front porch
#define DISPLAY_VFP          2              // Vertical front porch
#define DISPLAY_HSYNC_POL    htl::LTDCPolarity::activeLow
#define DISPLAY_VSYNC_POL    htl::LTDCPolarity::activeLow
#define DISPLAY_DE_POL       htl::LTDCPolarity::activeLow
#define DISPLAY_PC_POL       htl::LTDCPolarity::activeLow

#define DISPLAY_BUFFER       0xC0000000

#define DISPLAY_CLK_FDIV     5


#endif // USE_DISPLAY


// -----------------------------------------------------------------------
// Integrated display capacitative touchpad
// -----------------------------------------------------------------------
//
#if defined(USE_TOUCHPAD) & defined(USE_DISPLAY)
#define EXIST_TOUCHPAD

#define TOUCHPAD_SCL_GPIO    htl::GPIO_H7
#define TOUCHPAD_SDA_GPIO    htl::GPIO_H8
#define TOUCHPAD_INT_GPIO    htl::GPIO_I13
#define TOUCHPAD_INT_EXTI    htl::EXTI_13

#define TOUCHPAD_I2C         htl::I2CMaster_3
#define TOUCHPAD_I2C_ADDR    0x70

#define TOUCHPAD_WIDTH       DISPLAY_WIDTH
#define TOUCHPAD_HEIGHT      DISPLAY_HEIGHT


#endif // USE_TOUCHPAD


// -----------------------------------------------------------------------
// Arduino expansion conector
// -----------------------------------------------------------------------
//
#ifdef USE_ARDUINO
#define EXIST_ARDUINO

#define ARDUINO_D0           htl::GPIO_C7
#define ARDUINO_D1           htl::GPIO_C6
#define ARDUINO_D2           htl::GPIO_G6
#define ARDUINO_D3           htl::GPIO_B4
#define ARDUINO_D4           htl::GPIO_G7
#define ARDUINO_D5           htl::GPIO_I0
#define ARDUINO_D6           htl::GPIO_H6
#define ARDUINO_D7           htl::GPIO_I3
#define ARDUINO_D8           htl::GPIO_I2
#define ARDUINO_D9           htl::GPIO_A15
#define ARDUINO_D10          htl::GPIO_A8
#define ARDUINO_D11          htl::GPIO_B15
#define ARDUINO_D12          htl::GPIO_B14
#define ARDUINO_D13          htl::GPIO_I1
#define ARDUINO_D14          htl::GPIO_B9
#define ARDUINO_D15          htl::GPIO_B8

#define ARDUINO_UART         htl::UART_6
#define ARDUINO_RX           htl::GPIO_C7
#define ARDUINO_TX           htl::GPIO_C6

#define ARDUINO_I2C          htl::I2CMaster_1
#define ARDUINO_SCL          htl::GPIO_B8
#define ARDUINO_SDA          htl::GPIO_B9

#define ARDUINO_SPI          htl::SPI_2
#define ARDUINO_SCK          htl::GPIO_I1
#define ARDUINO_MISO         htl::GPIO_B14
#define ARDUINO_MOSI         htl::GPIO_B15

#endif // USE_ARDUINO


// -----------------------------------------------------------------------
// Camara DCIM OV9655
// -----------------------------------------------------------------------

#ifdef USE_CAMERA
#define EXIST_CAMERA

// Tamany de la imatge
//
#define CAMERA_IMAGE_WIDTH        0  // Seleccionable per software
#define CAMERA_IMAGE_HEIGHT       0  // Seleccionable per software

// Format de la imatge
//
#define CAMERA_FORMAT             RGB565

#define CAMERA_PIXCK_PORT         HAL_GPIO_PORT_A
#define CAMERA_PIXCK_PIN          HAL_GPIO_PIN_6
#define CAMERA_PIXCH_AF           HAL_GPIO_AF13

#define CAMERA_HSYNC_PORT         HAL_GPIO_PORT_A
#define CAMERA_HSYNC_PIN          HAL_GPIO_PIN_4
#define CAMERA_HSYNC_AF           HAL_GPIO_AF13

#define CAMERA_VSYNC_PORT         HAL_GPIO_PORT_G
#define CAMERA_VSYNC_PIN          HAL_GPIO_PIN_9
#define CAMERA_VSYNC_AF           HAL_GPIO_AF13

#define CAMERA_D0_PORT            HAL_GPIO_PORT_H
#define CAMERA_D0_PIN             HAL_GPIO_PIN_9
#define CAMERA_D0_AF              HAL_GPIO_AF13

#define CAMERA_D1_PORT            HAL_GPIO_PORT_H
#define CAMERA_D1_PIN             HAL_GPIO_PIN_10
#define CAMERA_D1_AF              HAL_GPIO_AF13

#define CAMERA_D2_PORT            HAL_GPIO_PORT_H
#define CAMERA_D2_PIN             HAL_GPIO_PIN_11
#define CAMERA_D2_AF              HAL_GPIO_AF13

#define CAMERA_D3_PORT            HAL_GPIO_PORT_H
#define CAMERA_D3_PIN             HAL_GPIO_PIN_12
#define CAMERA_D3_AF              HAL_GPIO_AF13

#define CAMERA_D4_PORT            HAL_GPIO_PORT_H
#define CAMERA_D4_PIN             HAL_GPIO_PIN_14
#define CAMERA_D4_AF              HAL_GPIO_AF13

#define CAMERA_D5_PORT            HAL_GPIO_PORT_D
#define CAMERA_D5_PIN             HAL_GPIO_PIN_3
#define CAMERA_D5_AF              HAL_GPIO_AF13

#define CAMERA_D6_PORT            HAL_GPIO_PORT_E
#define CAMERA_D6_PIN             HAL_GPIO_PIN_5
#define CAMERA_D6_AF              HAL_GPIO_AF13

#define CAMERA_D7_PORT            HAL_GPIO_PORT_E
#define CAMERA_D7_PIN             HAL_GPIO_PIN_6
#define CAMERA_D7_AF              HAL_GPIO_AF13

#define CAMERA_PE_PORT            HAL_GPIO_PORT_H
#define CAMERA_PE_PIN             HAL_GPIO_PIN_13


#endif // USE_CAMERA


// -----------------------------------------------------------------------
// Controlador SD
// -----------------------------------------------------------------------

#ifdef USE_SD
#define EXIST_SD

#define SD_PRESENT_PORT           HAL_GPIO_PORT_C
#define SD_PRESENT_PIN            HAL_GPIO_PIN_13

#define SD_DMA_RX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_RX_STREAM          DMA2_Stream3
#define SD_DMA_RX_IRQ             DMA2_Stream3_IRQn

#define SD_DMA_TX_CHANNEL         DMA_CHANNEL_4
#define SD_DMA_TX_STREAM          DMA2_Stream6
#define SD_DMA_TX_IRQ             DMA2_Stream6_IRQn

#define SD_MODULE                 SDMMC1

#endif // USE_SD



#endif // __board_SMT32F746G_DISCO__
