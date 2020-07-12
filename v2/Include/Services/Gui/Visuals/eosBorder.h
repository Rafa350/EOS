#ifndef __eosBorder__
#define __eosBorder__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosDecorator.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class RenderContext;

    class Border: public Decorator {
    	private:
    		Color backgroundColor;
    		Color color;
    		Thickness thickness;
    		int radius;
    		Visual *content;

    	protected:
    		void onRender(RenderContext *context) override;
			Size measureOverride(const Size &availableSize) const override;

        public:
    		Border();

            void setBackgroundColor(const Color &value);
            void setColor(const Color &value);
            void setThickness(int value);
            void setRadius(int value);
            void setContent(Visual* value);

            inline Color getColor() const { return color; }
            inline Color getBackgroundColor() const { return backgroundColor; }
            inline const Thickness& getThickness() const { return thickness; }
            inline int getRadius() const { return radius; }
            inline Visual* getContent() const { return content; }
    };

}


#endif // __eosBorder__
