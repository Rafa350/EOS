#ifndef __eosMath__
#define __eosMath__


/// EOS includes
//
#include "eos.h"


namespace eos {

    namespace Math {

		template <typename T_>
		inline T_ min(T_ a, T_ b) {
			return a < b ? a : b;
		}

		template <typename T_>
		inline T_ max(T_ a, T_ b) {
			return a > b ? a : b;
		}

		template <typename T_>
		inline T_ abs(T_ a) {
			return a < 0 ? -a : a;
		}

		inline int32_t abs(int32_t val) {
			uint32_t temp = val >> 31;
			val ^= temp;
			val += temp & 1;
			return val;
		}

		/// \brief Intercambia dues variables A i B.
		/// \param a: Variable A.
		/// \param b: Variable B.
		template <typename T_>
		inline void swap(T_ &a, T_ &b) {
			T_ t = a;
			a = b;
			b = t;
		}
    }
}


#endif // __eosMath__
