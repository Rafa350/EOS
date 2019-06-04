@echo off

mklink /J "CMSIS_CORE_Include"   "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.15.0\Drivers\CMSIS\Core\Include"
mklink /J "CMSIS_DEVICE_Include" "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.15.0\Drivers\CMSIS\Device\ST\STM32F4xx\Include"
mklink /J "CMSIS_DEVICE_Source"  "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.15.0\Drivers\CMSIS\Device\ST\STM32F4xx\Source"

mklink /J "HAL_Include"          "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.15.0\Drivers\STM32F4xx_HAL_Driver\Inc"
mklink /J "HAL_Source"           "C:\Library\STMicroelectronics\STM32Cube\STM32Cube_FW_F7_V1.15.0\Drivers\STM32F4xx_HAL_Driver\Src"
