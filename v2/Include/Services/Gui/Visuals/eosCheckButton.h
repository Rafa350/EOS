#ifndef __eosCheckButton__
#define __eosCheckButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


namespace eos {

	struct Message;
	class RenderContext;

    enum class CheckButtonState {
    	unchecked,
		checked,
		null
    };

    class CheckButton: public ButtonBase {

    	private:
    		CheckButtonState state;

    };

}


#endif // __eosCheckButton__
