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
			uint32_t _count;

        public:
        	Input(PinDriver *drv, DigInput::Tag tag = 0xFFFFFFFF);

        	bool scan();
        	bool getValue() const;
        	uint32_t getCount(bool clear);
    };

}


#endif // __eos_diginput_inputs__
