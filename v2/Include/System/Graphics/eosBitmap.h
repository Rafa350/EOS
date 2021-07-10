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
			typedef SharedPtr<Impl> ImplPtr;

    	private:
    		ImplPtr _impl;

		private:
            ImplPtr makeImpl();

		public:
			Bitmap(const void* bitmapResource);
			Bitmap(int width, int height, ColorFormat format, Color color);
			Bitmap(int width, int height, ColorFormat format, void* pixels);
			Bitmap(int width, int height, ColorFormat format, const void* pixels);
			Bitmap(const Bitmap& bitmap);
			~Bitmap();

			Bitmap& operator = (const Bitmap& bitmap);

			void setPixel(int x, int y, Color color);
			Color getPixel(int x, int y);

			int getWidth() const;
			int getHeight() const;
			void* getPixels() const;
			ColorFormat getFormat() const;
			int getBytesPerPixel() const;
			int getBytesPerLine() const;
	};
}


#endif // __eosBitmap__
