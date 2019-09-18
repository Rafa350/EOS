#ifndef __eosLabel__
#define __eosLabel__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Core/eosString.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"


namespace eos {

    class RenderContext;
    class Message;

    class Label: public Visual {
    	private:
    		Color textColor;
    		Color backgroundColor;
    		HorizontalTextAlign horizontalTextAlign;
    		VerticalTextAlign verticalTextAlign;
    		Font *textFont;
    		String text;

    	protected:
    		void onRender(RenderContext &context) override;

    		Size measureOverride(const Size &availableSize) const override;

        public:
    		Label();

            void setTextColor(const Color &color);
            void setBackgroundColor(const Color &color);
            void setTextFont(Font *font);
            void setText(const String &text);
            void setHorizontalTextAlign(HorizontalTextAlign align);
            void setVerticalTextAlign(VerticalTextAlign align);

            inline Color getTextColor() const { return textColor; }
            inline Color getBackgroundColor() const { return backgroundColor; }
            inline const String& getText() const { return text; }
    };

}


#endif // __eosLabel__
