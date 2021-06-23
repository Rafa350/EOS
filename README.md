# EOS (Embedded Operating System)

## Features:
* Verified targets STM32F4xx, STM32F7xx, PIC32MX.
* FreeRTOS scheduler.
* Graphic module.
  * Fonts (Conversion tool from TrueType/OpenType).
  * ARGB8888, RGB888, RGB565 color scheme.
  * Basic primitives line, circle, rectangle, ellipse, etc.
  * Single and double buffer.
  * Use hardware acceleration where available (STM32/DMA2D)
  * Drivers for LCD, TFT, OLED, etc.
* Based on services.
  * Digital inputs service.
  * Digital outputs service.
  * User loop service.
  * GUI service (Graphic User Interface).
  * FSM service (Finite State Machine).
  * I2C comunication queue service.
* Multiple examples.


## Folder structure 
* EOS (Root folder)
  * v1 (Older version)
  * v2 (Current version)
    * Include (Include files)
	* Source (Source files)
	* Library (STM32F4, STM32F4, PIC32 libraries)
	* Demo (Demos)
	* Build (Projects and builds for demos)
	* Tools (EOS developement tools)