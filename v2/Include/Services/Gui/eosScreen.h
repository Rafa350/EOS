#ifndef __eosScreen__
#define __eosScreen__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class Graphics;

    class Screen: public Visual {
    	private:
    		Color color;

    	protected:
            void onRender(Graphics *graphics) override;

    	public:
            void setColor(const Color &color);

            inline Color getColor() const { return color; }
    };

}


#endif // __eosVisual__
