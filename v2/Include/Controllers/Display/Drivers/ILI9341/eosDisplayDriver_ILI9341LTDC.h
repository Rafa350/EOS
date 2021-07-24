#ifndef __eosDisplayDriver_ILI9341LTDC__
#define	__eosDisplayDriver_ILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HAL/halSPI.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320  // Tamany fix del controlador
#endif


namespace eos {

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
    	private:
    		typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;

    	private:
    		constexpr static int _displayWidth = DISPLAY_IMAGE_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_IMAGE_HEIGHT;
    		constexpr static int _displayBuffer = DISPLAY_IMAGE_BUFFER;

        private:
    		SPIData _spiData;
    		SPIHandler _hSpi;
            FrameBuffer* _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC();

            void initialize() override;
            void shutdown() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            int getImageWidth() const override { return _frameBuffer->getImageWidth(); }
            int getImageHeight() const override { return _frameBuffer->getImageHeight(); }

            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) override;

            void writePixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int pitch) override;
            void readPixels(int x, int y, int width, int height, void *pixels, ColorFormat format, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            void hwInitialize();
            static void hwReset();
            static void hwOpen();
            static void hwClose();
            void hwWriteCommand(uint8_t d);
            void hwWriteData(uint8_t d);
    };
}


#endif // __eos_DisplayDriver_ILI9341LTDC__
