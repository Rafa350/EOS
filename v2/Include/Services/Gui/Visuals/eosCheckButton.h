#ifndef __eosCheckButton__
#define __eosCheckButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosButtonBase.h"


namespace eos {

	class RenderContext;

    class CheckButton: public ButtonBase {
    	public:
    		enum class State {
    			unchecked,
				checked
    		};

    	private:
    		State _state;

    	protected:
    		void onRender(RenderContext *context) override;
    		void onClick(const ButtonEventArgs& args) override;

    		void setState(State value);

    	public:
    		CheckButton();

    		inline void check() { setState(State::checked); }
    		inline void uncheck() { setState(State::unchecked); }
    		inline bool isChecked() const { return _state == State::checked; }
    };

}


#endif // __eosCheckButton__
