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
			GpioPinAdapter<DISPLAY_LCDE_PORT, DISPLAY_LCDE_PIN> _pinLCDE;
			GpioPinAdapter<DISPLAY_BKE_PORT, DISPLAY_BKE_PIN> _pinBKE;
			GpioPinAdapter<DISPLAY_HSYNC_PORT, DISPLAY_HSYNC_PIN> _pinHSYNC;
			GpioPinAdapter<DISPLAY_VSYNC_PORT, DISPLAY_VSYNC_PIN> _pinVSYNC;
			GpioPinAdapter<DISPLAY_DE_PORT, DISPLAY_DE_PIN> _pinDE;
			GpioPinAdapter<DISPLAY_DOTCLK_PORT, DISPLAY_DOTCLK_PIN> _pinDOTCLK;

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
