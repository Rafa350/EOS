#ifndef __eosSimpleQueue__
#define __eosSimpleQueue__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosStdHeapAllocator.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif
            /// \brief Implementa un contenidor FIFO de tamany fix, implementat
            ///        com un buffer circular.
            /// \remarks El contenidor enmagatzema copies del element.
            ///
            template <typename Element_, int maxCapacity_ = 10>
            class SimpleQueue {
                public:
                    typedef Element_ Value;
                    typedef Element_& Reference;
                    typedef const Element_& CReference;
                    typedef Element_* Pointer;

                private:
                    Pointer _container;
                    int _iput;
                    int _iget;
                    int _count;

                public:

                    /// \brief Constructor per defecte.
                    ///
                    SimpleQueue() :
                    	_container(new Value[maxCapacity_]()),
						_iput(0),
						_iget(0),
						_count(0) {
                    }

                    SimpleQueue(const SimpleQueue& other) = delete;

                    /// \brief Destructor.
                    ///
                    ~SimpleQueue() {
                    	delete[] _container;
                    }

                    /// \brief Afegeix un element a la cua
                    /// \param element: L'element a afeigir.
                    /// \return True si tot es correcte.
                    ///
                    bool enqueue(CReference element) {
                    	if (_count < maxCapacity_) {
                    		_container[_iput] = element;
                    		_count++;
                    		if (++_iput == maxCapacity_)
                    			_iput = 0;
                    		return true;
                    	}
                    	return false;
                    }

                    /// Extreu un element de la cua.
                    /// \return L'element.
                    ///
                    CReference dequeue() {
                    	eosAsert(_count > 0);
                   		Reference element = _container[_iget];
                    	_count--;
                    	if (++_iget == maxCapacity_)
                    		_iget = 0;
                    	return element;
                    }

                    /// \brief Buida el contingut de la cua.
                    ///
                    inline void clear() {
                    	_count = 0;
                    	_iget = 0;
                    	_iput = 0;
                    }

                    /// \brief Obte el tamany de la cua.
                    /// \return El valor.
                    ///
                    inline int getSize() const {
                        return _count;
                    }

                    /// \brief Obte la capacitat de la cua.
                    /// \return El valor.
                    ///
                    inline int getCapacity() const {
                        return maxCapacity_;
                    }

                    /// \brief Indica si la cua es buida.
                    /// \return True si es buida.
                    ///
                    inline bool isEmpty() const {
                        return _count == 0;
                    }

                    /// \brief Indica si la cua es plena.
                    /// \return True si es plena.
                    ///
                    inline bool isFull() const {
                        return _count == maxCapacity_;
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosSimpleQueue__
