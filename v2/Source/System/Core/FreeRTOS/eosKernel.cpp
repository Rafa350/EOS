module;


#include "eos.h"

#include "FreeRTOS.h"
#include "task.h"


export module Eos.System.Core.Kernel;


export namespace eos {

	class Kernel final {
		public:
			static constexpr uint32_t tickFrequency = configTICK_RATE_HZ;

		public:
			enum class State {
				stopped,
				running,
				suspended
			};

		private:
			static void tickHandler();

		public:
			static void startScheduler();
			static void stopScheduler();

			static void suspendAll();
			static void resumeAll();

			static uint32_t getTickCount();
			static uint32_t getTickCountISR();

			static State getState();

			static bool isRunning() {
				return  getState() == State::running;
			}
	};
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el planificador
///
void eos::Kernel::startScheduler(){

	if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)
		vTaskStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Para el planificador
///
void eos::Kernel::stopScheduler() {

	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		vTaskEndScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de tics desde el inici de l'aplicacio
/// \return   El valor.
///
uint32_t eos::Kernel::getTickCount() {

	return xTaskGetTickCount();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de tics desde el inici de l'aplicacio
/// \return   El valor.
///
uint32_t eos::Kernel::getTickCountISR() {

	return xTaskGetTickCountFromISR();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del planificador.
/// \return   L'estat.
///
eos::Kernel::State eos::Kernel::getState() {

	switch (xTaskGetSchedulerState()) {
		case taskSCHEDULER_RUNNING:
			return State::running;

		case taskSCHEDULER_SUSPENDED:
			return State::suspended;

		default:
			return State::stopped;
	}
}
