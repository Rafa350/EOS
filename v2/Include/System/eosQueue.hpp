#ifndef __EOS_QUEUE_HPP
#define __EOS_QUEUE_HPP


#include "eos.hpp"


namespace eos {
    
    class QueueBase {
        public:
            ~QueueBase();
            void clear();
            virtual bool put(void *data, unsigned timeout);
            virtual bool get(void *data, unsigned timeout);
            virtual bool putISR(void *data);
            virtual bool getISR(void *data);            
        private:
            QueueBase(unsigned itemSize, unsigned maxItems);
            void *handle;
        
    };
    
    template <typename itemType>
    class Queue: public QueueBase {
        public:
            Queue(unsigned maxItems):
                QueueBase(sizeof(itemType), maxItems) {
            }
            
            bool put(itemType *data, unsigned timeout) {
                return QueueBase::put((void*) data, timeout);
            }
            
            bool get(itemType *data, unsigned timeout) {
                return QueueBase::get((void*) data, timeout);
            }
    };
}


#endif