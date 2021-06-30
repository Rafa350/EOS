#ifndef __eosLabel__
#define __eosLabel__


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

    class Label: public Control {
    	private:
    		Color _textColor;
    		Color _backgroundColor;
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
    		Label();

            void setTextColor(Color value);
            void setBackgroundColor(Color value);
            void setFontName(const String& value);
            void setFontHeight(int value);
            void setFontStyle(FontStyle value);
            void setText(const String& value);
            void setHorizontalTextAlign(HorizontalTextAlign value);
            void setVerticalTextAlign(VerticalTextAlign value);

            inline Color getTextColor() const { return _textColor; }
            inline Color getBackgroundColor() const { return _backgroundColor; }
            inline const String& getText() const { return _text; }
    };

}


#endif // __eosLabel__
