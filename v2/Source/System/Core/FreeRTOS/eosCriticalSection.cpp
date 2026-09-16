module;


#include "eos.h"

#include "FreeRTOS.h"
#include "task.h"


export module Eos.System.Core.CriticalSection;


export namespace eos {

	class CriticalSection final {
		public:
			CriticalSection() = delete;
			~CriticalSection() = delete;

			static inline void enter() {
				taskENTER_CRITICAL();
			}

			static inline void exit() {
			    taskEXIT_CRITICAL();
			}
	};


	class CriticalSectionLocker {
		public:
			CriticalSectionLocker(const CriticalSectionLocker&) = delete;
			CriticalSectionLocker& operator=(const CriticalSectionLocker&) = delete;

			inline CriticalSectionLocker() {
				CriticalSection::enter();
			}

			inline ~CriticalSectionLocker() {
				CriticalSection::exit();
			}
	};
}
