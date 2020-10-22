#include "eos.h"
#include "System/Core/eosMutex.h"


using namespace eos;


Mutex::Mutex() {

	hMutex = osalMutexCreate();
}


Mutex::~Mutex() {

	osalMutexDestroy(hMutex);
}


bool Mutex::wait(
	unsigned blockTime) {

	return osalMutexWait(hMutex, blockTime);
}


void Mutex::release() {

	osalMutexRelease(hMutex);
}
