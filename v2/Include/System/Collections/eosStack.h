#ifndef __eosStack__
#define	__eosStack__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosStdHeapAllocator.h"

// Std includes
//
#include <vector>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif

            /// \brief Implementa un contenidos FIFO de tamany fix o variable.
        	/// \remarks El contenidor enmagatzema copies del element.
            ///
			template <typename Element, int initialCapacity = 0, bool fixedCapacity = false>
			class Stack {
				private:
					typedef std::vector<Element, StdHeapAllocator<Element> > V;

				public:
					typedef Element& Reference;
					typedef const Element& CReference;

				private:
					V _v;

				public:

					/// \brief Contructor per defecte
					///
					Stack() {
						if constexpr (initialCapacity > 0)
							_v.reserve(initialCapacity);
					}

					/// \brief Constructor copia
					///
					Stack(const Stack& other) = delete;

					/// \brief Afegeix un element a la pila.
					/// \param element: L'element a afeigir.
					//
					inline bool push(CReference element) {
						if constexpr (fixedCapacity)
							if (_v.size() == _v.capacity())
								return false;
						_v.push_back(element);
						return true;
					}

					/// \brief Elimina un element de la pila.
					///
					inline bool pop() {
						if (_v.size() > 0) {
							_v.pop_back();
							return true;
						}
						return false;
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline Reference peek() {
						eosAssert(_v.size() > 0);
						return _v.back();
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline CReference peek() const {
						eosAssert(_v.size() > 0);
						return _v.back();
					}

					/// \brief Buida la pila.
					///
					inline void clear() {
						_v.clear();
					}

					/// \brief: Indica si la pila es buida.
					/// \return: True si es buida.
					///
					inline bool isEmpty() const {
						return _v.empty();
					}

					/// \brief: Indica si la pila es plena
					/// \return: True si es plena.
					///
					inline bool isFull() const {
						return _v.size() == _v.capacity();
					}

					/// \brief Obte el tamany de la pila.
					/// \return El valor.
					///
					inline int getSize() const {
						return _v.size();
					}

					/// \brief Obte capacitat actual de la pila.
					/// \return El valor.
					///
					inline int getCapacity() const {
						return _v.capacity();
					}
			};

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosStack__


