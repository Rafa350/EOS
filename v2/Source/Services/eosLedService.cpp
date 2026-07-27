#include "eos.h"
#include "eosTime.h"
#include "HTL/htlGPIO.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"
#include "Services/eosLedService.h"


using namespace htl;


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


void eos::LedService::setLedMode(
	LedMode value) {

	if (_mode != value) {
		_mode = value;
	}
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
