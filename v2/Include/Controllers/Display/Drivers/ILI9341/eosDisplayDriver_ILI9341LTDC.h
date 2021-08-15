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
#include "HAL/halGPIOTpl.h"
#include "HAL/halSPITpl.h"


namespace eos {

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
    	private:
    		typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_CS_PORT), GPIOPin(DISPLAY_CS_PIN)> PinCS;
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_RS_PORT), GPIOPin(DISPLAY_RS_PIN)> PinRS;
#ifdef DISPLAY_RTS_PIN
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_RST_PORT), GPIOPin(DISPLAY_RST_PIN)> PinRST;
#endif
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_SCK_PORT), GPIOPin(DISPLAY_SCK_PIN)> PinSCK;
    		typedef GPIOPinAdapter<GPIOPort(DISPLAY_MOSI_PORT), GPIOPin(DISPLAY_MOSI_PIN)> PinMOSI;
    		typedef SPIAdapter<SPIChannel(DISPLAY_SPI_CHANNEL)> Spi;

    	private:
    		constexpr static int _displayWidth = DISPLAY_IMAGE_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_IMAGE_HEIGHT;
    		constexpr static int _displayBuffer = DISPLAY_IMAGE_BUFFER;

        private:
    		PinCS _pinCS;
    		PinRS _pinRS;
#ifdef DISPLAY_RST_PIN
    		PinRST _pinRST;1
#endif
    		PinSCK _pinSCK;
    		PinMOSI _pinMOSI;
    		Spi _spi;
            FrameBuffer* _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC();

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
