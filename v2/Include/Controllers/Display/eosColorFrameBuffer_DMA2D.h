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
			Color::Pixel *_buffer;
			int _bufferPitch;

		private:
			inline Color::Pixel *getPixelPtr(int x, int y) const { return &_buffer[(y * _bufferPitch) + x]; }

		protected:
			void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color *colors, int offset) override;
            void write(int x, int y, int width, int height, const void *pixels, ColorFormat format, int offset) override;

		public:
			ColorFrameBuffer_DMA2D(int frameWidth, int frameHeight, DisplayOrientation orientation, void *buffer, int bufferPitch);
            void *getImageBuffer() const override;
};
}


#endif // __eosFrameBuffer_DMA2D__
