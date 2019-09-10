#ifndef __eosScreen__
#define __eosScreen__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class RenderContext;

    class Screen final: public Panel {
    	public:
            Screen();
    };

}


#endif // __eosScreen__
