#pragma once
#ifndef __eosQueue__
#define __eosQueue__


// EOS includes
//
#include "eos.h"
#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosQueue.h"


namespace eos {

    /// \brief Cua
    /// \param T_: Tipus del element en la cua.
	///
    template <typename T_>
    class Queue {
    	private:
    		rtos::Queue _queue;

        public:
            /// \brief Constructor.
            /// \param: capacity: Nombre d'elements que pot contindre la cua.
            ///
            inline Queue(uint32_t capacity):
                _queue {sizeof(T_), capacity} {
            }

            /// \brief Afegeix un element en la cua.
            /// \param element: L'element.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool push(const T_ &element, uint32_t blockTime) const {
            	return _queue.put(&element, rtos::Miliseconds(blockTime));
            }

            /// \brief Afegeix un element en la cua des d'una interrupcio
            /// \param element: L'element.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool pushISR(const T_ &element) const {
            	return _queue.putISR(&element);
            }

            /// \brief Extreu un element de la cua.
            /// \param element: L'element.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool pop(T_ &element, uint32_t blockTime) const {
            	return _queue.get(&element, rtos::Miliseconds(blockTime));
            }

            /// \brief Obte un element de la cua sense treurel
            /// \param element: L'element.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool peek(T_ &element, uint32_t blockTime) const {
                return _queue.peek(&element, rtos::Miliseconds(blockTime));
            }
    };

}


#endif // __eosQueue__
