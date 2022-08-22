#pragma once
#ifndef __eosFrameBuffer__
#define __eosFrameBuffer__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayOrientation.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram.
	///
	class FrameBuffer {
		private:
			const int _frameWidth;
			const int _frameHeight;
			int _maxX;
			int _maxY;
			DisplayOrientation _orientation;

            void transform(int& x, int& y) const;
            void transform(int& x1, int& y1, int &x2, int& y2) const;

        protected:
            virtual void put(int x, int y, Color color) = 0;
            virtual void fill(int x, int y, int width, int height, Color color) = 0;
            virtual void copy(int x, int y, int width, int height, const Color *colors, int colorPitch) = 0;
            virtual void copy(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch) = 0;

		public:
			FrameBuffer(int width, int height, DisplayOrientation orientation);
			virtual ~FrameBuffer() = default;

            void setOrientation(DisplayOrientation orientation);

            inline int getMaxX() const { return _maxX; }
            inline int getMaxY() const { return _maxY; }
            inline int getWidth() const { return _frameWidth; }
            inline int getHeight() const { return _frameHeight; }
            virtual void *getBuffer() const = 0;

            void clear(Color color);
            void setPixel(int x, int y, Color color);
            inline void setHPixels(int x, int y, int size, Color color) { setPixels(x, y, size, 1, color); }
            inline void setVPixels(int x, int y, int size, Color color) { setPixels(x, y, 1, size, color); }
            void setPixels(int x, int y, int width, int height, Color color);
            void setPixels(int x, int y, int width, int height, const Color *colors, int colorPitch);
            void setPixels(int x, int y, int width, int height, const void *colors, ColorFormat colorFormat, int colorPitch);
	};
}


#endif // __eosFrameBuffer__
