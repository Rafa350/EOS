#ifndef __eosStack__
#define	__eosStack__


#include "eos.h"
#include "eosAssert.h"


namespace eos {

    /// \brief Pila
    ///
    template <typename T, const int SIZE = 10>
    class Stack {

    	private:
    		T container[SIZE];
    		int top;

        public:

    		/// \brief Contructor.
            Stack():
            	top(-1) {
            }

            /// \brief Afegeix un element a la pila.
            /// \param element: L'element a afeigir.
            void push(const T &element) {
            	if (!isFull())
            		container[++top] = element;
            }

            /// \brief Elimina el primer element de la pila.
            void pop() {
            	if (!isEmpty())
            		top--;
            }

            /// \brief: Obte el primer element de la pila.
            /// \return: El primer element.
            inline const T &peek() const {

                return container[top];
            }

            /// \brief Buida la pila.
            inline void clear() {
            	top = -1;
            }

            /// \brief: Indica si la pila es buida.
            /// \return: True si es buida.
            inline bool isEmpty() const {
                return top == -1;
            }

            /// \brief: Indica si la pila es plena.
            /// \return: True si es plena.
            inline bool isFull() const {
            	return top == SIZE - 1;
            }
    };

}


#endif // __eosStack__


