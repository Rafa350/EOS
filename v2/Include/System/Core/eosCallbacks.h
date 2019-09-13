#ifndef __eosCallbacks__
#define	__eosCallbacks__


#include "eos.h"


namespace eos {

    template <typename P1Type>
    class ICallbackP1 {
        public:
    		virtual ~ICallbackP1() {
    		}

    		virtual void execute(P1Type p1) const = 0;
    };

    template <class Class, typename P1Type>
    class CallbackP1: public ICallbackP1<P1Type> {
        public:
            typedef void (Class::*Method)(P1Type);

        private:
            Class* instance;
            Method method;

        public:
            CallbackP1(Class *instance, Method method): instance(instance), method(method) {
            }

            void execute(P1Type p1) const override {
            	if ((instance != nullptr) && (method != nullptr))
            		(instance->*method)(p1);
            }
    };


    template <typename P1Type, typename P2Type>
    class ICallbackP2 {
        public:
    		virtual ~ICallbackP2() {
    		}

    		virtual void execute(P1Type p1, P2Type p2) const = 0;
    };

    template <class Class, typename P1Type, typename P2Type>
    class CallbackP2: public ICallbackP2<P1Type, P2Type> {
        public:
            typedef void (Class::*Method)(P1Type, P2Type);

        private:
            Class* instance;
            Method method;

        public:
            CallbackP2(Class *instance, Method method): instance(instance), method(method) {
            }

            void execute(P1Type p1, P2Type p2) const override {
            	if ((instance != nullptr) && (method != nullptr))
            		(instance->*method)(p1, p2);
            }
    };


    template <typename RType, typename P1Type>
    class ICallbackP1R {
        public:
    		virtual ~ICallbackP1R() {
    		}

            virtual RType execute(P1Type p1) const = 0;
    };

    template <class Class, typename RType, typename P1Type>
    class CallbackP1R: public ICallbackP1R<RType, P1Type> {
        public:
            typedef RType (Class::*Method)(P1Type);

        private:
            Class* instance;
            Method method;

        public:
            CallbackP1R(Class *instance, Method method): instance(instance), method(method) {
            }

            RType execute(P1Type p1) const override {
            	if ((instance != nullptr) && (method != nullptr))
            		return (instance->*method)(p1);
            	else
            		return RType();
            }
    };


    template <typename RType, typename P1Type, typename P2Type>
    class ICallbackP2R {
        public:
    		virtual ~ICallbackP2R() {
			}
            virtual RType execute(P1Type p1, P2Type p2) const = 0;
    };

    template <class Class, typename RType, typename P1Type, typename P2Type>
    class CallbackP2R: public ICallbackP2R<RType, P1Type, P2Type> {
        public:
            typedef RType (Class::*Method)(P1Type, P2Type);

        private:
            Class* instance;
            Method method;

        public:
            CallbackP2R(Class *instance, Method method): instance(instance), method(method) {
            }

            RType execute(P1Type p1, P2Type p2) const override {
            	if ((instance != nullptr) && (method != nullptr))
            		return (instance->*method)(p1, p2);
            	return
            		RType();
            }
    };
}


#endif // __eosCallbacks__

