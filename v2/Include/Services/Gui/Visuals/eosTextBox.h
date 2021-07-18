#ifndef __eosTextBox__
#define __eosTextBox__


#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class TextBox: public Control {
		private:
			String _text;
			int _visiblePos;
			int _visibleLength;
			int _insertPos;

		protected:
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
			void onKeyboardPress(KeyCode keyCode, KeyFlags flags, char ch) override;
#endif
			void onRender(RenderContext* context) override;

		public:
			TextBox();

			void clearText();

			void setText(const String& value);

			const String& getText() const { return _text; }
	};
}



#endif
