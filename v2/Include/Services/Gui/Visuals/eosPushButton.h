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
    		State state;

        protected:
        	void onRender(RenderContext *context) override;
            void onPress() override;
            void onRelease() override;

            void setState(State value);

        public:
            PushButton();
    };
    
}


#endif // __eosPushButton__
