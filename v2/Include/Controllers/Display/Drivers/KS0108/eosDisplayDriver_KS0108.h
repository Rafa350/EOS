#ifndef __eosKS0108__
#define	__eosKS0108__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      128  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT      64  // Tamany fix del controlador
#endif


namespace eos {
    
    class Color;
    
    class KS0108Driver: public IDisplayDriver {
        private:
            int screenWidth;
            int screenHeight;
            DisplayOrientation orientation;
            
        public:
            KS0108Driver();
            
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const override { return screenWidth; }
            int getHeight() const override { return screenHeight; }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color);
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;
            
        private:
            void writePixel(Color color, unsigned count);
            void writePixel(const Color *colors, unsigned count);
            void readPixel(Color *colors, unsigned count);
            void selectRegion(int x, int y, int width, int height);
            void startMemoryWrite();
            void startMemoryRead();
            
        private:
            void setPage(uint8_t page);
            void setColumn(uint8_t column);
            void writeDataRegister(uint8_t data);
            void writeCtrlRegister(uint8_t data);
            void writeRegister(uint8_t data);
    };
}


#endif	// __eosKS0108__
