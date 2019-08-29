#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosList.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosSize.h"


namespace eos {

	class RenderContext;
	class Message;

	/// \brief Clase base que representa tots els elements visuals.
	///
    class Visual {
        private:
            typedef List<Visual*> VisualList;
            typedef ListIterator<Visual*> VisualListIterator;

    	private:
    		Visual *pParent;
    		VisualList childs;
    		bool needRender;
    		bool visible;
    		Point position;
			Size size;

    	protected:
    		virtual void onRender(RenderContext &context) = 0;
    		virtual void onDispatch(const Message &msg);
    		virtual void onActivate(const Message &msg);
    		virtual void onDeactivate(const Message &msg);

    		void addVisual(Visual *pVisual);
            void removeVisual(Visual *pVisual);
            void removeVisuals();

        public:
    		Visual();
    		virtual ~Visual();

            inline Visual *getParent() const { return pParent; }
            Visual *getVisualAt(const Point &p);

            bool isRenderizable();
            inline bool isVisible() const;
            void setVisible(bool visible);

            void setPosition(const Point &p);
            void setSize(const Size &s);

            inline const Point& getPosition() const { return position; }
            Point getAbsolutePosition() const;
            inline const Size& getSize() const { return size; }
            inline Rect getRect() const { return Rect(Point(0, 0), size); }

            void dispatch(const Message &msg);
            bool render(RenderContext &context);
    		void invalidate();
    };

}


#endif // __eosVisual__
