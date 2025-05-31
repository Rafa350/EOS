@echo off

rd "CMSIS_CORE"
rd "CMSIS_DEVICE"
rd "HAL"
rd "BSP"

rd "FreeRTOS"
rd "FatFs"
rd "LwIP"
rd "LibJPEG"

rd "Audio"
rd "USBDevice"
rd "USBHost"


mklink /J "CMSIS_CORE"    "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Drivers\CMSIS\Device\ST\STM32F7xx"
mklink /J "HAL"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Drivers\STM32F7xx_HAL_Driver"
mklink /J "BSP"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Drivers\BSP"

mklink /J "FreeRTOS"      "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\Third_Party\FreeRTOS\Source"

mklink /J "FatFs"         "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\Third_Party\LwIP"
mklink /J "LibJPEG"       "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\Third_Party\LibJPEG"

mklink /J "Audio"         "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\ST\STM32_Audio"
mklink /J "USBDevice"     "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.17.3\Middlewares\ST\STM32_USB_Host_Library"


pause