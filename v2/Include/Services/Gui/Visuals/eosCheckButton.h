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

    	protected:
    		void onRender(RenderContext &context) override;

    	public:
    		CheckButton();
    		void setState(CheckButtonState newState);

    };

}


#endif // __eosCheckButton__
