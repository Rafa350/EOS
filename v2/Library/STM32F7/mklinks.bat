@echo off

mklink /J "CMSIS_CORE"    "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Drivers\CMSIS\Device\ST\STM32F7xx"
mklink /J "HAL"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Drivers\STM32F7xx_HAL_Driver"
mklink /J "BSP"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Drivers\BSP"

mklink /J "FreeRTOS"      "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\Third_Party\FreeRTOS"
mklink /J "FatFs"         "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\Third_Party\LwIP"
mklink /J "LibJPEG"       "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\Third_Party\LibJPEG"

mklink /J "Audio"         "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\ST\STM32_Audio"
mklink /J "USBDevice"     "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.16.0\Middlewares\ST\STM32_USB_Host_Library"


pause