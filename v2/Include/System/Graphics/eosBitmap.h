#ifndef __eosBitmap__
#define __eosBitmap__


// EOS includes
//
#include "eos.h"
#include "System/eosPointers.h"
#include "System/Graphics/eosColor.h"


#ifndef eosGraphics_MaxBitmaps
#define eosGraphics_MaxBitmaps 50
#endif


namespace eos {

	class Bitmap {
		private:
			struct Impl;
			typedef SharedPtr<Impl> PImpl;

    	private:
    		PImpl _pImpl;
		private:
			int _width;
			int _height;
			ColorFormat _format;
			bool _allocated;
			bool _readonly;
			void *_pixels;

		private:
            PImpl allocate();

		public:
			Bitmap(const void *bitmapResource);
			Bitmap(int width, int height, ColorFormat format, Color color);
			Bitmap(int width, int height, ColorFormat format, void *pixels);
			Bitmap(int width, int height, ColorFormat format, const void *pixels);
			Bitmap(const Bitmap& bitmap);
			~Bitmap();

			Bitmap& operator = (const Bitmap& bitmap);

			void setPixel(int x, int y, const Color &color);
			Color getPixel(int x, int y);

			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }
			inline void *getPixels() const { return _pixels; }
			inline ColorFormat getFormat() const { return _format; }
			int getBytesPerPixel() const;
			int getBytesPerLine() const;
	};
}


#endif // __eosBitmap__
