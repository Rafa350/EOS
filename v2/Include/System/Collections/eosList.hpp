#ifndef __EOS_LIST_HPP
#define	__EOS_LIST_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif


namespace eos {
    
    /// \brief Interface generic per les llistes.
    //
    template <typename elementType>
    class IList {
        public:
            virtual unsigned add(const elementType &element) = 0;
            virtual void remove(unsigned index) = 0;
            virtual unsigned getCount() const = 0;
            virtual elementType &operator[](unsigned index) = 0;
    };
    
    /// \brief Llista generica implementada com array de bytes.
    //
    class GenericList {
        private:
            unsigned size;             // Tamany del element
            unsigned count;            // Numero d'elements en la llista
            unsigned capacity;         // Capacitat de la llista en elements
            unsigned initialCapacity;  // Capacitat inicial de la llita
            void *container;           // Contenidor d'elements
    
        public:
            virtual ~GenericList();
        protected:
            GenericList(unsigned size, unsigned initialCapacity);
            void genericClear();
            unsigned genericAdd(const void *element);
            void genericRemove(unsigned index);
            unsigned genericGetCount() const { return count; }
            void *genericGet(unsigned index) const;
            unsigned genericIndexOf(const void *element);
        private:
            void *getPtr(unsigned index) const;
            void resize(unsigned newCapacity);
    };
    
    /// \brief Llista d'elements
    ///
    template <typename elementType>
    class List: private GenericList, public IList<elementType> {
        public:
            /// \brief Contructor.
            ///
            List() :
                GenericList(sizeof(elementType), 10) {
            }
            
            /// \brief Afegeix un element a la llista
            /// \param element: Referencia al element a afeigir
            ///
            inline unsigned add(const elementType &element) {
                
                return genericAdd(&element);
            }

            /// \brief Elimina un element de la llista
            /// \param index: El index del element.
            inline void remove(unsigned index) {
                
                genericRemove(index);
            }
            
            /// \brief Elimina tots els elements de la llista.
            ///
            inline void clear() {
                
                genericClear();
            }
            
            /// \brief Obte l'index del element especificat.
            /// \param element: El element.
            ///
            inline unsigned indexOf(const elementType &element) {
                
                return genericIndexOf(&element);
            }
            
            /// \brief Obte el numero d'elements en la llista
            /// \return El numero d'elements en la llista.
            ///
            inline unsigned getCount() const {
                
                return genericGetCount();
            }

            /// \brief Obte un element de la llista.
            /// \param index: Index del element.
            /// \return Referencia al element.
            ///
            inline elementType &operator[](unsigned index) {
                
                return *((elementType*) genericGet(index));
            }
    };
    
    /// \brief Iterator de llistes
    ///
    template <typename elementType>
    class ListIterator {
        private:
            unsigned index;
            unsigned endIndex;
            IList<elementType> &list;
            
        public:
            /// \brief: Contructor.
            /// \param: list: La llista a iterar.
            ///
            ListIterator(IList<elementType> &_list):
                list(_list),
                index(0),
                endIndex(_list.getCount()) {
            }            
                
            /// \brief Reseteja el iterator per començar de nou.
            ///
            inline void reset() { 
                
                index = 0; 
            }
            
            /// \brief Compriva si el iterator ha arribat al final.
            /// \return True si ha arribat al final.
            ///
            inline bool isEnd() const { 
                
                return index >= endIndex; 
            }
            
            /// \brief Obte el element actual.
            /// \return L'element actual
            ///
            inline elementType &current() const { 
                
                return list[index]; 
            }
            
            /// \brief Pasa al seguent element a iterar.
            ///
            inline void next() {
                
                index++;
            }
            
            /// \brief Pasa al seguent element a iterar.
            ///
            inline void operator++() { 
                
                next(); 
            }
    };
}

#endif

