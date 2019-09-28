#ifndef __eosRenderContext__
#define __eosRenderContext__


#include "eos.h"


namespace eos {

	class Visual;
	class Graphics;
	class Rect;

	class RenderContext {
		private:
			Graphics &graphics;

		public:
			RenderContext(Graphics &graphics);
			Graphics &beginRender(Visual *pVisual);
			void endRender();
	};
}


#endif // __eosRenderContext__
