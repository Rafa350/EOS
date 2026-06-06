#pragma once
#ifndef __eosSingleton__
#define __eosSingleton__


namespace eos {

	template <typename Type_>
	class Singleton final {
		private:
			static Singleton _instance;

		private:
			Singleton() = default;
			Singleton(const Singleton&) = delete;
			Singleton(const Singleton&&) = delete;

			Singleton& operator = (const Singleton&) = delete;
			Singleton& operator = (const Singleton&&) = delete;

		public:
			static constexpr Type_ *pInst = &_instance;
			static constexpr Type_ &rInst = _instance;
	};

	template <typename Type_>
	Singleton<Type_> Singleton<Type_>::_instance;
}


#endif // __eosSingleton__
