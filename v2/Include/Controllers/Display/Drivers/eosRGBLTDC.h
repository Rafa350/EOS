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
typedef int16_t pixel_t;                    // Tipus per un pixel
#elif defined(DISPLAY_COLOR_RGB888)
typedef int32_t pixel_t
#endif
#define PIXEL_SIZE                sizeof(pixel_t)
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
    		int frontFrameAddr;
    		int backFrameAddr;

    	private:
            RGBDirectDriver();

        public:
            static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const override { return screenWidth; }
            int getHeight() const override { return screenHeight; }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            void gpioInitialize();
            void ltdcInitialize();
            void fill(int x, int y, int width, int height, const Color &color);
            void copy(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
    };
}

#endif // __eosRGBDirect__
