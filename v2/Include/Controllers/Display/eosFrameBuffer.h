#ifndef __eosFrameBuffer__
#define __eosFrameBuffer__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosDisplayDriver.h"


namespace eos {

	/// \brief Superficie de dibuix basada en memoria ram
	///
	class FrameBuffer {

		private:
			int _screenWidth;
			int _screenHeight;
			int _maxX;
			int _maxY;
			DisplayOrientation _orientation;

        protected:
            void rotate(int& x, int& y);
            void rotate(int& x1, int& y1, int &x2, int& y2);

        protected:
            virtual void put(int x, int y, const Color& color) = 0;
            virtual void fill(int x, int y, int width, int height, const Color& color) = 0;
            virtual void copy(int x, int y, int width, int height, const Color* colors, int dx, int dy, int pitch) = 0;

		public:
			FrameBuffer(int screenWidth, int screenHeight, DisplayOrientation orientation);
			virtual ~FrameBuffer() = default;

            void setOrientation(DisplayOrientation orientation);

            inline int getWidth() const { return _maxX + 1; }
            inline int getHeight() const { return _maxY + 1; }
	};
}


#endif // __eosFrameBuffer__
