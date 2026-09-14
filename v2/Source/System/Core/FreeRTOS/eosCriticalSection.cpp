module;


#include "eos.h"

#include "FreeRTOS.h"
#include "task.h"


export module Eos.System.Core.CriticalSection;


export namespace eos {

	class CriticalSection final {
		public:
			static inline void enter() {
				taskENTER_CRITICAL();
			}

			static inline void exit() {
			    taskEXIT_CRITICAL();
			}
	};


	class CriticalSectionLocker {
		public:
			inline CriticalSectionLocker() {
				CriticalSection::enter();
			}

			inline ~CriticalSectionLocker() {
				CriticalSection::exit();
			}
	};
}
