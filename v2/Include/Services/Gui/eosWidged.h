#ifndef __eosWidged__
#define __eosWidged__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class RenderContext;

    class Widget: public Visual {
    	private:
    		Color backgroundColor;
    		Color borderColor;
    		int borderThickness;

    	protected:
    		void onRender(RenderContext *context) override;

        public:
            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);

            inline Color getBorderColor() const { return borderColor; }
            inline Color getBackgroundColor() const { return backgroundColor; }
    };

}


#endif // __eosWidged__
