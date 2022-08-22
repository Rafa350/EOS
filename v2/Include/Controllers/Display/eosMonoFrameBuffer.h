#ifndef __eosMonoFrameBuffer__
#define __eosMonoFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class MonoFrameBuffer: public FrameBuffer {
        private:
            uint8_t *_buffer;
            const int _framePitch;

		protected:
            void put(int x, int y, Color color) override;
            void fill(int x, int y, int width, int height, Color color) override;
            void copy(int x, int y, int width, int height, const Color *colors, int colorPitch) override;
            void copy(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch) override;

        public:
            MonoFrameBuffer(int width, int height, DisplayOrientation orientation, void *buffer, int pitch);

            inline void *getBuffer() const override { return _buffer; }
    };
}


#endif // __eosMonoFrameBuffer__
