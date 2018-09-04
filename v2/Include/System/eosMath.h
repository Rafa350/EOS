#ifndef __eosMath__
#define __eosMath__


namespace eos {

    class Math {
        public:

    		template <typename T>
            static T inline min(T a, T b) {
                return a < b ? a : b;
            }

    		template <typename T>
            static T inline max(T a, T b) {
                return a > b ? a : b;
            }

    		template <typename T>
            static T inline abs(T a) {
                return a < 0 ? -a : a;
            }

            /// \brief Intercambia dues variables A i B.
            /// \param a: Variable A.
            /// \param b: Variable B.
    		template <typename T>
            static inline void swap(T &a, T &b) {
                T t = a;
                a = b;
                b = t;
            }
    };
}


#endif // __eosMath__
