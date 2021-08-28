#ifndef __eosTextBox__
#define __eosTextBox__


#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/Visuals/eosTextBlock.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class TextBox: public TextBlock {
		private:
			int _visiblePos;
			int _visibleLength;
			int _insertPos;

		protected:
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
			void onKeyboardPress(const KeyboardPressEventArgs& args) override;
#endif
			void onRender(RenderContext* context) override;

		public:
			TextBox();

			void clearText();
	};
}



#endif
