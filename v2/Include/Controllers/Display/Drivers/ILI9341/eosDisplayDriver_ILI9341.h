#ifndef __eosILI9341__
#define	__eosILI9341__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320  // Tamany fix del controlador
#endif


namespace eos {

    class DisplayDriver_ILI9341: public IDisplayDriver {
    	private:
    		static IDisplayDriver *_instance;
    		int _imageWidth;
    		int _imageHeight;

        public:
    		static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const { return _imageWidth; }
            int getHeight() const { return _imageHeight; }
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
            DisplayDriver_ILI9341();
            void writeRegion(const Color &color);
            void writeRegion(const Color &color, int count);
            void writeRegion(const Color *colors, int count);
            void readRegion(Color *colors, int count);
            void selectRegion(int x, int y, int width, int height);

        private:
            static void hwInitialize();
            static void hwReset();
            static void hwOpen();
            static void hwClose();
            static void hwWriteCommand(uint8_t cmd);
            static void hwWriteData(uint8_t data);
            static void hwWriteData(uint8_t *data, int count);
            static uint8_t hwReadData();
    };
}


#endif // __eosILI9341__

