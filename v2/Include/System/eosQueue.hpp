#ifndef __EOS_QUEUE_HPP
#define __EOS_QUEUE_HPP


#include "eos.hpp"


namespace eos {
    
    class GenericQueue {
        private:
            void *handle;
        
        public:
            GenericQueue(unsigned size, unsigned capacity);                   
            ~GenericQueue();
            void clear();
            bool put(void *element, unsigned blockTime);
            bool get(void *element, unsigned blockTime);
            bool putISR(void *element);
            bool getISR(void *element);            
    };
    
    template <typename elementType>
    class Queue: private GenericQueue {
        public:
            inline Queue(unsigned capacity):
                GenericQueue(sizeof(elementType), capacity) {
            }
            
            inline bool put(elementType &element, unsigned blockTime) {
                return GenericQueue::put((void*) &element, blockTime);
            }
            
            inline bool get(elementType &element, unsigned blockTime) {
                return GenericQueue::get((void*) &element, blockTime);
            }
    };
}


#endif