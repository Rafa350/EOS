#pragma once


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif


            /// \brief Implementa un contenidor FIFO.
        	/// \remarks El contenidor enmagatzema copies del element en un buffer extern.
            ///
			template <typename T_>
			class StackBase {
				public:
					using ValueType = T_;
                    using Pointer = ValueType*;
                    using CPointer = const ValueType*;
					using Reference = ValueType&;
					using CReference = const ValueType&;

				private:
                    Pointer _begin;
                    Pointer _end;
                    Pointer _sp;
                    
                private:
					StackBase(const StackBase &) = delete;
                    StackBase & operator = (const StackBase &) = delete;

				public:

					/// \brief Constructor per defecte
					///
					StackBase(Pointer container, unsigned capacity):
                        _begin {container},
                        _end {container + capacity},
                        _sp {container} {
                            
                        eosAssert(container != nullptr);
                        eosAssert(capacity > 1);
					}

					/// \brief Afegeix un element a la pila.
					/// \param element: L'element a afeigir.
					//
					inline void push(CReference element) {
                        eosAssert(!full());
                        *_sp++ = element;
					}

					/// \brief Elimina un element de la pila.
					///
					inline void pop() {
                        eosAssert(!empty());
						_sp--;
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline Reference peek() {
                        eosAssert(!empty());
						return *(_sp - 1); // Sempre apunta al seguent
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline CReference peek() const {
                        eosAssert(!empty());
						return *(_sp - 1);
					}

					/// \brief Buida la pila.
					///
					inline void clear() {
						_sp = _begin;
					}

					/// \brief: Indica si la pila es buida.
					/// \return: True si es buida.
					///
					inline bool empty() const {
						return _sp == _begin;
					}

					/// \brief: Indica si la pila es plena
					/// \return: True si es plena.
					///
					inline bool full() const {
                        return _sp == _end;
					}

					/// \brief Obte el tamany de la pila.
					/// \return El valor.
					///
					inline unsigned size() const {
						return _sp - _begin;
					}

					/// \brief Obte capacitat actual de la pila.
					/// \return El valor.
					///
					inline unsigned capacity() const {
						return _end - _begin;
					}
			};
            
            
            template <typename T_, unsigned capacity_>
            class FixedCapacityStack: public StackBase<T_> {
                private:
                    T_ _container[capacity_];
                public:
                    FixedCapacityStack() :
                        StackBase<T_>(_container, capacity_) {                            
                        }
            };
            

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}
