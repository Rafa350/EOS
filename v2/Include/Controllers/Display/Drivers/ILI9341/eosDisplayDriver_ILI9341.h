#ifndef __eosILI9341__
#define	__eosILI9341__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


// Amplada d'imatge
//
#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240
#endif

// Alçada d'imatge
//
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320
#endif

// Format de color
#ifndef DISPLAY_COLOR_FORMAT
#define DISPLAY_COLOR_FORMAT      ColorFormat::rgb565
#endif


namespace eos {

    class DisplayDriver_ILI9341: public IDisplayDriver {
    	private:
    		typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;
    		typedef CI::color_t pixel_t;

    	private:
    		constexpr static int _displayWidth = DISPLAY_IMAGE_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_IMAGE_HEIGHT;

    	private:
    		int _imageWidth;
    		int _imageHeight;

        public:
            DisplayDriver_ILI9341();

            void initialize() override;
            void shutdown() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getImageWidth() const { return _imageWidth; }
            inline int getImageHeight() const { return _imageHeight; }

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
            void writeRegion(Color color);
            void writeRegion(Color color, int count);
            void writeRegion(const Color *colors, int count);
            void readRegion(Color *colors, int count);
            void selectRegion(int x, int y, int width, int height);

            inline static pixel_t toPixel(Color color) { return ConvertTo<CI::format>(color); }

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

