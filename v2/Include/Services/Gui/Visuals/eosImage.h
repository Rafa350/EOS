#ifndef __eosImage__
#define __eosImage__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Bitmap;
	class RenderContext;

	class Image: public Visual {
		private:
			Bitmap *pBitmap;

		protected:
			void onRender(RenderContext &context);

		public:
			Image();

			void setBitmap(Bitmap *newBitmap);
			Bitmap *getBitmap() const { return pBitmap; }
	};

}


#endif // __eosImage__
