#pragma once
#ifndef __eosDisplayDriver_ILI9341__
#define __eosDisplayDriver_ILI9341__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosColorFrameBuffer_DMA2D.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/STM32/htlLTDC.h"


namespace eos {

    class Device_ILI9341;

    class DisplayDriver_ILI9341LTDC: public DisplayDriver {
    	private:
			using PinDE = DISPLAY_DE_Pin;
			using PinHSYNC = DISPLAY_HSYNC_Pin;
			using PinVSYNC = DISPLAY_VSYNC_Pin;
			using PinPC = DISPLAY_PC_Pin;
			using PinR2 = DISPLAY_R2_Pin;
			using PinR3 = DISPLAY_R3_Pin;
			using PinR4 = DISPLAY_R4_Pin;
			using PinR5 = DISPLAY_R5_Pin;
			using PinR6 = DISPLAY_R6_Pin;
			using PinR7 = DISPLAY_R7_Pin;
			using PinG2 = DISPLAY_G2_Pin;
			using PinG3 = DISPLAY_G3_Pin;
			using PinG4 = DISPLAY_G4_Pin;
			using PinG5 = DISPLAY_G5_Pin;
			using PinG6 = DISPLAY_G6_Pin;
			using PinG7 = DISPLAY_G7_Pin;
			using PinB2 = DISPLAY_B2_Pin;
			using PinB3 = DISPLAY_B3_Pin;
			using PinB4 = DISPLAY_B4_Pin;
			using PinB5 = DISPLAY_B5_Pin;
			using PinB6 = DISPLAY_B6_Pin;
			using PinB7 = DISPLAY_B7_Pin;

			static constexpr uint16_t _hSync       = DISPLAY_HSYNC;
			static constexpr uint16_t _vSync       = DISPLAY_VSYNC;
			static constexpr uint16_t _hBP         = DISPLAY_HBP;
			static constexpr uint16_t _vBP         = DISPLAY_VBP;
			static constexpr uint16_t _hFP         = DISPLAY_HFP;
			static constexpr uint16_t _vFP         = DISPLAY_VFP;
			static constexpr htl::ltdc::PinPolarity _hSyncPol = DISPLAY_HSYNC_POL;
			static constexpr htl::ltdc::PinPolarity _vSyncPol = DISPLAY_VSYNC_POL;
			static constexpr htl::ltdc::PinPolarity _dePol    = DISPLAY_DE_POL;
			static constexpr htl::ltdc::PinPolarity _pcPol    = DISPLAY_PC_POL;
			static constexpr htl::ltdc::LTDCDevice *_ltdc = htl::ltdc::LTDCDevice::pInst;
            static constexpr htl::ltdc::LTDCLayerDevice1 *_ltdcLayer = htl::ltdc::LTDCLayerDevice1::pInst;

        private:
            Device_ILI9341 * const _device;
            FrameBuffer * const _frameBuffer;

        public:
            DisplayDriver_ILI9341LTDC(Device_ILI9341 *device, FrameBuffer *frameBuffer);
            DisplayDriver_ILI9341LTDC(htl::ltdc::LTDCDevice *devLTDC,
            		htl::ltdc::LTDCLayerDevice *devLTDCLayer,
					Device_ILI9341 *device, FrameBuffer *frameBuffer);

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


#endif // __eosDisplayDriver_ILI9341__
