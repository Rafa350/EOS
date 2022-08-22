#ifndef __eosDisplayDriver_ILI9341__
#define	__eosDisplayDriver_ILI9341__


#include "eos.h"


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
#include "HTL/htlSPI.h"
#endif
#include "HTL/htlGPIO.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class DisplayDriver_ILI9341: public IDisplayDriver {
    	private:
#ifdef DISPLAY_RST_PIN
    		using GPIO_RST = board::display::GPIO_RST;
#endif
    		using GPIO_CS = board::display::GPIO_CS;
    		using GPIO_RS = board::display::GPIO_RS;
#if (DISPLAY_ILI9341_INTERFACE == DISPLAY_ILI9341_INTERFACE_SPI)
    		using GPIO_SCK = board::display::GPIO_SCK;
    		using GPIO_MOSI = board::display::GPIO_MOSI;
    		using SPI = board::display::SPI;
#endif

    	private:
    		constexpr static int _displayWidth = board::display::width;
    		constexpr static int _displayHeight =board::display::height;

    	private:
    		int _maxX;
    		int _maxY;

        public:
            DisplayDriver_ILI9341();

            void initialize() override;
            void deinitialize() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getMaxX() const { return _maxX; }
            inline int getMaxY() const { return _maxY; }

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
            void selectRegion(int x1, int y1, int x2, int y2);

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

