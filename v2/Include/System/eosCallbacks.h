#pragma once
#ifndef __eosCallbacks__
#define __eosCallbacks__


// EOS includes
//
#include "eos.h"


namespace eos {

	class ICallbackP0 {
		public:
			virtual ~ICallbackP0() {
			}
			virtual void execute() const = 0;
			inline void operator()() const {
			    execute();
			}
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
			    (_instance.*_method)();
			}
	};


    template <typename Param1_>
    class ICallbackP1 {
        public:
            virtual ~ICallbackP1() {
            }
            virtual void execute(Param1_ p1) const = 0;
			inline void operator()(Param1_ p1) const {
			    execute(p1);
			}
    };

    template <typename Instance_, typename Param1_>
    class CallbackP1: public ICallbackP1<Param1_> {
        public:
			using RInstance = Instance_ &;
            using Method = void (Instance_::*)(Param1_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP1(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(Param1_ p1) const override {
                (_instance.*_method)(p1);
            }
    };


    template <typename Param1_, typename Param2_>
    class ICallbackP2 {
        public:
            virtual ~ICallbackP2() {
            }
            virtual void execute(Param1_ p1, Param2_ p2) const = 0;
			inline void operator()(Param1_ p1, Param2_ p2) const {
				execute(p1, p2);
			}
    };

    template <typename Instance_, typename Param1_, typename Param2_>
    class CallbackP2: public ICallbackP2<Param1_, Param2_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(Param1_, Param2_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP2(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(Param1_ p1, Param2_ p2) const override {
                (_instance.*_method)(p1, p2);
            }
    };


    template <typename Param1_, typename Param2_, typename Param3_>
    class ICallbackP3 {
        public:
            virtual ~ICallbackP3() {
            }
            virtual void execute(Param1_ p1, Param2_ p2, Param3_ p3) const = 0;
			inline void operator()(Param1_ p1, Param2_ p2, Param3_ p3) const {
				execute(p1, p2, p3);
			}
    };

    template <typename Instance_, typename Param1_, typename Param2_, typename Param3_>
    class CallbackP3: public ICallbackP3<Param1_, Param2_, Param3_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(Param1_, Param2_, Param3_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP3(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(Param1_ p1, Param2_ p2, Param3_ p3) const override {
                (_instance.*_method)(p1, p2, p3);
            }
    };


    template <typename Param1_, typename Param2_, typename Param3_, typename Param4_>
    class ICallbackP4 {
        public:
            virtual ~ICallbackP4() {
            }
            virtual void execute(Param1_ p1, Param2_ p2, Param3_ p3, Param4_ p4) const = 0;
			inline void operator()(Param1_ p1, Param2_ p2, Param3_ p3, Param4_ p4) const {
				execute(p1, p2, p3, p4);
			}
    };

    template <typename Instance_, typename Param1_, typename Param2_, typename Param3_, typename Param4_>
    class CallbackP4: public ICallbackP4<Param1_, Param2_, Param3_, Param4_> {
        public:
			using RInstance = Instance_ &;
    	    using Method = void (Instance_::*)(Param1_, Param2_, Param3_, Param4_);
        private:
            RInstance const _instance;
            Method const _method;
        public:
            inline CallbackP4(RInstance instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            void execute(Param1_ p1, Param2_ p2, Param3_ p3, Param4_ p4) const override {
                (_instance.*_method)(p1, p2, p3, p4);
            }
    };


    template <typename Result_, typename Param1_>
    class ICallbackP1R {
        public:
            virtual ~ICallbackP1R() {
            }
            virtual Result_ execute(Param1_ p1) const = 0;
			inline Result_ operator()(Param1_ p1) const {
				return execute(p1);
			}
    };

    template <typename Instance_, typename Result_, typename Param1_>
    class CallbackP1R: public ICallbackP1R<Result_, Param1_> {
        public:
            using Method = Result_ (Instance_::*)(Param1_);
        private:
            Instance_ &_instance;
            Method _method;
        public:
            inline CallbackP1R(Instance_ &instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            Result_ execute(Param1_ p1) const override {
                return (_instance.*_method)(p1);
            }
    };


    template <typename Result_, typename Param1_, typename Param2_>
    class ICallbackP2R {
        public:
            virtual ~ICallbackP2R() {
            }
            virtual Result_ execute(Param1_ p1, Param2_ p2) const = 0;
    };

    template <typename Instance_, typename Result_, typename Param1_, typename Param2_>
    class CallbackP2R: public ICallbackP2R<Result_, Param1_, Param2_> {
        public:
            using Method = Result_ (Instance_::*)(Param1_, Param2_);
        private:
            Instance_ &_instance;
            Method _method;
        public:
            inline CallbackP2R(Instance_ &instance, Method method):
            	_instance {instance},
				_method {method} {
            }
            Result_ execute(Param1_ p1, Param2_ p2) const override {
                return (_instance.*_method)(p1, p2);
            }
    };

}


#endif // __eosCallbacks__
