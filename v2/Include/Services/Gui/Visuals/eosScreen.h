#ifndef __eosScreen__
#define __eosScreen__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class RenderContext;

    class Screen final: public Panel {
    	private:
    		Color color;

    	protected:
            void onRender(RenderContext &context) override;
            void onDispatch(const Message &msg) override;

    	public:
            Screen();

            void setColor(const Color &newColor);
            inline Color getColor() const { return color; }
    };

}


#endif // __eosScreen__
