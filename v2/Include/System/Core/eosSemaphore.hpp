#ifndef __EOS_SEMAPHORE_HPP
#define	__EOS_SEMAPHORE_HPP


namespace eos {

    class BinarySemaphore {
        private:
            void *handle;
            
        public:
            BinarySemaphore();
            ~BinarySemaphore();
            bool take(unsigned blockTime);
            bool give();
            void giveISR();
    };
}


#endif

