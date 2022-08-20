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
			using PinBKE = board::display::GPIO_BKE;
			using PinLCDE = board::display::GPIO_LCDE;
			using PinDE = board::display::GPIO_DE;
			using PinHSYNC = board::display::GPIO_HSYNC;
			using PinVSYNC = board::display::GPIO_VSYNC;
			using PinPC = board::display::GPIO_PC;
			using PinR0 = board::display::GPIO_R0;
			using PinR1 = board::display::GPIO_R1;
			using PinR2 = board::display::GPIO_R2;
			using PinR3 = board::display::GPIO_R3;
			using PinR4 = board::display::GPIO_R4;
			using PinR5 = board::display::GPIO_R5;
			using PinR6 = board::display::GPIO_R6;
			using PinR7 = board::display::GPIO_R7;
			using PinG0 = board::display::GPIO_G0;
			using PinG1 = board::display::GPIO_G1;
			using PinG2 = board::display::GPIO_G2;
			using PinG3 = board::display::GPIO_G3;
			using PinG4 = board::display::GPIO_G4;
			using PinG5 = board::display::GPIO_G5;
			using PinG6 = board::display::GPIO_G6;
			using PinG7 = board::display::GPIO_G7;
			using PinB0 = board::display::GPIO_B0;
			using PinB1 = board::display::GPIO_B1;
			using PinB2 = board::display::GPIO_B2;
			using PinB3 = board::display::GPIO_B3;
			using PinB4 = board::display::GPIO_B4;
			using PinB5 = board::display::GPIO_B5;
			using PinB6 = board::display::GPIO_B6;
			using PinB7 = board::display::GPIO_B7;
			using Ltdc = htl::LTDC_1;
			using LtdcLayer = htl::LTDCLayer_1;

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
			static constexpr uint16_t _displayWidth      = board::display::width;
			static constexpr uint16_t _displayHeight     = board::display::height;
			static constexpr uint32_t _buffer      = board::display::buffer;

    		FrameBuffer *_displayFrameBuffer;
    		FrameBuffer *_workFrameBuffer;

            void initializeGPIO();
            void initializeLTDC();

		public:
    		DisplayDriver_RGBLTDC(FrameBuffer *frameBuffer1, FrameBuffer *frameBuffer2 = nullptr);

            void initialize() override;
            void deinitialize() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getWidth() const override { return _displayFrameBuffer->getWidth(); }
            inline int getHeight() const override { return _displayFrameBuffer->getHeight(); }

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
