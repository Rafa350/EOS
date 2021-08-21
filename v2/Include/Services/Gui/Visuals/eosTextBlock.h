#ifndef __eosTextBlock__
#define __eosTextBlock__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosText.h"
#include "System/Graphics/eosGraphics.h"


namespace eos {

    class RenderContext;
    class Message;

    class TextBlock: public Control {
    	private:
    		Text _ft;

    	protected:
    		void onRender(RenderContext* context) override;
#if eosGuiService_TouchPadEnabled
    		void onDispatch(const Message& msg) override;
#endif
    		Size measureOverride(const Size& availableSize) const override;

        public:
    		TextBlock();

            void setForeground(const Brush& value);
            void setFont(const Font& value);
            void setText(const String& value);
            void setTextAlign(TextAlign value);

            inline const Brush& getForeground() const { return _ft.getForeground(); }
            inline const Font& getFont() const { return _ft.getFont(); }
            inline const String& getText() const { return _ft.getText(); }
    };
}


#endif // __eosTextBlock__
