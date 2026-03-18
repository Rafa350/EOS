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


mklink /J "CMSIS_CORE"    "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Drivers\CMSIS\Device\ST\STM32G0xx"
mklink /J "HAL"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Drivers\STM32G0xx_HAL_Driver"
mklink /J "BSP"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Drivers\BSP"

mklink /J "FreeRTOS"      "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Middlewares\Third_Party\FreeRTOS\Source"

mklink /J "FatFs"         "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Middlewares\Third_Party\LwIP"

mklink /J "USBDevice"     "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_G0_V1.6.3\Middlewares\ST\STM32_USB_Host_Library"


pause