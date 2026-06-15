#pragma once
#ifndef __rtosQueue__
#define __rtosQueue__


#include "eos.h"


namespace eos {

	class Time;
}


namespace rtos {

	class Queue final {
		private:
			void * const _handler;

		public:
			Queue(uint32_t elementSize, uint32_t capacity);
			~Queue();

			void clear() const;
			bool put(const void *element, eos::Time blockTime) const;
			bool putISR(const void *element) const;
			bool get(void *element, eos::Time blockTime) const;
			bool getISR(void *element) const;
			bool peek(void *element, eos::Time blockTime) const;
			bool peekISR(void *element) const;

            bool isEmpty() const;
            bool isEmptyISR() const;

            uint32_t getCount() const;
            uint32_t getCountISR() const;
	};
}


#endif // __rtosQueue__
