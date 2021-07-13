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

	PriorityQueue<int, std::greater<int> > q;


	int r = 400;
	q.push(r);
	q.push(500);
	q.push(100);
	q.push(700);
	q.remove(500);

	q.peek(r);
	q.pop();
	r = q.peek();

	LEDS_Led1Initialize();

    MyApplication *application = new MyApplication();
    application->run();
    delete application;
}
