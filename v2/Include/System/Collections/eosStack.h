#ifndef __eosStack__
#define	__eosStack__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"

// Std includes
//
#include <vector>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif

            /// \brief Implementa un contenidos FIFO de tamany fix o variable.
        	/// \remarks El contenidor enmagatzema copies del element.
            ///
			template <typename Element_, unsigned initialCapacity_ = 0, bool fixedCapacity_ = false>
			class Stack {
				private:
					using Container = std::vector<Element_>;

				public:
					using Value = typename Container::value_type;
					using Reference = typename Container::reference;
					using CReference = typename Container::const_reference;

				private:
					Container _c;

				public:

					/// \brief Contructor per defecte
					///
					Stack() {
						if constexpr (initialCapacity_ > 0)
							_c.reserve(initialCapacity_);
					}

					/// \brief Constructor copia
					///
					Stack(const Stack &other) = delete;

					/// \brief Afegeix un element a la pila.
					/// \param element: L'element a afeigir.
					//
					inline void push(CReference element) {
						eosAssert((fixedCapacity_ && (_c.size() < _c.capacity())) || !fixedCapacity_);
						_c.push_back(element);
					}

					/// \brief Elimina un element de la pila.
					///
					inline void pop() {
						eosAssert(_c.size() > 0);
						_c.pop_back();
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline Reference peek() {
						eosAssert(_c.size() > 0);
						return _c.back();
					}

					/// \brief: Obte el primer element de la pila.
					/// \return: El primer element.
					///
					inline CReference peek() const {
						eosAssert(_c.size() > 0);
						return _c.back();
					}

					/// \brief Buida la pila.
					///
					inline void clear() {
						_c.clear();
					}

					/// \brief: Indica si la pila es buida.
					/// \return: True si es buida.
					///
					inline bool isEmpty() const {
						return _c.empty();
					}

					/// \brief: Indica si la pila es plena
					/// \return: True si es plena.
					///
					inline bool isFull() const {
						if constexpr (fixedCapacity_)
							return _c.size() == _c.capacity();
						else
							return false;
					}

					/// \brief Obte el tamany de la pila.
					/// \return El valor.
					///
					inline unsigned getSize() const {
						return _c.size();
					}

					/// \brief Obte capacitat actual de la pila.
					/// \return El valor.
					///
					inline unsigned getCapacity() const {
						return _c.capacity();
					}
			};

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosStack__


