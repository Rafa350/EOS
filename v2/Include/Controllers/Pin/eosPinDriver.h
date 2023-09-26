#pragma once
#ifndef __eosPinDriver__
#define	__eosPinDriver__


// EOS includes
//
#include "eos.h"


namespace eos {

    
    /// \brief Clase abstracta que implementa del driver del pin
    ///
    class PinDriver {
        public:
            virtual ~PinDriver() = default;
            virtual void set() = 0;
            virtual void clear() = 0;
            virtual void toggle() = 0;
            virtual void write(bool state) = 0;
            virtual bool read() const = 0;
    };


    template <typename Device_, uint8_t pinNumber_>
	class PinDriver_Generic final: public PinDriver {
		public:
			void set() override {
                Device_::set(1 << pinNumber_);
            }
			void clear() override {
                Device_::clear(1 << pinNumber_);
            }
			void toggle() override {
                Device_::toggle(1 << pinNumber_);
            }
			void write(bool state) override {
				if (state)
					Device_::set(1 << pinNumber_);
				else
					Device_::clear(1 << pinNumber_);
			}
			bool read() const override {
				return (Device_::read() & ~(1 << pinNumber_)) != 0;
			}
	};
}


#endif // __eosPinDriver__
