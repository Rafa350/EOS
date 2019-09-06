#ifndef __eosButtons__
#define __eosButtons__


#include "eos.h"


namespace eos {

	struct Message;
	class RenderContext;

    class ButtonBase: public Visual {
    };
    
    class PushButton: public ButtonBase {
    
        protected:
        	void onRender(const RenderContext &context);
            void onTouchPadEvent(const Message &msg);
    };
    
    class ToggleButton: public Buttonbase {
    };

}


#endif // __eosButtons__
