module;


#include "eos.h"
#include "eosTime.h"
#include "HTL/htlGPIO.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"
#include "Services/eosService.h"


export module Eos.Services.LedService;


export namespace eos {

	class LedService: public Service {
	    public:
	        using Pin = htl::gpio::PinDevice;

	        enum class LedMode {
	        	on,
				off,
				slowBlink,
				mediumBlink,
				fastBlink,
				flash1,
				flash2,
				flash3,
				flash4
	        };

	    private:
	        static constexpr const char *_serviceName = "Led";
	        static constexpr uint32_t _serviceStackDepth = 96;
	        static constexpr rtos::Task::Priority _servicePriority = rtos::Task::Priority::low;

	        static constexpr Time _stepInterval  = Time::fromMiliseconds(150);
	        static constexpr Time _slowBlinkInterval = Time::fromMiliseconds(1000);
	        static constexpr Time _mediumBlinkInterval = Time::fromMiliseconds(500);
	        static constexpr Time _fastBlinkInterval = Time::fromMiliseconds(250);

	        static constexpr uint16_t _flash1Pattern    = 0b0000000001001111;
	        static constexpr uint16_t _flash2Pattern    = 0b0000000101001111;
	        static constexpr uint16_t _flash3Pattern    = 0b0000010101001111;
	        static constexpr uint16_t _flash4Pattern    = 0b0001010101001111;

	    private:
	        Pin * const _pinLED;
	        LedMode _mode;
	        uint8_t _step;

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			LedService(Pin *pinLED);

			void setLedMode(LedMode value);
	};
}


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    pinLED: El pin del LED
///
eos::LedService::LedService(
     Pin *pinLED) :

	 Service(),
	 _pinLED {pinLED},
	 _mode {LedMode::mediumBlink} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
///
void eos::LedService::onInitialize(
	ServiceParams &params) {

	params.name = _serviceName;
	params.stackDepth = _serviceStackDepth;
	params.priority = _servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief 	  Tasca del servei.
///
void eos::LedService::onExecute() {

    _pinLED->clear();

    _step = 0;

    while (!stopSignal()) {

    	switch (_mode) {
    		case LedMode::on:
    			_pinLED->set();
    			rtos::Task::delayUntil(Time::fromMiliseconds(1000));
    			break;

    		case LedMode::off:
    			_pinLED->clear();
    			rtos::Task::delayUntil(Time::fromMiliseconds(1000));
    			break;

    		case LedMode::slowBlink:
    		case LedMode::mediumBlink:
    		case LedMode::fastBlink: {
    			auto interval = _slowBlinkInterval;
    			switch (_mode) {
    				case LedMode::mediumBlink:
    					interval = _mediumBlinkInterval;
    					break;

    				case LedMode::fastBlink:
    					interval = _fastBlinkInterval;
    					break;
    			}
    			_pinLED->toggle();
    			rtos::Task::delayUntil(interval);
    			break;
    		}

    		case LedMode::flash1:
    		case LedMode::flash2:
    		case LedMode::flash3:
    		case LedMode::flash4: {
    		    auto pattern = _flash1Pattern;
    			switch (_mode) {
    	    		case LedMode::flash2:
    	    			pattern = _flash2Pattern;
    	    			break;

    	    		case LedMode::flash3:
    	    			pattern = _flash3Pattern;
    	    			break;

    	    		case LedMode::flash4:
    	    			pattern = _flash4Pattern;
    	    			break;
    			}
    			_pinLED->write((pattern & (1 << _step)) != 0);
    			_step = (_step + 1) & 0x0F;
    			rtos::Task::delayUntil(_stepInterval);
    			break;
    		}
    	}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el modus d'iluminacio del led.
/// \param    value: El modus.
///
void eos::LedService::setLedMode(
	LedMode value) {

	if (_mode != value) {
		_mode = value;
	}
}
