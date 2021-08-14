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


#include "HAL/halGPIOTpl.h"
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
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_BKE_PORT), GPIOPin(DISPLAY_BKE_PIN)> PinBKE;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_LCDE_PORT), GPIOPin(DISPLAY_LCDE_PIN)> PinLCDE;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_HSYNC_PORT), GPIOPin(DISPLAY_HSYNC_PIN)> PinHSYNC;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_VSYNC_PORT), GPIOPin(DISPLAY_VSYNC_PIN)> PinVSYNC;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_DE_PORT), GPIOPin(DISPLAY_DE_PIN)> PinDE;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_DOTCLK_PORT), GPIOPin(DISPLAY_DOTCLK_PIN)> PinDOTCLK;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R0_PORT), GPIOPin(DISPLAY_R0_PIN)> PinR0;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R1_PORT), GPIOPin(DISPLAY_R1_PIN)> PinR1;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R2_PORT), GPIOPin(DISPLAY_R2_PIN)> PinR2;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R3_PORT), GPIOPin(DISPLAY_R3_PIN)> PinR3;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R4_PORT), GPIOPin(DISPLAY_R4_PIN)> PinR4;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R5_PORT), GPIOPin(DISPLAY_R5_PIN)> PinR5;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R6_PORT), GPIOPin(DISPLAY_R6_PIN)> PinR6;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_R7_PORT), GPIOPin(DISPLAY_R7_PIN)> PinR7;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G0_PORT), GPIOPin(DISPLAY_G0_PIN)> PinG0;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G1_PORT), GPIOPin(DISPLAY_G1_PIN)> PinG1;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G2_PORT), GPIOPin(DISPLAY_G2_PIN)> PinG2;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G3_PORT), GPIOPin(DISPLAY_G3_PIN)> PinG3;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G4_PORT), GPIOPin(DISPLAY_G4_PIN)> PinG4;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G5_PORT), GPIOPin(DISPLAY_G5_PIN)> PinG5;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G6_PORT), GPIOPin(DISPLAY_G6_PIN)> PinG6;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_G7_PORT), GPIOPin(DISPLAY_G7_PIN)> PinG7;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B0_PORT), GPIOPin(DISPLAY_B0_PIN)> PinB0;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B1_PORT), GPIOPin(DISPLAY_B1_PIN)> PinB1;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B2_PORT), GPIOPin(DISPLAY_B2_PIN)> PinB2;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B3_PORT), GPIOPin(DISPLAY_B3_PIN)> PinB3;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B4_PORT), GPIOPin(DISPLAY_B4_PIN)> PinB4;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B5_PORT), GPIOPin(DISPLAY_B5_PIN)> PinB5;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B6_PORT), GPIOPin(DISPLAY_B6_PIN)> PinB6;
			typedef GPIOPinAdapter<GPIOPort(DISPLAY_B7_PORT), GPIOPin(DISPLAY_B7_PIN)> PinB7;

    	private:
			PinLCDE _pinLCDE;
			PinBKE _pinBKE;
			PinHSYNC _pinHSYNC;
			PinVSYNC _pinVSYNC;
			PinDE _pinDE;
			PinDOTCLK _pinDOTCLK;
			PinR0 _pinR0;
			PinR1 _pinR1;
			PinR2 _pinR2;
			PinR3 _pinR3;
			PinR4 _pinR4;
			PinR5 _pinR5;
			PinR6 _pinR6;
			PinR7 _pinR7;
			PinG0 _pinG0;
			PinG1 _pinG1;
			PinG2 _pinG2;
			PinG3 _pinG3;
			PinG4 _pinG4;
			PinG5 _pinG5;
			PinG6 _pinG6;
			PinG7 _pinG7;
			PinB0 _pinB0;
			PinB1 _pinB1;
			PinB2 _pinB2;
			PinB3 _pinB3;
			PinB4 _pinB4;
			PinB5 _pinB5;
			PinB6 _pinB6;
			PinB7 _pinB7;

    		FrameBuffer* _frontFrameBuffer;
    		FrameBuffer* _backFrameBuffer;
    		void* _frontImageBuffer;
    		void* _backImageBuffer;

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
