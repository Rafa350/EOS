#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"
#include "System/Graphics/eosThickness.h"


namespace eos {

	class RenderContext;
	class Message;

	enum class Visibility {
		visible,
		hidden,
		collapsed
	};

	enum class Orientation {
		horitzontal,
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
    typedef List<Visual*> VisualList;
    //typedef ReadOnlyList<Visual*> ReadOnlyVisualList;
    typedef ListIterator<Visual*> VisualListIterator;

    /// \brief Clase base que representa tots els elements visuals.
	///
    class Visual {
    	private:
    		Visual *pParent;
    		VisualList childs;
    		bool needRender;
    		Visibility visibility;
    		Point position;
			Size size;
			Size minSize;
			Size maxSize;
			Size desiredSize;
			Rect bounds;
			Thickness margin;
			HorizontalAlignment horizontalAlignment;
			VerticalAlignment verticalAlignment;

    	protected:
    		virtual void onRender(RenderContext &context) = 0;
    		virtual void onDispatch(const Message &msg);
    		virtual void onActivate(Visual *pVisual);
    		virtual void onDeactivate(Visual *pVisual);
#ifdef OPT_GUI_TouchPad
    		virtual void onDispatchTouchPadEvent(const Message &msg);
    		virtual void onTouchPadEnter();
    		virtual void onTouchPadLeave();
    		virtual void onTouchPadPress(const Point &position);
    		virtual void onTouchPadRelease();
    		virtual void onTouchPadMove(const Point &position);
#endif
            virtual Size measureOverride(const Size &availableSize) const;
            virtual Size arrangeOverride(const Size &finalSize) const;

            void addVisual(Visual *pVisual);
            void removeVisual(Visual *pVisual);
            void removeVisuals();

        public:
            // Constructors i destructors
    		Visual();
    		virtual ~Visual();

            inline Visual *getParent() const { return pParent; }
            inline const VisualList& getChilds() const { return childs; }
            Visual *getVisualAt(const Point &p);

            // Checkers
            bool isRenderizable();
            bool isVisible() const;

            // Setters
            void setHorizontalAlignment(HorizontalAlignment horizontalAlignment);
            void setMargin(const Thickness &margin);
            void setMinSize(const Size &size);
            void setPosition(const Point &position);
            void setSize(const Size &size);
            void setVerticalAlignment(VerticalAlignment verticalAlignment);
            void setVisibility(Visibility visibility);

            // Getters
            Point getAbsolutePosition() const;
            inline HorizontalAlignment getHorizontalAlignment() const { return horizontalAlignment; }
            inline const Size& getMaxSize() const { return maxSize; }
            inline const Thickness& getMargin() const { return margin; }
            inline const Size& getMinSize() const { return minSize; }
            inline const Point& getPosition() const { return position; }
            inline Rect getRect() const { return Rect(Point(0, 0), size); }
            inline const Size& getSize() const { return size; }
            inline VerticalAlignment getVerticalAlignment() const { return verticalAlignment; }
            Visibility getVisibility() const { return visibility; }

            void measure(const Size &availableSize);
            void arrange(const Rect &finalRect);
            const Size& getDesiredSize() const { return desiredSize; }
            const Rect& getBounds() const { return bounds; }

            void dispatch(const Message &msg);
            bool render(RenderContext &context);
    		void invalidate();
    };

}


#endif // __eosVisual__
