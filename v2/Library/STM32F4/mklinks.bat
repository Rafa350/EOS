@echo off

mklink /J "CMSIS_CORE_Include"   "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1\Drivers\CMSIS\Include"
mklink /J "CMSIS_DEVICE_Include" "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1\Drivers\CMSIS\Device\ST\STM32F4xx\Include"
mklink /J "CMSIS_DEVICE_Source"  "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1\Drivers\CMSIS\Device\ST\STM32F4xx\Source"

mklink /J "HAL_Include"          "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1\Drivers\STM32F4xx_HAL_Driver\Inc"
mklink /J "HAL_Source"           "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1\Drivers\STM32F4xx_HAL_Driver\Src"

mklink /J "STM32Cube_FW_F4" "C:\Library\STMicroelectronics\STM32Cube\Firmwares\STM32Cube_FW_F4_V1.24.1"