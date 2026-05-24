#pragma once


#include "eos.h"


namespace rtos {

	class Miliseconds;

	class Queue {
		private:
			void * const _handler;

		public:
			Queue(uint32_t elementSize, uint32_t capacity);
			~Queue();

			void clear() const;
			bool put(const void *element, Miliseconds blockTime) const;
			bool putISR(const void *element) const;
			bool get(void *element, Miliseconds blockTime) const;
			bool getISR(void *element) const;
			bool peek(void *element, Miliseconds blockTime) const;
			bool peekISR(void *element) const;

            bool isEmpty() const;
            bool isEmptyISR() const;

            uint32_t getCount() const;
            uint32_t getCountISR() const;
	};
}
