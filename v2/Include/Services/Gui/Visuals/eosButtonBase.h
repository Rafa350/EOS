#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"


namespace eos {

	struct Message;

    class ButtonBase: public ContentControl {
    	protected:
			virtual void onClick();
			virtual void onPress();
			virtual void onRelease();

    	public:
			void onTouchPadEvent(const Message &msg) override;
			void click();

    };


}


#endif // __eosButtonBase__
