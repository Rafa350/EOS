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
			static constexpr int _displayWidth = DISPLAY_IMAGE_WIDTH;
			static constexpr int _displayHeight = DISPLAY_IMAGE_HEIGHT;
			static constexpr int _imageBuffer   = DISPLAY_IMAGE_BUFFER;

    	private:
			#ifdef DISPLAY_RST_PORT
				using GPIO_RST = board::display::GPIO_RST;
			#endif
			#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)
				using GPIO_CS = board::display::GPIO_CS;
				using GPIO_DC = board::display::GPIO_DC;
				using GPIO_SCK = board::display::GPIO_SCK;
				using GPIO_MOSI = board::display::GPIO_MOSI;
				using SPI = board::display::SPI;
			#elif (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_I2C)
			#endif

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
            void setPixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int pitch) override;

            void refresh() override;

        private:
            void initializeInterface();
            void initializeController();
            void writeCommand(uint8_t cmd);
            void writeData(const uint8_t* data, int length);
    };
}


#endif // __eosDisplayDriver_SSD1306__

