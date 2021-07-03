#ifndef __eosRenderContext__
#define __eosRenderContext__


#include "eos.h"


namespace eos {

	class Visual;
	class Graphics;

	class RenderContext {
		private:
			Graphics *_graphics;

		public:
			RenderContext(Graphics *graphics);
			Graphics &beginRender(Visual *visual);
			void endRender();
	};
}


#endif // __eosRenderContext__
