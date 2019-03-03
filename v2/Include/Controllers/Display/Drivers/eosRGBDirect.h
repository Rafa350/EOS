#ifndef __eosRGBDirect__
#define	__eosRGBDirect__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"
#if defined(EOS_STM32F7)
#include "stm32f7xx.h"
#else
#error Hardware no soportado
#endif

// Standard includes
//
#include "stdint.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       480       // Tamany fix del controlador
#endif

#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      272       // Tamany fix del controlador
#endif


#if defined(DISPLAY_COLOR_RGB565)
#define PIXEL_TYPE                int16_t
#elif defined(DISPLAY_COLOR_RGB888)
#define PIXEL_TYPE                int32_t
#endif
#define PIXEL_SIZE                sizeof(PIXEL_TYPE)
#define LINE_SIZE                 (((DISPLAY_IMAGE_WIDTH * PIXEL_SIZE) + 63) & 0xFFFFFFC0)
#define LINE_WIDTH                (LINE_SIZE / PIXEL_SIZE)
#define FRAME_SIZE                (LINE_SIZE * DISPLAY_IMAGE_HEIGHT)


namespace eos {

    class RGBDirectDriver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int screenWidth;
    		int screenHeight;
    		int sin;
    		int cos;
    		int dx;
    		int dy;
    		DisplayOrientation orientation;
    		int layer1Addr;
    		int layer2Addr;

    	private:
            RGBDirectDriver();

        public:
            static IDisplayDriver *getInstance();
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
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
            void vScroll(int delta, int x, int y, int width, int height);
            void hScroll(int delta, int x, int y, int width, int height);

        private:
            void gpioInitialize();
            void ltdcInitialize();
            void ltdcInitializeLayer(LTDC_Layer_TypeDef* layer, int frameAddr);
            void ltdcActivateLayer(LTDC_Layer_TypeDef *layer, bool activate);
            void dma2dInitialize();
            void dma2dFill(int x, int y, int width, int height, const Color &color);
            void dma2dCopy(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
            void dma2dWaitFinish();
    };
}

#endif // __eosRGBDirect__
