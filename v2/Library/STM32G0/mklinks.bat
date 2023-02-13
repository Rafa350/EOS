@echo off


rmdir "CMSIS_CORE"
rmdir "CMSIS_DEVICE"
rmdir "HAL"
rmdir "BSP"

rmdir "FreeRTOS"
rmdir "FatFs"
rmdir "LwIP"

rmdir "USBDevice"
rmdir "USBHost"


mklink /J "CMSIS_CORE"    "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Drivers\CMSIS\Device\ST\STM32G0xx"
mklink /J "HAL"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Drivers\STM32G0xx_HAL_Driver"
mklink /J "BSP"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Drivers\BSP"

mklink /J "FreeRTOS"      "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Middlewares\Third_Party\FreeRTOS\Source"

mklink /J "FatFs"         "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Middlewares\Third_Party\LwIP"

mklink /J "USBDevice"     "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_G0_V1.6.1\Middlewares\ST\STM32_USB_Host_Library"


pause