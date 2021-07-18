#ifndef __eosCommandButton__
#define __eosCommandButton__


#include "eos.h"
#include "Services/Gui/Visuals/eosPushButton.h"


namespace eos {

	class CommandButton: public PushButton {
		private:
			int _id;
			void* _param;
			Visual* _target;

		protected:
			void onClick() override;

		public:
			CommandButton();

			inline void setId(int id) { _id = id; }
			inline void setParam(void* param) { _param = param; }
			inline void setTarget(Visual* target) { _target = target; }

			inline int getId() const { return _id; }
			inline void* getParam() const { return _param; }
			inline Visual* getTarget() const { return _target; }
	};
}


#endif
