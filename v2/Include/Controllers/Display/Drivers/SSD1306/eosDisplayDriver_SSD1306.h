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

// Interficie amb el controlador
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
#include "HAL/halSPITpl.h"
#include "HAL/halGPIOTpl.h"
#elif (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_I2C)
#include "HAL/halI2C.h"
#endif


namespace eos {

    class DisplayDriver_SSD1306: public IDisplayDriver {
    	private:
			constexpr static const int _displayWidth = DISPLAY_IMAGE_WIDTH;
			constexpr static const int _displayHeight = DISPLAY_IMAGE_HEIGHT;
			constexpr static const int _imageBuffer   = DISPLAY_IMAGE_BUFFER;

    	private:
#ifdef DISPLAY_RST_PORT
			typedef GpioPinAdapter<GpioPort(DISPLAY_RST_PORT), GpioPin(DISPLAY_RST_PIN)> PinRST;
#endif
			typedef GpioPinAdapter<GpioPort(DISPLAY_CS_PORT), GpioPin(DISPLAY_CS_PIN)> PinCS;
			typedef GpioPinAdapter<GpioPort(DISPLAY_DC_PORT), GpioPin(DISPLAY_DC_PIN)> PinDC;
			typedef GpioPinAdapter<GpioPort(DISPLAY_SCK_PORT), GpioPin(DISPLAY_SCK_PIN)> PinSCK;
			typedef GpioPinAdapter<GpioPort(DISPLAY_MOSI_PORT), GpioPin(DISPLAY_MOSI_PIN)> PinMOSI;
			typedef SpiAdapter<SpiChannel(DISPLAY_SPI_CHANNEL)> Spi;

    	private:
#if (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_SPI)
	#ifdef DISPLAY_RST_PORT
			PinRST _pinRST;
	#endif
			PinCS _pinCS;
			PinDC _pinDC;
			PinSCK _pinSCK;
			PinMOSI _pinMOSI;
			Spi _spi;
#elif (DISPLAY_SSD1306_INTERFACE == DISPLAY_SSD1306_INTERFACE_I2C)
#endif

    		static IDisplayDriver* _instance;
    		FrameBuffer* _frameBuffer;

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

