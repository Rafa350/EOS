#ifndef __EOS_HAL_EINT_PIC32_H
#define	__EOS_HAL_EINT_PIC32_H


#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define HAL_EINT_INPUT_0     0
#define HAL_EINT_INPUT_1     1
#define HAL_EINT_INPUT_2     2
#define HAL_EINT_INPUT_3     3
#define HAL_EINT_INPUT_4     4
#define HAL_EINT_INPUT_5     5
#define HAL_EINT_INPUT_6     6
#define HAL_EINT_INPUT_7     7
#define HAL_EINT_INPUT_8     8
#define HAL_EINT_INPUT_9     9
#define HAL_EINT_INPUT_10    10
#define HAL_EINT_INPUT_11    11
#define HAL_EINT_INPUT_12    12
#define HAL_EINT_INPUT_13    13
#define HAL_EINT_INPUT_14    14
#define HAL_EINT_INPUT_15    15
#define HAL_EINT_INPUT_16    16
#define HAL_EINT_INPUT_17    17
#define HAL_EINT_INPUT_18    18
#define HAL_EINT_INPUT_19    19
    
#define HAL_EINT_ENABLE_MASK 0b0000001
#define HAL_EINT_ENABLE_ON   0b0000001
#define HAL_EINT_ENABLE_OFF  0b0000000
    
#define HAL_EINT_PULLUP_MASK 0b0000110    
#define HAL_EINT_PULLUP_OFF  0b0000000
#define HAL_EINT_PULLUP_UP   0b0000010
#define HAL_EINT_PULLUP_DN   0b0000100

    
typedef uint8_t EINTInput;     
typedef uint8_t EINTOptions;    


extern void halEINTInitialize(EINTInput input, EINTOptions options);


#ifdef	__cplusplus
}
#endif


#endif	/* __EOS_HAL_EINT_PIC32_H */

