#ifndef __eosPushButton__
#define __eosPushButton__


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
        	void onRender(RenderContext *context) override;
            void onPress() override;
            void onRelease() override;

            void setState(PushButtonState value);

        public:
            PushButton();
    };
    
}


#endif // __eosPushButton__
