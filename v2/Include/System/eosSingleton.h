#ifndef __eosSingleton__
#define __eosSingleton__


namespace eos {

	template <typename T>
	class Singleton {
		public:
			typedef T Value;
			typedef T& Reference;

		private:
			Singleton() {}
			~Singleton() {}

		public:
			static Reference instance() {
				static Value s;
				return s;
			}

			Singleton(const Singleton&) = delete;
			Singleton& operator = (const Singleton&) = delete;
	};
}

#endif // __eosSingleton__
