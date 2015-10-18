#ifndef __EOS_LIST_HPP
#define	__EOS_LIST_HPP


namespace eos {
    
    template <typename elementType>
    class IList {
        public:
            virtual void add(elementType &element) = 0;
            virtual void remove(unsigned index) = 0;
            virtual unsigned getCount() const = 0;
            virtual elementType &operator[](unsigned index) = 0;
    };
    
    class GenericList {
        private:
            unsigned elementSize;
            unsigned count;
            unsigned size;
            void *data;
        protected:
            GenericList(unsigned elementSize);
            ~GenericList();
            void addElement(void *element);
            void removeElement(unsigned index);
            unsigned getCount() const { return count; }
            void *getElement(unsigned index) const;
        private:
            void resize(unsigned newSize);
    };
    
    template <typename elementType>
    class List: public GenericList, public IList<elementType> {
        public:
            List() :
                GenericList(sizeof(elementType)) {
            }
            
            void add(elementType &element) {
                
                addElement(&element);
            }
            
            void remove(unsigned index) {
                
                removeElement(index);
            }
            
            unsigned getCount() const {
                
                return GenericList::getCount();
            }

            elementType &operator[](unsigned index) {
                
                return *((elementType*) getElement(index));
            }
    };
    
    template <typename elementType>
    class ListIterator {
        private:
            unsigned index;
            unsigned endIndex;
            IList<elementType> &list;
        public:
            ListIterator(IList<elementType> &_list):
                list(_list) {
                index = 0;
                endIndex = _list.getCount();
            }
            
            void reset() { index = 0; }
            bool isEnd() const { return index >= endIndex; }
            elementType &current() const { return list[index]; }
            void operator++() { index++; }
    };
}

#endif

