#ifndef __EOS_HAL_CN_PIC32_H
#define	__EOS_HAL_CN_PIC32_H


#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define HAL_CN_INPUT_0       0
#define HAL_CN_INPUT_1       1
#define HAL_CN_INPUT_2       2
#define HAL_CN_INPUT_3       3
#define HAL_CN_INPUT_4       4
#define HAL_CN_INPUT_5       5
#define HAL_CN_INPUT_6       6
#define HAL_CN_INPUT_7       7
#define HAL_CN_INPUT_8       8
#define HAL_CN_INPUT_9       9
#define HAL_CN_INPUT_10      10
#define HAL_CN_INPUT_11      11
#define HAL_CN_INPUT_12      12
#define HAL_CN_INPUT_13      13
#define HAL_CN_INPUT_14      14
#define HAL_CN_INPUT_15      15
#define HAL_CN_INPUT_16      16
#define HAL_CN_INPUT_17      17
#define HAL_CN_INPUT_18      18
#define HAL_CN_INPUT_19      19
#define HAL_CN_INPUT_20      20
#define HAL_CN_INPUT_21      21
    
#define HAL_CN_ENABLE_MASK   0b0000001
#define HAL_CN_ENABLE_ON     0b0000001
#define HAL_CN_ENABLE_OFF    0b0000000
    
#define HAL_CN_PULLUP_MASK   0b0000110    
#define HAL_CN_PULLUP_OFF    0b0000000
#define HAL_CN_PULLUP_UP     0b0000010
#define HAL_CN_PULLUP_DN     0b0000100

    
typedef uint8_t CNInput;     
typedef uint8_t CNOptions;    
typedef void (*CNInterruptCallback)(CNInput input, void *param);


extern void halCNInitialize(CNInput input, CNOptions options);


#ifdef	__cplusplus
}
#endif


#endif	/* __EOS_HAL_CN_PIC32_H */

