#ifndef __EOS_STACK_HPP
#define	__EOS_STACK_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif


namespace eos {
    
    /// \brief Interface generic per les piles.
    //
    template <typename elementType>
    class IStack {
        public:
            virtual const elementType &top() const = 0;
            virtual void push(elementType &element) = 0;
            virtual void pop() = 0;
            virtual bool isEmpty() const = 0;
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
        protected:
            GenericStack(unsigned size, unsigned initialCapacity);
            void genericPush(void *element);
            void genericPop();
            void *genericTop() const;
            
            /// \brief Obte el nombre d'elements en la pila
            /// \return El nombre d'elements.
            ///
            inline unsigned genericGetCount() const { return count; }
        private:
            void resize(unsigned newCapacity);
            void *getPtr(unsigned index) const;
    };
    
    /// \brief Pila d'elements
    ///
    template <typename elementType>
    class Stack: private GenericStack, public IStack<elementType> {
        public:
            /// \brief Contructor.
            ///
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
            
            /// \brief: Indica si la pila es buida.
            /// \return: True si es buida.
            ///
            inline bool isEmpty() const {
                
                return genericGetCount() == 0;
            }
    };   
    
}




#endif


