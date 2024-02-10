#pragma once
#ifndef __eosPinDriver_VNI8200XP__
#define __eosPinDriver_VNI8200XP__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"


namespace eos {
    
    class Device_VNI8200XP;

    /// \brief Clase que implementa del driver del pin amb el chip VNI8200XP
    ///
    class PinDriver_VNI8200XP final: public PinDriver {
		private:
			Device_VNI8200XP * const _dev;
			uint8_t const _pinMask;

		public:
			PinDriver_VNI8200XP(Device_VNI8200XP *dev, unsigned pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };
}


#endif // __eosPinDriver_VNI8200XP__
