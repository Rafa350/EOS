#ifndef __eosRGBDirect__
#define	__eosRGBDirect__


// EOS includes
//
#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

// Standard includes
//
#include "stdint.h"


#ifndef RGBDIRECT_SCREEN_WIDTH
#define RGBDIRECT_SCREEN_WIDTH      480       // Tamany fix del controlador
#endif

#ifndef RGBDIRECT_SCREEN_HEIGHT
#define RGBDIRECT_SCREEN_HEIGHT     272       // Tamany fix del controlador
#endif


namespace eos {

    class RGBDirectDriver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int screenWidth;
    		int screenHeight;
    		DisplayOrientation orientation;
    		unsigned curLayer;
    		uint8_t *image;

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
            void writePixels(int x, int y, int width, int height, const Color *colors);
            void readPixels(int x, int y, int width, int height, Color *colors);
            void vScroll(int delta, int x, int y, int width, int height);
            void hScroll(int delta, int x, int y, int width, int height);

        private:
            void gpioInitialize();
            void ltdcInitialize();
            void dma2dInitialize();
            void dma2dFill(const uint8_t *addr, int width, int height, const Color &color);
    };
}


#endif // __eosRGBDirect__

