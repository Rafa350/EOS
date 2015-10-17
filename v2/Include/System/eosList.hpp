#ifndef __EOS_LIST_HPP
#define	__EOS_LIST_HPP


namespace eos {
    
    template <typename elementType>
    class IList {
        public:
            virtual void add(elementType &element) = 0;
            virtual void remove(elementType &element) = 0;
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
            void addElement(void *data);
            void removeElement(void *data);
    };
    
    template <typename elementType>
    class List: public GenericList, IList<elementType> {
        public:
            List(unsigned elementSize) :
                GenericList(elementSize) {
            }
            
            void add(elementType &element) {
                
                addElement(&element);
            }
            
            void remove(elementType &element) {
                
                removeElement(&element);
            }
    };
}

#endif

