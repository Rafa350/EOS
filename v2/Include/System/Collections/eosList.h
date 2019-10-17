#ifndef __eosList__
#define	__eosList__


#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"

#include <string.h>


namespace eos {
    
    template <typename T>
    class List {

        private:
    		constexpr static unsigned initialCapacity = 5;

        private:
            unsigned count;
            unsigned capacity;
            T *container;
            
        private:

            /// \brief Modifica el tamany del contenidor de dades.
            /// \param newCapacity: Nova capacitat del contenidor.
            void resize(unsigned newCapacity) {

                // Comprova si cal aumentar la capacitat.
                //
                if (capacity < newCapacity) {

                    // Salva un punter al contenidor actual
                    //
                    void *oldContainer = container;

                    // Reserva memoria per un nou contenidor
                    //
                    container = static_cast<T*>(osalHeapAlloc(nullptr, newCapacity * sizeof(T)));

                    // Comprova si hi havia un contenidor previ
                    //
                    if (oldContainer != nullptr) {

                        // Copia les dades de l'antic contenidor al nou
                        //
                        memcpy(container, oldContainer, count * sizeof(T));

                        // Allivera l'antic contenidor
                        //
                        osalHeapFree(nullptr, oldContainer);
                    }

                    capacity = newCapacity;
                }
            }


    	public:

            /// \brief Constructor.
    		List():
                count(0),
				capacity(0),
				container(nullptr) {
    			resize(initialCapacity);
            }

    		/// \brief Destructor.
    		~List() {
    			if (container != nullptr)
    				osalHeapFree(nullptr, container);
    		}

    		/// \brief Afegeix un element a la llista.
    		/// \param element: L'element a afeigir.
			void add(T element) {
			    if (count == capacity)
			        resize(capacity * 2);
			    memcpy(&container[count], &element, sizeof(T));
			    count += 1;
			}

			/// \brief Elimina un element de la llista.
			/// \param element: L'element a eliminar.
			void remove(T element) {
				for (unsigned index = 0; index < count; index++) {
					if (container[index] == element) {
						if (index < (count - 1))
							memcpy(&container[index], &container[index + 1], (count - index - 1) * sizeof(T));
						count--;
					}
				}
			}

			/// \brief Buida la llista.
			void clear() {
		        count = 0;
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
			inline T get(unsigned index) const {
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
            inline const T* begin() const {
                return &container[0];
            }

			/// \brief Obte el iterator final
			/// \return El iterator.
            inline const T* end() const {
                return &container[count];
            }
    };
}


#endif // __eosList__

