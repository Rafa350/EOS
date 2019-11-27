#include "eos.h"
#include "Services/eosTimerService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany el servei.
///
TimerService::TimerService(
    Application *application):

    Service(application),
    commandQueue(10) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerService::~TimerService() {

    while (!timers.isEmpty()) {
        TimerCounter *timer = timers.getFirst();
        removeTimer(timer);
        delete timer;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un contador al servei.
/// \param    timer: El temporitzador a afeigir.
///
void TimerService::addTimer(
    TimerCounter *timer) {

    // Prerequisits
    //
    eosAssert(timer != nullptr);
    eosAssert(timer->service == nullptr);

    timers.add(timer);
    timer->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un contador del servei.
/// \param    timer: El temporitzador a eliminar.
///
void TimerService::removeTimer(
    TimerCounter *timer) {

    // Precondicions
    //
    eosAssert(timer != nullptr);
    eosAssert(timer->service == this);

    timer->service = nullptr;
    timers.remove(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots temporitzadors del servei.
///
void TimerService::removeTimers() {

    while (!timers.isEmpty())
        removeTimer(timers.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief    Inicia un temporitzador.
/// \param    timer: El temporitzador.
/// \param    time: El periode.
///
void TimerService::start(
    TimerCounter *timer,
    int time) {

    timer->time = time;

    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::start;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El temporitzador.
///
void TimerService::stop(
    TimerCounter *timer) {

    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::stop;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Posa el temporitzador en pausa.
/// \param    timer: El temporitzador.
///
void TimerService::pause(
    TimerCounter *timer) {

    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::pause;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Torna a posar en marxa el temporitzador despres d'una pausa.
/// \param    timer: El temporitzador.
///
void TimerService::resume(
    TimerCounter *timer) {

    Command cmd;
    cmd.timer = timer;
    cmd.opCode = OpCode::resume;
    commandQueue.put(cmd, 1000);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la tasca del servei.
///
void TimerService::onTask() {

    while (true) {
        processActiveTimers();
        processCommands();
        waitTime();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els temporitzadors actius.
///
void TimerService::processActiveTimers() {

    if (!activeTimers.isEmpty()) {

        int decrement = 1;

        // Procesa els temporitzadors actius
        //
        TimerList discardTimers;

        for (auto timer: activeTimers) {
            if (!timer->paused) {

                // Decrementa el contador
                //
                if (timer->counter > decrement)
                    timer->counter -= decrement;
                else
                    timer->counter = 0;

                // Si el contador arriba a zero, genera l'event
                //
                if ((timer->counter) == 0 && (timer->callback != nullptr)) {

                    // Afegeix el temporitzador a la llista de descartables
                    //
                    discardTimers.add(timer);

                    // Genera l'event
                    //
                    TimerCounter::EventArgs args;
                    args.timer = timer;
                    timer->callback->execute(args);
                }

            }
        }

        for (auto timer: discardTimers)
            activeTimers.remove(timer);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la cua de comandes.
///
void TimerService::processCommands() {

    Command cmd;
    while (commandQueue.get(cmd, 0)) {
        switch (cmd.opCode) {
            case OpCode::start:
                cmd.timer->paused = false;
                cmd.timer->counter = cmd.timer->time;
                activeTimers.add(cmd.timer);
                break;

            case OpCode::stop:
                cmd.timer->counter = 0;
                break;

            case OpCode::pause:
                cmd.timer->paused = true;
                break;

            case OpCode::resume:
                cmd.timer->paused = false;
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Espera el event de temps.
///
void TimerService::waitTime() {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    callback: El callback dels events.
///
TimerCounter::TimerCounter(
    TimerService *service,
    IEventCallback *callback):

    service(nullptr),
    callback(callback),
    paused(false),
    counter(0),
    time(0) {

    if (service != nullptr)
        service->addTimer(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
TimerCounter::~TimerCounter() {

    if (service != nullptr)
        service->removeTimer(this);
}
