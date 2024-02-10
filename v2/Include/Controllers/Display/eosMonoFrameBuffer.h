#pragma once
#ifndef __eosMonoFrameBuffer__
#define __eosMonoFrameBuffer__


#include "eos.h"
#include "Controllers/Display/eosFrameBuffer.h"


namespace eos {

    class MonoFrameBuffer final: public FrameBuffer {
        public:
            enum class Mapping {
                horizontal8BBP,
                vertical8BPP
            };
        private:
            uint8_t * const _buffer;
            unsigned const _bufferPitch;
            Mapping const _mapping;

		protected:
            void put(int16_t x, int16_t y, Color color) override;
            void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) override;
            void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) override;

        public:
            MonoFrameBuffer(int16_t frameWidth, int16_t frameHeight, DisplayOrientation orientation, uint8_t *buffer, unsigned bufferPitch, Mapping mapping);

            inline uint8_t *getBuffer() const override { return _buffer; }
            inline unsigned getBufferPitch() const { return _bufferPitch; }
            inline Mapping getMapping() const { return _mapping; }
    };
}


#endif // __eosMonoFrameBuffer__
