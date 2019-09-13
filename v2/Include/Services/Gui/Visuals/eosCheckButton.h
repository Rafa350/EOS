#ifndef __eosCheckButton__
#define __eosCheckButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


namespace eos {

	struct Message;
	class RenderContext;

    enum class CheckButtonState {
    	unchecked,
		checked
    };

    class CheckButton: public ButtonBase {

    	private:
    		CheckButtonState state;

    	protected:
    		void onRender(RenderContext &context) override;
    		void onClick() override;

    		void setState(CheckButtonState state);

    	public:
    		CheckButton();

    		inline void check() { setState(CheckButtonState::checked); }
    		inline void uncheck() { setState(CheckButtonState::unchecked); }
    		inline bool isChecked() const { return state == CheckButtonState::checked; }
    };

}


#endif // __eosCheckButton__
