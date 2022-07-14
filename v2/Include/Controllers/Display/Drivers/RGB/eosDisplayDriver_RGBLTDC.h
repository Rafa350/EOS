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

			typedef DISPLAY_BKE_TYPE GPIO_BKE;
			typedef DISPLAY_LCDE_TYPE GPIO_LCDE;
			typedef DISPLAY_HSYNC_TYPE GPIO_HSYNC;
			typedef DISPLAY_VSYNC_TYPE GPIO_VSYNC;
			typedef DISPLAY_DE_TYPE GPIO_DE;
			typedef DISPLAY_DOTCLK_TYPE GPIO_DOTCLK;
			typedef DISPLAY_R0_TYPE GPIO_R0;
			typedef DISPLAY_R1_TYPE GPIO_R1;
			typedef DISPLAY_R2_TYPE GPIO_R2;
			typedef DISPLAY_R3_TYPE GPIO_R3;
			typedef DISPLAY_R4_TYPE GPIO_R4;
			typedef DISPLAY_R5_TYPE GPIO_R5;
			typedef DISPLAY_R6_TYPE GPIO_R6;
			typedef DISPLAY_R7_TYPE GPIO_R7;
			typedef DISPLAY_G0_TYPE GPIO_G0;
			typedef DISPLAY_G1_TYPE GPIO_G1;
			typedef DISPLAY_G2_TYPE GPIO_G2;
			typedef DISPLAY_G3_TYPE GPIO_G3;
			typedef DISPLAY_G4_TYPE GPIO_G4;
			typedef DISPLAY_G5_TYPE GPIO_G5;
			typedef DISPLAY_G6_TYPE GPIO_G6;
			typedef DISPLAY_G7_TYPE GPIO_G7;
			typedef DISPLAY_B0_TYPE GPIO_B0;
			typedef DISPLAY_B1_TYPE GPIO_B1;
			typedef DISPLAY_B2_TYPE GPIO_B2;
			typedef DISPLAY_B3_TYPE GPIO_B3;
			typedef DISPLAY_B4_TYPE GPIO_B4;
			typedef DISPLAY_B5_TYPE GPIO_B5;
			typedef DISPLAY_B6_TYPE GPIO_B6;
			typedef DISPLAY_B7_TYPE GPIO_B7;
			typedef htl::LTDC_1 LCD;
			typedef htl::LTDCLayer_1 LCDLayer;

		private:
			constexpr static const int _imageWidth       = DISPLAY_IMAGE_WIDTH;
			constexpr static const int _imageHeight      = DISPLAY_IMAGE_HEIGHT;
			constexpr static const int _imageBuffer      = DISPLAY_IMAGE_BUFFER;
			constexpr static const bool _useDoubleBuffer = DISPLAY_DOUBLEBUFFER;

    	private:
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
