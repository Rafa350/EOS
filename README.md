# EOS (Embedded Operating System)

## Features:
* Verified targets STM32F0xx, STM32F1xx, STM32F4xx, STM32F7xx, STM32G030xx, STM32G0x1xx, PIC32MX.
* FreeRTOS scheduler.
* HAL module.
  * Independent HTL (HAL Template Library) with minimal overload. C++17
* Graphic module.
  * Fonts (Conversion tool from TrueType/OpenType).
  * Color displays: ARGB8888, RGB888, RGB565, L8 (Optional CLUT) color scheme.
  * Monochrome displays: L1.
  * Basic primitives line, circle, rectangle, ellipse, etc.
  * Single and double buffer.
  * Use hardware acceleration where available (STM32/DMA2D)
  * Drivers for LCD, TFT, OLED, etc.
* Based on services.
  * Digital inputs service.
  * Digital outputs service.
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
	* Library (STM32, PIC32 libraries)
	* Demo (Demos)
	* Build (Projects and builds for demos)
	* Tools (EOS developement tools)
	
## PlatformIO/VSCode integration (Experimental)