#ifndef __eosMath__
#define __eosMath__


namespace eos {

    class Math {
        public:

    		template <typename T>
            static inline T min(T a, T b) {
                return a < b ? a : b;
            }

    		template <typename T>
            static inline T max(T a, T b) {
                return a > b ? a : b;
            }

    		template <typename T>
            static inline T abs(T a) {
                return a < 0 ? -a : a;
            }

    		static inline int32_t abs(int32_t val) {
    		    uint32_t temp = val >> 31;
    		    val ^= temp;
    		    val += temp & 1;
    		    return val;
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
