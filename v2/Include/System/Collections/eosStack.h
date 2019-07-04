#ifndef __eosStack__
#define	__eosStack__


#include "eos.h"


namespace eos {

    /// \brief Interface generic per les piles.
    //
    template <typename T>
    class IStack {
        public:
    		virtual ~IStack() {}
            virtual const T &peek() const = 0;
            virtual void push(const T &element) = 0;
            virtual void pop() = 0;
            virtual bool isEmpty() const = 0;
            virtual void clear() = 0;
    };


    /// \brief Pila
    ///
    template <typename T, const int SIZE = 10>
    class Stack: public IStack<T> {
    	private:
    		T container[SIZE];
    		int top;
        public:
            /// \brief Contructor.
            ///
            Stack():
            	top(-1) {
            }

            /// \brief Afegeix un element a la pila.
            /// \param element: L'element a afeigir.
            ///
            inline void push(const T &element) override {

            	container[++top] = element;
            }

            /// \brief Elimina el primer element de la pila.
            ///
            inline void pop() override {

            	top--;
            }

            /// \brief: Obte el primer element de la pila.
            /// \return: El primer element.
            ///
            inline const T &peek() const override {

                return container[top];
            }

            /// \brief Buida la pila.
            ///
            inline void clear() {

            	top = -1;
            }

            /// \brief: Indica si la pila es buida.
            /// \return: True si es buida.
            ///
            inline bool isEmpty() const override {

                return top == -1;
            }
    };

}


#endif // __eosStack__


