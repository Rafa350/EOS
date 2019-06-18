#ifndef __eosGuiVisual__
#define __eosGuiVisual__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class Display;
	class Visual;
	class VisualContainer;

    class Visual {
    	private:
    		Visual *parent;
    		Visual *firstChild;
    		Visual *lastChild;
    		Visual *nextSibling;
    		Visual *prevSibling;
    		unsigned numChilds;
    		bool needRender;

    	protected:
    		virtual void onRender(Display *display) = 0;
    		void invalidate();

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

            void render(Display *display);
    };

    class Screen: public Visual {
    	private:
    		Color color;

    	protected:
            void onRender(Display *display) override;

    	public:
            void setColor(const Color &color);

            inline Color getColor() const { return color; }
    };

    class Window: public Visual {
    	private:
    		int x;
    		int y;
    		int width;
    		int height;

    	public:
            void setPosition(int x, int y);
            void setSize(int width, int height);

            inline int getX() const { return x; }
            inline int getY() const { return y; }
            inline int getWidth() const { return width; }
            inline int getHeight() const { return height; }
    };

    class Widget: public Window {
    	private:
    		Color backgroundColor;
    		Color borderColor;
    		int borderThickness;

    	protected:
    		void onRender(Display *display) override;

        public:
            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);

            inline Color getBorderColor() const { return borderColor; }
    };

}


#endif // __eosGuiVisual__
