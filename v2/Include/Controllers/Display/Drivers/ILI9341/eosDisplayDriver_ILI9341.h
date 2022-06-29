#ifndef __eosDisplayDriver_ILI9341__
#define	__eosDisplayDriver_ILI9341__


#include "eos.h"


// Amplada d'imatge
//
#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240
#endif
#if (DISPLAY_IMAGE_WIDTH != 240)
#error "DISPLAY_IMAGE_WIDTH"
#endif

// Alçada d'imatge
//
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320
#endif
#if (DISPLAY_IMAGE_HEIGHT != 320)
#error "DISPLAY_IMAGE_HEIGHT"
#endif

// Format de color
//
#ifndef DISPLAY_COLOR_FORMAT
#define DISPLAY_COLOR_FORMAT      ColorFormat::rgb565
#endif

// Interficie amb el controlador
//
#define DISPLAY_ILI9341_INTERRFACE_SPI      0
#define DISPLAY_ILI9341_INTERRFACE_SIO      1
#define DISPLAY_ILI9341_INTERRFACE_PIO8     2
#ifndef DISPLAY_ILI9341_INTERFACE
#define DISPLAY_ILI9341_INTERFACE           DISPLAY_INTERFACE_SPI
#endif
#if (DISPLAY_ILI9341_INTERFACE != DISPLAY_ILI9341_INTERFACE_SPI) && \
    (DISPLAY_ILI9341_INTERFACE != DISPLAY_ILI9341_INTERFACE_SIO) && \
    (DISPLAY_ILI9341_INTERFACE != DISPLAY_ILI9341_INTERFACE_PIO)
#error "DISPLAY_ILI9341_INTERFACE"
#endif


#if (DISPLAY_ILI9341_INTERFACE == DISPLAY_ILI9341_INTERFACE_SPI)
#include "HAL/halSPI_ex.h"
#endif
#include "HAL/halGPIO_ex.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class DisplayDriver_ILI9341: public IDisplayDriver {
    	private:
    		typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;
    		typedef CI::color_t pixel_t;
#ifdef DISPLAY_RST_PIN
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_RST_PORT), GPIOPin(DISPLAY_RTT_PIN)> PinRTS;
#endif
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_CS_PORT), GPIOPin(DISPLAY_CS_PIN)> PinCS;
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_RS_PORT), GPIOPin(DISPLAY_RS_PIN)> PinRS;
#if (DISPLAY_ILI9341_INTERFACE == DISPLAY_ILI9341_INTERFACE_SPI)
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_SCK_PORT), GPIOPin(DISPLAY_SCK_PIN)> PinSCK;
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_MOSI_PORT), GPIOPin(DISPLAY_MOSI_PIN)> PinMOSI;
    		typedef SPIAdapter<SPIChannel(DISPLAY_SPI_CHANNEL)> Spi;
#endif

    	private:
    		constexpr static int _displayWidth = DISPLAY_IMAGE_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_IMAGE_HEIGHT;

    	private:
#ifdef DISPLAY_RST_PIN
    		PinRST _pinRST;
#endif
    		PinCS _pinCS;
    		PinRS _pinRS;
#if (DISPLAY_ILI9341_INTERFACE == DISPLAY_ILI9341_INTERFACE_SPI)
    		PinSCK _pinSCK;
    		PinMOSI _pinMOSI;
    		Spi _spi;
#endif
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
            void setPixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int pitch) override;

            void refresh() override;

        private:
            void writeRegion(Color color);
            void writeRegion(Color color, int count);
            void writeRegion(const Color *colors, int count);
            void readRegion(Color *colors, int count);
            void selectRegion(int x, int y, int width, int height);

            inline static pixel_t toPixel(Color color) { return color.convertTo<CI::format>(); }

            void initializeInterface();
            void initializeController();

            void open();
            void close();
            void writeCommand(uint8_t cmd);
            void writeData(uint8_t data);
            void writeData(const uint8_t *data, int length);
    };
}


#endif // __eosDisplayDriver_ILI9341__

