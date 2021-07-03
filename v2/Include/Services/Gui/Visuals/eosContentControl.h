#ifndef __eosContentControl__
#define __eosContentControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ContentControl: public Control {
		private:
            Thickness _padding;
			Visual *_content;

		public:
			ContentControl();

			void setPadding(const Thickness &value);
			void setContent(Visual *value);

			inline const Thickness &getPadding() const { return _padding; }
			inline Visual* getContent() const { return _content; }
	};
}


#endif // __eosContentControl__
