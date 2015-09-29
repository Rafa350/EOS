#ifndef __EOS_TASK_HPP
#define	__EOS_TASK_HPP


namespace eos {
    
    class Process {
        public:
            Process(unsigned stackSize, unsigned priority);
        protected:
            void delay(unsigned time);
            void delayUntil(unsigned time, unsigned *lastTick);
            unsigned getTickCount();
            virtual void run() = 0;
        private:            
            static void function(void *params);
    };
}


#endif
