#ifndef __eosDisplayDriver_RGBLTDC__
#define	__eosDIsplayDriver_RGBLTDC__


// EOS includes
//
#include "eos.h"


// Amplada de la imatge
//
#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH      480
#endif
#if (DISPLAY_IMAGE_WIDTH != 480)
#error DISPLAY_IMAGE_WIDTH
#endif

// Alçada de la imatge
//
#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT     272
#endif
#if (DISPLAY_IMAGE_HEIGHT != 272)
#error DISPLAY_IMAGE_WIDTH
#endif

// Format de color
//
#ifndef DISPLAY_COLOR_FORMAT
#define DISPLAY_COLOR_FORMAT      ColorFormat::rgb565
#endif

// Activacio del doble buffer
//
#ifndef DISPLAY_DOUBLEBUFFER
#define DISPLAY_DOUBLEBUFFER      false
#endif


#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlLTDC.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

	class DisplayDriver_RGBLTDC: public IDisplayDriver {
		private:
			typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;

		private:
			constexpr static const int _imageWidth       = DISPLAY_IMAGE_WIDTH;
			constexpr static const int _imageHeight      = DISPLAY_IMAGE_HEIGHT;
			constexpr static const int _imageBuffer      = DISPLAY_IMAGE_BUFFER;
			constexpr static const bool _useDoubleBuffer = DISPLAY_DOUBLEBUFFER;

		private:
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_BKE_PORT), htl::GPIOPin(DISPLAY_BKE_PIN)> PinBKE;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_LCDE_PORT), htl::GPIOPin(DISPLAY_LCDE_PIN)> PinLCDE;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_HSYNC_PORT), htl::GPIOPin(DISPLAY_HSYNC_PIN)> PinHSYNC;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_VSYNC_PORT), htl::GPIOPin(DISPLAY_VSYNC_PIN)> PinVSYNC;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_DE_PORT), htl::GPIOPin(DISPLAY_DE_PIN)> PinDE;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_DOTCLK_PORT), htl::GPIOPin(DISPLAY_DOTCLK_PIN)> PinDOTCLK;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R0_PORT), htl::GPIOPin(DISPLAY_R0_PIN)> PinR0;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R1_PORT), htl::GPIOPin(DISPLAY_R1_PIN)> PinR1;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R2_PORT), htl::GPIOPin(DISPLAY_R2_PIN)> PinR2;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R3_PORT), htl::GPIOPin(DISPLAY_R3_PIN)> PinR3;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R4_PORT), htl::GPIOPin(DISPLAY_R4_PIN)> PinR4;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R5_PORT), htl::GPIOPin(DISPLAY_R5_PIN)> PinR5;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R6_PORT), htl::GPIOPin(DISPLAY_R6_PIN)> PinR6;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_R7_PORT), htl::GPIOPin(DISPLAY_R7_PIN)> PinR7;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G0_PORT), htl::GPIOPin(DISPLAY_G0_PIN)> PinG0;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G1_PORT), htl::GPIOPin(DISPLAY_G1_PIN)> PinG1;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G2_PORT), htl::GPIOPin(DISPLAY_G2_PIN)> PinG2;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G3_PORT), htl::GPIOPin(DISPLAY_G3_PIN)> PinG3;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G4_PORT), htl::GPIOPin(DISPLAY_G4_PIN)> PinG4;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G5_PORT), htl::GPIOPin(DISPLAY_G5_PIN)> PinG5;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G6_PORT), htl::GPIOPin(DISPLAY_G6_PIN)> PinG6;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_G7_PORT), htl::GPIOPin(DISPLAY_G7_PIN)> PinG7;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B0_PORT), htl::GPIOPin(DISPLAY_B0_PIN)> PinB0;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B1_PORT), htl::GPIOPin(DISPLAY_B1_PIN)> PinB1;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B2_PORT), htl::GPIOPin(DISPLAY_B2_PIN)> PinB2;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B3_PORT), htl::GPIOPin(DISPLAY_B3_PIN)> PinB3;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B4_PORT), htl::GPIOPin(DISPLAY_B4_PIN)> PinB4;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B5_PORT), htl::GPIOPin(DISPLAY_B5_PIN)> PinB5;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B6_PORT), htl::GPIOPin(DISPLAY_B6_PIN)> PinB6;
			typedef htl::GPIOPinAdapter<htl::GPIOPort(DISPLAY_B7_PORT), htl::GPIOPin(DISPLAY_B7_PIN)> PinB7;

    	private:
			htl::LTDC_1 _ltdc;
    		FrameBuffer *_frontFrameBuffer;
    		FrameBuffer *_backFrameBuffer;
    		void *_frontImageBuffer;
    		void *_backImageBuffer;

        public:
    		DisplayDriver_RGBLTDC();

            void initialize() override;
            void shutdown() override;

            void displayOn() override;
            void displayOff() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int getImageWidth() const override { return _frontFrameBuffer->getImageWidth(); }
            inline int getImageHeight() const override { return _frontFrameBuffer->getImageHeight(); }

            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color* colors, int pitch) override;
            void setPixels(int x, int y, int width, int height, const void* pixels, ColorFormat format, int pitch) override;

            void refresh() override;

        private:
            void initializeGPIO();
            void initializeLTDC();
    };
}

#endif // __eosDisplayDriver_RGBLTDC__
