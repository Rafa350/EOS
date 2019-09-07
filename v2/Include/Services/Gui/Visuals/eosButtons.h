#ifndef __eosButtons__
#define __eosButtons__


#include "eos.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


namespace eos {

	struct Message;
	class RenderContext;

    enum class PushButtonState {
    	normal,
		pushed,
		disabled
    };
    
    class PushButton: public ButtonBase {

    	private:
    		PushButtonState state;
    
        protected:
        	void onRender(RenderContext &context) override;
            void onPress() override;
            void onRelease() override;

            void setState(PushButtonState newState);

        public:
            PushButton();
    };
    

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


#endif // __eosButtons__
