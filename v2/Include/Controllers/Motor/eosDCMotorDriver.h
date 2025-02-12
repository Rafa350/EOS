#pragma once
#ifndef __eosDCMotorDriver__
#define	__eosDCMotorDriver__


#include "eos.h"


namespace eos {

    class DCMotorDriver {
    	protected:
    		virtual void implForward(unsigned speed) = 0;
    		virtual void implBackward(unsigned speed) = 0;
    		virtual void implStop() = 0;
    	public:
    		void forward(unsigned speed);
    		void backward(unsigned speed);
    		void stop();
    };
}


#endif

