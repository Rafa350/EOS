#ifndef __EOS_CALLBACKS_HPP
#define	__EOS_CALLBACKS_HPP


namespace eos {
    
    template <typename P1Type>
    class ICallbackP1 {
        public:
            virtual void execute(P1Type p1) = 0;
    };
    
    template <class Class, typename P1Type>
    class CallbackP1: public ICallbackP1<P1Type> {
        public:
            typedef void (Class::*Method)(P1Type);
            
        private:    
            Class* instance;
            Method method;

        public:
            CallbackP1(Class *instance, Method method) {
                
                this->instance = instance;
                this->method = method;
            }

            void execute(P1Type p1) {
                
                (instance->*method)(p1);
            }
    };    


    template <typename P1Type, typename P2Type>
    class ICallbackP2 {
        public:
            virtual void execute(P1Type p1, P2Type p2) = 0;
    };
    
    template <class Class, typename P1Type, typename P2Type>
    class CallbackP2: public ICallbackP2<P1Type, P2Type> {
        public:
            typedef void (Class::*Method)(P1Type, P2Type);
            
        private:    
            Class* instance;
            Method method;

        public:
            CallbackP2(Class *instance, Method method) {
                
                this->instance = instance;
                this->method = method;
            }

            void execute(P1Type p1, P2Type p2) {
                
                (instance->*method)(p1, p2);
            }
    };


    template <class Class, typename RType, typename P1Type>
    class CallbackP1R {
        public:
            typedef RType (Class::*Method)(P1Type);

        private:    
            Class* instance;
            Method method;

        public:
            CallbackP1R(Class *instance, Method method) {
                
                this->instance = instance;
                this->method = method;
            }

            RType execute(P1Type p1) {
                
                return (instance->*method)(p1);
            }
    };

}

#endif

