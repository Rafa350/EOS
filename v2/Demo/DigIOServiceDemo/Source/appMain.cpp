#include "eos.h"

#include "appApplication.h"


#include "System/Collections/eosStaticArray.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Collections/eosPriorityQueueHeap.h"


using namespace eos;
using namespace app;


bool compare(const long& a, const long& b) {

    return a < b;
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {
    
    PriorityQueueHeap<long> pq(compare);
    pq.push(100);
    pq.push(700);
    pq.push(300);
    pq.push(400);
    pq.push(900);
    pq.pop();
    
	Application* app = new MyApplication();
	app->run();
	delete app;
}
