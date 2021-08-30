#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "System/eosEvents.h"


namespace eos {

	class ButtonBase;

	struct ButtonEventArgs: public VisualEventArgs {
		unsigned id;

		inline ButtonEventArgs(ButtonBase* button, unsigned id):
			VisualEventArgs((Visual*)button),
			id(id) {
		}
	};

	typedef ICallbackP1<const ButtonEventArgs&> IButtonEventCallback;

	template <typename C_>
	class ButtonEventCallback: public CallbackP1<C_, const ButtonEventArgs&> {
		public:
			using M = typename CallbackP1<C_, const ButtonEventArgs&>::Method;
		public:
			inline ButtonEventCallback(C_* instance, M handler):
				CallbackP1<C_, const ButtonEventArgs&>(instance, handler) {
			}
	};


	class ButtonBase: public ContentControl {
    	public:
			enum class ClickMode {
				atPress,
				atRelease
			};

    	private:
			bool _pressed;
			ClickMode _clickMode;
			const IButtonEventCallback* _clickEventCallback;
			const IButtonEventCallback* _pressEventCallback;
			const IButtonEventCallback* _releaseEventCallback;

    	protected:
#if eosGuiService_TouchpadEnabled
		    void onTouchpadPress(const TouchpadPressEventArgs& args) override;
		    void onTouchpadRelease(const TouchpadReleaseEventArgs& args) override;
		    void onTouchpadLeave(const TouchpadLeaveEventArgs& args) override;
#endif
			virtual void onClick(const ButtonEventArgs& args);
			virtual void onPress(const ButtonEventArgs& args);
			virtual void onRelease(const ButtonEventArgs& args);

			inline bool isPressed() const { return _pressed; }

    	public:
			ButtonBase();

			void setClickMode(ClickMode value);
			inline ClickMode getClickMode() const { return _clickMode; }

			void click();

			inline void setClickEventCallback(const IButtonEventCallback* callback) {
				_clickEventCallback = callback;
			}

			inline void setPressEventCallback(const IButtonEventCallback* callback) {
				_pressEventCallback = callback;
			}

			inline void setReleaseEventCallback(const IButtonEventCallback* callback) {
				_releaseEventCallback = callback;
			}
    };

}


#endif // __eosButtonBase__
