#ifndef __EOS_QUEUE_HPP
#define __EOS_QUEUE_HPP


#include "eos.hpp"


namespace eos {
    
    /// \brief Cua generica basada en la cua de FreeRTOS
    ///
    class GenericQueue {
        private:
            void *handle;
        
        public:
            virtual ~GenericQueue();
            void clear();
        protected:
            GenericQueue(unsigned size, unsigned capacity);                   
            bool genericPut(void *element, unsigned blockTime);
            bool genericGet(void *element, unsigned blockTime);
            bool putISR(void *element);
            bool getISR(void *element);            
    };
    
    template <typename elementType>

    /// \brief Cua personalitzaba amb plantilla.
    ///
    class Queue: private GenericQueue {
        public:
            /// \brief Constructor.
            /// \param: capacity: Nombre d'elements que pot contindre la cua.
            ///
            inline Queue(unsigned capacity):
                GenericQueue(sizeof(elementType), capacity) {
            }
                
            /// \brief Afegeix un element en la cua.
            /// \param element: L'element a afeigir.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool put(elementType &element, unsigned blockTime) {
                
                return genericPut((void*) &element, blockTime);
            }
            
            /// \br Extreu un element de la cua.
            /// \param element: L'element a Exterure.
            /// \param blockTime: Temps maxim de bloqueig en ticks.
            /// \return True si ha finalitzat l'operacio correctament.
            ///
            inline bool get(elementType &element, unsigned blockTime) {
                
                return genericGet((void*) &element, blockTime);
            }
    };
}


#endif