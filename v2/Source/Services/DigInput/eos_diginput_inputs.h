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
			static constexpr uint32_t _patternMask    = 0x000000FF;
			static constexpr uint32_t _patternPosEdge = 0x0000007F;
			static constexpr uint32_t _patternNegEdge = 0x00000080;
			static constexpr uint32_t _patternActive  = 0x000000FF;
			static constexpr uint32_t _patternIdle    = 0x00000000;

        private:
			PinDriver * const _drv;
        	uint32_t _pattern;
			bool _value;
			uint32_t _count;

        public:
        	Input(PinDriver *drv, uint32_t tag = 0xFFFFFFFF);

        	bool scan();
        	bool getValue() const;
        	uint32_t getCount(bool clear);
    };

}


#endif // __eos_diginput_inputs__
