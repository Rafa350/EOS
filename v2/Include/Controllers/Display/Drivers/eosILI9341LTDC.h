#ifndef __eosILI9341LTDC__
#define	__eosILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"


#if !defined(DISPLAY_COLOR_RGB565) && !defined(DISPLAY_COLOR_RGB888)
	#error Formato de color no soportado
#endif


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320  // Tamany fix del controlador
#endif


#if defined(DISPLAY_COLOR_RGB565)
typedef int16_t pixel_t;
#elif defined(DISPLAY_COLOR_RGB888)
typedef int32_t pixel_t;
#endif
#define PIXEL_SIZE                sizeof(pixel_t)
#define LINE_SIZE                 (((DISPLAY_IMAGE_WIDTH * PIXEL_SIZE) + 63) & 0xFFFFFFC0)

namespace eos {

    class Color;

    class DisplayDriver_ILI9341_LTDC: public IDisplayDriver {
        private:
    		static IDisplayDriver* _instance;
            FrameBuffer* _frameBuffer;

        public:
            static IDisplayDriver *getInstance();;
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const override { return _frameBuffer->getWidth(); }
            int getHeight() const override { return _frameBuffer->getHeight(); }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            DisplayDriver_ILI9341_LTDC();
            void writeCommands(const uint8_t *dada);

        private:
            void initializeGPIO();
            void initializeSPI();
            void initializeLTDC();
            void lcdInitialize();
            void lcdReset();
            void lcdOpen();
            void lcdClose();
            void lcdWriteCommand(uint8_t d);
            void lcdWriteData(uint8_t d);
    };
}


#endif // __eos_ILI9341LTDC__
