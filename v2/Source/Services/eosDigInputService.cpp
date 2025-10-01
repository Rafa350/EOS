#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"

#include <cmath>

#include "HTL/htlINT.h"


namespace eos {

    class Input final: public DigInput {

		private: static constexpr const uint32_t _patternMask    = 0x000000FF;
		private: static constexpr const uint32_t _patternPosEdge = 0x0000007F;
		private: static constexpr const uint32_t _patternNegEdge = 0x00000080;
		private: static constexpr const uint32_t _patternActive  = 0x000000FF;
		private: static constexpr const uint32_t _patternIdle    = 0x00000000;

    	public: enum class ScanMode {
			polling,
			interrupt
		};

        public: ScanMode scanMode;

        private: PinDriver * const _drv;
        private: unsigned _pattern;
        private: struct {
			unsigned state : 1;
			unsigned flag : 1;
			unsigned edges : 30;
		} _status;


        public: Input(PinDriver *pinDrv):
			_drv {pinDrv} {

			if (_drv->read()) {
				_status.state = 1;
				_pattern = _patternActive;
			}
			else {
				_status.state = 0;
				_pattern = _patternIdle;
			}
			_status.edges = 0;
			_status.flag = 0;
		}

        public: bool scan() {

        	_pattern <<= 1;
            if (_drv->read())
                _pattern |= 1;

            // Analitza el patro per detectar un flanc positiu
            //
            if ((_pattern & _patternMask) == _patternPosEdge) {
                _status.state = 1;
                _status.edges += 1;
                _status.flag = 1;
                return true;
            }

            // Analitza el patro per detectar un flanc negatiu
            //
            else if ((_pattern & _patternMask) == _patternNegEdge) {
                _status.state = 0;
                _status.edges += 1;
                _status.flag = 1;
                return true;
            }

            else
            	return false;
        }

        public: inline bool getState() const {
        	return _status.state;
        }

        public: inline unsigned getEdges(bool clear) {
        	auto edges = _status.edges;
        	if (clear)
        		_status.edges = 0;
        	return edges;
        }

        public: inline bool readFlag() {
        	bool flag = _status.flag == 1;
        	_status.flag = 0;
        	return flag;
        }
    };
}


using namespace eos;
using namespace htl;
using namespace htl::irq;


constexpr const char *serviceName = "DigInput";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 128;

constexpr unsigned minScanPeriod = 5;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \params   settings: Conmfigurationparameters.
///
DigInputService::DigInputService():
    Service(),
    _scanPeriod {minScanPeriod} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

	removeInputs();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode d'escaneig.
/// \param    scanPeriod: El period en milisegons.
///
void DigInputService::setScanPeriod(
    unsigned scanPeriod) {

    _scanPeriod = std::max(scanPeriod, minScanPeriod);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::notifyChanged(
    DigInput *input) {

    if (_erNotify.isEnabled(NotifyID::changed)) {
    	NotifyEventArgs args = {
    		.changed {
    			.input = input
    		}
    	};
    	_erNotify.raise(NotifyID::changed, &args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el inici del scaneig de les entrades.
///
void DigInputService::notifyBeforeScan() {

	if (_erNotify.isEnabled(NotifyID::beforeScan))
    	_erNotify.raise(NotifyID::beforeScan);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void DigInputService::notifyInitialize(
	ServiceParams *params) {

	if (_erNotify.isEnabled(NotifyID::initialize)) {
		NotifyEventArgs args = {
			.initialize {
				.params = params
			}
		};
		_erNotify.raise(NotifyID::initialize, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Crea una entrada.
/// \param    pinDrv: El driver del pin.
/// \return   L'entrada.
///
DigInput * DigInputService::makeInput(
	PinDriver * pinDrv) {

    eosAssert(pinDrv != nullptr);

    return new Input(pinDrv);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Afegeix l'entrada a la llista
    //
    auto i = static_cast<Input*>(input);
    if (!_inputs.contains(i))
		_inputs.pushFront(i);

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput *input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    auto i = static_cast<Input*>(input);
    if (_inputs.contains(i))
        _inputs.remove(i);

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void DigInputService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.priority = servicePriority;
	params.stackSize = serviceStackSize;

	notifyInitialize(&params);
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei
///
void DigInputService::onExecute() {

    unsigned lastWeakTime = Task::getTickCount();

    while (!stopSignal()) {

		Task::delay(_scanPeriod, lastWeakTime);

		notifyBeforeScan();

		if (scanInputs()) {
			for (auto input: _inputs) {

				auto i = static_cast<Input*>(input);

				bool s = getInterruptState();
				if (s)
					disableInterrupts();

				bool flag = i->readFlag();

				if (s)
					enableInterrupts();

				if (flag)
					notifyChanged(input);
			}
		}
	}
}


/// ---------------------------------------------------------------------
/// \brief    Escaneja l'estat de les entrades.
/// \return   True si s'han produit canvis en l'estat de les entrades.
///
bool DigInputService::scanInputs() {

    bool changed = false;

    // Procesa totes les entrades
    //
    for (auto input: _inputs) {

        auto i = static_cast<Input*>(input);
        if (i->scanMode == Input::ScanMode::polling)
        	changed |= i->scan();
    }

    return changed;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \param    input: La entrada.
/// \return   True si esta en estat ACTIVE, false en cas contrari.
///
bool DigInputService::read(
    const DigInput *input) const {

    eosAssert(input != nullptr);

    Task::enterCriticalSection();

    auto i = static_cast<const Input*>(input);
    auto value = i->getState();

    Task::exitCriticalSection();

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de pulsos de l'entrada.
/// \param    input: La entrada.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
uint32_t DigInputService::getEdges(
	DigInput *input,
	bool clear) const {

    eosAssert(input != nullptr);

    Task::enterCriticalSection();

    auto i = static_cast<Input*>(input);
    auto edges = i->getEdges(clear);

    Task::exitCriticalSection();

    return edges;
}
