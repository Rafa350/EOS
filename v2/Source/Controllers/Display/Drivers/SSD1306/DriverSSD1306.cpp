export module Eos.Controllers.Display.Drivers.SSD1306;

export import Eos.Controllers.Display;

import Eos.Controllers.Display.Buffers.L1;
import Eos.Hardware.DMA;
import Eos.Hardware.GPIO;
import Eos.Hardware.SPI;
import Eos.System.Graphics.Color;
import Eos.Types;


using namespace eos::hardware::dma;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


export namespace eos {

    class DisplayDevice_SSD1306;

    class DisplayDriver_SSD1306: public DisplayDriver {
    	private:
            DisplayDevice_SSD1306 * const _device;
			DisplayBuffer_L1 * const _frameBuffer;

    	public:
            DisplayDriver_SSD1306(DisplayDevice_SSD1306 *device, DisplayBuffer_L1 *frameBuffer);

            void initialize() override;
            void deinitialize() override;
            void enable() override;
            void disable() override;
            Int16 getMaxX() const override { return _frameBuffer->getMaxX(); }
            Int16 getMaxY() const override { return _frameBuffer->getMaxY(); }
            Int16 getWidth() const override { return _frameBuffer->getWidth(); }
            Int16 getHeight() const override { return _frameBuffer->getHeight(); };

            void clear(Color color) override;
            void setPixel(Int16 x, Int16 y, Color color) override;
            void setHPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setVPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 pitch) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *pixels, ColorFormat format, Int16 pitch) override;

            void refresh() override;
    };


    class DisplayDevice_SSD1306 {
        public:
            struct Command {
                static constexpr UInt8 DISPLAY_ON          = 0xAF;
                static constexpr UInt8 DISPLAY_OFF         = 0xAE;
                static constexpr UInt8 SET_ADDRESSING_MODE = 0x20;
                static constexpr UInt8 SET_COLUMN          = 0x21;
                static constexpr UInt8 SET_PAGE            = 0x22;
            };

        protected:
            DisplayDevice_SSD1306();

            void writeScript(const UInt8 *script, UInt32 scriptSize);

        public:
            DisplayDevice_SSD1306(const DisplayDevice_SSD1306 &) = delete;
            virtual ~DisplayDevice_SSD1306() = default;

            virtual void writeCommand(const UInt8 *data, UInt32 dataSize) = 0;
            virtual void writeData(const UInt8 *data, UInt32 dataSize) = 0;

            DisplayDevice_SSD1306 & operator = (const DisplayDevice_SSD1306 &) = delete;
    };


    class DisplayDevice_SSD1306_SPI: public DisplayDevice_SSD1306 {
        protected:
            PinDevice const * const _pinCS;
            PinDevice const * const _pinDC;
            PinDevice const * const _pinRST;
            SPIDevice * const _devSPI;

        public:
            DisplayDevice_SSD1306_SPI(PinDevice *pinCS, PinDevice *pinDC, PinDevice *pinRST, SPIDevice *devSPI);
            ~DisplayDevice_SSD1306_SPI();

            void initialize(const UInt8 *script, UInt32 scriptSize);
            void deinitialize();

            void writeCommand(const UInt8 *data, UInt32 dataSize) override;
            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };

    class DisplayDevice_SSD1306_SPIDMA: public DisplayDevice_SSD1306_SPI {
        private:
            DMADevice * const _devDMA;

        public:
            DisplayDevice_SSD1306_SPIDMA(PinDevice *pinCS, PinDevice *pinDC, PinDevice *pinRST, SPIDevice *devSPI, DMADevice *devDMA);

            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };

}
