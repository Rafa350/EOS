#ifndef __eosControl__
#define __eosControl__


#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "System/Graphics/eosBrush.h"


namespace eos {

	class Control: public Visual {
		private:
			Brush _background;

		protected:
			virtual void initializeControl();

		public:
			Control();

            void setBackground(const Brush& value);
            inline const Brush& getBackground() const { return _background; }
	};
}


#endif // __eosControl__
