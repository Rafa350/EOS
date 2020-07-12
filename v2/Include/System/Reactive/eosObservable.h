#ifndef __eosObservable__
#define __eosObservable__


#include "eos.h"
#include "System/Collections/eosDynamicArray.h"


namespace eos {

	template <typename Value>
	class Observer {
		public:
			void onUpdate(Value value) {
                
            }
	};

    template <typename Observer>
	class Observable {
		public:
        	typedef DynamicArray<Observer*> ObserverList;
		protected:
        	ObserverList observers;
        public:
			inline void addObserver(Observer* observer) {
				observers.pushBack(observer);
			}
			void removeObserver(Observer* observer) {
				int index = observers.indexOf(observer);
				observers.removeAt(index);
			}
			inline void removeObservers() {
				observers.empty();
			}
	};

    template <typename Value>
    class ObservableValue: public Observable<Observer<Value> > {
    	private:
    		Value value;
        private:
            void updated(Value value) {
                for(auto it = this->observers.begin(); it != this->observers.end(); it++) {
                    auto observer = *it;
                    observer->onUpdate(value);
                }
            }
    	public:
            ObservableValue() {
            }
            ObservableValue(Value initialValue) {
                value = initialValue;
            }
    		void setValue(Value newValue) {
    			if (value != newValue) {
    				value = newValue;
                    updated(value);
    			}
    		}
    		inline Value getValue() const {
    			return _value;
    		}
    };
}

#endif // __eosObservable__
