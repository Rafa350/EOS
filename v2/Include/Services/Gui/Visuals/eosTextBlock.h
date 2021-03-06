#ifndef __eosTextBlock__
#define __eosTextBlock__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosFont.h"
#include "System/Graphics/eosGraphics.h"


namespace eos {

    class RenderContext;
    class Message;

    class TextBlock: public Control {
    	private:
    		Brush _foreground;
			Brush _background;
    		HorizontalTextAlign _horizontalTextAlign;
    		VerticalTextAlign _verticalTextAlign;
    		String _fontName;
    		int _fontHeight;
    		FontStyle _fontStyle;
    		String _text;

    	protected:
    		void onRender(RenderContext* context) override;
#if eosGuiService_TouchPadEnabled
    		void onDispatch(const Message& msg) override;
#endif
    		Size measureOverride(const Size& availableSize) const override;

        public:
    		TextBlock();

            void setForeground(const Brush& value);
            void setBackground(const Brush& value);
            void setFontName(const String& value);
            void setFontHeight(int value);
            void setFontStyle(FontStyle value);
            void setText(const String& value);
            void setHorizontalTextAlign(HorizontalTextAlign value);
            void setVerticalTextAlign(VerticalTextAlign value);

            inline const Brush& getForeground() const { return _foreground; }
            inline const Brush& getBackground() const { return _background; }
            inline const String& getText() const { return _text; }
    };
}


#endif // __eosTextBlock__
