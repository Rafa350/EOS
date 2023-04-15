#pragma once
#ifndef __eosDisplayDriver_ILI9341__
#define	__eosDisplayDriver_ILI9341__


#include "eos.h"


#if !defined(DISPLAY_INTERFACE_SPI) && \
    !defined(DISPLAY_INTERFACE_8080) && \
    !defined(DISPLAY_INTERFACE_6800) && \
    !defined(DISPLAY_INTERFACE_RGB)
    #error "Undefined DISPLAY_INTERFACE_xxxx"
#endif


#if defined(DISPLAY_INTERFACE_SPI) || \
    defined(DISPLAY_INTERFACE_RGB)
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
			#if defined (DISPLAY_INTERFACE_6800)
				using PinTE = DISPLAY_TE_GPIO;
			#endif
			#if defined(DISPLAY_INTERFACE_SPI) || \
			    defined(DISPLAY_INTERFACE_RGB)
    			using PinTE = DISPLAY_TE_Pin;
				using PinSCK = DISPLAY_SCK_Pin;
				using PinMOSI = DISPLAY_MOSI_Pin;
				using Spi = DISPLAY_SPI;
			#endif
			#if defined(DISPLAY_RST_GPIO)
    			using PinRST = DISPLAY_RST_GPIO;
			#endif
    		using PinCS = DISPLAY_CS_Pin;
    		using PinRS = DISPLAY_RS_Pin;

    	private:
    		constexpr static int16_t _displayWidth = DISPLAY_WIDTH;
    		constexpr static int16_t _displayHeight = DISPLAY_HEIGHT;

    	private:
    		int16_t _maxX;
    		int16_t _maxY;

        public:
            DisplayDriver_ILI9341();

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int16_t getMaxX() const override { return _maxX; }
            inline int16_t getMaxY() const override { return _maxY; }
            inline int16_t getWidth() const override { return _displayWidth; }
            inline int16_t getHeight() const override { return _displayHeight; }

            void clear(Color color) override;

            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t pitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *pixels, ColorFormat format, int16_t pitch) override;

            void refresh() override;

        private:
            void writeRegion(Color color);
            void writeRegion(Color color, int32_t count);
            void writeRegion(const Color *colors, int32_t count);
            void readRegion(Color *colors, int32_t count);
            void selectRegion(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

            void initializeInterface();
            void initializeController();

            void open();
            void close();
            void writeCommand(uint8_t cmd);
            void writeData(uint8_t data);
            void writeData(const uint8_t *data, int32_t length);
    };
}


#endif // __eosDisplayDriver_ILI9341__

