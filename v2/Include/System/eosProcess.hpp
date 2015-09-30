#ifndef __EOS_TASK_HPP
#define	__EOS_TASK_HPP


namespace eos {
    
    class Process;
    
    typedef Process *HProcess;    
       
    class Process {
        public:
            Process(unsigned stackSize, unsigned priority);
            virtual ~Process();
        protected:
            void delay(unsigned time);
            void delayUntil(unsigned time, unsigned *lastTick);
            unsigned getTickCount();
            void enterCriticalSection();
            void exitCriticalSection();
            void suspendAllThreads();
            void resumeAllThreads();
            virtual void run() = 0;
        private:     
            void *taskHandle;
            static void function(void *params);
    };    
}


#endif
