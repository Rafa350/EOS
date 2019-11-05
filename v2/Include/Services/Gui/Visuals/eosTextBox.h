#ifndef __eosTextBox__
#define __eosTextBox__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class TextBox: public Control {

		protected:
			void onRender(RenderContext *context) override;

		public:
			TextBox();
	};
}



#endif
