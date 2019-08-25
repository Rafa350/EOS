#ifndef __eosRenderContext__
#define __eosRenderContext__


#include "eos.h"
#include "System/Graphics/eosPoint.h"
#include "System/graphics/eosRect.h"


namespace eos {

	class Visual;
	class Graphics;
	class Color;

	class RenderContext {
		private:
			Graphics &graphics;

		private:
			Rect getClip(Visual *pVisual) const;

		public:
			RenderContext(Graphics &graphics);
			Graphics &beginRender(Visual *pVisual);
			void endRender();
	};
}


#endif // __eosRenderContext__
