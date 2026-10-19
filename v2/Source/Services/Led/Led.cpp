export module Eos.Services.LedService;

import Eos.Hardware.GPIO;
import Eos.Services.Service;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;
import Eos.Types;


namespace eos {

	export class LedService: public Service {
	    public:
	        using Pin = eos::hardware::gpio::PinDevice;

	        enum class LedMode: UInt8 {
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
	        static constexpr UInt32 _serviceStackDepth = 96;
	        static constexpr auto _servicePriority = Task::Priority::low;

	        static constexpr auto _stepInterval        = Ticks::fromMiliseconds(150);
	        static constexpr auto _slowBlinkInterval   = Ticks::fromMiliseconds(1000);
	        static constexpr auto _mediumBlinkInterval = Ticks::fromMiliseconds(500);
	        static constexpr auto _fastBlinkInterval   = Ticks::fromMiliseconds(250);

	        static constexpr UInt16 _flash1Pattern    = 0b0000000001001111;
	        static constexpr UInt16 _flash2Pattern    = 0b0000000101001111;
	        static constexpr UInt16 _flash3Pattern    = 0b0000010101001111;
	        static constexpr UInt16 _flash4Pattern    = 0b0001010101001111;

	    private:
	        Pin * const _pinLED;
	        LedMode _mode;
	        UInt8 _step;

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			LedService(Pin *pinLED);

			void setLedMode(LedMode value);
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    pinLED: El pin del LED
///
LedService::LedService(
     Pin *pinLED) :

	 Service(),
	 _pinLED {pinLED},
	 _mode {LedMode::mediumBlink} {
}


/// ---------------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
///
void LedService::onInitialize(
	ServiceParams &params) {

	params.name = _serviceName;
	params.stackDepth = _serviceStackDepth;
	params.priority = _servicePriority;
}


/// ---------------------------------------------------------------------------
/// \brief 	  Tasca del servei.
///
void LedService::onExecute() {

    _pinLED->clear();

    _step = 0;

    while (!stopSignal()) {

    	switch (_mode) {
    		case LedMode::on:
    			_pinLED->set();
    			Task::delayUntil(Ticks::fromMiliseconds(1000));
    			break;

    		case LedMode::off:
    			_pinLED->clear();
    			Task::delayUntil(Ticks::fromMiliseconds(1000));
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
    			Task::delayUntil(interval);
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
    			Task::delayUntil(_stepInterval);
    			break;
    		}
    	}
	}
}


/// ---------------------------------------------------------------------------
/// \brief    Asigna el modus d'iluminacio del led.
/// \param    value: El modus.
///
void LedService::setLedMode(
	LedMode value) {

	if (_mode != value) {
		_mode = value;
	}
}
