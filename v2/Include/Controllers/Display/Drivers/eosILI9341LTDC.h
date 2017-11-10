#ifndef __eosILI9341LTDC__
#define	__eosILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include "stm32f4xx_hal_ltdc.h"

#include <stdint.h>


#if !defined(EOS_STM32F4) && !defined(EOS_STM32F7)
    #error CPU no soportada
#endif


#define ILI9341LTDC_SCREEN_WIDTH       240  // Tamany fix del controlador
#define ILI9341LTDC_SCREEN_HEIGHT      320  // Tamany fix del controlador


namespace eos {

    class ILI9341LTDC_Driver: public IDisplayDriver {
        private:
    		LTDC_HandleTypeDef ltdcHandle;
			int16_t screenWidth;
			int16_t screenHeight;
    		uint32_t curLayer;
            uint8_t *image;

        public:
            ILI9341LTDC_Driver();
            void initialize();
            void shutdown();
            void displayOn();
            void displayOff();
            void setOrientation(DisplayOrientation orientation);
            int16_t getWidth() const { return screenWidth; }
            int16_t getHeight() const { return screenHeight; }
            void clear(const Color &color);
            void setPixel(int16_t x, int16_t y, const Color &color);
            void setHPixels(int16_t x, int16_t y, int16_t size, const Color &color);
            void setVPixels(int16_t x, int16_t y, int16_t size, const Color &color);
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color &color);
            void writePixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors);
            void readPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color *colors);
            void vScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height);
            void hScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height);

        private:
            void displayInit();
            void writeCommands(const uint8_t *dada);

        private:
            void ltdcInitialize();

            void dma2dInitialize();
            void dma2dFill(const uint8_t *addr, int16_t width, int16_t height, const Color &color);

            void lcdInitialize();
            void lcdReset();
            void lcdOpen();
            void lcdClose();
            void lcdWriteCommand(uint8_t d);
            void lcdWriteData(uint8_t d);
    };
}


#endif // __eos_ILI9341LTDC__
