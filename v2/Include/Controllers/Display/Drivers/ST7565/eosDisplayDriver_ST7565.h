#ifndef __eosST7565__
#define	__eosST7565__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      128  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT      64  // Tamany fix del controlador
#endif


namespace eos {

    class ST7565Driver: public IDisplayDriver {
        private:
            int screenWidth;
            int screenHeight;
            DisplayOrientation orientation;

        public:
            ST7565Driver();

            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getImageWidth() const override { return screenWidth; }
            int getImageHeight() const override { return screenHeight; }
            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *color, int pitch) override;
            virtual void setPixels(int x, int y, int width, int height, const void* pixels, ColorFormat format, int pitch) override;

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


#endif	// __eosST7565__
