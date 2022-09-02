@echo off

rmdir "Harmony"
rmdir "FreeRTOS"
rmdir "LwIP"

mklink /J "Harmony"        "C:\Library\Microchip\Harmony\v2_06"
mklink /J "FreeRTOS"       "C:\Library\Microchip\Harmony\v2_06\third_party\rtos\FreeRTOS\Source"
mklink /J "LwIP"           "C:\Library\LwIP-2.1.2"

pause
