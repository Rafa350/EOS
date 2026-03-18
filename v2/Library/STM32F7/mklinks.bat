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


mklink /J "CMSIS_CORE"    "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Drivers\CMSIS\Device\ST\STM32F7xx"
mklink /J "HAL"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Drivers\STM32F7xx_HAL_Driver"
mklink /J "BSP"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Drivers\BSP"

mklink /J "FreeRTOS"      "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\Third_Party\FreeRTOS\Source"

mklink /J "FatFs"         "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\Third_Party\LwIP"
mklink /J "LibJPEG"       "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\Third_Party\LibJPEG"

mklink /J "Audio"         "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\ST\STM32_Audio"
mklink /J "USBDevice"     "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.4\Middlewares\ST\STM32_USB_Host_Library"


pause