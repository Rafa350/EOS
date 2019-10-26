#ifndef __eosList__
#define	__eosList__


#include "eos.h"
#include "eosAssert.h"

#include <string.h>


namespace eos {

	void *allocContainer(int capacity, int elementSize);
	void freeContainer(void *container);
	void *resizeContainer(void *oldContainer, int oldCapacity, int newCapacity, int count, int elementSize);
	void insertElement(void *container, int count, int position, void *element, int elementSize);
	void removeElement(void *container, int count, int position, int elementSize);

    template <typename T, const unsigned INITIAL_CAPACITY>
    class List {

        private:
    		constexpr static int initialCapacity = INITIAL_CAPACITY;
    		constexpr static int elementSize = sizeof(T);

        public:
    		typedef T value_type;
    		typedef T& reference;
    		typedef T* iterator;
    		typedef const T* const_iterator;

        private:
            int count;
            int capacity;
            T *container;
            
    	public:

            /// \brief Constructor.
    		List():
                count(0),
				capacity(0),
				container(nullptr) {
            }

    		/// \brief Destructor.
    		~List() {
    			if (container != nullptr)
    				freeContainer(container);
    		}

    		/// \brief Afegeix un element a la llista.
    		/// \param element: L'element a afeigir.
			void add(T element) {
			    if (count == capacity) {
			    	int newCapacity = (capacity == 0) ? initialCapacity : capacity * 2;
			    	container = static_cast<T*>(resizeContainer(container, capacity, newCapacity, count, elementSize));
			    	capacity = newCapacity;
			    }
			    memcpy(&container[count], &element, elementSize);
			    count += 1;
			}

			void insert(T element, int index) {

			}

			/// \brief Elimina un element de la llista.
			/// \param element: L'element a eliminar.
			void remove(T element) {
				for (int index = 0; index < count; index++) {
					if (container[index] == element) {
						if (index < (count - 1))
							memcpy(&container[index], &container[index + 1], (count - index - 1) * elementSize);
						count--;
						return;
					}
				}
			}

			/// \brief Buida la llista, pero deixa el contenidor.
			inline void empty() {
		        count = 0;
			}

			/// \brief Buida la llista i borra el contenidor.
			inline void clear() {
		        freeContainer(container);
		        count = 0;
		        capacity = 0;
		        container = nullptr;
			}

			/// \brief Comprova si la llista es buida.
			/// \return True si es buida.
			inline bool isEmpty() {
				return count == 0;
			}

			/// \brief Obte el numero d'elements que conte la llista.
		    /// \return El numero d'elements.
			inline int getCount() const {
				return count;
			}

			/// \brief Obte l'element en la posicio indicada de la llista.
			/// \return L'element.
			inline T get(int index) const {
				eosAssert(index < count);
				return container[index];
			}

			/// \brief Obte el primer element de la llista.
			/// \return L'element.
			inline T getFirst() const {
				eosAssert(count > 0);
				return container[0];
			}

			/// \brief Obte l'ultim element de la llista.
			/// \return L'element.
			inline T getLast() const {
				eosAssert(count > 0);
				return container[count - 1];
			}
            
			/// \brief Obte el iterator inicial
			/// \return El iterator.
            inline const_iterator begin() const {
                return &container[0];
            }

			/// \brief Obte el iterator final
			/// \return El iterator.
            inline const_iterator end() const {
                return &container[count];
            }


    };
}


#endif // __eosList__

