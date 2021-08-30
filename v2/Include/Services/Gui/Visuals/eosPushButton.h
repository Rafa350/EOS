#ifndef __eosPushButton__
#define __eosPushButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


namespace eos {

	class RenderContext;
    
    class PushButton: public ButtonBase {
    	public:
        	enum class State {
        		normal,
				pushed,
				disabled
        	};

    	private:
    		State _state;

        protected:
        	void onRender(RenderContext *context) override;
            void onPress(const ButtonEventArgs& args) override;
            void onRelease(const ButtonEventArgs& args) override;

            void setState(State value);

        public:
            PushButton();
    };
    
}


#endif // __eosPushButton__
