module;


#include "FreeRTOS.h"
#include "task.h"


export module Eos.System.Core.CriticalSection;


export namespace eos {

	class CriticalSection final {
		public:
			CriticalSection() = delete;
			~CriticalSection() = delete;

			static void enter() {
				taskENTER_CRITICAL();
			}

			static void exit() {
			    taskEXIT_CRITICAL();
			}
	};


	class CriticalSectionLocker {
		public:
			CriticalSectionLocker(const CriticalSectionLocker&) = delete;
			CriticalSectionLocker& operator=(const CriticalSectionLocker&) = delete;

			CriticalSectionLocker() {
				CriticalSection::enter();
			}

			~CriticalSectionLocker() {
				CriticalSection::exit();
			}
	};
}
