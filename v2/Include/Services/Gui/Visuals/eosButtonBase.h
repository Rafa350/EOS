#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"


namespace eos {

	struct Message;

    class ButtonBase: public ContentControl {
    	private:
			bool pressed;

    	protected:
#ifdef OPT_GUI_TouchPad
		    void onTouchPadPress(const Point &position) override;
		    void onTouchPadRelease() override;
		    void onTouchPadLeave() override;
#endif
			virtual void onClick();
			virtual void onPress();
			virtual void onRelease();

			bool isPressed() const { return pressed; }

    	public:
			ButtonBase();

			void click();
    };


}


#endif // __eosButtonBase__
