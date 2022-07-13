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
    		typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;
    		typedef DISPLAY_CS_TYPE GPIO_CS;
    		typedef DISPLAY_RS_TYPE GPIO_RS;
#ifdef DISPLAY_RTS_PIN
    		typedef DISPLAY_RST_TYPE GPIO_RST;
#endif
    		typedef DISPLAY_SCK_TYPE GPIO_SCK;
    		typedef DISPLAY_MOSI_TYPE GPIO_MOSI;
    		typedef DISPLAY_SPI_TYPE SPI;
    		typedef DISPLAY_DE_TYPE GPIO_DE;
    		typedef DISPLAY_HSYNC_TYPE GPIO_HSYNC;
    		typedef DISPLAY_VSYNC_TYPE GPIO_VSYNC;
    		typedef DISPLAY_DOTCLK_TYPE GPIO_DOTCLK;
    		typedef DISPLAY_R2_TYPE GPIO_R2;
    		typedef DISPLAY_R3_TYPE GPIO_R3;
    		typedef DISPLAY_R4_TYPE GPIO_R4;
    		typedef DISPLAY_R5_TYPE GPIO_R5;
    		typedef DISPLAY_R6_TYPE GPIO_R6;
    		typedef DISPLAY_R7_TYPE GPIO_R7;
    		typedef DISPLAY_G2_TYPE GPIO_G2;
    		typedef DISPLAY_G3_TYPE GPIO_G3;
    		typedef DISPLAY_G4_TYPE GPIO_G4;
    		typedef DISPLAY_G5_TYPE GPIO_G5;
    		typedef DISPLAY_G6_TYPE GPIO_G6;
    		typedef DISPLAY_G7_TYPE GPIO_G7;
    		typedef DISPLAY_B2_TYPE GPIO_B2;
    		typedef DISPLAY_B3_TYPE GPIO_B3;
    		typedef DISPLAY_B4_TYPE GPIO_B4;
    		typedef DISPLAY_B5_TYPE GPIO_B5;
    		typedef DISPLAY_B6_TYPE GPIO_B6;
    		typedef DISPLAY_B7_TYPE GPIO_B7;

    	private:
    		constexpr static int _displayWidth = DISPLAY_IMAGE_WIDTH;
    		constexpr static int _displayHeight = DISPLAY_IMAGE_HEIGHT;
    		constexpr static int _displayBuffer = DISPLAY_IMAGE_BUFFER;

        private:
            FrameBuffer *_frameBuffer;

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
