#ifndef __eosLIFOContainer__
#define	__eosLIFOContainer__


#include "eos.h"
#include "eosAssert.h"


namespace eos {

    /// \brief Implementa una pila (LIFO)
    ///
    template <typename Element, typename Container>
    class LIFOContainer {
        public:
            typedef Element Value;
            typedef Element& Reference;
            typedef const Element& CReference;
            typedef Element* Pointer;
            typedef const Element* CPointer;

    	private:
            Container container;

        public:

    		/// \brief Contructor per defecte
            ///
            LIFOContainer() {
            }

            /// \brief Afegeix un element a la pila.
            /// \param element: L'element a afeigir.
            //
            inline void push(CReference element) {
                container.pushBack(element);
            }

            /// \brief Elimina un element de la pila.
            ///
            inline void pop() {
                container.popBack();
            }

            /// \brief: Obte el primer element de la pila.
            /// \return: El primer element.
            ///
            inline Reference peek() {
                return container.getBack();
            }

            /// \brief: Obte el primer element de la pila.
            /// \return: El primer element.
            ///
            inline CReference peek() const {
                return container.getBack();
            }

            /// \brief Buida la pila.
            ///
            inline void clear() {
            	container.clear();
            }

            /// \brief: Indica si la pila es buida.
            /// \return: True si es buida.
            ///
            inline bool isEmpty() const {
                return container.isEmpty();
            }
    };

}


#endif // __eosLIFOContainer__


