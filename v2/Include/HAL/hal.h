#ifndef __hal__
#define __hal__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


#define HAL_RESULT_OK             0
#define HAL_RESULT_ERROR          1
#define HAL_RESULT_BUSY           2
#define HAL_RESULT_TIMEOUT        3

typedef uint32_t halRESULT;


// Bit operation macros
//
#define __set_bit_msk(a, b)       ((a) |= (b))
#define __clear_bit_msk(a, b)     ((a) &= ~(b))
#define __set_bit_pos(a, b)       ((a) |= (1 << (b)))
#define __clear_bit_pos(a, b)     ((a) &= ~(1 << (b)))

#define __check_bit_msk(a, b)     ((((a) & (b)) == (b)) ? true : false)
#define __check_bit_pos(a, b)     ((((a) & (1 << (b))) == (1 << (b))) ? true : false)

#define __clear_reg(a)            a = 0
#define __read_bit(a, b)          ((a) & (b))

// Operacions aritmetiques
//
#define __abs_diff(hi, lo)        ((hi) > (lo) ? (hi) - (lo) : (lo) - (hi))


#endif // __hal__
