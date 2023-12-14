#pragma once
#ifndef __eosDisplayDriver_RGBLTDC__
#define __eosDisplayDriver_RGBLTDC__


// EOS includes
//
#include "eos.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

	class DisplayDriver_RGBLTDC: public IDisplayDriver {
		private:
	        using PinPC = DISPLAY_PC_Pin;
	        using PinHSYNC = DISPLAY_HSYNC_Pin;
            using PinVSYNC = DISPLAY_VSYNC_Pin;
            using PinDE = DISPLAY_DE_Pin;

			using PinR0 = DISPLAY_R0_Pin;
			using PinR1 = DISPLAY_R1_Pin;
			using PinR2 = DISPLAY_R2_Pin;
			using PinR3 = DISPLAY_R3_Pin;
			using PinR4 = DISPLAY_R4_Pin;
			using PinR5 = DISPLAY_R5_Pin;
			using PinR6 = DISPLAY_R6_Pin;
			using PinR7 = DISPLAY_R7_Pin;
			using PinG0 = DISPLAY_G0_Pin;
			using PinG1 = DISPLAY_G1_Pin;
			using PinG2 = DISPLAY_G2_Pin;
			using PinG3 = DISPLAY_G3_Pin;
			using PinG4 = DISPLAY_G4_Pin;
			using PinG5 = DISPLAY_G5_Pin;
			using PinG6 = DISPLAY_G6_Pin;
			using PinG7 = DISPLAY_G7_Pin;
			using PinB0 = DISPLAY_B0_Pin;
			using PinB1 = DISPLAY_B1_Pin;
			using PinB2 = DISPLAY_B2_Pin;
			using PinB3 = DISPLAY_B3_Pin;
			using PinB4 = DISPLAY_B4_Pin;
			using PinB5 = DISPLAY_B5_Pin;
			using PinB6 = DISPLAY_B6_Pin;
			using PinB7 = DISPLAY_B7_Pin;
			using PinLCDE = DISPLAY_LCDE_Pin;
			using PinBKE = DISPLAY_BKE_Pin;
			using DevLTDC = htl::ltdc::LTDCDevice;
			using DevLTDCLayer = htl::ltdc::LTDCLayerDevice1;

			static constexpr PinLCDE *_pinLCDE = PinLCDE::pInst;
            static constexpr PinBKE *_pinBKE = PinBKE::pInst;

            static constexpr DevLTDC *_devLTDC = DevLTDC::pInst;
			static constexpr DevLTDCLayer *_devLTDCLayer = DevLTDCLayer::pInst;

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
			static constexpr int16_t _displayWidth = DISPLAY_WIDTH;
			static constexpr int16_t _displayHeight= DISPLAY_HEIGHT;
			static constexpr uint32_t _buffer      = DISPLAY_BUFFER;

    		FrameBuffer *_displayFrameBuffer;
    		FrameBuffer *_workFrameBuffer;

            void initializeGPIO();
            void initializeLTDC();

		public:
    		DisplayDriver_RGBLTDC(FrameBuffer *frameBuffer1, FrameBuffer *frameBuffer2 = nullptr);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int16_t getWidth() const override { return _displayWidth; }
            inline int16_t getHeight() const override { return _displayHeight; }
            inline int16_t getMaxX() const override { return _displayFrameBuffer->getMaxX(); }
            inline int16_t getMaxY() const override { return _displayFrameBuffer->getMaxY(); }

            void clear(Color color) override;
            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

            void refresh() override;
    };
}


#endif // __eosDisplayDriver_RGBLTDC__
