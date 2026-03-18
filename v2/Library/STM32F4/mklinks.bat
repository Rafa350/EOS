@echo off


rmdir "CMSIS_CORE"
rmdir "CMSIS_DEVICE"
rmdir "HAL"
rmdir "BSP"

rmdir "FreeRTOS"
rmdir "FatFs"
rmdir "LwIP"
rmdir "LibJPEG"

rmdir "Audio"
rmdir "USBDevice"
rmdir "USBHost"


mklink /J "CMSIS_CORE"    "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Drivers\CMSIS\Core"
mklink /J "CMSIS_DEVICE"  "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Drivers\CMSIS\Device\ST\STM32F4xx"
mklink /J "HAL"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Drivers\STM32F4xx_HAL_Driver"
mklink /J "BSP"           "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Drivers\BSP"

mklink /J "FreeRTOS"      "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\Third_Party\FreeRTOS\Source"

mklink /J "FatFs"         "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\Third_Party\FatFs"
mklink /J "LwIP"          "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\Third_Party\LwIP"
mklink /J "LibJPEG"       "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\Third_Party\LibJPEG"

mklink /J "Audio"         "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\ST\STM32_Audio"
mklink /J "USBDevice"     "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\ST\STM32_USB_Device_Library"
mklink /J "USBHost"       "%USERPROFILE%\STM32Cube\Repository\STM32Cube_FW_F4_V1.28.3\Middlewares\ST\STM32_USB_Host_Library"


pause