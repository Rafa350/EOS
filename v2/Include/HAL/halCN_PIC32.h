#ifndef __EOS_HAL_CN_PIC32_H
#define	__EOS_HAL_CN_PIC32_H


#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define HAL_CN_PIN_0         0
#define HAL_CN_PIN_1         1
#define HAL_CN_PIN_2         2
#define HAL_CN_PIN_3         3
#define HAL_CN_PIN_4         4
#define HAL_CN_PIN_5         5
#define HAL_CN_PIN_6         6
#define HAL_CN_PIN_7         7
#define HAL_CN_PIN_8         8
#define HAL_CN_PIN_9         9
#define HAL_CN_PIN_10        10
#define HAL_CN_PIN_11        11
#define HAL_CN_PIN_12        12
#define HAL_CN_PIN_13        13
#define HAL_CN_PIN_14        14
#define HAL_CN_PIN_15        15
#define HAL_CN_PIN_16        16
#define HAL_CN_PIN_17        17
#define HAL_CN_PIN_18        18
#define HAL_CN_PIN_19        19
#define HAL_CN_PIN_20        20
#define HAL_CN_PIN_21        21
    
#define HAL_CN_ENABLE_MASK   0b0000001
#define HAL_CN_ENABLE_ON     0b0000001
#define HAL_CN_ENABLE_OFF    0b0000000
    
#define HAL_CN_PULLUP_MASK   0b0000110    
#define HAL_CN_PULLUP_OFF    0b0000000
#define HAL_CN_PULLUP_UP     0b0000010
#define HAL_CN_PULLUP_DN     0b0000100

    
typedef uint8_t CNPin;     
typedef uint8_t CNOptions;    
typedef void (*CNInterruptCallback)(CNPin pin, void *param);


extern void halCNInitialize(CNPin pin, CNOptions options, CNInterruptCallback callback, void *param);
extern void halCNEnable();
extern void halCNDisable();


#ifdef	__cplusplus
}
#endif


#endif	/* __EOS_HAL_CN_PIC32_H */

