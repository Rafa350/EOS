#pragma once
#ifndef __eosColorFrameBuffer_DMA2D__
#define __eosColorFrameBuffer_DMA2D__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"
#include "HTL/STM32/htlDMA2D.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram
	///
	class ColorFrameBuffer_DMA2D: public FrameBuffer {
	    private:
	        using DevDMA2D = htl::dma2d::DMA2DDevice;
            static constexpr DevDMA2D *_devDMA2D = DevDMA2D::pInst;

		private:
			Color::Pixel * const _buffer;
			int16_t const _framePitch;

		private:
			inline Color::Pixel *getPixelPtr(int16_t x, int16_t y) const { return &_buffer[(y * _framePitch) + x]; }

		protected:
			void put(int16_t x, int16_t y, Color color) override;
            void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

		public:
			ColorFrameBuffer_DMA2D(int16_t width, int16_t height, int16_t pitch, DisplayOrientation orientation, void *buffer);
            uint8_t *getBuffer() const override;
	};
}


#endif // __eosColorFrameBuffer_DMA2D__
