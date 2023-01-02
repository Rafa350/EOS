#pragma once
#ifndef __eosDisplayDriver_RGBLTDC__
#define	__eosDisplayDriver_RGBLTDC__


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
			using PinR0 = DISPLAY_R0_GPIO;
			using PinR1 = DISPLAY_R1_GPIO;
			using PinR2 = DISPLAY_R2_GPIO;
			using PinR3 = DISPLAY_R3_GPIO;
			using PinR4 = DISPLAY_R4_GPIO;
			using PinR5 = DISPLAY_R5_GPIO;
			using PinR6 = DISPLAY_R6_GPIO;
			using PinR7 = DISPLAY_R7_GPIO;
			using PinG0 = DISPLAY_G0_GPIO;
			using PinG1 = DISPLAY_G1_GPIO;
			using PinG2 = DISPLAY_G2_GPIO;
			using PinG3 = DISPLAY_G3_GPIO;
			using PinG4 = DISPLAY_G4_GPIO;
			using PinG5 = DISPLAY_G5_GPIO;
			using PinG6 = DISPLAY_G6_GPIO;
			using PinG7 = DISPLAY_G7_GPIO;
			using PinB0 = DISPLAY_B0_GPIO;
			using PinB1 = DISPLAY_B1_GPIO;
			using PinB2 = DISPLAY_B2_GPIO;
			using PinB3 = DISPLAY_B3_GPIO;
			using PinB4 = DISPLAY_B4_GPIO;
			using PinB5 = DISPLAY_B5_GPIO;
			using PinB6 = DISPLAY_B6_GPIO;
			using PinB7 = DISPLAY_B7_GPIO;

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
			static constexpr int _displayWidth     = DISPLAY_WIDTH;
			static constexpr int _displayHeight    = DISPLAY_HEIGHT;
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
            inline int getWidth() const override { return _displayWidth; }
            inline int getHeight() const override { return _displayHeight; }
            inline int getMaxX() const override { return _displayFrameBuffer->getMaxX(); }
            inline int getMaxY() const override { return _displayFrameBuffer->getMaxY(); }

            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *colors, int colorPitch) override;
            void setPixels(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch) override;

            void refresh() override;
    };
}

#endif // __eosDisplayDriver_RGBLTDC__
