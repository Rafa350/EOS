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
			uint8_t command;

        protected:
        	void onRender(RenderContext *context) override;
        	void onClick() override;
            void onPress() override;
            void onRelease() override;

            void setState(PushButtonState value);

        public:
            PushButton();

			void setCommand(uint8_t command) { this->command = command; }
			uint8_t getCommand() const { return id; }
    };
    
}


#endif // __eosPushButton__
