#include "eos.h"

#include "appApplication.h"


#include "System/Collections/eosStaticArray.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Collections/eosPriorityQueueHeap.h"
#include "System/Collections/eosStack.h"


using namespace eos;
using namespace app;


bool compare(const long& a, const long& b) {

    return a < b;
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {
    
    Stack<int, DynamicArray<int, 20> > stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.pop();
    stack.peek();
    
    PriorityQueueHeap<long, DynamicArray<long, 10> > pq(compare);
    pq.push(100);
    pq.push(700);
    pq.push(300);
    pq.push(400);
    pq.push(900);
    pq.pop();
    long l = pq.top();
    
	Application* app = new MyApplication();
	app->run();
	delete app;
}
