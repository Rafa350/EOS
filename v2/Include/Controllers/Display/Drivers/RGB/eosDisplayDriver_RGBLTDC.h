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
			using GPIO_BKE = board::display::GPIO_BKE;
			using GPIO_LCDE = board::display::GPIO_LCDE;
			using GPIO_DE = board::display::GPIO_DE;
			using GPIO_HSYNC = board::display::GPIO_HSYNC;
			using GPIO_VSYNC = board::display::GPIO_VSYNC;
			using GPIO_PC = board::display::GPIO_PC;
			using GPIO_R0 = board::display::GPIO_R0;
			using GPIO_R1 = board::display::GPIO_R1;
			using GPIO_R2 = board::display::GPIO_R2;
			using GPIO_R3 = board::display::GPIO_R3;
			using GPIO_R4 = board::display::GPIO_R4;
			using GPIO_R5 = board::display::GPIO_R5;
			using GPIO_R6 = board::display::GPIO_R6;
			using GPIO_R7 = board::display::GPIO_R7;
			using GPIO_G0 = board::display::GPIO_G0;
			using GPIO_G1 = board::display::GPIO_G1;
			using GPIO_G2 = board::display::GPIO_G2;
			using GPIO_G3 = board::display::GPIO_G3;
			using GPIO_G4 = board::display::GPIO_G4;
			using GPIO_G5 = board::display::GPIO_G5;
			using GPIO_G6 = board::display::GPIO_G6;
			using GPIO_G7 = board::display::GPIO_G7;
			using GPIO_B0 = board::display::GPIO_B0;
			using GPIO_B1 = board::display::GPIO_B1;
			using GPIO_B2 = board::display::GPIO_B2;
			using GPIO_B3 = board::display::GPIO_B3;
			using GPIO_B4 = board::display::GPIO_B4;
			using GPIO_B5 = board::display::GPIO_B5;
			using GPIO_B6 = board::display::GPIO_B6;
			using GPIO_B7 = board::display::GPIO_B7;

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

    		FrameBuffer *_displayFrameBuffer;
    		FrameBuffer *_workFrameBuffer;

            void initializeGPIO();
            void initializeLTDC();

		public:
    		DisplayDriver_RGBLTDC(FrameBuffer *frameBuffer1, FrameBuffer *frameBuffer2 = nullptr);

            void initialize() override;
            void shutdown() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getImageWidth() const override { return _displayFrameBuffer->getImageWidth(); }
            inline int getImageHeight() const override { return _displayFrameBuffer->getImageHeight(); }

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
