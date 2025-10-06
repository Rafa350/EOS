#pragma once
#ifndef __eosSelectorService__
#define __eosSelectorService__


#include "eos.h"
#include "Controllers/Pin/Drivers/GPIO/eosPinDriver_GPIO.h"
#include "System/eosCallbacks.h"
#include "Services/eosService.h"


namespace eos {

	/// \brief Servei que gestiona un encoder rotatiou
	///
    class SelectorService final: public Service {
        public:
            struct ChangedEventArgs {
                int16_t position;
                bool button;
            };
            using IChangedEvent = ICallbackP2<const SelectorService*, const ChangedEventArgs&>;
            template <typename Instance_> using ChangedEvent = CallbackP2<Instance_, const SelectorService*, const ChangedEventArgs&>;

        private:
            static constexpr unsigned _delay = 50;
            static constexpr uint8_t _patternMask = 0b00001111;

            PinDriver * const _drvINA;
            PinDriver * const _drvINB;
            PinDriver * const _drvSW;

            int16_t _position;
            bool _button;

            uint8_t _patternA;
            uint8_t _patternB;
            uint8_t _patternSW;
            uint8_t _shiftA;
            uint8_t _shiftB;
            uint8_t _shiftSW;
            uint8_t _transition;

            IChangedEvent *_changedEvent;
            bool _changedEventEnabled;

        private:
            bool scanEncoder();
            uint8_t getINA() const;
            uint8_t getINB() const;
            uint8_t getSW() const;

        protected:
            void onExecute() override;

        public:
            SelectorService(PinDriver *drvINA, PinDriver *drvINB, PinDriver *drvSW);

            void setChangedEvent(IChangedEvent &event, bool enabled);
            void enableChangedEvent();
            void disableChangedEvent();
    };
}


#endif // __eosSelectorService__
