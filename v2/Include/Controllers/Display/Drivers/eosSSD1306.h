#ifndef __eosSSD1306__
#define __eosSSD1306__


#include "eos.h"
#include "HAL/halSPI.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      128  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     64   // Tamany fix del controlador
#endif


namespace eos {

    class SSD1306Driver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *_instance;
    		const int _screenWidth;
    		const int _screenHeight;
    		SPIHandler _hSpi;

        public:
    		static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const { return _screenWidth; }
            int getHeight() const { return _screenHeight; }
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
            SSD1306Driver();

            void oledInitialize();
            void oledSelect();
            void oledUnselect();
            void oledWriteCommand(uint8_t cmd);
            void oledWriteData(uint8_t data);
    };
}


#endif // __eosSSD1306__

