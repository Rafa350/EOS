#ifndef __eosGuiVisual__
#define __eosGuiVisual__


// EOS includes
//
#include "eos.h"


namespace eos {

	class Color;
	class Visual;
	class VisualContainer;

	void addVisual(VisualContainer *container, Visual *visual);
	void removeVisual(VisualContainer *container, Visual *visual);

    class Visual {
    	private:
    		Visual *parent;
    		Visual *nextSibling;
    		Visual *prevSibling;

        public:
    		Visual();
    		virtual ~Visual() {}

            virtual void render() = 0;

            inline Visual *getParent() const { return parent; }
            inline Visual *getNextSibling() const { return nextSibling; }
            inline Visual *getPrevSibling() const { return prevSibling; }

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

            void render() override;
            void renderChilds();

            friend void addVisual(VisualContainer *container, Visual *visual);
            friend void removeVisual(VisualContainer *container, Visual *visual);
    };

    class Screen: public VisualContainer {
        public:
            void setColor(const Color &color);

            void render() override;
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
