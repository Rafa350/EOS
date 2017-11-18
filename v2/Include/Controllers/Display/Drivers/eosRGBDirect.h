#ifndef __eosRGBDirect__
#define	__eosRGBDirect__


#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <stdint.h>


#ifndef RGBDIRECT_SCREEN_WIDTH
#define RGBDIRECT_SCREEN_WIDTH      480       // Tamany fix del controlador
#endif

#ifndef RGBDIRECT_SCREEN_HEIGHT
#define RGBDIRECT_SCREEN_HEIGHT     272       // Tamany fix del controlador
#endif


namespace eos {

    class RGBDirect_Driver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int16_t screenWidth;
    		int16_t screenHeight;
    		uint8_t curLayer;
    		uint8_t *image;

    	private:
            RGBDirect_Driver();

        public:
            static IDisplayDriver *getInstance();
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
            void gpioInitialize();
            void ltdcInitialize();
            void dma2dInitialize();
            void dma2dFill(const uint8_t *addr, int16_t width, int16_t height, const Color &color);
    };
}


#endif // __eosRGBDirect__

