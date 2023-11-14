#pragma once
#ifndef __eosDisplayDriver_ILI9341LTDC__
#define	__eosDisplayDriver_ILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/STM32/htlLTDC.h"


namespace eos {

    class DisplayDriver_ILI9341LTDC: public IDisplayDriver {
    	private:
    		using PinSCK = DISPLAY_SCK_Pin;
    		using PinMOSI = DISPLAY_MOSI_Pin;
    		using DevSPI = DISPLAY_SPI;

    		using PinCS = DISPLAY_CS_Pin;
    		using PinRS = DISPLAY_RS_Pin;

			using PinDE = DISPLAY_DE_Pin;
			using PinHSYNC = DISPLAY_HSYNC_Pin;
			using PinVSYNC = DISPLAY_VSYNC_Pin;
			using PinPC = DISPLAY_PC_Pin;
			using PinR2 = DISPLAY_R2_Pin;
			using PinR3 = DISPLAY_R3_Pin;
			using PinR4 = DISPLAY_R4_Pin;
			using PinR5 = DISPLAY_R5_Pin;
			using PinR6 = DISPLAY_R6_Pin;
			using PinR7 = DISPLAY_R7_Pin;
			using PinG2 = DISPLAY_G2_Pin;
			using PinG3 = DISPLAY_G3_Pin;
			using PinG4 = DISPLAY_G4_Pin;
			using PinG5 = DISPLAY_G5_Pin;
			using PinG6 = DISPLAY_G6_Pin;
			using PinG7 = DISPLAY_G7_Pin;
			using PinB2 = DISPLAY_B2_Pin;
			using PinB3 = DISPLAY_B3_Pin;
			using PinB4 = DISPLAY_B4_Pin;
			using PinB5 = DISPLAY_B5_Pin;
			using PinB6 = DISPLAY_B6_Pin;
			using PinB7 = DISPLAY_B7_Pin;

			static constexpr uint16_t _hSync       = DISPLAY_HSYNC;
			static constexpr uint16_t _vSync       = DISPLAY_VSYNC;
			static constexpr uint16_t _hBP         = DISPLAY_HBP;
			static constexpr uint16_t _vBP         = DISPLAY_VBP;
			static constexpr uint16_t _hFP         = DISPLAY_HFP;
			static constexpr uint16_t _vFP         = DISPLAY_VFP;
			static constexpr htl::ltdc::PinPolarity _hSyncPol = DISPLAY_HSYNC_POL;
			static constexpr htl::ltdc::PinPolarity _vSyncPol = DISPLAY_VSYNC_POL;
			static constexpr htl::ltdc::PinPolarity _dePol    = DISPLAY_DE_POL;
			static constexpr htl::ltdc::PinPolarity _pcPol    = DISPLAY_PC_POL;
			static constexpr uint16_t _width       = DISPLAY_WIDTH;
			static constexpr uint16_t _height      = DISPLAY_HEIGHT;
			static constexpr uint32_t _buffer      = DISPLAY_BUFFER;

			static constexpr htl::ltdc::LTDCDevice *_ltdc = htl::ltdc::LTDCDevice::pInst;
            static constexpr htl::ltdc::LTDCLayerDevice1 *_ltdcLayer = htl::ltdc::LTDCLayerDevice1::pInst;
            static constexpr PinCS *_pinCS = PinCS::pInst;
            static constexpr PinRS *_pinRS = PinRS::pInst;
            static constexpr DevSPI *_devSPI = DevSPI::pInst;

        private:
            FrameBuffer * const _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            int16_t getMaxX() const override { return _frameBuffer->getMaxX(); }
            int16_t getMaxY() const override { return _frameBuffer->getMaxY(); }
            int16_t getWidth() const override { return _width; }
            int16_t getHeight() const override { return _height; }

            void clear(Color color) override;
            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t pitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *pixels, ColorFormat format, int16_t pitch) override;

            void refresh() override;

        private:
            void initializeInterface();
            void initializeController();

            void delay(unsigned time);
            void open();
            void close();
            void writeCommand(uint8_t cmd);
            void writeData(uint8_t data);
    };
}


#endif // __eosDisplayDriver_ILI9341LTDC__
