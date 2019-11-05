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
    		Color textColor;
    		Color backgroundColor;
    		HorizontalTextAlign horizontalTextAlign;
    		VerticalTextAlign verticalTextAlign;
    		String fontName;
    		int fontHeight;
    		FontStyle fontStyle;
    		String text;

    	protected:
    		void onRender(RenderContext *context) override;
#ifdef OPT_GUI_TouchPad
    		void onDispatch(const Message &msg) override;
#endif
    		Size measureOverride(const Size &availableSize) const override;

        public:
    		Label();

            void setTextColor(const Color &value);
            void setBackgroundColor(const Color &value);
            void setFontName(const String &value);
            void setFontHeight(int value);
            void setFontStyle(FontStyle value);
            void setText(const String &value);
            void setHorizontalTextAlign(HorizontalTextAlign value);
            void setVerticalTextAlign(VerticalTextAlign value);

            inline Color getTextColor() const { return textColor; }
            inline Color getBackgroundColor() const { return backgroundColor; }
            inline const String& getText() const { return text; }
    };

}


#endif // __eosLabel__
