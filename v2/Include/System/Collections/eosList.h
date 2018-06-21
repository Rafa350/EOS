#ifndef __EOS_LIST_H
#define	__EOS_LIST_H


#include "eos.h"


namespace eos {
    
    class GenericListImpl;
    
    /// \brief Llista generica implementada com array de bytes. 
    //
    class GenericList {
        private:
            GenericListImpl *impl;
    
        public:
            virtual ~GenericList();
            
        protected:
            GenericList(unsigned size, unsigned initialCapacity);
            GenericList(const GenericList &list);
            void clear();
            void addFront(const void *element);
            void addBack(const void *element);
            void remove(unsigned index);
            void remove(const void *element);
            void removeFront();
            void removeBack();
            unsigned getCount() const;
            void *get(unsigned index) const;
            unsigned indexOf(const void *element);
            bool isEmpty() const;
    };
        
    
    /// \brief Interface generic per les llistes.
    //
    template <typename T>
    class IList {
        public:
            virtual void add(const T &element) = 0;
            virtual void remove(unsigned index) = 0;
            virtual unsigned getCount() const = 0;
            virtual bool isEmpty() const = 0;
            virtual T &operator[](unsigned index) = 0;
    };
    
    
    /// \brief Llista d'elements.
    ///
    template <typename T>
    class List: private GenericList, public IList<T> {
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
            inline void remove(unsigned index) {
                
                GenericList::remove(index);
            }
            
            /// \brief Elimina un element de la llista
            /// \param index: El index del element.
            inline void remove(const T &element) {
                
                GenericList::remove(indexOf(element));
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
            IList<T> &list;
            unsigned index;
            unsigned count;
            
        public:
            /// \brief: Contructor.
            /// \param: list: La llista a iterar.
            ///
            ListIterator(IList<T> &_list):
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

#endif

