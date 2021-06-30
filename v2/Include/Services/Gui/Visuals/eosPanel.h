#ifndef __eosPanel__
#define __eosPanel__


#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosBrush.h"


namespace eos {

	class RenderContext;

	class Panel: public Visual {
		private:
			Brush _background;

		protected:
			void onRender(RenderContext* context) override;

		public:
			Panel();

			inline void addChild(Visual* visual) { addVisual(visual); }

			void setBackground(const Brush &value);
			inline const Brush& getBackground() const { return _background; }
	};
}


#endif // __eosPanel__
