#ifndef __eosCallbacks__
#define	__eosCallbacks__


// EOS includes
//
#include "eos.h"


namespace eos {

	class ICallbackP0 {
		public:
			virtual ~ICallbackP0() {
			}
			virtual void execute() const = 0;
	};

	template <typename Instance_>
	class CallbackP0: public ICallbackP0 {
		public:
			using RInstance = Instance_ &;
			using Method = void (Instance_::*)();
		private:
			RInstance const _instance;
			Method const _method;
		public:
			inline CallbackP0(RInstance instance, Method method):
				_instance {instance},
				_method {method} {
			}
			void execute() const override {
				if (_method != nullptr)
					(_instance.*_method)();
			}
	};


    template <typename param1_>
    class ICallbackP1 {
        public:
            virtual ~ICallbackP1() {
            }
            virtual void execute(param1_ p1) const = 0;
    };

    template <typename Instance_, typename param1_>
    class CallbackP1: public ICallbackP1<param1_> {
        public:
			using RInstance = Instance_ &;
            using Method = void (Instance_::*)(param1_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP1(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(param1_ p1) const override {
                if (_method != nullptr)
                    (_instance.*_method)(p1);
            }
    };


    template <typename param1_, typename param2_>
    class ICallbackP2 {
        public:
            virtual ~ICallbackP2() {
            }
            virtual void execute(param1_ p1, param2_ p2) const = 0;
    };

    template <typename Instance_, typename param1_, typename param2_>
    class CallbackP2: public ICallbackP2<param1_, param2_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(param1_, param2_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP2(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(param1_ p1, param2_ p2) const override {
                if (_method != nullptr)
                    (_instance.*_method)(p1, p2);
            }
    };


    template <typename param1_, typename param2_, typename param3_>
    class ICallbackP3 {
        public:
            virtual ~ICallbackP3() {
            }
            virtual void execute(param1_ p1, param2_ p2, param3_ p3) const = 0;
    };

    template <typename Instance_, typename param1_, typename param2_, typename param3_>
    class CallbackP3: public ICallbackP3<param1_, param2_, param3_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(param1_, param2_, param3_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP3(RInstance instance, Method method):
            	_instance(instance),
				_method(method) {
            }
            void execute(param1_ p1, param2_ p2, param3_ p3) const override {
                if (_method != nullptr)
                    (_instance.*_method)(p1, p2, p3);
            }
    };


    template <typename param1_, typename param2_, typename param3_, typename param4_>
    class ICallbackP4 {
        public:
            virtual ~ICallbackP4() {
            }
            virtual void execute(param1_ p1, param2_ p2, param3_ p3, param4_ p4) const = 0;
    };

    template <typename Instance_, typename param1_, typename param2_, typename param3_, typename param4_>
    class CallbackP4: public ICallbackP4<param1_, param2_, param3_, param4_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(param1_, param2_, param3_, param4_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP4(RInstance instance, Method method):
            	_instance(instance),
				_method(method) {
            }
            void execute(param1_ p1, param2_ p2, param3_ p3, param4_ p4) const override {
                if (_method != nullptr)
                    (_instance.*_method)(p1, p2, p3, p4);
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
            using Method = R_ (C_::*)(P1_);
        private:
            C_ &_instance;
            Method _method;
        public:
            inline CallbackP1R(C_ &instance, Method method):
            	_instance(instance),
				_method(method) {
            }
            R_ execute(P1_ p1) const override {
                if (_method != nullptr)
                    return (_instance.*_method)(p1);
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
            using Method = R_ (C_::*)(P1_, P2_);
        private:
            C_ &_instance;
            Method _method;
        public:
            inline CallbackP2R(C_ &instance, Method method):
            	_instance(instance),
				_method(method) {
            }
            R_ execute(P1_ p1, P2_ p2) const override {
                if (_method != nullptr)
                    return (_instance.*_method)(p1, p2);
                else
                	return R_();
            }
    };

}


#endif // __eosCallbacks__

