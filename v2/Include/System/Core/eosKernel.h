#pragma once
#ifndef __eosKerner__
#define __eosKerner__


#include "eos.h"


namespace eos {

	class Kernel final {
		private:
			static Kernel _instance;

		public:
			static constexpr Kernel *pInst = &_instance;
			static constexpr Kernel &rInst = _instance;

		private:
			Kernel();

		public:
			void startScheduler();
			void suspendAll();
			void resumeAll();

			unsigned getTickCount() const;
	};
}


#endif // __eosKerner__

