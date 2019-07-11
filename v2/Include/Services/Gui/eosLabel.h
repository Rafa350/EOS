#ifndef __eosLabel__
#define __eosLabel__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class RenderContext;

    class Label: public Visual {
    	private:
    		Color color;
    		char *text;

    	protected:
    		void onRender(RenderContext *context) override;

        public:
            void setColor(const Color &color);
            void setText(const char *text);

            inline Color getColor() const { return color; }
            inline char* getText() const { return text; }
    };

}


#endif // __eosLabel__
