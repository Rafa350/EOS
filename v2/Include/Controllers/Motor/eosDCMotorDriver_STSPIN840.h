#pragma once
#ifndef __eosDCMotorDriver_STSPIN840__
#define __eosDCMotorDriver_STSPIN840__


#include "eos.h"
#include "Controllers/Motor/eosDCMotorDriver.h"
#include "Controllers/Motor/Drivers/STSPIN840/eosDevice_STSPIN840.h"


namespace eos {

	class DCMotorDriver_STSPIN840: public DCMotorDriver {
		private:
			STSPIN840_Device * const _dev;
    	protected:
    		void implForward(unsigned speed) override;
    		void implBackward(unsigned speed) override;
    		void implStop() override;
		public:
			DCMotorDriver_STSPIN840(STSPIN840_Device *dev);
	};
}

#endif
