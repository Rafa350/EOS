#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "System/eosCallbacks.h"


namespace eos {

	struct Message;
	class ButtonBase;

    class ButtonBase: public ContentControl {
    	public:
			enum class ClickMode {
				atPress,
				atRelease
			};
			enum class EventType {
				press,
				release,
				click
			};
			struct EventArgs {
				ButtonBase *button;
				EventType event;
				uint8_t id;
			};
			typedef ICallbackP1<const EventArgs&> IEventCallback;

    	private:
			bool pressed;
			ClickMode clickMode;
			const IEventCallback* eventCallback;

    	protected:
#if eosGuiService_TouchPadEnabled
		    void onTouchPadPress(const Point& position) override;
		    void onTouchPadRelease() override;
		    void onTouchPadLeave() override;
#endif
			virtual void onClick();
			virtual void onPress();
			virtual void onRelease();

			inline bool isPressed() const { return pressed; }

    	public:
			ButtonBase();

			void click();

			inline void setEventCallback(const IEventCallback* callback) {
				eventCallback = callback;
			}
    };

}


#endif // __eosButtonBase__
