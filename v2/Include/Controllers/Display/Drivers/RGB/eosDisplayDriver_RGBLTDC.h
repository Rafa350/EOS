#ifndef __eosDisplayDriver_RGBLTDC__
#define	__eosDIsplayDriver_RGBLTDC__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"


// Amplada de la imatge
//
#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      480
#endif

// Alçada de la imatge
//
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     272
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


namespace eos {

	class DisplayDriver_RGBLTDC: public IDisplayDriver {
		private:
			typedef ColorInfo<DISPLAY_COLOR_FORMAT> CI;

		private:
			constexpr static const int _screenWidth         = DISPLAY_SCREEN_WIDTH;
			constexpr static const int _screenHeight        = DISPLAY_SCREEN_HEIGHT;
			constexpr static const int _imageBuffer         = DISPLAY_IMAGE_BUFFER;
			constexpr static const bool _useDoubleBuffer    = DISPLAY_DOUBLEBUFFER;

    	private:
    		FrameBuffer *_frontFrameBuffer;
    		FrameBuffer *_backFrameBuffer;
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
            void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) override;

            void writePixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, void *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;

            void refresh() override;

        private:
            void initializeGPIO();
            void initializeLTDC();
    };
}

#endif // __eosDisplayDriver_RGBLTDC__
