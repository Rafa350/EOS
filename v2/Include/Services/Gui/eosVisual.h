#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosThickness.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosVector.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"

#if eosGuiService_TouchpadEnabled
	#include "Services/Gui/Events/eosTouchpadEvents.h"
#endif

#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
	#include "Services/Gui/Events/eosKeyboardEvents.h"
#endif


namespace eos {

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

	/// \brief Clase base que representa tots els elements visuals.
	///
    class Visual {
    	public:
			typedef Vector<Visual*> VisualList;
			typedef typename VisualList::Iterator VisualIterator;

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
#if eosGuiService_TouchpadEnabled
			ITouchpadPressEventCallback* _touchpadPressEventCallback;
			ITouchpadReleaseEventCallback* _touchpadReleaseEventCallback;
#endif
			unsigned _id;

    	protected:
    		virtual void onRender(RenderContext* context);
    		virtual void onDispatch(const Message& msg);
    		virtual void onActivate(Visual* visual);
    		virtual void onDeactivate(Visual* visual);
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
    		virtual void onDispatchKeyboardEvent(const MsgKeyboard& msg);
    		virtual void onKeyboardPress(const KeyboardEventArgs& args);
    		virtual void onKeyboardRelease(const KeyboardEventArgs& args);
#endif
#if eosGuiService_TouchpadEnabled
    		virtual void onDispatchTouchpadEvent(const MsgTouchpad& msg);
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

#if eosGuiService_TouchpadEnabled
            inline void setTouchpadPressEventCallback(ITouchpadPressEventCallback* callback) { _touchpadPressEventCallback = callback; }
            inline void setTouchpadReleaseEventCallback(ITouchpadReleaseEventCallback* callback) { _touchpadReleaseEventCallback = callback; }
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


#endif // __eosVisual__
