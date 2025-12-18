#pragma once
#ifndef __eos_canopen_service_slave__
#define __eos_canopen_service_slave__


#include "eos.h"
#include "Services/CanOpen/eos_canopen_service.h"


namespace eos {

	class CanOpenSlaveService: public CanOpenService {
		public:
			CanOpenSlaveService(InitParams const &params);
	};
}



#endif // __eos_canopen_service_slave__
