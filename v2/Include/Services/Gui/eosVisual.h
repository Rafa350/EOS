#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosMsgQueue.h"
#include "Services/Gui/eosThickness.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"


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

	typedef DynamicArray<Visual*> VisualList;
	typedef DynamicArray<Visual*>::Iterator VisualListIterator;
	typedef DynamicArray<Visual*>::ConstIterator VisualListConstIterator;

	/// \brief Clase base que representa tots els elements visuals.
	///
    class Visual {
        	private:
    		Visual *parent;
    		VisualList childs;
    		bool needRender;
    		Visibility visibility;
			Size size;
			Size minSize;
			Size maxSize;
			Size desiredSize;
			Rect bounds;
			Thickness margin;
			HorizontalAlignment horizontalAlignment;
			VerticalAlignment verticalAlignment;

    	protected:
    		virtual void onRender(RenderContext *context) = 0;
    		virtual void onDispatch(const Message &msg);
    		virtual void onActivate(Visual *visual);
    		virtual void onDeactivate(Visual *visual);
#if defined(OPT_GUI_Keyboard) || defined(OPT_GUI_VirtualKeyboard)
    		virtual void onDispatchKeyboardEvent(const MsgKeyboard &msg);
    		virtual void onKeyboardPress(KeyCode keyCode, char ch);
    		virtual void onKeyboardRelease(KeyCode keyCode, char ch);
#endif
#ifdef OPT_GUI_TouchPad
    		virtual void onDispatchTouchPadEvent(const MsgTouchPad &msg);
    		virtual void onTouchPadEnter();
    		virtual void onTouchPadLeave();
    		virtual void onTouchPadPress(const Point &position);
    		virtual void onTouchPadRelease();
    		virtual void onTouchPadMove(const Point &position);
#endif
            virtual Size measureOverride(const Size &availableSize) const;
            virtual Size arrangeOverride(const Size &finalSize) const;

            void addVisual(Visual *visual);
            void removeVisual(Visual *visual);
            void removeVisuals();

        public:
            // Constructors i destructors
    		Visual();
    		virtual ~Visual();

            inline Visual *getParent() const { return parent; }
            inline const VisualList& getChilds() const { return childs; }

            // Checkers
            bool isRenderizable() const;
            bool isVisible() const;
            bool isEnabled() const;

            // Setters
            void setHorizontalAlignment(HorizontalAlignment value);
            void setMargin(const Thickness &value);
            void setMinSize(const Size &value);
            void setSize(const Size &value);
            void setVerticalAlignment(VerticalAlignment value);
            void setVisibility(Visibility value);

            // Getters
            inline const Rect& getBounds() const { return bounds; }
            inline HorizontalAlignment getHorizontalAlignment() const { return horizontalAlignment; }
            inline const Size& getMaxSize() const { return maxSize; }
            inline const Thickness& getMargin() const { return margin; }
            inline const Size& getMinSize() const { return minSize; }
            inline const Size& getSize() const { return size; }
            inline VerticalAlignment getVerticalAlignment() const { return verticalAlignment; }
            Visibility getVisibility() const { return visibility; }

            void measure(const Size &availableSize);
            void arrange(const Rect &finalRect);
            const Size& getDesiredSize() const { return desiredSize; }

            void dispatch(const Message &msg);
            void send(const Message &msg);
            bool render(RenderContext *context);
    		void invalidate();
    		void invalidateLayout();
    };

}


#endif // __eosVisual__
