#pragma once


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosThickness.h"
#include "System/eosCallbacks.h"
#include "System/eosEvents.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"


namespace eos {

	class Visual;

	/// \brief Clase base pels parametres dels events generats per visuals
	//
	struct VisualEventArgs: public EventArgs<Visual> {

		inline VisualEventArgs(Visual* visual):
			EventArgs(visual) {
		}
	};

#if eosGuiService_TouchpadEnabled
	struct TouchpadPressEventArgs: public VisualEventArgs {

		Point position;

		inline TouchpadPressEventArgs(Visual* visual, const Point& position):
			VisualEventArgs(visual),
			position(position) {
		}
	};

	struct TouchpadMoveEventArgs: public VisualEventArgs {

		Point position;

		inline TouchpadMoveEventArgs(Visual* visual, const Point& position):
			VisualEventArgs(visual),
			position(position) {
		}
	};

	typedef VisualEventArgs TouchpadReleaseEventArgs;
	typedef VisualEventArgs TouchpadEnterEventArgs;
	typedef VisualEventArgs TouchpadLeaveEventArgs;

	typedef ICallbackP1<const TouchpadMoveEventArgs&> ITouchpadMoveEventCallback;
	typedef ICallbackP1<const TouchpadPressEventArgs&> ITouchpadPressEventCallback;
	typedef ICallbackP1<const VisualEventArgs&> ITouchpadReleaseEventCallback;
	typedef ICallbackP1<const VisualEventArgs&> ITouchpadEnterEventCallback;
	typedef ICallbackP1<const VisualEventArgs&> ITouchpadLeaveEventCallback;

	template <typename C_>
	class TouchpadMoveEventCallback: public CallbackP1<C_, const TouchpadMoveEventArgs&> {
		public:
			using M = typename CallbackP1<C_, const TouchpadMoveEventArgs&>::Method;
		public:
			inline TouchpadMoveEventCallback(C_* instance, M handler):
				CallbackP1<C_, const TouchpadMoveEventArgs&>(instance, handler) {
			}
	};

	template <typename C_>
	class TouchpadPressEventCallback: public CallbackP1<C_, const TouchpadPressEventArgs&> {
		public:
			using M = typename CallbackP1<C_, const TouchpadPressEventArgs&>::Method;
		public:
			inline TouchpadPressEventCallback(C_ &instance, M handler):
				CallbackP1<C_, const TouchpadPressEventArgs&>(instance, handler) {
			}
	};

#endif

#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
	struct KeyboardEventArgs: public VisualEventArgs {
		KeyCode keyCode;
		KeyFlags keyFlags;
		char ch;

		inline KeyboardEventArgs(Visual* visual, KeyCode keyCode, KeyFlags keyFlags, char ch):
			VisualEventArgs(visual),
			keyCode(keyCode),
			keyFlags(keyFlags),
			ch(ch) {
		}
	};

	typedef KeyboardEventArgs KeyboardPressEventArgs;
	typedef KeyboardEventArgs KeyboardReleaseEventArgs;

	typedef ICallbackP1<const KeyboardPressEventArgs&> IKeyboardPressEventCallback;
	typedef ICallbackP1<const KeyboardReleaseEventArgs&> IKeyboardReleaseEventCallback;

	template <typename C_>
	class KeyboardPressEventCallback: public CallbackP1<C_, const KeyboardPressEventArgs&> {
		public:
			using M = typename CallbackP1<C_, const KeyboardPressEventArgs&>::Method;
		public:
			inline KeyboardPressEventCallback(C_* instance, M handler):
				CallbackP1<C_, const KeyboardPressEventArgs&>(instance, handler) {
			}
	};

	template <typename C_>
	class KeyboardReleaseEventCallback: public CallbackP1<C_, const KeyboardReleaseEventArgs&> {
		public:
			using M = typename CallbackP1<C_, const KeyboardReleaseEventArgs&>::Method;
		public:
			inline KeyboardReleaseEventCallback(C_* instance, M handler):
				CallbackP1<C_, const KeyboardReleaseEventArgs&>(instance, handler) {
			}
	};
#endif

	class RenderContext;

	enum class Visibility {
		visible,
		hidden,
		collapsed
	};

	enum class Orientation {
		horizontal,
		vertical,
	};

	enum class HorizontalAlignment {
		stretch,
		left,
		center,
		right
	};

	enum class VerticalAlignment {
		stretch,
		top,
		center,
		bottom
	};

	class Visual;
    using VisualList = IntrusiveForwardList<Visual, 0>;
    using VisualListNode = IntrusiveForwardListNode<Visual, 0>;

