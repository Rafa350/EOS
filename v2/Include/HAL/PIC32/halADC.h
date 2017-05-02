#ifndef __EOS_HAL_PIC32_ADC_H
#define	__EOS_HAL_PIC32_ADC_H


#include <xc.h>
#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


#define HAL_ADC_PIN_0             0
#define HAL_ADC_PIN_1             1
#define HAL_ADC_PIN_2             2
#define HAL_ADC_PIN_3             3
#define HAL_ADC_PIN_4             4
#define HAL_ADC_PIN_5             5
#define HAL_ADC_PIN_6             6
#define HAL_ADC_PIN_7             7
#define HAL_ADC_PIN_8             8
#define HAL_ADC_PIN_NONE          255

    
typedef uint8_t ADCPin;  



#ifdef	__cplusplus
}
#endif


#endif	/* __EOS_HALADC_PIC32_H */

