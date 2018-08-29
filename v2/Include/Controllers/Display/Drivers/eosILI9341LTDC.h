#ifndef __eosILI9341LTDC__
#define	__eosILI9341LTDC__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include "stdint.h"


#if !defined(EOS_STM32F4) && !defined(EOS_STM32F7)
    #error Hardware no soportado
#endif

#if !defined(DISPLAY_COLOR_RGB565) && !defined(DISPLAY_COLOR_RGB888)
	#error Formato de color no soportado
#endif


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     320  // Tamany fix del controlador
#endif


#if defined(DISPLAY_COLOR_RGB565)
#define PIXEL_TYPE                int16_t
#elif defined(DISPLAY_COLOR_RGB888)
#define PIXEL_TYPE                int32_t
#endif
#define PIXEL_SIZE                ((int)sizeof(PIXEL_TYPE))
#define LINE_SIZE                 (DISPLAY_SCREEN_WIDTH * PIXEL_SIZE)
#define FRAME_SIZE                (LINE_SIZE * DISPLAY_SCREEN_HEIGHT)


namespace eos {

    class ILI9341LTDCDriver: public IDisplayDriver {
        private:
    		static IDisplayDriver *instance;
    		int screenWidth;
    		int screenHeight;
    		int sin;
    		int cos;
    		int dx;
    		int dy;
            int vRamAddr;

        public:
            static IDisplayDriver *getInstance();;
            void initialize();
            void shutdown();
            void displayOn();
            void displayOff();
            void setOrientation(DisplayOrientation orientation);
            int getWidth() { return screenWidth; }
            int getHeight() { return screenHeight; }
            void clear(const Color &color);
            void setPixel(int x, int y, const Color &color);
            void setHPixels(int x, int y, int size, const Color &color);
            void setVPixels(int x, int y, int size, const Color &color);
            void setPixels(int x, int y, int width, int height, const Color &color);
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format);
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format);
            void vScroll(int delta, int x, int y, int width, int height);
            void hScroll(int delta, int x, int y, int width, int height);

        private:
            ILI9341LTDCDriver();
            void displayInit();
            void writeCommands(const uint8_t *dada);

        private:
            void ltdcInitialize();
            void dma2dInitialize();
            void dma2dFill(int x, int y, int width, int height, const Color &color);
            void dma2dWaitFinish();
            void lcdInitialize();
            void lcdReset();
            void lcdOpen();
            void lcdClose();
            void lcdWriteCommand(uint8_t d);
            void lcdWriteData(uint8_t d);
    };
}


#endif // __eos_ILI9341LTDC__
