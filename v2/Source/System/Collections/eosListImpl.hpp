#ifndef ___EOS_LISTIMPL_HPP
#define ___EOS_LISTIMPL_HPP


namespace eos {
    
    class GenericList;

    /// \brief Implementacio interna de la llista generica.
    class GenericListImpl {
        private:
            unsigned size;             // Tamany del element
            unsigned count;            // Numero d'elements en la llista
            unsigned capacity;         // Capacitat de la llista en elements
            unsigned initialCapacity;  // Capacitat inicial de la llista
            void *container;           // Contenidor d'elements
    
        public:
            GenericListImpl(unsigned size, unsigned initialCapacity);
            GenericListImpl(const GenericListImpl *impl);
            ~GenericListImpl();
            void clear();
            void addFront(const void *element);
            void addBack(const void *element);
            void remove(unsigned index);
            void remove(const void *element);
            void removeFront();
            void removeBack();
            inline unsigned getCount() const { return count; }
            void *getAt(unsigned index) const;
            unsigned indexOf(const void *element);
            inline bool isEmpty() const { return count == 0; }
        private:
            void *getPtr(unsigned index) const;
            void resize(unsigned newCapacity);
    };

}


#endif