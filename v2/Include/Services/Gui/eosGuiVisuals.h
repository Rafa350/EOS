#ifndef __eosGuiVisual__
#define __eosGuiVisual__


// EOS includes
//
#include "eos.h"


namespace eos {

	class Color;
	class Display;
	class Visual;
	class VisualContainer;

	void addVisual(VisualContainer *container, Visual *visual);
	void removeVisual(VisualContainer *container, Visual *visual);

    class Visual {
    	private:
    		Visual *parent;
    		Visual *nextSibling;
    		Visual *prevSibling;
    		bool needRender;

    	protected:
    		virtual void onRender(Display *display) = 0;

        public:
    		Visual();
    		virtual ~Visual() {}

            inline Visual *getParent() const { return parent; }
            inline Visual *getNextSibling() const { return nextSibling; }
            inline Visual *getPrevSibling() const { return prevSibling; }

            inline bool getNeedRender() const { return needRender; }

            virtual void render(Display *display);

            friend void addVisual(VisualContainer *container, Visual *visual);
            friend void removeVisual(VisualContainer *container, Visual *visual);
    };

    class VisualContainer: public Visual {
    	private:
    		Visual *firstChild;
    		Visual *lastChild;
    		unsigned numChilds;

        public:
    		VisualContainer();
    		~VisualContainer();

            void addVisual(Visual *visual);
            void removeVisual(Visual *visual);
            inline Visual *getFirstChild() const { return firstChild; }
            inline Visual *getLastChild() const { return lastChild; }
            inline unsigned getNumChilds() const { return numChilds; }

            void render(Display *display) override;

            friend void addVisual(VisualContainer *container, Visual *visual);
            friend void removeVisual(VisualContainer *container, Visual *visual);
    };

    class Screen: public VisualContainer {
    	private:
    		Color color;
        public:
            void setColor(const Color &color);

            void onRender(Display *display) override;
    };

    class Control: public VisualContainer {
    	private:
    		int x;
    		int y;
    		int width;
    		int height;
        public:
            void setPosition(int x, int y);
            void setSize(int width, int height);
    };

    class Window: public Control {
        public:
            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);
    };

}


#endif // __eosGuiVisual__
