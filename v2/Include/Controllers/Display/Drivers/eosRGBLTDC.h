#ifndef __eosRGBLTDC__
#define	__eosRGBLTDC__


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
    		//int layer2Addr;

    	private:
            RGBDirectDriver();

        public:
            static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() override { return screenWidth; }
            int getHeight() override { return screenHeight; }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;

        private:
            void gpioInitialize();
            void ltdcInitialize();
            void ltdcInitializeLayer(LTDC_Layer_TypeDef* layer);
            void ltdcSetFrameAddress(LTDC_Layer_TypeDef *layer, int frameAddr);
            void ltdcActivateLayer(LTDC_Layer_TypeDef *layer, bool activate);
            void dma2dInitialize();
            void dma2dFill(int x, int y, int width, int height, const Color &color);
            void dma2dCopy(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
            void dma2dWaitFinish();
    };
}

#endif // __eosRGBDirect__
