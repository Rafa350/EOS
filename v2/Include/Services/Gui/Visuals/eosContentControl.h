#ifndef __eosContentControl__
#define __eosContentControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ContentControl: public Control {
		private:
            Thickness padding;
			Visual *content;

		public:
			ContentControl();

			void setPadding(const Thickness &value);
			void setContent(Visual *value);

			inline const Thickness &getPadding() const { return padding; }
			inline Visual* getContent() const { return content; }
	};
}


#endif // __eosContentControl__
