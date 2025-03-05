@echo off

echo Generando variantes para STM32F030
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F0\F030\UART.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F0\F030\TMR.xml

echo Generando variantes para STM32F429
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F4\F429\TMR.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F4\F429\SPI.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F4\F429\LTDC.xml

echo Generando variantes para STM32F746
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32F7\F746\UART.xml

echo Generando variantes para STM32G071
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32G0\G071\UART.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32G0\G071\TMR.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32G0\G071\SPI.xml
"C:\Users\Rafael\Documents\Projectes\Net\EosTools\v2\artifacts\bin\EOSConfigurator\debug\EOSConfigurator.exe" AlternatePins\STM32G0\G071\I2C.xml


pause
