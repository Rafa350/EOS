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
			const int _framePitch;

			inline Color::Pixel *getPixelPtr(int x, int y) const { return &_buffer[(y * _framePitch) + x]; }

		protected:
			void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color *colors, int colorPitch) override;
            void copy(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch) override;

		public:
			ColorFrameBuffer_DMA2D(int width, int height, int pitch, DisplayOrientation orientation, void *buffer);
            void *getBuffer() const override;
	};
}


#endif // __eosFrameBuffer_DMA2D__
