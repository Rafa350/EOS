#ifndef __eosDisplayDriver_SSD1306__
#define __eosDisplayDriver_SSD1306__


#include "eos.h"


// Amplada del display
//
#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       128
#endif
#if (DISPLAY_IMAGE_WIDTH != 128) && \
	(DISPLAY_IMAGE_WIDTH != 256)
#error "DISPLAY_WIDTH"
#endif

// Alçada del display
//
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      64
#endif
#if (DISPLAY_IMAGE_HEIGHT != 32) && \
	(DISPLAY_IMAGE_HEIGHT != 64) && \
	(DISPLAY_IMAGE_HEIGHT != 128)
#error "DISPLAY_HEIGHT"
#endif

// Tipus d'interficie amb el controlador
//
#define DISPLAY_SSD1306_INTERFACE_SPI  0
#define DISPLAY_SSD1306_INTERFACE_I2C  1
#ifndef DISPLAY_SSD1306_INTERFACE
#define DISPLAY_SSD1306_INTERFACE      DISPLAY_SSD1306_INTERFACE_SPI
#endif
#if (DISPLAY_SSD1306_INTERFASE != DISPLAY_SSD1306_INTERFACE_SPI) && \
    (DISPLAY_SSD1306_INTERFASE != DISPLAY_SSD1306_INTERFACE_I2C)
#error "DISPLAY_SSD1306_INTERFACE"
#endif


#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/Graphics/eosColor.h"
#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)
#include "HTL/htlSPI.h"
#include "HTL/htlGPIO.h"
#elif (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_I2C)
#include "HTL/htlI2C.h"
#endif


namespace eos {

    class DisplayDriver_SSD1306: public IDisplayDriver {
    	private:
			static constexpr int _displayWidth  = DISPLAY_WIDTH;
			static constexpr int _displayHeight = DISPLAY_HEIGHT;

			FrameBuffer *_frameBuffer;
    		int _pages;
    		int _columns;

            void initializeInterface();
            void initializeController();
            void writeCommand(uint8_t cmd);
            void writeData(const uint8_t* data, int length);

    	public:
            DisplayDriver_SSD1306(FrameBuffer *frameBuffer);

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


#endif // __eosDisplayDriver_SSD1306__

