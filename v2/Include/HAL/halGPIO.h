#ifndef __EOS_HAL_GPIO_H
#define	__EOS_HAL_GPIO_H


#ifdef	__cplusplus
extern "C" {
#endif
    
    
#include <stdbool.h>
#include <stdint.h>
   
    
#define HAL_GPIO_PIN1            0
#define HAL_GPIO_PIN2            1
#define HAL_GPIO_PIN3            2
#define HAL_GPIO_PIN4            3
#define HAL_GPIO_PIN5            4
#define HAL_GPIO_PIN6            5
#define HAL_GPIO_PIN7            6
#define HAL_GPIO_PIN8            7
#define HAL_GPIO_PIN9            8
#define HAL_GPIO_PIN10           9
#define HAL_GPIO_PIN11          10
#define HAL_GPIO_PIN12          11
#define HAL_GPIO_PIN13          12
#define HAL_GPIO_PIN14          13
#define HAL_GPIO_PIN15          14
#define HAL_GPIO_PIN16          15
#define HAL_GPIO_PIN17          16
#define HAL_GPIO_PIN18          17
#define HAL_GPIO_PIN19          18
#define HAL_GPIO_PIN20          19
#define HAL_GPIO_PIN21          20
#define HAL_GPIO_PIN22          21
#define HAL_GPIO_PIN23          22
#define HAL_GPIO_PIN24          23
#define HAL_GPIO_PIN25          24
#define HAL_GPIO_PIN26          25
#define HAL_GPIO_PIN27          26
#define HAL_GPIO_PIN28          27
#define HAL_GPIO_PIN29          28
#define HAL_GPIO_PIN30          29
#define HAL_GPIO_PIN31          30
#define HAL_GPIO_PIN32          31
#define HAL_GPIO_PIN33          32
#define HAL_GPIO_PIN34          33
#define HAL_GPIO_PIN35          34
#define HAL_GPIO_PIN36          35
#define HAL_GPIO_PIN37          36
#define HAL_GPIO_PIN38          37
#define HAL_GPIO_PIN39          38
#define HAL_GPIO_PIN40          39

    
typedef struct {                       // Configuracio dels pins
    volatile uint32_t *trisCLR;        // -Adressa TRISxCLR
    volatile uint32_t *trisSET;        // -Adressa TRISxSET
    volatile uint32_t *odcCLR;         // -Addrese ODCxCLR
    volatile uint32_t *odcSET;         // -Addresa ODCxSET
    volatile uint32_t *port;           // -Addresa PORTx
    volatile uint32_t *latCLR;         // -Adressa LATxCLR
    volatile uint32_t *latSET;         // -Adressa LATxSET
    volatile uint32_t *latINV;         // -Adressa LATxINV
    uint32_t mask;                     // -Mascara del pin
    int analog;                        // -Port analogic (-1 cap))
} PinInfo;


void halGPIOInitializeBoard();

void halGPIOInitialize(const PinInfo *pinInfo, uint8_t numPins);
void halGPIOPinSetModeOutput(uint8_t pin, bool openDrain);
void halGPIOPinSetModeInput(uint8_t pin);
bool halGPIOPinGetState(uint8_t pin);
void halGPIOPinSetState(uint8_t pin, bool state);
void halGPIOPinToggleState(uint8_t pin);


#ifdef	__cplusplus
}
#endif


#endif	

