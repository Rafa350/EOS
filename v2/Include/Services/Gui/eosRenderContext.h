#ifndef __eosRenderContext__
#define __eosRenderContext__


#include "eos.h"


namespace eos {

	class Visual;
	class Graphics;
	class Color;

	class RenderContext {
		private:
			Graphics *graphics;
			int offsetX;
			int offsetY;

		public:
			RenderContext(Graphics *graphics);
			void beginRender(Visual *visual);
			void endRender();

			void fillRectangle(int x, int y, int width, int height, const Color &color);
			void drawRectangle(int x, int y, int width, int height, const Color &color);
	};
}


#endif // __eosRenderContext__
