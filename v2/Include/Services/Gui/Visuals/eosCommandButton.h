#ifndef __eosCommandButton__
#define __eosCommandButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosPushButton.h"


namespace eos {

	class CommandButton: public PushButton {
		private:
			int id;
			void *param;
			Visual *target;

		protected:
			void onClick() override;

		public:
			CommandButton();

			void setId(int id) { this->id = id; }
			void setParam(void *param) { this->param = param; }
			void setTarget(Visual *target) { this->target = target; }
			int getId() const { return id; }
			void *getParam() const { return param; }
			Visual *getTarget() const { return target; }
	};
}


#endif
