#ifndef __EOS_CALLBACKS_HPP
#define	__EOS_CALLBACKS_HPP

namespace eos {

    template <class Class, typename P1Type>
    class CallbackP1 {
        public:
            typedef void (Class::*Method)(P1Type);

        public:
            CallbackP1(Class *instance, Method method) {
                
                this->instance = instance;
                this->method = method;
            }

            void operator()(P1Type p1) {
                
                (instance->*method)(p1);
            }

            void execute(P1Type p1) {
                
                operator()(p1);
            }

        private:    
            Class* instance;
            Method method;
    };
    
    template <class Class, typename RType, typename P1Type>
    class CallbackP1R {
        public:
            typedef RType (Class::*Method)(P1Type);

        public:
            CallbackP1R(Class *instance, Method method) {
                
                this->instance = instance;
                this->method = method;
            }

            RType operator()(P1Type p1) {
                
                return (instance->*method)(p1);
            }

            RType execute(P1Type p1) {
                
                return operator()(p1);
            }

        private:    
            Class* instance;
            Method method;
    };

}

#endif

