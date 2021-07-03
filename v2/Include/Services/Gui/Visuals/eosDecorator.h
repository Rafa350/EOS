#ifndef __eosDecorator__
#define __eosDecorator__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Decorator: public Visual {
		private:
			Visual *_child;
		public:
			Decorator();

        	void setChild(Visual *value);
        	inline Visual* getChild() const { return _child; }
	};
}


#endif // __eosDecorator__
