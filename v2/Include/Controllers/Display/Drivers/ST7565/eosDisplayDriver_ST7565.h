#pragma once
#ifndef __eosDisplayDriver_ST7565__
#define	__eosDisplayDriver_ST7565__


#include "eos.h"


// Amplada del display
//
#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH        128
#endif
#if (DISPLAY_WIDTH != 128) && \
	(DISPLAY_WIDTH != 256)
#error "Invalid DISPLAY_WIDTH"
#endif

// Alçada del display
//
#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT       64
#endif
#if (DISPLAY_HEIGHT != 32) && \
	(DISPLAY_HEIGHT != 64) && \
	(DISPLAY_HEIGHT != 128)
#error "Invalid DISPLAY_HEIGHT"
#endif


#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "Controllers/Display/Drivers/ST7565/eosDevice_ST7565.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class DisplayDriver_ST7565: public IDisplayDriver {
    	private:
            static constexpr int _displayWidth = DISPLAY_WIDTH;
            static constexpr int _displayHeight = DISPLAY_HEIGHT;

    	private:
            Device_ST7565 * const _device;
            FrameBuffer * const _frameBuffer;

        private:
            void initializeController();
            void writePixel(Color color, unsigned count);
            void writePixel(const Color *colors, unsigned count);
            void readPixel(Color *colors, unsigned count);
            void selectRegion(int x, int y, int width, int height);
            void startMemoryWrite();
            void startMemoryRead();
            void setPage(uint8_t page);
            void setColumn(uint8_t column);

            void initializeInterface();
            void writeDataRegister(uint8_t data);
            void writeCtrlRegister(uint8_t data);
            void writeRegister(uint8_t data);

        public:
            DisplayDriver_ST7565(Device_ST7565 *device, FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getMaxX() const override { return _frameBuffer->getMaxX(); }
            int getMaxY() const override { return _frameBuffer->getMaxY(); }
            int getWidth() const override { return _displayWidth; }
            int getHeight() const override { return _displayHeight; };

            void clear(Color color) override;
            void setPixel(int x, int y, Color color) override;
            void setHPixels(int x, int y, int size, Color color) override;
            void setVPixels(int x, int y, int size, Color color) override;
            void setPixels(int x, int y, int width, int height, Color color) override;
            void setPixels(int x, int y, int width, int height, const Color *colors, int pitch) override;
            void setPixels(int x, int y, int width, int height, const void *pixels, ColorFormat format, int pitch) override;
            void refresh() override;
    };
}


#endif	// __eosDislayDriver_ST7565__
