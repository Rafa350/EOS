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
    		Text _text;

    	protected:
    		void onRender(RenderContext* context) override;
    		Size measureOverride(const Size& availableSize) const override;

        public:
    		TextBlock();

            void setTextForeground(const Brush &value);
            void setTextBackground(const Brush &value);
            void setFont(const Font &value);
            void setText(const String &value);
            void setTextAlign(Text::Align value);

            inline const Brush & getForeground() const { return _text.getForeground(); }
            inline const Font & getFont() const { return _text.getFont(); }
            inline const String & getText() const { return _text.getText(); }
    };
}


#endif // __eosTextBlock__
