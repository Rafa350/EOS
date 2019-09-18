#ifndef __eosBorder__
#define __eosBorder__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/Visuals/eosDecorator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosThickness.h"


namespace eos {

    class RenderContext;

    class Border: public Decorator {
    	private:
    		Color backgroundColor;
    		Color color;
    		Thickness thickness;
    		int radius;
    		Visual *pContent;

    	protected:
    		void onRender(RenderContext &context) override;
			Size measureOverride(const Size &availableSize) const override;

        public:
    		Border();

            void setBackgroundColor(const Color &newColor);
            void setColor(const Color &newColor);
            void setThickness(int newThickness);
            void setRadius(int newRadius);
            void setContent(Visual *pNewContent);

            inline Color getColor() const { return color; }
            inline Color getBackgroundColor() const { return backgroundColor; }
            inline const Thickness& getThickness() const { return thickness; }
            inline int getRadius() const { return radius; }
            inline Visual* getContent() const { return pContent; }
    };

}


#endif // __eosBorder__
