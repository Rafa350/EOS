#ifndef __eosDisplayDriver_ILI9341LTDC__
#define	__eosDisplayDriver_ILI9341LTDC__


#include "eos.h"


// Amplada d'imatge
//
#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       240  // Tamany fix del controlador
#endif
#if (DISPLAY_IMAGE_WIDTH != 240)
#error ""DISPLAY_IMAGE_WIDTH
#endif

// Alçada d'imatge
//
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      320  // Tamany fix del controlador
#endif
#if (DISPLAY_IMAGE_HEIGHT != 320)
#error ""DISPLAY_IMAGE_HEIGHT
#endif

// Format de color
//
#ifndef DISPLAY_COLOR_FORMAT
#define DISPLAY_COLOR_FORMAT      ColorFormat::rgb565
#endif


#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
    	private:
    		using GPIO_CS = board::display::GPIO_CS;
    		using GPIO_RS = board::display::GPIO_RS;
    		using GPIO_SCK = board::display::GPIO_SCK;
    		using GPIO_MOSI = board::display::GPIO_MOSI;

			using GPIO_DE = board::display::GPIO_DE;
			using GPIO_HSYNC = board::display::GPIO_HSYNC;
			using GPIO_VSYNC = board::display::GPIO_VSYNC;
			using GPIO_PC = board::display::GPIO_PC;
			using GPIO_R2 = board::display::GPIO_R2;
			using GPIO_R3 = board::display::GPIO_R3;
			using GPIO_R4 = board::display::GPIO_R4;
			using GPIO_R5 = board::display::GPIO_R5;
			using GPIO_R6 = board::display::GPIO_R6;
			using GPIO_R7 = board::display::GPIO_R7;
			using GPIO_G2 = board::display::GPIO_G2;
			using GPIO_G3 = board::display::GPIO_G3;
			using GPIO_G4 = board::display::GPIO_G4;
			using GPIO_G5 = board::display::GPIO_G5;
			using GPIO_G6 = board::display::GPIO_G6;
			using GPIO_G7 = board::display::GPIO_G7;
			using GPIO_B2 = board::display::GPIO_B2;
			using GPIO_B3 = board::display::GPIO_B3;
			using GPIO_B4 = board::display::GPIO_B4;
			using GPIO_B5 = board::display::GPIO_B5;
			using GPIO_B6 = board::display::GPIO_B6;
			using GPIO_B7 = board::display::GPIO_B7;

			using SPI = board::display::SPI;

			static constexpr uint16_t _hSync       = board::display::hSync;
			static constexpr uint16_t _vSync       = board::display::vSync;
			static constexpr uint16_t _hBP         = board::display::hBP;
			static constexpr uint16_t _vBP         = board::display::vBP;
			static constexpr uint16_t _hFP         = board::display::hFP;
			static constexpr uint16_t _vFP         = board::display::vFP;
			static constexpr htl::LTDCPolarity _hSyncPol = board::display::hSyncPol;
			static constexpr htl::LTDCPolarity _vSyncPol = board::display::vSyncPol;
			static constexpr htl::LTDCPolarity _dePol    = board::display::dePol;
			static constexpr htl::LTDCPolarity _pcPol    = board::display::pcPol;
			static constexpr uint16_t _width       = board::display::width;
			static constexpr uint16_t _height      = board::display::height;
			static constexpr uint32_t _buffer      = board::display::buffer;

        private:
            FrameBuffer *_frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(FrameBuffer *frameBuffer);

            void initialize() override;
            void shutdown() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            int getImageWidth() const override { return _frameBuffer->getImageWidth(); }
            int getImageHeight() const override { return _frameBuffer->getImageHeight(); }

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

            void open();
            void close();
            void writeCommand(uint8_t cmd);
            void writeData(uint8_t data);
    };
}


#endif // __eos_DisplayDriver_ILI9341LTDC__
