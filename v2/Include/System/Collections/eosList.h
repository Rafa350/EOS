#pragma once
#ifndef __eosList__
#define __eosList__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


// Std includes
//
#include <list>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif            
            template <typename Element_>
            class List {
            	private:
            		using Container = std::list<Element_>;

                public:
                    using Value = typename Container::value_type;
                    using Pointer = typename Container::pointer;
                    using Reference = typename Container::reference;
                    using CReference = typename Container::const_reference;
                    using Iterator = typename Container::iterator;
                    using CIterator = typename Container::const_iterator;

                private:
            		Container _c;

            	public:
            		inline void pushFront(CReference element) {
            			_c.push_front(element);
            		}

            		inline void pushBack(CReference element) {
            			_c.push_back(element);
            		}

            		inline void popFront() {
            			eosAssert(_c.size() > 0);
            			_c.pop_front();
            		}

            		inline void popBack() {
            			eosAssert(_c.size() > 0);
            			_c.pop_back();
            		}

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference peekFront() {
            			eosAssert(_c.size() > 0);
                        return _c.front();
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference peekFront() const {
            			eosAssert(_c.size() > 0);
                        return _c.front();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference peekBack() {
            			eosAssert(_c.size() > 0);
                        return _c.back();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference peekBack() const {
            			eosAssert(_c.size() > 0);
                        return _c.back();
                    }

            		inline void remove(CReference element) {
            			_c.remove(element);
            		}

            		inline void clear() {
            			_c.clear();
            		}

                    /// \brief Obte el iterator inicial
                    ///
                    inline Iterator begin() {
                        return _c.begin();
                    }

                    /// \brief Obte el iteratror final.
                    ///
                    inline Iterator end() {
                        return _c.end();
                    }

                    inline unsigned getSize() const {
                    	return _c.size();
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosList__
