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

    class Label: public Visual {
    	private:
    		Color color;
    		HorizontalTextAlign horizontalTextAlign;
    		VerticalTextAlign verticalTextAlign;
    		const char *text;

    	protected:
    		void onRender(RenderContext *context) override;

        public:
    		Label();

            void setColor(const Color &color);
            void setText(const char *text);
            void setHorizontalTextAlign(HorizontalTextAlign align);
            void setVerticalTextAlign(VerticalTextAlign align);

            inline Color getColor() const { return color; }
            inline const char* getText() const { return text; }
    };

}


#endif // __eosLabel__
