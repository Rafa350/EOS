#include "eos.h"
#include "System/Reactive/eosObservable.h"


using namespace eos;


void appMain() {
    
    Observer<int> intObserver;
    
    ObservableValue<int> intValue(0);
    intValue.addObserver(&intObserver);
    
    intValue.setValue(12);
    
}
