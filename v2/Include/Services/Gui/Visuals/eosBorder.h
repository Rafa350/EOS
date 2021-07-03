#ifndef __eosBorder__
#define __eosBorder__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosThickness.h"
#include "Services/Gui/Visuals/eosDecorator.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosBrush.h"


namespace eos {

    class RenderContext;

    class Border: public Decorator {
    	private:
    		Brush _background;
    		Brush _borderBrush;
    		Thickness _borderThickness;
    		int _radius;

    	protected:
    		Size measureOverride(const Size &availableSize) const override;
    		void onRender(RenderContext *context) override;

        public:
    		Border();

            void setBackground(const Brush &value);
            void setBorderBrush(const Brush &value);
            void setBorderThickness(int value);
            void setRadius(int value);

            inline const Brush& getBorderBrush() const { return _borderBrush; }
            inline const Brush& getBackground() const { return _background; }
            inline const Thickness& getThickness() const { return _borderThickness; }
            inline int getRadius() const { return _radius; }
    };

}


#endif // __eosBorder__
