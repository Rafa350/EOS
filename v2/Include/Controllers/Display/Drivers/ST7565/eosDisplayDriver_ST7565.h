#ifndef __eosDisplayDriver_ST7565__
#define	__eosDisplayDriver_ST7565__


#include "eos.h"


// Amplada del display
//
#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH        128
#endif
#if (DISPLAY_WIDTH != 128) && \
	(DISPLAY_WIDTH != 256)
#error "DISPLAY_WIDTH"
#endif

// Alçada del display
//
#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT       64
#endif
#if (DISPLAY_HEIGHT != 32) && \
	(DISPLAY_HEIGHT != 64) && \
	(DISPLAY_HEIGHT != 128)
#error "DISPLAY_HEIGHT"
#endif


// Tipus d'interficie amb el controlador
//
#define DISPLAY_INTERFACE_ST7565_SPI  0
#define DISPLAY_INTERFACE_ST7565_I2C  1
#define DISPLAY_INTERFACE_ST7565_8080 2
#define DISPLAY_INTERFACE_ST7565_6800 3

#ifndef DISPLAY_INTERFACE
#define DISPLAY_INTERFACE    DISPLAY_ST7565_INTERFACE_SPI
#endif
#if (DISPLAY_INTERFACE != DISPLAY_INTERFACE_ST7565_SPI) && \
    (DISPLAY_INTERFACE != DISPLAY_INTERFACE_ST7565_I2C) && \
    (DISPLAY_INTERFACE != DISPLAY_INTERFACE_ST7565_8080) && \
    (DISPLAY_INTERFACE != DISPLAY_INTERFACE_ST7565_6800)
#error "DISPLAY_INTERFACE"
#endif


#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class DisplayDriver_ST7565: public IDisplayDriver {
    	private:
            static constexpr int _displayWidth = DISPLAY_WIDTH;
            static constexpr int _displayHeight = DISPLAY_HEIGHT;

            FrameBuffer *_frameBuffer;

        private:
            void initializeController();
            void writePixel(Color color, unsigned count);
            void writePixel(const Color *colors, unsigned count);
            void readPixel(Color *colors, unsigned count);
            void selectRegion(int x, int y, int width, int height);
            void startMemoryWrite();
            void startMemoryRead();
            void setPage(uint8_t page);
            void setColumn(uint8_t column);


            void initializeInterface();
            void writeDataRegister(uint8_t data);
            void writeCtrlRegister(uint8_t data);
            void writeRegister(uint8_t data);

        public:
            DisplayDriver_ST7565(FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getMaxX() const override { return _frameBuffer->getMaxX(); }
            int getMaxY() const override { return _frameBuffer->getMaxY(); }
            int getWidth() const override { return _displayWidth; }
            int getHeight() const override { return _displayHeight; };

            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) override;
            void setPixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int pitch) override;
            void refresh() override;
    };
}


#endif	// __eosDislayDriver_ST7565__
