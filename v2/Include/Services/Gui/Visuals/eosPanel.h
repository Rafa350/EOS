#ifndef __eosPanel__
#define __eosPanel__


#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class RenderContext;

	class Panel: public Visual {
		private:
			Color color;

		protected:
			void onRender(RenderContext &context) override;

		public:
			Panel();

			inline void addChild(Visual *pVisual) { addVisual(pVisual); }

			void setColor(const Color &color);
			inline Color getColor() const { return color; }
	};
}


#endif // __eosPanel__
