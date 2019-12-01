#ifndef __eosArrayList__
#define	__eosArrayList__


#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"

#include <string.h>


namespace eos {

	void *allocContainer(int capacity, int elementSize);
	void freeContainer(void *container);
	void *resizeContainer(void *oldContainer, int oldCapacity, int newCapacity, int count, int elementSize);

    /// \brief Implementa una llista a partir d'un array
    /// \remarks La llista enmagatzema copies del element.
    template <typename Element, const int initialCapacity = 0>
    class ArrayList {

        public:
            /// \brief Iterator bidireccional per la llista.
            class Iterator {
                private:
                    const ArrayList<Element>& list;
                    int index;
                    
                public:
                    /// \brief Constructor.
                    /// \param list: La llista a iterar.
                    /// \param reverse: True si es recorre la llista del final al principi.
                    /// \remarks No es permet modificar la llista mente s'utilitzi el iterator.
                    ///
                    Iterator(const ArrayList<Element>& list, bool reverse = false):
                        list(list),
                        index(reverse ? list.getCount() - 1 : 0) {
                    }
                        
                    /// \brief Mou el iterator al primer element.
                    /// \return True si tot es correcte.
                    ///
                    inline bool first() {
                        if (list.isEmpty())
                            return false;
                        else {
                            index = 0;
                            return true;
                        }
                    }
                    
                    /// \brief Mou el iterator a l'ultim element.
                    /// \return True si tot es correcte.
                    ///
                    inline bool last() {
                        if (list.isEmpty())
                            return false;
                        else {
                            index = list.getCount() - 1;
                            return true;
                        }
                    }
                        
                    /// \brief Mou el iterator al anterior element.
                    /// \return True si tot es correcte.
                    ///
                    inline bool prev() {
                        if (!list.isEmpty() && (index > 0)) {
                            index -=1;
                            return true;
                        }
                        else
                            return false;
                    }
                        
                    /// \brief Mou el iterator al seguent element.
                    /// \return True si tot es correcte.
                    ///
                    inline bool next() {
                        if (!list.isEmpty() && (index < list.getCount())) {
                            index += 1;
                            return true;
                        }
                        else
                            return false;
                    }
                    
                    /// \brief Indica si hi ha un element previ.
                    /// \return True si existeix l'element previ.
                    ///
                    inline bool hasPrev() const {
                        return !list.isEmpty() && (index >= 0);
                    }
                    
                    /// \brief Indica si hi ha un element posterior.
                    /// \return True si existeix l'element posterior.
                    ///
                    inline bool hasNext() const {
                        return !list.isEmpty() && (index < list.getCount());
                    }
                    
                    /// \brief Obter l'element actual.
                    /// \return L'element actual.
                    ///
                    inline const Element& getCurrent() const {
                        return list.get(index);
                    }
            };
            
        private:
            int count;
            int capacity;
            Element* container;
            
        private:
            void updateCapacity() {
                if (count == capacity) {
                    int newCapacity = (capacity == 0) ? 
                        Math::max(5, initialCapacity) : 
                        ((capacity < 50) ? 
                            capacity * 2 : 
                            capacity + 25);
                    container = static_cast<Element*>(resizeContainer(container, capacity, newCapacity, count, sizeof(Element)));
                    capacity = newCapacity;
                }                    
            }

    	public:

            /// \brief Constructor.
            ///
    		ArrayList():
                count(0),
				capacity(0),
				container(nullptr) {
            }

    		/// \brief Destructor.
            ///
    		~ArrayList() {
    			if (container != nullptr)
    				freeContainer(container);
    		}

    		/// \brief Afegeix un element al final de la llista.
    		/// \param element: L'element a afeigir.
            /// \return L'index de l'element afeigit.
            ///
			int add(const Element& element) {
                updateCapacity();
                int index = count;
                container[index] = element;
			    count += 1;                
                return index;
			}

