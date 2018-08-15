#ifndef __eosILI9341__
#define	__eosILI9341__


#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <stdint.h>


#define ILI9341_SCREEN_WIDTH      240       // Tamany fix del controlador
#define ILI9341_SCREEN_HEIGHT     320       // Tamany fix del controlador


namespace eos {

    class ILI9341Driver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int16_t screenWidth;
    		int16_t screenHeight;

        public:
    		static IDisplayDriver *getInstance();
            void initialize();
            void shutdown();
            void displayOn();
            void displayOff();
            void setOrientation(DisplayOrientation orientation);
            int16_t getWidth() { return screenWidth; }
            int16_t getHeight() { return screenHeight; }
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
            ILI9341Driver();
            void displayInit();
            void writeCommands(const uint8_t *data);
            void writeRegion(const Color &color);
            void writeRegion(const Color &color, int32_t count);
            void writeRegion(const Color *colors, int32_t count);
            void readRegion(Color *colors, int32_t count);
            void selectRegion(int16_t x, int16_t y, int16_t width, int16_t height);

        private:
            static void lcdInitialize();
            static void lcdReset();
            static void lcdOpen();
            static void lcdClose();
            static void lcdWriteCommand(uint8_t cmd);
            static void lcdWriteData(uint8_t data);
            static void lcdWriteData(uint8_t *data, int32_t size);
            static uint8_t lcdReadData();
    };
}


#endif // __eosILI9341__

