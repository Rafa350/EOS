#ifndef __eosBorder__
#define __eosBorder__


// EOS includes
//
#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosColor.h"


namespace eos {

    class RenderContext;

    class Border: public Visual {
    	private:
    		Color backgroundColor;
    		Color borderColor;
    		int borderThickness;
    		int borderRadius;
    		Visual *content;

    	protected:
    		void onRender(RenderContext &context) override;

        public:
    		Border();

            void setBackgroundColor(const Color &color);
            void setBorderColor(const Color &color);
            void setBorderThickness(int thickness);
            void setBorderRadius(int radius);
            void setContent(Visual *content);

            inline Color getBorderColor() const { return borderColor; }
            inline Color getBackgroundColor() const { return backgroundColor; }
            inline int getBorderThickness() const { return borderThickness; }
            inline int getBorderRadius() const { return borderRadius; }
            inline Visual* getContent() const { return content; }
    };

}


#endif // __eosBorder__