    /// \brief Clase base que representa tots els elements visuals.
	///
    class Visual: public VisualListNode {
      	private:
			MsgQueue& _msgQueue;
    		Visual* _parent;
    		VisualList _childs;
    		bool _needRender;
    		Visibility _visibility;
			Size _size;
			Size _minSize;
			Size _maxSize;
			Size _desiredSize;
			Rect _bounds;
			Thickness _margin;
			HorizontalAlignment _horizontalAlignment;
			VerticalAlignment _verticalAlignment;
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
			const IKeyboardPressEventCallback* _keyboardPressEventCallback;
			const IKeyboardReleaseEventCallback* _keyboardReleaseEventCallback;
#endif
#if eosGuiService_TouchpadEnabled
			const ITouchpadPressEventCallback* _touchpadPressEventCallback;
			const ITouchpadReleaseEventCallback* _touchpadReleaseEventCallback;
			const ITouchpadEnterEventCallback* _touchpadEnterEventCallback;
			const ITouchpadLeaveEventCallback* _touchpadLeaveEventCallback;
			const ITouchpadMoveEventCallback* _touchpadMoveEventCallback;
#endif
			unsigned _id;

    	protected:
    		virtual void onRender(RenderContext* context);
    		virtual void onDispatchMessage(const Message& msg);
    		virtual void onActivate(Visual* visual);
    		virtual void onDeactivate(Visual* visual);
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
    		virtual void onDispatchKeyboardMessage(const MsgKeyboard& msg);
    		virtual void onKeyboardPress(const KeyboardEventArgs& args);
    		virtual void onKeyboardRelease(const KeyboardEventArgs& args);
#endif
#if eosGuiService_TouchpadEnabled
    		virtual void onDispatchTouchpadMessage(const MsgTouchpad& msg);
    		virtual void onTouchpadEnter(const TouchpadEnterEventArgs& args);
    		virtual void onTouchpadLeave(const TouchpadLeaveEventArgs& args);
    		virtual void onTouchpadPress(const TouchpadPressEventArgs& args);
    		virtual void onTouchpadRelease(const TouchpadReleaseEventArgs& args);
    		virtual void onTouchpadMove(const TouchpadMoveEventArgs& args);
#endif
            virtual Size measureOverride(const Size& availableSize) const;
            virtual Size arrangeOverride(const Size& finalSize) const;

            void addVisual(Visual* visual);
            void removeVisual(Visual* visual);
            void removeVisuals();

        public:
            // Constructors i destructors
    		Visual();
    		virtual ~Visual();

            inline Visual* getParent() const { return _parent; }
            inline const VisualList& getChilds() const { return _childs; }

            // Checkers
            bool isRenderizable() const;
            bool isVisible() const;
            bool isEnabled() const;

            // Setters
            void setId(unsigned id) { _id = id; }
            void setHorizontalAlignment(HorizontalAlignment value);
            void setMargin(const Thickness& value);
            void setMinSize(const Size& value);
            void setSize(const Size& value);
            void setVerticalAlignment(VerticalAlignment value);
            void setVisibility(Visibility value);

#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
            inline void setKeyboardPressEventCallback(const IKeyboardPressEventCallback* callback) {
            	_keyboardPressEventCallback = callback;
            }

            inline void setKayboardReleaseEventCallback(const IKeyboardReleaseEventCallback* callback) {
            	_keyboardReleaseEventCallback = callback;
            }
#endif
#if eosGuiService_TouchpadEnabled
            inline void setTouchpadPressEventCallback(const ITouchpadPressEventCallback* callback) {
            	_touchpadPressEventCallback = callback;
            }

            inline void setTouchpadReleaseEventCallback(const ITouchpadReleaseEventCallback* callback) {
            	_touchpadReleaseEventCallback = callback;
            }
#endif

            // Getters
            inline const Rect& getBounds() const { return _bounds; }
            inline HorizontalAlignment getHorizontalAlignment() const { return _horizontalAlignment; }
            inline unsigned getId() const { return _id; }
            inline const Size& getMaxSize() const { return _maxSize; }
            inline const Thickness& getMargin() const { return _margin; }
            inline const Size& getMinSize() const { return _minSize; }
            inline const Size& getSize() const { return _size; }
            inline VerticalAlignment getVerticalAlignment() const { return _verticalAlignment; }
            Visibility getVisibility() const { return _visibility; }

            void measure(const Size& availableSize);
            void arrange(const Rect& finalRect);
            const Size& getDesiredSize() const { return _desiredSize; }

            void dispatch(const Message& msg);
            void send(const Message& msg);
            bool render(RenderContext* context);
    		void invalidate();
    		void invalidateLayout();
    };

}
