#pragma once
#ifndef __eosDisplayDriver_SSD1327__
#define __eosDisplayDriver_SSD1327__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosL4FrameBuffer.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class Device_SSD1327;

    class DisplayDriver_SSD1327: public DisplayDriver {
    	private:
            Device_SSD1327 * const _device;
			L4FrameBuffer * const _frameBuffer;

    	public:
            DisplayDriver_SSD1327(Device_SSD1327 *device, L4FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
            void setOrientation(DisplayOrientation orientation) override;
            int16_t getMaxX() const override { return _frameBuffer->getMaxX(); }
            int16_t getMaxY() const override { return _frameBuffer->getMaxY(); }
            int16_t getWidth() const override { return _frameBuffer->getWidth(); }
            int16_t getHeight() const override { return _frameBuffer->getHeight(); };

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


#endif // __eosDisplayDriver_SSD1327__

