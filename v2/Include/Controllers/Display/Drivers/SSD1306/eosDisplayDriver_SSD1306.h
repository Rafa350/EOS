#ifndef __eosDisplayDriver_SSD1306__
#define __eosDisplayDriver_SSD1306__


#include "eos.h"


// Amplada del display
//
#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH        128
#endif
#if (DISPLAY_WIDTH != 128) && \
	(DISPLAY_WIDTH != 256)
#error "Invalid DISPLAY_WIDTH"
#endif

// Alçada del display
//
#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT       64
#endif
#if (DISPLAY_HEIGHT != 32) && \
	(DISPLAY_HEIGHT != 64) && \
	(DISPLAY_HEIGHT != 128)
#error "Invalid DISPLAY_HEIGHT"
#endif

// Tipus d'interficie amb el controlador
//
#if !defined(DISPLAY_INTERFACE_SPI) && \
    !defined(DISPLAY_INTERFACE_I2C)
#error "Undefined DISPLAY_INTERFACE_xxxx"
#endif


#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "System/Graphics/eosColor.h"
#if defined(DISPLAY_INTERFACE_SPI)
#include "HTL/htlSPI.h"
#include "HTL/htlGPIO.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"
#elif defined(DISPLAY_INTERFACE_I2C)
#include "HTL/htlI2C.h"
#include "HTL/htlGPIO.h"
#include "Controllers/Display/Drivers/SSD1306/eosDevice_SSD1306.h"
#endif


namespace eos {

    class DisplayDriver_SSD1306: public IDisplayDriver {
    	private:
			static constexpr int16_t _displayWidth  = DISPLAY_WIDTH;
			static constexpr int16_t _displayHeight = DISPLAY_HEIGHT;
			static constexpr htl::spi::ClockDivider _spiClockDivider = htl::spi::ClockDivider::_32;
			static constexpr htl::spi::ClkPolarity _spiClkPolarity = htl::spi::ClkPolarity::low;
			static constexpr htl::spi::ClkPhase _spiClkPhase = htl::spi::ClkPhase::edge1;

			#if defined(DISPLAY_INTERFACE_SPI)
			using PinCS = DISPLAY_CS_Pin;
			using PinDC = DISPLAY_DC_Pin;
			static constexpr PinCS *_pinCS = PinCS::pInst;
			static constexpr PinDC *_pinDC = PinDC::pInst;
			#ifdef DISPLAY_RST_Pin
			using PinRST = DISPLAY_RST_Pin;
            static constexpr PinRST *_pinRST = PinRST::pInst;
			#endif
			using PinSCK = DISPLAY_SCK_Pin;
			using PinMOSI = DISPLAY_MOSI_Pin;
			using DevSPI = DISPLAY_SPI_Device;
			using DevSSD1306 = SSD1306_SPI_Device;
			static constexpr DevSPI *_devSPI = DevSPI::pInst;
			#endif

			FrameBuffer *_frameBuffer;
			DevSSD1306 _device;

    	public:
            DisplayDriver_SSD1306(FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
            void setOrientation(DisplayOrientation orientation) override;
            int16_t getMaxX() const override { return _frameBuffer->getMaxX(); }
            int16_t getMaxY() const override { return _frameBuffer->getMaxY(); }
            int16_t getWidth() const override { return _displayWidth; }
            int16_t getHeight() const override { return _displayHeight; };

            void clear(Color color) override;
            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t pitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *pixels, ColorFormat format, int16_t pitch) override;

            void refresh() override;
    };
}


#endif // __eosDisplayDriver_SSD1306__

