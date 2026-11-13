export module Eos.Controllers.Pin;

import Eos.Types;


export namespace eos {

    class PinDriver: private NonCopyableClass {
        public:
            virtual ~PinDriver() = default;

            virtual void set() = 0;
            virtual void clear() = 0;
            virtual void toggle() = 0;
            virtual void write(bool state) = 0;
            virtual bool read() = 0;
    };

}
