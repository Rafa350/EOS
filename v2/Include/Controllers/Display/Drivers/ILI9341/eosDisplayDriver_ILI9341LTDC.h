#pragma once
#ifndef __eosDisplayDriver_ILI9341LTDC__
#define __eosDisplayDriver_ILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "HTL/STM32/htlLTDC.h"


namespace eos {

    class Device_ILI9341;

    class DisplayDriver_ILI9341LTDC: public DisplayDriver {
        private:
            Device_ILI9341 * const _devILI9341;
            htl::ltdc::LTDCDevice * const _devLTDC;
            htl::ltdc::LTDCLayerDevice * const _devLTDCLayer;
            FrameBuffer * const _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(Device_ILI9341 *devILI9341,
            	htl::ltdc::LTDCDevice *devLTDC, htl::ltdc::LTDCLayerDevice *devLTDCLayer,
				FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            int16_t getMaxX() const override { return _frameBuffer->getMaxX(); }
            int16_t getMaxY() const override { return _frameBuffer->getMaxY(); }
            int16_t getWidth() const override { return _frameBuffer->getWidth(); }
            int16_t getHeight() const override { return _frameBuffer->getHeight(); }

            void clear(Color color) override;
            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t pitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *pixels, ColorFormat format, int16_t pitch) override;

            void refresh() override;
    };
}


#endif // __eosDisplayDriver_ILI9341LTDC__
