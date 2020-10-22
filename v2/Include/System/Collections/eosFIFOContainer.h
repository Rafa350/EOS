#ifndef __eosFIFOContainer__
#define __eosFIFOContainer__


#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosStaticArray.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif
            /// \brief Implementa un contenidor FIFO de tamany fix.
            /// \remarks El contenidor enmagatzema copies del element.
            ///
            template <typename Element, const unsigned size>
            class FIFOContainer {

                private:
                    typedef StaticArray<Element, size> Container;

                public:
                    typedef Element Value;
                    typedef Element& Reference;
                    typedef const Element& CReference;

                private:
                    unsigned count;
                    unsigned enqueueIndex;
                    unsigned dequeueIndex;
                    Container container;

                public:

                    /// \brief Constructor per defecte.
                    ///
                    FIFOContainer():
                        count(0),
                        enqueueIndex(0),
                        dequeueIndex(0) {

                    }

                    /// \brief Afegeix un elemenmt a la cua
                    /// \param element: L'element a afeigir.
                    /// \return True si tot es correcte.
                    bool enqueue(CReference element) {
                        if (count < size) {
                            container[enqueueIndex++] = element;
                            if (enqueueIndex == size)
                                enqueueIndex = 0;
                            count++;
                            return true;
                        }
                        else
                        	return false;
                    }

                    /// \brief Extreu un element
                    /// \param element: Referencia on deixar l'element.
                    /// \return Trus si tot es correcte.
                    bool dequeue(Reference element) {
                        if (count > 0) {
                            element = container[dequeueIndex++];
                            if (dequeueIndex == size)
                                dequeueIndex = 0;
                            count--;
                            return true;
                        }
                        else
                        	return false;
                    }

                    inline void clear() {
                    	count = 0;
                    }

                    inline unsigned getCount() const {
                        return count;
                    }

                    inline unsigned getSize() const {
                        return size;
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


#endif // __eosFIFOContainer__
