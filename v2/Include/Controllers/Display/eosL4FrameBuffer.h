#pragma once
#ifndef __eosL4FrameBuffer__
#define __eosL4FrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class L4FrameBuffer final: public FrameBuffer {
        private:
            uint8_t * const _buffer;
            int16_t const _bufferPitch;

		protected:
            void put(int16_t x, int16_t y, Color color) override;
            void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

        public:
            L4FrameBuffer(int16_t frameWidth, int16_t frameHeight, DisplayOrientation orientation, uint8_t *buffer, int16_t bufferPitch);

            inline uint8_t *getBuffer() const override { return _buffer; }
            inline int16_t getBufferPitch() const { return _bufferPitch; }
    };

}


#endif // __eosL4FrameBuffer__
