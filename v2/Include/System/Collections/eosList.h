#ifndef __eosList__
#define	__eosList__


#include "eos.h"

#include <algorithm>
#include <vector>


namespace eos {

    template <typename T>
    class List {
    	private:
    		std::vector<T*> items;

    	public:
    		List() {
    			items.reserve(5);
            }

			inline void add(T *item) {
				items.push_back(item);
			}

			inline void remove(T *item) {
				auto it = std::find(items.begin(), items.end(), item);
				items.erase(it);
			}

			inline void clear() {
				items.clear();
			}

			inline bool isEmpty() {
				return items.empty();
			}

			inline int getCount() const {
				return items.count();
			}

			inline T* getFirst() const {
				return items.front();
			}

			inline T* getLast() const {
				return items.back();
			}

			inline std::vector<T*> enumerate() const {
				return items;
			}
    };
}


#endif // __eosList__

