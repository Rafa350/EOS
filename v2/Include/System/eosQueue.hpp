#ifndef __EOS_QUEUE_HPP
#define __EOS_QUEUE_HPP


#include "eos.hpp"


namespace eos {
    
    class GenericQueue {
        private:
            void *handle;
        
        public:
            GenericQueue(unsigned itemSize, unsigned maxItems);                   
            ~GenericQueue();
            void clear();
            bool put(void *data, unsigned timeout);
            bool get(void *data, unsigned timeout);
            bool putISR(void *data);
            bool getISR(void *data);            
    };
    
    template <typename itemType>
    class Queue: public GenericQueue {
        public:
            inline Queue(unsigned maxItems):
                GenericQueue(sizeof(itemType), maxItems) {
            }
            
            inline bool put(itemType &data, unsigned timeout) {
                return GenericQueue::put((void*) &data, timeout);
            }
            
            inline bool get(itemType &data, unsigned timeout) {
                return GenericQueue::get((void*) &data, timeout);
            }
    };
}


#endif