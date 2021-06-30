#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Application;

    /// \brief Clase que representa un servei.
    ///
    class Service {
        private:
            Application *_application;
            unsigned stackSize;
            Task::Priority priority;
            bool initialized;
            String name;

            Service(const Service &) = delete;
            Service& operator=(const Service &) = delete;

        protected:
            Service(Application *application);

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTask(Task *task);
#if Eos_ApplicationTickEnabled
            virtual void onTick();
#endif

        public :
            virtual ~Service();

            void initialize();
            void terminate();
#if Eos_ApplicationTickEnabled
            void tick();
#endif
            void task(Task *task);

            inline void setName(const String &name) {
                this->name = name;
            }

            inline void setPriority(Task::Priority priority) {
                this->priority = priority;
            }

            inline void setStackSize(unsigned stackSize) {
                this->stackSize = stackSize;
            }

            inline Application * getApplication() const {
                return _application;
            }

            inline const String & getName() const {
                return name;
            }

            inline Task::Priority getPriority() const {
                return priority;
            }

            inline unsigned getStackSize() const {
                return stackSize;
            }

            inline bool isInitialized() const {
                return initialized;
            }

        friend void link(Application *application, Service *service);
        friend void unlink(Application *application, Service *service);
    };

}


#endif	// __eosService__
