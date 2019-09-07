#ifndef __eosLabel__
#define __eosLabel__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosGraphics.h"


namespace eos {

    class RenderContext;
    class Message;

    class Label: public Visual {
    	private:
    		Color color;
    		Color backgroundColor;
    		HorizontalTextAlign horizontalTextAlign;
    		VerticalTextAlign verticalTextAlign;
    		const char *text;

    	protected:
    		void onRender(RenderContext &context) override;
    		void onDispatch(const Message &msg) override;

        public:
    		Label();

            void setColor(const Color &newColor);
            void setText(const char *newText);
            void setHorizontalTextAlign(HorizontalTextAlign newAlign);
            void setVerticalTextAlign(VerticalTextAlign newAlign);

            inline Color getColor() const { return color; }
            inline const char* getText() const { return text; }
    };

}


#endif // __eosLabel__
