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
    		Brush _borderBrush;
    		Thickness _borderThickness;
    		int _cornerRadius;

    	protected:
    		Size measureOverride(const Size &availableSize) const override;
    		void onRender(RenderContext *context) override;

        public:
    		Border();

            void setBorderBrush(const Brush &value);
            void setBorderThickness(int value);
            void setCornerRadius(int value);

            inline const Brush& getBorderBrush() const { return _borderBrush; }
            inline const Thickness& getBorderThickness() const { return _borderThickness; }
            inline int getCornerRadius() const { return _cornerRadius; }
    };

}


#endif // __eosBorder__
