#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/graphics/eosSize.h"


namespace eos {

	class RenderContext;

    class Visual {
    	private:
    		Visual *parent;
    		Visual *firstChild;
    		Visual *lastChild;
    		Visual *nextSibling;
    		Visual *prevSibling;
    		unsigned numChilds;
    		bool needRender;
    		bool visible;
    		Point position;
			Size size;

    	protected:
    		virtual void onRender(RenderContext *context) = 0;

    		void addVisual(Visual *visual);
            void removeVisual(Visual *visual);

        public:
    		Visual();
    		virtual ~Visual();

            inline Visual *getParent() const { return parent; }
            inline Visual *getFirstChild() const { return firstChild; }
            inline Visual *getLastChild() const { return lastChild; }
            inline unsigned getNumChilds() const { return numChilds; }
            inline Visual *getNextSibling() const { return nextSibling; }
            inline Visual *getPrevSibling() const { return prevSibling; }

            inline bool getNeedRender() const { return needRender; }
            inline bool isVisible() const { return visible; }
            void setVisible(bool visible);

            void setPosition(const Point &p);
            void setSize(const Size &s);

            inline const Point& getPosition() const { return position; }
            inline const Size& getSize() const { return size; }
            inline Rect getRect() const { return Rect(0, 0, size.getWidth(), size.getHeight()); }

            void render(RenderContext *context);
    		void invalidate();
    };

}


#endif // __eosVisual__
