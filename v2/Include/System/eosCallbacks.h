#ifndef __eosCallbacks__
#define	__eosCallbacks__


// EOS includes
//
#include "eos.h"


namespace eos {

    template <typename P1>
    class ICallbackP1 {
        public:
            virtual ~ICallbackP1() {
            }

            virtual void execute(P1 p1) const = 0;
    };

    template <typename C, typename P1>
    class CallbackP1: public ICallbackP1<P1> {
        public:
    	    typedef C* Instance;
            typedef void (C::*Method)(P1);

        private:
            Instance instance;
            Method method;

        public:
            inline CallbackP1(Instance instance, Method method):
            	instance(instance),
				method(method) {
            }

            void execute(P1 p1) const override {
                if ((instance != nullptr) && (method != nullptr))
                    (instance->*method)(p1);
            }
    };


    template <typename P1, typename P2>
    class ICallbackP2 {
        public:
            virtual ~ICallbackP2() {
            }

            virtual void execute(P1 p1, P2 p2) const = 0;
    };

    template <typename C, typename P1, typename P2>
    class CallbackP2: public ICallbackP2<P1, P2> {
        public:
    		typedef C* Instance;
    	    typedef void (C::*Method)(P1, P2);

        private:
            Instance instance;
            Method method;

        public:
            inline CallbackP2(Instance instance, Method method):
            	instance(instance),
				method(method) {
            }

            void execute(P1 p1, P2 p2) const override {
                if ((instance != nullptr) && (method != nullptr))
                    (instance->*method)(p1, p2);
            }
    };


    template <typename R, typename P1>
    class ICallbackP1R {
        public:
            virtual ~ICallbackP1R() {
            }

            virtual R execute(P1 p1) const = 0;
    };

    template <typename C, typename R, typename P1>
    class CallbackP1R: public ICallbackP1R<R, P1> {
        public:
    		typedef C* Instance;
            typedef R (C::*Method)(P1);

        private:
            Instance instance;
            Method method;

        public:
            inline CallbackP1R(Instance instance, Method method):
            	instance(instance),
				method(method) {
            }

            R execute(P1 p1) const override {
                if ((instance != nullptr) && (method != nullptr))
                    return (instance->*method)(p1);
                else
                    return R();
            }
    };


    template <typename R, typename P1, typename P2>
    class ICallbackP2R {
        public:
            virtual ~ICallbackP2R() {
            }
            virtual R execute(P1 p1, P2 p2) const = 0;
    };

    template <typename C, typename R, typename P1, typename P2>
    class CallbackP2R: public ICallbackP2R<R, P1, P2> {
        public:
    		typedef C* Instance;
            typedef R (C::*Method)(P1, P2);

        private:
            Instance instance;
            Method method;

        public:
            inline CallbackP2R(Instance instance, Method method):
            	instance(instance),
				method(method) {
            }

            R execute(P1 p1, P2 p2) const override {
                if ((instance != nullptr) && (method != nullptr))
                    return (instance->*method)(p1, p2);
                else
                	return R();
            }
    };

}


#endif // __eosCallbacks__

