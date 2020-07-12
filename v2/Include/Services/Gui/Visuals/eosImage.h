#ifndef __eosImage__
#define __eosImage__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Bitmap;
	class RenderContext;

	class Image: public Visual {
		private:
			Bitmap *bitmap;

		protected:
			void onRender(RenderContext &context);

		public:
			Image();

			void setBitmap(Bitmap* value);
			Bitmap* getBitmap() const { return bitmap; }
	};

}


#endif // __eosImage__
