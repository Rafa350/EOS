#pragma once


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayOrientation.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram.
	///
	class FrameBuffer {
		private:
			const int16_t _frameWidth;
			const int16_t _frameHeight;
			int16_t _maxX;
			int16_t _maxY;
			DisplayOrientation _orientation;

            void transform(int16_t &x, int16_t &y) const;
            void transform(int16_t &x1, int16_t &y1, int16_t &x2, int16_t &y2) const;

        protected:
            virtual void put(int16_t x, int16_t y, Color color) = 0;
            virtual void fill(int16_t x, int16_t y, int16_t width, int16_t height, Color color) = 0;
            virtual void copy(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch) = 0;
            virtual void copy(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch) = 0;

		public:
			FrameBuffer(int16_t frameWidth, int16_t frameHeight, DisplayOrientation orientation);
			virtual ~FrameBuffer() = default;

            void setOrientation(DisplayOrientation orientation);

            inline int16_t getMaxX() const { return _maxX; }
            inline int16_t getMaxY() const { return _maxY; }
            inline int16_t getWidth() const { return _frameWidth; }
            inline int16_t getHeight() const { return _frameHeight; }
            virtual uint8_t *getBuffer() const = 0;

            void clear(Color color);
            void setPixel(int16_t x, int16_t y, Color color);
            inline void setHPixels(int16_t x, int16_t y, int16_t size, Color color) { setPixels(x, y, size, 1, color); }
            inline void setVPixels(int16_t x, int16_t y, int16_t size, Color color) { setPixels(x, y, 1, size, color); }
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color color);
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors, int16_t colorPitch);
            void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const void *colors, ColorFormat colorFormat, int16_t colorPitch);
	};
}
