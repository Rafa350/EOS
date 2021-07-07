#ifndef __eosDecorator__
#define __eosDecorator__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Decorator: public Visual {
		private:
			Visual *_child;
			Thickness _padding;

		public:
			Decorator();

        	void setChild(Visual *value);
        	void setPadding(Thickness value);

        	inline Visual* getChild() const { return _child; }
        	inline Thickness getPadding() const { return _padding; }
	};
}


#endif // __eosDecorator__
