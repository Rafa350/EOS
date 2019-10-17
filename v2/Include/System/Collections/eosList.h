#ifndef __eosList__
#define	__eosList__


#include "eos.h"


namespace eos {
    
    /*class GenericList {
        private:
            unsigned size;
            unsigned count;
            unsigned capacity;
            char *container;
            
        private:
            void resize(unsigned newCapacity);
            void copy(void *dst, void *src, unsigned count);
            
        protected:
            GenericList(unsigned size, unsigned initialCapacity);
            GenericList(const GenericList& other);
            ~GenericList();
            
            void addFront(const void *element);
            void addBack(const void *element);
            void removeAt(unsigned index);
            void clear();

            unsigned getCount() const { return count; }
            
            unsigned indexOf(const void *element) const;
            void *get(unsigned index) const;
            void *getFront() const;
            void *getBack() const;
            void *getPtr(unsigned index) const;
    };*/

    template <typename T>
    class List {
        private:
            unsigned size;
            unsigned count;
            T buffer[5];
            
    	public:
    		List():
                count(0),
                size(5) {
            }

			inline void add(T element) {
                if (count < size)
                    buffer[count++] = element;
                else
                    while (true) {
                        
                    }
			}

			inline void remove(T element) {
			}

			inline void clear() {
                count = 0;
			}

			inline bool isEmpty() {
				return count == 0;
			}

			inline int getCount() const {
				return count;
			}

			inline T getFirst() const {
				return buffer[0];
			}

			inline T getLast() const {
				return buffer[count - 1];
			}
            
            inline const T* begin() const {
                return &buffer[0];
            }

            inline const T* end() const {
                return &buffer[count];
            }
    };
}


#endif // __eosList__

