#ifndef __eosScreen__
#define __eosScreen__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class Size;

    class Screen final: public Panel {
    	protected:
			Size measureOverride(const Size& availableSize) const override;

    	public:
            Screen();
    };

}


#endif // __eosScreen__
