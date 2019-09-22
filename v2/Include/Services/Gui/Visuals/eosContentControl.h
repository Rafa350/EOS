#ifndef __eosContentControl__
#define __eosContentControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ContentControl: public Control {
		private:
            Thickness padding;
			Visual *pContent;

			protected:
				Size measureOverride(const Size &availableSize) const override;

		public:
			ContentControl();

			void setPadding(const Thickness &padding);
			inline const Thickness &getPadding() const { return padding; }
			void setContent(Visual *pNewContent);
			inline Visual* getContent() const { return pContent; }
	};
}


#endif // __eosContentControl__
