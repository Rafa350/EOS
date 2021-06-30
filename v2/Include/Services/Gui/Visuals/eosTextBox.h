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
			Color _textColor;
			String _text;

		protected:
			void onKeyboardPress(KeyCode keyCode, char ch) override;
			void onRender(RenderContext* context) override;

		public:
			TextBox();

			void clearText();
			void setTextColor(Color value);
			void setText(const String &value);
	};
}



#endif