			/// \brief Elimina un element de la llista.
			/// \param element: L'element a eliminar.
            /// \return L'index del element eliminat.
            ///
			int remove(const Element& element) {
                int index = indexOf(element);
                if (index != -1) {
                    memmove(&container[index], &container[index + 1], (count - index - 1) * sizeof(Element));
                    count -= 1;
                }
                return index;
			}
            
            /// \brief Inserta un element en la posicio indicada.
            /// \param element: L'element a insertar.
            /// \param index: La posicio on insertar l'element.
            /// \return True si tot es correcte. False en cas contrari.
            ///
			bool insertAt(int index, const Element& element) {
                if (index < 0) 
                    return false;
                else if (index <= count) {
                    updateCapacity();
                    if (index < count)
                        memmove(&container[index + 1], &container[index], (count - index) * sizeof(Element));
                    container[index] = element;
                    count += 1;
                    return true;
                }
                else
                    return false;
			}

            /// \brief Elimina un element de la posicio indicada.
            /// \param index: Posicio del element a eliminar.
            /// \return True si tot es correcte. False en cas contrari.
            ///
            bool removeAt(int index) {
                if (index < 0)
                    return false;
				else if (index <= (count - 1)) {
                    if (index < (count - 1))
                        memmove(&container[index], &container[index + 1], (count - index - 1) * sizeof(Element));
                    count -= 1;
                    return true;
				}               
                else
                    return true;
            }
            
            /// \brief Copia el contingut en un array.
            /// \param dst: El array de destinacio.            
            /// \param offset: Index del primer element a copiar.
            /// \param length: Numero d'elements a copiar.
            ///
            void copyTo(Element* dst, int offset, int length) const {
                eosAssert(offset + length <= count);
                memcpy(dst, &container[offset], length * sizeof(Element));
            }
            
            /// \brief Obte l'index d'un element.
            /// \return L'index o -1 si l'element no existeix.
            ///
            int indexOf(const Element &element) const {
				for (int index = 0; index < count; index++) 
					if (container[index] == element) 
                        return index;
                return -1;                
            }

			/// \brief Buida la llista, pero deixa el contenidor.
            ///
			void empty() {
		        count = 0;
			}

			/// \brief Buida la llista i borra el contenidor.
            ///
			void clear() {
		        freeContainer(container);
		        count = 0;
		        capacity = 0;
		        container = nullptr;
			}

			/// \brief Comprova si la llista es buida.
			/// \return True si es buida.
            ///
			inline bool isEmpty() const {
				return count == 0;
			}

			/// \brief Obte el numero d'elements que conte la llista.
		    /// \return El numero d'elements.
            ///
			inline int getCount() const {
				return count;
			}
            
            /// \brief Obte la capacitat actual.
            /// \return La capacitat.
            ///
            inline int getCapacity() const {
                return capacity;
            }

			/// \brief Obte l'element en la posicio indicada de la llista.
			/// \return L'element.
            ///
			inline const Element& get(int index) const {
				eosAssert(index < count);
				return container[index];
			}

			/// \brief Obte el primer element de la llista.
			/// \return L'element.
            ///
			inline const Element& getFirst() const {
				eosAssert(count > 0);
				return container[0];
			}

			/// \brief Obte l'ultim element de la llista.
			/// \return L'element.
            ///
			inline const Element& getLast() const {
				eosAssert(count > 0);
				return container[count - 1];
			}

			/// \brief Obte el iterator inicial.
			/// \return El iterator.
            ///
            inline Element* begin() const {
                return &container[0];
            }

			/// \brief Obte el iterator final.
			/// \return El iterator.
            ///
            inline Element* end() const {
                return &container[count];
            }
            
            /// \brief Implementa l'operador []
            /// \return El lemement en la posicio indicada.
            ///
            inline const Element& operator[](int index) const {
                return get(index);
            }
    };
}


#endif // __eosArrayList__

