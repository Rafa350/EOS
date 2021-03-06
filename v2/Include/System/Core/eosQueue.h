#ifndef __eosQueue__
#define __eosQueue__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalQueue.h"


namespace eos {

    /// \brief Interface generic per les cues.
    ///
    class GenericQueue {
        private:
            HQueue hQueue;

        public:
            virtual ~GenericQueue();
            void clear();

        protected:
            GenericQueue(unsigned size, unsigned capacity);
            bool genericPut(const void* element, unsigned blockTime);
            bool genericGet(void* element, unsigned blockTime);
            bool genericPutISR(void* element);
            bool genericGetISR(void* element);
            bool genericIsEmpty() const { return osalQueueIsEmpty(hQueue); }
            bool genericIsEmptyISR() const { return osalQueueIsEmptyISR(hQueue); }
    };

    /// \brief Cua personalitzada amb plantilla.
    ///
    template <typename T>
    class Queue: private GenericQueue {
        public:
            /// \brief Constructor.
            /// \param: capacity: Nombre d'elements que pot contindre la cua.
            ///
            inline Queue(unsigned capacity):
                GenericQueue(sizeof(T), capacity) {
            }

            /// \brief Afegeix un element en la cua.
            /// \param element: L'element a afeigir.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool push(const T& element, unsigned blockTime) {
                return genericPut((void*) &element, blockTime);
            }

            /// \brief Afegeix un element en la cua des d'una interrupcio
            /// \param element: L'element a afeigir.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool pushISR(const T& element) {
                return genericPutISR((void*) &element);
            }

            /// \brief Extreu un element de la cua.
            /// \param element: L'element a Exterure.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool pop(T& element,  unsigned blockTime) {
                return genericGet((void*) &element, blockTime);
            }

            /// \brief Indica si la cua es buida
            /// \truen True si es buida
            //
            inline bool isEmpty() const {
            	return genericIsEmpty();
            }
    };

}


#endif // __eosQueue__
