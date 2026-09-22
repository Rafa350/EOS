module;


#include "eos.h"
#include "eosAssert.h"


export module Eos.System.Collections.Stack;


export namespace eos {

	/// \brief Implementa un contenidor FIFO.
	/// \remarks El contenidor enmagatzema copies del element en un buffer extern.
	///
	template <typename T_>
	class StackBase {
		public:
			using ValueType = T_;
			using ValuePtr = ValueType*;
			using CPointer = const ValueType*;
			using Reference = ValueType&;
			using CReference = const ValueType&;

		private:
			ValuePtr _begin;
			ValuePtr _end;
			ValuePtr _sp;

		private:
			StackBase(const StackBase &) = delete;
			StackBase & operator = (const StackBase &) = delete;

		public:

			/// \brief Constructor per defecte
			///
			StackBase(ValuePtr container, size_t capacity):
				_begin {container},
				_end {container + capacity},
				_sp {container} {

				eosAssert(container != nullptr);
				eosAssert(capacity > 1);
			}

			/// \brief Afegeix un element a la pila.
			/// \param element: L'element a afeigir.
			//
			void push(CReference element) {
				eosAssert(!full());
				*_sp++ = element;
			}

			/// \brief Elimina un element de la pila.
			///
			void pop() {
				eosAssert(!empty());
				_sp--;
			}

			/// \brief: Obte el primer element de la pila.
			/// \return: El primer element.
			///
			Reference peek() {
				eosAssert(!empty());
				return *(_sp - 1); // Sempre apunta al seguent
			}

			/// \brief: Obte el primer element de la pila.
			/// \return: El primer element.
			///
			CReference peek() const {
				eosAssert(!empty());
				return *(_sp - 1);
			}

			/// \brief Buida la pila.
			///
			void clear() {
				_sp = _begin;
			}

			/// \brief: Indica si la pila es buida.
			/// \return: True si es buida.
			///
			bool empty() const {
				return _sp == _begin;
			}

			/// \brief: Indica si la pila es plena
			/// \return: True si es plena.
			///
			bool full() const {
				return _sp == _end;
			}

			/// \brief Obte el tamany de la pila.
			/// \return El valor.
			///
			size_t size() const {
				return _sp - _begin;
			}

			/// \brief Obte capacitat actual de la pila.
			/// \return El valor.
			///
			size_t capacity() const {
				return _end - _begin;
			}
	};


	template <typename T_, size_t capacity_>
	class FixedCapacityStack: public StackBase<T_> {
		private:
			T_ _container[capacity_];

		public:
			FixedCapacityStack() :
				StackBase<T_>(_container, capacity_) {
				}
	};

}
