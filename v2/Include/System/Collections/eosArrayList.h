#ifndef __eosArrayList__
#define	__eosArrayList__


#include "eos.h"
#include "eosAssert.h"

#include <string.h>


namespace eos {

	void *allocContainer(int capacity, int elementSize);
	void freeContainer(void *container);
	void *resizeContainer(void *oldContainer, int oldCapacity, int newCapacity, int count, int elementSize);

    template <typename T, const unsigned INITIAL_CAPACITY = 10>
    class ArrayList {

        public:
            class Iterator {
                private:
                    const ArrayList<T>& list;
                    int index;
                    
                public:
                    Iterator(const ArrayList<T>& list, bool reverse = false):
                        list(list),
                        index(reverse ? list.getCount() - 1 : 0) {                        
                    }
                        
                    inline void first() {
                        index = 0;
                    }
                    
                    inline void last() {
                        index = list.getCount() - 1;
                    }
                        
                    inline void prev() {
                        index -=1;
                    }
                        
                    inline void next() {
                        index += 1;
                    }
                    
                    inline bool hasPrev() const {
                        return index >= 0;
                    }
                    
                    inline bool hasNext() const {
                        return index < list.getCount();
                    }
                    
                    inline const T& getCurrent() const {
                        return list.get(index);
                    }
            };
            
        private:
    		constexpr static int initialCapacity = INITIAL_CAPACITY;

            int count;
            int capacity;
            T* container;

    	public:

            /// \brief Constructor.
    		ArrayList():
                count(0),
				capacity(0),
				container(nullptr) {
            }

    		/// \brief Destructor.
    		~ArrayList() {
    			if (container != nullptr)
    				freeContainer(container);
    		}

    		/// \brief Afegeix un element a la llista.
    		/// \param element: L'element a afeigir.
			void add(const T& element) {
			    if (count == capacity) {
			    	int newCapacity = (capacity == 0) ? initialCapacity : capacity * 2;
			    	container = static_cast<T*>(resizeContainer(container, capacity, newCapacity, count, sizeof(T)));
			    	capacity = newCapacity;
			    }
                container[count] = element;
			    count += 1;
			}

            /// \brief Inserta un element en la posicio indicada.
            /// \param element: L'element a insertar.
            /// \param index: La posicio on insertar l'element.
            ///
			void insert(const T& element, int index) {
                eosAssert(index < count);
                memmove(&container[index + 1], &container[index], (count - index) * sizeof(T));
                container[index] = element;
			}

			/// \brief Elimina un element de la llista.
			/// \param element: L'element a eliminar.
			void remove(const T& element) {
				for (int index = 0; index < count; index++) {
					if (container[index] == element) {
						if (index < (count - 1))
							memmove(&container[index], &container[index + 1], (count - index - 1) * sizeof(T));
						count--;
						return;
					}
				}
			}
            
            /// \brief Copia el contingut en un array.
            /// \param dst: El array de destinacio.            
            /// \param offset: Index del primer element a copiar.
            /// \param length: Numero d'elements a copiar.
            void copyTo(T* dst, int offset, int length) const {
                eosAssert(offset + length <= count);
                memcpy(dst, &container[offset], length * sizeof(T));
            }

			/// \brief Buida la llista, pero deixa el contenidor.
			void empty() {
		        count = 0;
			}

			/// \brief Buida la llista i borra el contenidor.
			void clear() {
		        freeContainer(container);
		        count = 0;
		        capacity = 0;
		        container = nullptr;
			}

			/// \brief Comprova si la llista es buida.
			/// \return True si es buida.
			inline bool isEmpty() const {
				return count == 0;
			}

			/// \brief Obte el numero d'elements que conte la llista.
		    /// \return El numero d'elements.
			inline int getCount() const {
				return count;
			}

			/// \brief Obte l'element en la posicio indicada de la llista.
			/// \return L'element.
			inline const T& get(int index) const {
				eosAssert(index < count);
				return container[index];
			}

			/// \brief Obte el primer element de la llista.
			/// \return L'element.
			inline const T& getFirst() const {
				eosAssert(count > 0);
				return container[0];
			}

			/// \brief Obte l'ultim element de la llista.
			/// \return L'element.
			inline const T& getLast() const {
				eosAssert(count > 0);
				return container[count - 1];
			}

			/// \brief Obte el iterator inicial.
			/// \return El iterator.
            inline T* begin() const {
                return &container[0];
            }

			/// \brief Obte el iterator final.
			/// \return El iterator.
            inline T* end() const {
                return &container[count];
            }
            
            inline const T& operator[](int index) const {
                return get(index);
            }
    };
}


#endif // __eosArrayList__

