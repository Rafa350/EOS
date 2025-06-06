#ifndef __eosPriorityQueue__
#define __eosPriorityQueue__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosStdHeapAllocator.h"


/// Std includes
///
#include <vector>
#include <queue>
#include <algorithm>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif

            /// \brief Implementa una cua amb prioritat.
            ///
            template <typename Element_, typename Comparator_, int initialCapacity_ = 0, bool fixedCapacity_ = false>
            class PriorityQueue {
                private:
                    using Allocator = StdHeapAllocator<Element_>;
                    using Container = std::vector<Element_, Allocator>;

                public:
                    typedef typename Container::value_type Value;
                    typedef typename Container::reference Reference;
                    typedef typename Container::const_reference CReference;

                private:
                    class Queue: public std::priority_queue<Element_, Container, Comparator_> {
                        public:
                            Queue() {
                            }

                            Queue(Comparator_ comparator):
                                std::priority_queue<Element_, Container, Comparator_> {comparator} {
                            }

                            bool remove(CReference value) {
                                auto it = std::find(this->c.begin(), this->c.end(), value);
                                if (it != this->c.end()) {
                                    this->c.erase(it);
                                    std::make_heap(this->c.begin(), this->c.end(), this->comp);
                                    return true;
                                }
                                else
                                    return false;
                            }

                            bool contains(CReference value) {
                                auto it = std::find(this->c.begin(), this->c.end(), value);
                                return it != this->c.end();
                            }
                    };

                private:
                    Queue _q;

                public:
                    /// \brief Contructor per defecte
                    ///
                    PriorityQueue() :
                        _q() {
                    }

                    /// \brief Contructor
                    /// \param comparator: El objecte comparador.
                    ///
                    PriorityQueue(Comparator_ comparator) :
                        _q {comparator} {
                    }

                    PriorityQueue(const PriorityQueue &other) = delete;

                    /// \brief Afegeig un element a la cua.
                    /// \param element: L'element a afeigir.
                    /// \return True si tot es correcte.
                    ///
                    bool push(CReference element) {
                        if constexpr (fixedCapacity_)
                            if (_q.size() == initialCapacity_)
                                return false;
                        _q.push(element);
                        return true;
                    }

                    /// \brief Extreu el primer element de la cua.
                    /// \param: El element recuperat.
                    /// \return True si tot es correcte.
                    ///
                    bool pop() {
                        if (_q.size() > 0) {
                            _q.pop();
                            return true;
                        }
                        return false;
                    }

                    /// \brief Obte el primer element de la cua.
                    /// \param element: Referencia al resultat.
                    /// \return True si tot es correcte.
                    ///
                    bool peek(Reference element) {
                        if (_q.size() > 0) {
                            element = _q.top();
                            return true;
                        }
                        return false;
                    }

                    /// \brief Obte el primer element de la cua.
                    /// \return El element.
                    ///
                    CReference peek() const {
                        eosAssert(_q.size() > 0);
                        return _q.top();
                    }

                    /// \brief Elimina un element de la cua.
                    /// \param element: El element a eliminar.
                    /// \return True si tot es correcte.
                    ///
                    inline bool remove(CReference element) {
                        return _q.remove(element);
                    }

                    /// \brief Comprova si la cua conte un element.
                    /// \param element: El element a comprovar.
                    /// \return True si esta en la cua, false en cas contrari.
                    ///
                    inline bool contains(CReference element) {
                        return _q.contains(element);
                    }

                    /// \brief Borra el contingut de la cua.
                    ///
                    inline void clear() {
                        _q.clear();
                    }

                    /// \brief Obte el numero d'elements en la cua.
                    /// \return El valor.
                    ///
                    inline int getSize() const {
                        return _q.size();
                    }

                    /// \brief Obte la capacitat de la cua.
                    /// \return El valor.
                    ///
                    inline int getCapacity() const {
                        return _q.size();
                    }

                    /// \brief Indica si la cua es buida.
                    /// \remarks True si es buida.
                    ///
                    inline bool isEmpty() const {
                        return _q.empty();
                    }

                    /// \brief Indica si la cua es plena
                    /// \return True si es plena.
                    ///
                    inline bool isFull() const {
                        if constexpr (fixedCapacity_)
                            return _q.size() == initialCapacity_;
                        else
                            return false;
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosPriorityQueue__
