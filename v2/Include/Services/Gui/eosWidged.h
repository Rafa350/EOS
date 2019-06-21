#ifndef __eosWidged__
#define __eosWidged__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosWindow.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class Display;

    class Widget: public Window {
    	private:
    		Color backgroundColor;
    		Color borderColor;
    		int borderThickness;

    	protected:
    		void onRender(Display *display) override;

        public:
            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);

            inline Color getBorderColor() const { return borderColor; }
    };

}


#endif // __eosWidged__
