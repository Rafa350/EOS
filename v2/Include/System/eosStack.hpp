#ifndef __EOS_STACK_HPP
#define	__EOS_STACK_HPP


#include "eos.hpp"


namespace eos {
    
    /// \brief Ingerface generic per les piles.
    //
    template <typename elementType>
    class IStack {
        public:
            virtual const elementType &top() const = 0;
            virtual void push(elementType &element) = 0;
            virtual void pop() = 0;
    };
    
    /// \brief Pila generica implementada com array de bytes.
    //
    class GenericStack {
        private:
            unsigned capacity;
            unsigned count;
            unsigned size;
            void *container;
        public:
            virtual ~GenericStack();
            inline unsigned getCount() const { return count; }
        protected:
            GenericStack(unsigned size, unsigned initialCapacity);
            void genericPush(void *element);
            void genericPop();
            void *genericTop() const;
        private:
            void resize(unsigned newCapacity);
            void *getPtr(unsigned index) const;
    };
    
    /// \brief Pila d'elements
    ///
    template <typename elementType>
    class Stack: private GenericStack, public IStack<elementType> {
        public:
            Stack(): 
                GenericStack(sizeof(elementType), 10) {
            }
           
            /// \brief Afegeix un element a la pila.
            /// \param element: L'element a afeigir.
            ///
            inline void push(elementType &element) {

                genericPush(&element);
            }            

            /// \brief Elimina el primer element de la pila.
            ///            
            inline void pop() {
                
                genericPop();
            }

            /// \brief: Obte el primer element de la lila.
            /// \return: El primer element.
            ///
            inline const elementType &top() const {
                
                return * ((elementType*) genericTop());
            }
    };   
    
}




#endif


