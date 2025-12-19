#pragma once
#ifndef __eos_diginput_inputs__
#define __eos_diginput_inputs__


// EOS includes
//
#include "eos.h"
#include "Services\DigInput\eosDigInputService.h"


namespace eos {


	class PinDriver;

    /// \brief Clase que gestiona una entrada digital
    //
	class Input final: public DigInput {
        private:
			PinDriver * const _drv;
        	uint32_t _pattern;
			bool _value;
			unsigned _count;

        public:
        	Input(PinDriver *pinDrv);

        	bool scan();
        	bool getValue() const;
        	unsigned getCount(bool clear);
    };

}


#endif // __eos_diginput_inputs__
