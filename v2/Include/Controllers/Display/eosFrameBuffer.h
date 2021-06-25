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
			int _imageWidth;
			int _imageHeight;
			DisplayOrientation _orientation;

        private:
            void transform(int& x, int& y) const;
            void transform(int& x1, int& y1, int &x2, int& y2) const;

        protected:
            virtual void put(int x, int y, Color color) = 0;
            virtual void fill(int x, int y, int width, int height, Color color) = 0;
            virtual void copy(int x, int y, int width, int height, const Color* colors, int pitch) = 0;

		public:
			FrameBuffer(int frameWidth, int frameHeight, DisplayOrientation orientation);
			virtual ~FrameBuffer() = default;

            void setOrientation(DisplayOrientation orientation);

            inline int getImageWidth() const { return _imageWidth; }
            inline int getImageHeight() const { return _imageHeight; }

            void clear(Color color);
            void setPixel(int x, int y, Color color);
            inline void setHPixels(int x, int y, int size, Color color) { setPixels(x, y, size, 1, color); }
            inline void setVPixels(int x, int y, int size, Color color) { setPixels(x, y, 1, size, color); }
            void setPixels(int x, int y, int width, int height, Color color);
            void setPixels(int x, int y, int width, int height, const Color* colors, int pitch);
            void setPixels(int x, int y, int width, int height, void* pixels, ColorFormat format, int dx, int dy, int pitch);
	};
}


#endif // __eosFrameBuffer__
