#ifndef __EOS_STEPMOTOR_HPP
#define	__EOS_STEPMOTOR_HPP


#include "eos.hpp"


namespace eos {
    
    class StepMotorController {
        private:
            uint8_t stepPin;
            uint8_t dirPin;
            uint8_t enablePin;
            
        public:
            StepMotorController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
    };
}


#endif	

