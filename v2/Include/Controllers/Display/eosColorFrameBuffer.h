#ifndef __eosFrameBuffer_RGB565__
#define __eosFrameBuffer_RGB565__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

	class ColorFrameBuffer: public FrameBuffer {
		private:
			uint8_t* _buffer;
			int _bufferPitch;

		protected:
            void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int pitch) override;

		public:
			ColorFrameBuffer(int frameWidth, int frameHeight, DisplayOrientation orientation, void* buffer, int bufferPitch);
	};
}


#endif // __eosFrameBuffer_RGB565__
