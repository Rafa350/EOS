#ifndef __eosDisplayDriver_ILI9341LTDC__
#define	__eosDisplayDriver_ILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320  // Tamany fix del controlador
#endif


namespace eos {

    class Color;

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
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
            DisplayDriver_ILI9341LTDC();

            static void hwInitialize();
            static void hwReset();
            static void hwOpen();
            static void hwClose();
            static void hwWriteCommand(uint8_t d);
            static void hwWriteData(uint8_t d);
    };
}


#endif // __eos_DisplayDriver_ILI9341LTDC__
