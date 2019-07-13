#ifndef __eosVisual__
#define __eosVisual__


// EOS includes
//
#include "eos.h"


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
    		int x;
    		int y;
    		int width;
    		int height;

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

            void setPosition(int x, int y);
            void setSize(int width, int height);
            inline int getX() const { return x; }
            inline int getY() const { return y; }
            inline void getPosition(int &x, int &y) const { x = this->x; y = this->y; }
			int getAbsoluteX() const;
			int getAbsoluteY() const;
			void getAbsolutePosition(int &x, int &y) const;
            inline int getWidth() const { return width; }
            inline int getHeight() const { return height; }
            inline void getSize(int &width, int &height) const { width = this->width; height = this->height; }

            void render(RenderContext *context);
    		void invalidate();
    };

}


#endif // __eosVisual__
