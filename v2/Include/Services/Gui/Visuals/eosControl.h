#ifndef __eosControl__
#define __eosControl__


#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosBrush.h"


namespace eos {

	class Control: public Visual {
		private:
			Brush _foreground;
			Brush _background;
			Brush _borderBrush;
			Thickness _borderThickness;

		protected:
			virtual void initializeControl();
			Size measureOverride(const Size &availableSize) const override;

		public:
			Control();

            void setForeground(const Brush &value);
            void setBackground(const Brush &value);
            void setBorderBrush(const Brush &value);
            void setBorderThickness(int value);

            inline const Brush& getForeground() const { return _foreground; }
            inline const Brush& getBackground() const { return _background; }
			inline const Brush& getBorderBrush() const { return _borderBrush; }
            inline const Thickness& getBorderThickness() const { return _borderThickness; }
	};
}


#endif // __eosControl__
