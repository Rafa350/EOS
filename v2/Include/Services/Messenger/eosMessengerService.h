#pragma once


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/eosTypeID.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


namespace eos {

    class MessengerService final: public Service {
    	private:
    		struct RawMessage {
    			uint16_t id;
    			void *payload;
    		};
    		using RawMessageQueue = Queue<RawMessage>;

    	private:
    		RawMessageQueue _rawMessageQueue;

    	protected:
            void onExecute() override;

        public:
            MessengerService();

            template <typename Message_>
            void *createChannel() {
            	return nullptr;
            }

            void publish(unsigned id, void *payload, unsigned blockTime);
            void publishISR(unsigned id, void *payload);
    };

    /// \brief Objecte que permet publicar missatges i gestionarlos amb el
    ///        servei MessengerService.
    ///
    template <typename Message_>
    class Publisher {
    	private:
    		static constexpr auto const _id = TypeID<Message_, unsigned>::value;

    	private:
    		MessengerService * const _messenger;

    	public:
    		Publisher(MessengerService *messenger) :
    			_messenger {messenger} {

    		}

    		void *alloc() {

    			return nullptr;
    		}

    		void free(void *p) {

    		}

    		/// \brief  Publica un missatge.
    		/// \param  message: El missatge a publicar.
    		/// \param  blockTime: Tamps maxim de bloqueig
    		///
    		void publish(Message_ &message, unsigned blockTime) {

    			auto payload = alloc();
    			_messenger->publish(_id, payload, blockTime);
    		}

    		/// \brief  Publica un missatge des de una interrupcio.
    		/// \param  message: El missatge a publicar.
    		///
    		void publishISR(Message_ &message) {

    			auto payload = alloc();
    			_messenger->publishISR(message.id, payload);
    		}
    };
}
