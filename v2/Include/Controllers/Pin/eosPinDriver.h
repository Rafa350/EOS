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
}


#endif // __eosPinDriver__
