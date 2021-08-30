#ifndef __eosCallbacks__
#define	__eosCallbacks__


// EOS includes
//
#include "eos.h"


namespace eos {

    template <typename P1_>
    class ICallbackP1 {
        public:
            virtual ~ICallbackP1() {
            }

            virtual void execute(P1_ p1) const = 0;
    };

    template <typename C_, typename P1_>
    class CallbackP1: public ICallbackP1<P1_> {
        public:
            typedef void (C_::*Method)(P1_);

        private:
            C_* instance;
            Method method;

        public:
            inline CallbackP1(C_* instance, Method method):
            	instance(instance),
				method(method) {
            }

            void execute(P1_ p1) const override {
                if ((instance != nullptr) && (method != nullptr))
                    (instance->*method)(p1);
            }
    };


    template <typename P1_, typename P2_>
    class ICallbackP2 {
        public:
            virtual ~ICallbackP2() {
            }

            virtual void execute(P1_ p1, P2_ p2) const = 0;
    };

    template <typename C_, typename P1_, typename P2_>
    class CallbackP2: public ICallbackP2<P1_, P2_> {
        public:
    	    typedef void (C_::*Method)(P1_, P2_);

        private:
            C_* instance;
            Method method;

        public:
            inline CallbackP2(C_* instance, Method method):
            	instance(instance),
				method(method) {
            }

            void execute(P1_ p1, P2_ p2) const override {
                if ((instance != nullptr) && (method != nullptr))
                    (instance->*method)(p1, p2);
            }
    };


    template <typename R_, typename P1_>
    class ICallbackP1R {
        public:
            virtual ~ICallbackP1R() {
            }

            virtual R_ execute(P1_ p1) const = 0;
    };

    template <typename C_, typename R_, typename P1_>
    class CallbackP1R: public ICallbackP1R<R_, P1_> {
        public:
            typedef R_ (C_::*Method)(P1_);

        private:
            C_* instance;
            Method method;

        public:
            inline CallbackP1R(C_* instance, Method method):
            	instance(instance),
				method(method) {
            }

            R_ execute(P1_ p1) const override {
                if ((instance != nullptr) && (method != nullptr))
                    return (instance->*method)(p1);
                else
                    return R_();
            }
    };


    template <typename R_, typename P1_, typename P2_>
    class ICallbackP2R {
        public:
            virtual ~ICallbackP2R() {
            }
            virtual R_ execute(P1_ p1, P2_ p2) const = 0;
    };

    template <typename C_, typename R_, typename P1_, typename P2_>
    class CallbackP2R: public ICallbackP2R<R_, P1_, P2_> {
        public:
            typedef R_ (C_::*Method)(P1_, P2_);

        private:
            C_* instance;
            Method method;

        public:
            inline CallbackP2R(C_* instance, Method method):
            	instance(instance),
				method(method) {
            }

            R_ execute(P1_ p1, P2_ p2) const override {
                if ((instance != nullptr) && (method != nullptr))
                    return (instance->*method)(p1, p2);
                else
                	return R_();
            }
    };

}


#endif // __eosCallbacks__

