#ifndef __eosILI9341__
#define	__eosILI9341__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"

#include "stdint.h"


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     320  // Tamany fix del controlador
#endif


namespace eos {

    class ILI9341Driver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int screenWidth;
    		int screenHeight;

        public:
    		static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const { return screenWidth; }
            int getHeight() const { return screenHeight; }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            ILI9341Driver();
            void displayInit();
            void writeCommands(const uint8_t *data);
            void writeRegion(const Color &color);
            void writeRegion(const Color &color, int count);
            void writeRegion(const Color *colors, int count);
            void readRegion(Color *colors, int count);
            void selectRegion(int x, int y, int width, int height);

        private:
            static void lcdInitialize();
            static void lcdReset();
            static void lcdOpen();
            static void lcdClose();
            static void lcdWriteCommand(uint8_t cmd);
            static void lcdWriteData(uint8_t data);
            static void lcdWriteData(uint8_t *data, int size);
            static uint8_t lcdReadData();
    };
}


#endif // __eosILI9341__

