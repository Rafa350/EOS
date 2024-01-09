#pragma once
#ifndef __eosDispleyDriver_ILI9341__
#define __eosDisplayDriver_ILI9341__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "System/Graphics/eosColor.h"


namespace eos {
    
    class Device_ILI9341;

    class DisplayDriver_ILI9341: public DisplayDriver {
    	private:
            Device_ILI9341 * const _device;
            int16_t _displayWidth;
            int16_t _displayHeight;
    		int16_t _maxX;
    		int16_t _maxY;

        public:
            DisplayDriver_ILI9341(Device_ILI9341 *device, int16_t displayWidth, int16_t displayHeight);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            void setOrientation(DisplayOrientation orientation) override;
            inline int16_t getMaxX() const override { return _maxX; }
            inline int16_t getMaxY() const override { return _maxY; }
            inline int16_t getWidth() const override { return _displayWidth; }
            inline int16_t getHeight() const override { return _displayHeight; }

            void clear(Color color) override;

            void setPixel(int16_t x, int16_t y, Color color) override;
            void setHPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setVPixels(int16_t x, int16_t y, int16_t size, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t pitch) override;
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *pixels, ColorFormat format, int16_t pitch) override;

            void refresh() override;

        private:
            void writeRegion(Color color);
            void writeRegion(Color color, int32_t count);
            void writeRegion(const Color *colors, int32_t count);
            void readRegion(Color *colors, int32_t count);
            void selectRegion(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    };
}


#endif // __eosDisplayDriver_ILI9341__
