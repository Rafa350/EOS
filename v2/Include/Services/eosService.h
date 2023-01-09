#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "SYstem/eosEvents.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Application;
    class Service;

    struct ServiceEventArgs: public EventArgs<Service> {

    	inline ServiceEventArgs(Service* service):
    		EventArgs(service) {
    	}
    };

    /// \brief Clase que representa un servei.
    ///
    class Service {
        private:
            Application* _application;
            int _stackSize;
            Task::Priority _priority;
            bool _initialized;
            String _name;

            Service(const Service&) = delete;
            Service& operator=(const Service&) = delete;

        protected:
            Service(Application *application);

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTask();
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
            void task();

            inline void setName(const String& name) {
                _name = name;
            }

            inline void setPriority(Task::Priority priority) {
                _priority = priority;
            }

            inline void setStackSize(int stackSize) {
                _stackSize = stackSize;
            }

            inline Application* getApplication() const {
                return _application;
            }

            inline const String& getName() const {
                return _name;
            }

            inline Task::Priority getPriority() const {
                return _priority;
            }

            inline int getStackSize() const {
                return _stackSize;
            }

            inline bool isInitialized() const {
                return _initialized;
            }

        friend void link(Application* application, Service* service);
        friend void unlink(Application* application, Service* service);
    };

}


#endif	// __eosService__
