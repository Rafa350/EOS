export module Eos.Controllers.Display.Drivers.ILI9341LTDC;

import Eos.Controllers.Display;
import Eos.Controllers.Display.Drivers.ILI9341;
import Eos.Hardware.LTDC;
import Eos.System.Graphics.Color;
import Eos.Types;


using namespace eos::hardware::ltdc;


export namespace eos {

    class DisplayDriver_ILI9341LTDC: public DisplayDriver {
        private:
            Device_ILI9341 * const _devILI9341;
            LTDCDevice * const _devLTDC;
            LTDCLayerDevice * const _devLTDCLayer;
            DisplayBuffer * const _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(Device_ILI9341 *devILI9341,
            	LTDCDevice *devLTDC, LTDCLayerDevice *devLTDCLayer,
				DisplayBuffer *frameBuffer);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            Int16 getMaxX() const override { return _frameBuffer->getMaxX(); }
            Int16 getMaxY() const override { return _frameBuffer->getMaxY(); }
            Int16 getWidth() const override { return _frameBuffer->getWidth(); }
            Int16 getHeight() const override { return _frameBuffer->getHeight(); }

            void clear(Color color) override;
            void setPixel(Int16 x, Int16 y, Color color) override;
            void setHPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setVPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 pitch) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *pixels, ColorFormat format, Int16 pitch) override;

            void refresh() override;
    };
}
