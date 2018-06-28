#ifndef __eosList__
#define	__eosList__


#include "eos.h"


namespace eos {
    
    /// \brief Llista generica implementada com array de bytes. 
    //
    class GenericList {
        private:
            unsigned size;             // Tamany del element
            unsigned count;            // Numero d'elements en la llista
            unsigned capacity;         // Capacitat de la llista en elements
            unsigned initialCapacity;  // Capacitat inicial de la llista
            void *container;           // Contenidor d'elements

        private:
            void *getPtr(unsigned index) const;
            void resize(unsigned newCapacity);
    
        public:
            virtual ~GenericList();
            
        protected:
            GenericList(unsigned size, unsigned initialCapacity);
            GenericList(const GenericList &list);
            void clear();
            void addFront(const void *element);
            void addBack(const void *element);
            void remove(const void *element);
            void removeAt(unsigned index);
            void removeFront();
            void removeBack();
            inline unsigned getCount() const { return count; }
            void *get(unsigned index) const;
            unsigned indexOf(const void *element);
            bool isEmpty() const { return count > 0; }
    };
        
    
    /// \brief Llista d'elements.
    ///
    template <typename T>
    class List: private GenericList {
        public:
            /// \brief Contructor.
            ///
            List() :
                GenericList(sizeof(T), 10) {
            }
                
            /// \brief Contructor copia.
            ///
            List(const GenericList &list) :
                GenericList(list) {                
            }
            
            /// \brief Afegeix un element a la llista
            /// \param element: Referencia al element a afeigir
            ///
            inline void add(const T &element) {
                
                GenericList::addBack(&element);
            }

            /// \brief Elimina un element de la llista
            /// \param index: El index del element.
            inline void removeAt(unsigned index) {
                
                GenericList::removeAt(index);
            }
            
            /// \brief Elimina un element de la llista
            /// \param index: El index del element.
            inline void remove(const T &element) {
                
                GenericList::removeAt(indexOf(element));
            }

            /// \brief Elimina tots els elements de la llista.
            ///
            inline void clear() {
                
                GenericList::clear();
            }
            
            /// \brief Obte l'index del element especificat.
            /// \param element: El element.
            ///
            inline unsigned indexOf(const T &element) {
                
                return GenericList::indexOf(&element);
            }
            
            /// \brief Obte el numero d'elements en la llista
            /// \return El numero d'elements en la llista.
            ///
            inline unsigned getCount() const {
                
                return GenericList::getCount();
            }
            
            /// \brief Comprova si es buida.
            /// \return True si la llista es buida.
            ///
            inline bool isEmpty() const {
            
                return GenericList::getCount() == 0;
            }
            
            /// \brief Obte el primer element de la llista
            /// \return El primer element
            ///
            inline T &getFront() const {
                
                return *((T*) GenericList::get(0));
            }

            /// \brief Obte un element de la llista.
            /// \param index: Index del element.
            /// \return Referencia al element.
            ///
            inline T &operator[](unsigned index) {
                
                return *((T*) GenericList::get(index));
            }
    };
    
    /// \brief Iterator de llistes
    ///
    template <typename T>
    class ListIterator {
        private:
            List<T> &list;
            unsigned index;
            unsigned count;
            
        public:
            /// \brief: Contructor.
            /// \param: list: La llista a iterar.
            ///
            ListIterator(List<T> &_list):
                list(_list),
                index(0),
                count(_list.getCount()) {
            }                                        
                
            /// \brief Pasa al primer element.
            ///
            inline void first() { 
                
                index = 0; 
            }
            
            /// \brief Pasa al ultim element.
            ///
            inline void last() { 
                
                index = count - 1; 
            }
            
            /// \brief Comprova si hi ha un element posterior a l'actual.
            /// \return Resultat de l'operacio.
            ///
            inline bool hasNext() const { 
                
                return index < count; 
            }
            
            /// \brief Comprova si hi ha un element previ a l'actual
            /// \return Resultat de l'operacio.
            ///
            inline bool hasPrev() const { 
                
                return index > 0; 
            }
            
            /// \brief Obte el element actual.
            /// \return L'element actual
            ///
            inline T &current() const { 
                
                return list[index]; 
            }
            
            /// \brief Pasa al seguent element.
            ///
            inline void next() {
                
                index++;
            }
            
            /// \brief Pasa a l'element anterior.
            ///
            inline void prev() {
                
                index--;
            }
            
        private:
            ListIterator(const ListIterator &iterator);
    };
}

#endif // __eosList__

