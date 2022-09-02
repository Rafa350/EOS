#pragma once
#ifndef __eosDisplayDriver_ILI9341__
#define	__eosDisplayDriver_ILI9341__


#include "eos.h"
#if defined(DISPLAY_INTERFACE_SPI) || defined(DISPLAY_INTERFACE_RGB)
#include "HTL/htlSPI.h"
#endif
#include "HTL/htlGPIO.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class DisplayDriver_ILI9341: public IDisplayDriver {
    	private:
			#if defined(DISPLAY_INTERFACE_8080)
				using PinRDX = DISPLAY_RDX_GPIO;
				using PinWRX = DISPLAY_WRX_GPIO;
    			using PinTE = DISPLAY_TE_GPIO;
			#endif
			#if defined(DISPLAY_INTERFACE_6800)
				using PinTE = DISPLAY_TE_GPIO;
			#endif
			#if defined(DISPLAY_INTERFACE_SPI) || defined(DISPLAY_INTERFACE_RGB)
    			using PinTE = DISPLAY_TE_GPIO;
				using PinSCK = DISPLAY_SCK_GPIO;
				using PinMOSI = DISPLAY_MOSI_GPIO;
				using Spi = DISPLAY_SPI;
			#endif
			#ifdef DISPLAY_RST_GPIO
    			using PinRST = DISPLAY_RST_GPIO;
			#endif
    		using PinCS = DISPLAY_CS_GPIO;
    		using PinRS = DISPLAY_RS_GPIO;

    	private:
    		constexpr static int _displayWidth = DISPLAY_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_HEIGHT;

    	private:
    		int _maxX;
    		int _maxY;

        public:
            DisplayDriver_ILI9341();

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getMaxX() const override { return _maxX; }
            inline int getMaxY() const override { return _maxY; }
            inline int getWidth() const override { return _displayWidth; }
            inline int getHeight() const override { return _displayHeight; }

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

