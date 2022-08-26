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
#include "HTL/STM32/htlLTDC.h"


namespace eos {

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
    	private:
    		using PinCS = DISPLAY_CS_GPIO;
    		using PinRS = DISPLAY_RS_GPIO;
    		using PinSCK = DISPLAY_SCK_GPIO;
    		using PinMOSI = DISPLAY_MOSI_GPIO;

			using PinDE = DISPLAY_DE_GPIO;
			using PinHSYNC = DISPLAY_HSYNC_GPIO;
			using PinVSYNC = DISPLAY_VSYNC_GPIO;
			using PinPC = DISPLAY_PC_GPIO;
			using PinR2 = DISPLAY_R2_GPIO;
			using PinR3 = DISPLAY_R3_GPIO;
			using PinR4 = DISPLAY_R4_GPIO;
			using PinR5 = DISPLAY_R5_GPIO;
			using PinR6 = DISPLAY_R6_GPIO;
			using PinR7 = DISPLAY_R7_GPIO;
			using PinG2 = DISPLAY_G2_GPIO;
			using PinG3 = DISPLAY_G3_GPIO;
			using PinG4 = DISPLAY_G4_GPIO;
			using PinG5 = DISPLAY_G5_GPIO;
			using PinG6 = DISPLAY_G6_GPIO;
			using PinG7 = DISPLAY_G7_GPIO;
			using PinB2 = DISPLAY_B2_GPIO;
			using PinB3 = DISPLAY_B3_GPIO;
			using PinB4 = DISPLAY_B4_GPIO;
			using PinB5 = DISPLAY_B5_GPIO;
			using PinB6 = DISPLAY_B6_GPIO;
			using PinB7 = DISPLAY_B7_GPIO;

			using Spi = DISPLAY_SPI;
			using Ltdc = htl::LTDC_1;
			using LtdcLayer = htl::LTDCLayer_1;

			static constexpr uint16_t _hSync       = DISPLAY_HSYNC;
			static constexpr uint16_t _vSync       = DISPLAY_VSYNC;
			static constexpr uint16_t _hBP         = DISPLAY_HBP;
			static constexpr uint16_t _vBP         = DISPLAY_VBP;
			static constexpr uint16_t _hFP         = DISPLAY_HFP;
			static constexpr uint16_t _vFP         = DISPLAY_VFP;
			static constexpr htl::LTDCPolarity _hSyncPol = DISPLAY_HSYNC_POL;
			static constexpr htl::LTDCPolarity _vSyncPol = DISPLAY_VSYNC_POL;
			static constexpr htl::LTDCPolarity _dePol    = DISPLAY_DE_POL;
			static constexpr htl::LTDCPolarity _pcPol    = DISPLAY_PC_POL;
			static constexpr uint16_t _width       = DISPLAY_WIDTH;
			static constexpr uint16_t _height      = DISPLAY_HEIGHT;
			static constexpr uint32_t _buffer      = DISPLAY_BUFFER;

        private:
            FrameBuffer *_frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            int getMaxX() const override { return _frameBuffer->getMaxX(); }
            int getMaxY() const override { return _frameBuffer->getMaxY(); }
            int getWidth() const override { return _width; }
            int getHeight() const override { return _height; }

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
