#ifndef __eosILI9341LTDC__
#define	__eosILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include <stdint.h>


#if !defined(EOS_STM32F4) && !defined(EOS_STM32F7)
    #error CPU no soportada
#endif


namespace eos {

    class ILI9341LTDC_Driver: public IDisplayDriver {
        private:
            int16_t screenWidth;
            int16_t screenHeight;
            int16_t frameWidth;
            int16_t frameHeight;
            int8_t *frameBuffer;

        public:
            ILI9341LTDC_Driver();
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
            inline int offsetOf(int16_t x, int16_t y) { return x + (y * screenWidth); }
            void displayInit();
            void displayOff();
            void writeCommands(const uint8_t *dada);

        private:
            static void ltdcInitialize();

        private:
            static void lcdInitialize();
            static void lcdReset();
            static void lcdOpen();
            static void lcdClose();
            static void lcdWriteCommand(uint8_t d);
            static void lcdWriteData(uint8_t d);
    };
}


#endif // __eos_ILI9341LTDC__
