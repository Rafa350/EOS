#ifndef __eosFrameBuffer_L1_PAGECOL__
#define __eosFrameBuffer_L1_PAGECOL__


// EOS includes
//
#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class FrameBuffer_L1_PAGECOL: public FrameBuffer {
        private:
            void* _buffer;
		private:
			inline uint32_t getPixelAddr(int x, int y) const;

		protected:
			void put(int x, int y, const Color& color) override;
            void fill(int x, int y, int width, int height, const Color& color) override;
            void copy(int x, int y, int width, int height, const Color* colors, int pitch) override;

		public:
			FrameBuffer_L1_PAGECOL(int frameWidth, int frameHeight, DisplayOrientation orientation, void* buffer);
    };
}


#endif // __eosFrameBuffer_L1_C128P8__
