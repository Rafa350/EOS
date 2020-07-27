#ifndef __eosCircularQueue__
#define __eosCircularQueue__


#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosStaticArray.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            
            /// \brief Implementa una cua circular de tamany fix.
            /// \remarks La cua enmagatzema copies del element.
            ///
            template <typename Element, const unsigned size>
            class CircularQueue {
                
                private:
                    typedef StaticArray<Element, size> Data;
                    
                public:
                    typedef Element Value;
                    typedef Element& Reference;
                    typedef const Element& CReference;
                    
                private:
                    int count;
                    int enqueueIndex;
                    int dequeueIndex;
                    Data data;
                
                public:
                    
                    /// \brief Constructor per defecte.
                    ///
                    CircularQueue():
                        count(0),
                        enqueueIndex(0),
                        dequeueIndex(0) {
                        
                    }
                        
                    /// \brief Afegeix un elemenmt a la cua
                    /// \param element: L'element a afeigir.
                    ///
                    void enqueue(CReference element) {
                        eosAssert(count < size);
                        if (count < size) {
                            data[enqueueIndex++] = element;
                            if (enqueueIndex == size)
                                enqueueIndex = 0;
                            count++;
                        }
                    }
                    
                    Value dequeue() {
                        eosAssert(count > 0);
                        if (count > 0) {
                            Reference element = data[dequeueIndex++];
                            if (dequeueIndex == size)
                                dequeueIndex = 0;
                            count--;
                            return element;
                        }
                    }
                    
                    inline unsigned getCount() const { 
                        return count; 
                    }
                    
                    inline bool isEmpty() const {
                        return count == 0;
                    }
                    
                    inline bool isFull() const {
                        return count == size;
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosCircularQueue__
