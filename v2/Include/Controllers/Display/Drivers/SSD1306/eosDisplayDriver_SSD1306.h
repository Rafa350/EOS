#ifndef __eosDisplayDriver_SSD1306__
#define __eosDisplayDriver_SSD1306__


#include "eos.h"
#include "HAL/halSPI.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/Graphics/eosColor.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       128  // Tamany fix del controlador
#endif
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      64   // Tamany fix del controlador
#endif


namespace eos {

    class DisplayDriver_SSD1306: public IDisplayDriver {
    	private:
    		static IDisplayDriver *_instance;
    		FrameBuffer *_frameBuffer;

        public:
            DisplayDriver_SSD1306();

            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getImageWidth() const { return _frameBuffer->getImageWidth(); }
            int getImageHeight() const { return _frameBuffer->getImageHeight(); }
            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) override;

            void writePixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, void *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            static void hwInitialize();
            static void hwReset();
            static void hwOpen();
            static void hwClose();
            static void hwWriteCommand(uint8_t cmd);
            static void hwWriteData(uint8_t data);
    };
}


#endif // __eosDisplayDriver_SSD1306__

