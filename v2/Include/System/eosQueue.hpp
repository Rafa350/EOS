#ifndef __EOS_QUEUE_HPP
#define __EOS_QUEUE_HPP


#include "eos.hpp"


namespace eos {
    
    class GenericQueue {
        private:
            void *handle;
        
        public:
            ~GenericQueue();
            void clear();
            virtual bool put(void *data, unsigned timeout);
            virtual bool get(void *data, unsigned timeout);
            virtual bool putISR(void *data);
            virtual bool getISR(void *data);            
        private:
            GenericQueue(unsigned itemSize, unsigned maxItems);       
    };
    
    template <typename itemType>
    class Queue: public GenericQueue {
        public:
            inline Queue(unsigned maxItems):
                GenericQueue(sizeof(itemType), maxItems) {
            }
            
            inline bool put(itemType *data, unsigned timeout) {
                return GenericQueue::put((void*) data, timeout);
            }
            
            inline bool get(itemType *data, unsigned timeout) {
                return GenericQueue::get((void*) data, timeout);
            }
    };
}


#endif