#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"


namespace eos {

	class Graphics;

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

    	protected:
    		virtual void onRender(Graphics *graphics) = 0;

        public:
    		Visual();
    		virtual ~Visual();

            void addVisual(Visual *visual);
            void removeVisual(Visual *visual);

            inline Visual *getParent() const { return parent; }
            inline Visual *getFirstChild() const { return firstChild; }
            inline Visual *getLastChild() const { return lastChild; }
            inline unsigned getNumChilds() const { return numChilds; }
            inline Visual *getNextSibling() const { return nextSibling; }
            inline Visual *getPrevSibling() const { return prevSibling; }

            inline bool getNeedRender() const { return needRender; }
            inline bool isVisible() const { return visible; }

            void setVisible(bool visible);

            void render(Graphics *graphics);
    		void invalidate();
    };

}


#endif // __eosVisual__
