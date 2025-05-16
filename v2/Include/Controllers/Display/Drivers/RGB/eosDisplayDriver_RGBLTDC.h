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

	class DisplayDriver_RGBLTDC: public DisplayDriver {
		private:
			using PinLCDE = DISPLAY_LCDE_Pin;
			using PinBKE = DISPLAY_BKE_Pin;

			static constexpr auto _pinLCDE = PinLCDE::pInst;
            static constexpr auto _pinBKE = PinBKE::pInst;

            htl::ltdc::LTDCDevice * const _devLTDC;
			htl::ltdc::LTDCLayerDevice * const _devLTDCLayer;
    		FrameBuffer *_displayFrameBuffer;
    		FrameBuffer *_workFrameBuffer;

            void initializeGPIO();

		public:
    		DisplayDriver_RGBLTDC(
    			htl::ltdc::LTDCDevice *devLTDC, htl::ltdc::LTDCLayerDevice *devLTDCLayer,
				FrameBuffer *frameBuffer1, FrameBuffer *frameBuffer2);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int16_t getWidth() const override { return _displayFrameBuffer->getWidth(); }
            inline int16_t getHeight() const override { return _displayFrameBuffer->getHeight(); }
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
