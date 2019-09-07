#ifndef __eosContentControl__
#define __eosContentControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ContentControl: public Control {
		private:
			Visual *pContent;

		public:
			ContentControl();

			void setContent(Visual *pNewContent);
			inline Visual* getContent() const { return pContent; }
	};
}


#endif // __eosContentControl__
