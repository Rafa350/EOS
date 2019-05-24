#ifndef __eosQueue__
#define __eosQueue__


#include "eos.h"
#include "osal/osalQueue.h"


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
            bool genericPut(const void *element, unsigned blockTime);
            bool genericGet(void *element, unsigned blockTime);
            bool genericPutISR(void *element);
            bool genericGetISR(void *element);
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
            inline bool put(const T &element, unsigned blockTime) {
                return genericPut((void*) &element, blockTime);
            }

            /// \brief Extreu un element de la cua.
            /// \param element: L'element a Exterure.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool get(T &element, unsigned blockTime) {
                return genericGet((void*) &element, blockTime);
            }
    };
}


#endif // __eosQueue__
