#include "eos.h"
#include "HAL/halGPIO.h"
#include "appApplication.h"

#include "System/Collections/eosPriorityQueue.h"

using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

	PriorityQueue<int, int> pq;
	pq.push(1, 100);
	pq.remove(100);

	LEDS_Led1Initialize();

    MyApplication *application = new MyApplication();
    application->run();
    delete application;
}
