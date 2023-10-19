#ifndef __eosSingleton__
#define __eosSingleton__


namespace eos {

    // TODO: Revisar la utilitat

	template <typename T_>
	class Singleton {
		private:
			Singleton() {}
			~Singleton() {}

		public:
			static T_& instance() {
				static T_ s;
				return s;
			}

			Singleton(const Singleton&) = delete;
			Singleton& operator = (const Singleton&) = delete;
	};
}


#endif // __eosSingleton__
