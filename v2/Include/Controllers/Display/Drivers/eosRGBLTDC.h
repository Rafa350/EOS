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
typedef int16_t pixel_t;
#elif defined(DISPLAY_COLOR_RGB888)
typedef int32_t pixel_t
#endif
#define LINE_SIZE                 (((DISPLAY_IMAGE_WIDTH * sizeof(pixel_t)) + 63) & 0xFFFFFFC0)
#define LINE_WIDTH                (LINE_SIZE / sizeof(pixel_t))
#define FRAME_SIZE                (LINE_SIZE * DISPLAY_IMAGE_HEIGHT)

#define PAGE1_ADDR                DISPLAY_VRAM_ADDR
#define PAGE2_ADDR                DISPLAY_VRAM_ADDR + FRAME_SIZE


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
    		int page1Addr;
    		int page2Addr;

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
            void ltdcSetFrameAddress(int frameAddr);
            void fill(int x, int y, int width, int height, const Color &color);
            void copy(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
    };
}

#endif // __eosRGBDirect__
