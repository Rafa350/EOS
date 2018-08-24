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


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      480       // Tamany fix del controlador
#endif

#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     272       // Tamany fix del controlador
#endif


namespace eos {

    class RGBDirectDriver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		DisplayOrientation orientation;
    		int vRamAddr;

    	private:
            RGBDirectDriver();

        public:
            static IDisplayDriver *getInstance();
            void initialize();
            void shutdown();
            void displayOn();
            void displayOff();
            void setOrientation(DisplayOrientation orientation);
            int getWidth() { return DISPLAY_SCREEN_WIDTH; }
            int getHeight() { return DISPLAY_SCREEN_HEIGHT; }
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
            void dma2dFill(int x, int y, int width, int height, const Color &color);
            void dma2dCopy(int x, int y, int width, int height, const Color *colors);
            void dma2dWaitFinish();
    };
}


#endif // __eosRGBDirect__

