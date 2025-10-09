#pragma once
#ifndef __eosMessageBus__
#define __eosMessageBus__


#include "eos.h"
#include "OSAL/osalMutex.h"
#include <System/Collections/eosCircularBuffer.h>

#include <type_traits>


namespace eos {

	template <typename MessageID_>
	class MessageBus {

	    HMutex _mutex;
		CircularBuffer<uint8_t> _buffer;
		unsigned _bufferSize;

		static_assert(std::is_enum_v<MessageID_>, "Ha de ser un enumerador.");

		public:
			MessageBus(uint8_t *buffer, unsigned bufferSize) :
				_buffer {buffer, bufferSize},
				_bufferSize {bufferSize},
				_mutex {osalMutexCreate()} {
			}

			template <typename Args_>
			bool send(MessageID_ id, Args_ const &args, unsigned blockTime) {

				bool result = false;

				osalMutexWait(_mutex, blockTime);

				if ((_bufferSize - _buffer.getCount()) >= (sizeof(MessageID_) + sizeof(Args_))) {

					unsigned count;
					uint8_t * p;

					count = sizeof(id);
					p = (uint8_t*) &id;
					while (count--)
						_buffer.put(*p++);

					count = sizeof(Args_);
					p = (uint8_t*) &args;
					while (count--)
						_buffer.put(*p++);

					result = true;
				}

				osalMutexRelease(_mutex);

				return result;
			}

			bool receive(MessageID_ &id, unsigned blockTime) {

				bool result = false;

				uint8_t data;

				if (_buffer.peek(data)) {
					id = (MessageID_) data;
					result = true;
				}

				return result;
			}

			template <typename Args_>
			bool read(Args_ &args) {

				bool result = false;

/*				MessageID_ id;
				memcpy(&id, pPop, sizeof(id));
				if (id != Message_::id)
					return false;

				pPop += sizeof(MessageID_);

				memcpy(&args, pPop, sizeof(Args_));
				pPop += sizeof(Args_);
*/
				return result;
			}
	};
}


#endif // __eosMessageBus__
