module;


#include "eos.h"


export module Eos.Controllers.Display.Drivers.SSD1306;


export import Eos.Controllers.Display.Drivers;
export import Eos.Controllers.Display.Buffers.L1;

import Eos.System.Graphics.Color;


export namespace eos {

    class DisplayDevice_SSD1306;

    class DisplayDriver_SSD1306: public DisplayDriver {
    	private:
            DisplayDevice_SSD1306 * const _device;
			L1FrameBuffer * const _frameBuffer;

    	public:
            DisplayDriver_SSD1306(DisplayDevice_SSD1306 *device, L1FrameBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
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


    class DisplayDevice_SSD1306 {
        public:
            struct Command {
                static constexpr uint8_t DISPLAY_ON          = 0xAF;
                static constexpr uint8_t DISPLAY_OFF         = 0xAE;
                static constexpr uint8_t SET_ADDRESSING_MODE = 0x20;
                static constexpr uint8_t SET_COLUMN          = 0x21;
                static constexpr uint8_t SET_PAGE            = 0x22;
            };

        protected:
            DisplayDevice_SSD1306();

            void writeScript(const uint8_t *script, size_t scriptSize);

        public:
            DisplayDevice_SSD1306(const DisplayDevice_SSD1306 &) = delete;
            virtual ~DisplayDevice_SSD1306() = default;

            virtual void writeCommand(const uint8_t *data, size_t dataSize) = 0;
            virtual void writeData(const uint8_t *data, size_t dataSize) = 0;

            DisplayDevice_SSD1306 & operator = (const DisplayDevice_SSD1306 &) = delete;
    };
}
