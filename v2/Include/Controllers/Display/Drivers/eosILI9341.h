#ifndef __eosILI9341__
#define	__eosILI9341__


#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <stdint.h>


namespace eos {

    class ILI9341_Driver: public IDisplayDriver {
        private:
            int16_t screenWidth;
            int16_t screenHeight;

        public:
            ILI9341_Driver();
            void initialize();
            void shutdown();
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
            void displayOff();
            void writeCommands(const uint8_t *data);
            void ctrlWritePixel(const Color &color, int32_t count);
            void ctrlWritePixel(const Color *colors, int32_t count);
            void ctrlReadPixel(Color *colors, int32_t count);
            void selectRegion(int16_t x, int16_t y, int16_t width, int16_t height);
            void startWriteRegion();
            void startReadRegion();

        private:
            static void lcdInitialize();
            static void lcdReset();
            static void lcdOpen();
            static void lcdClose();
            static void lcdWriteCommand(uint8_t d);
            static void lcdWriteData(uint8_t d);
            static uint8_t lcdReadData();
    };
}


#endif // __eosILI9341__

