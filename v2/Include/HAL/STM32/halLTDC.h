#ifndef __STM32_halLTDC__
#define __STM32_halLTDC__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t LTDCLayerNum;
typedef uint8_t LTDCPixelFormat;

typedef struct __LDTCData *LTDCHandler;

typedef void (*LTDCInterruptFunction)(void *params, uint32_t event);

typedef struct {
    uint16_t HSYNC;
    uint16_t VSYNC;
    uint16_t HBP;
    uint16_t HFP;
    uint16_t VBP;
    uint16_t VFP;
    struct {                 // Polaritat
        unsigned HSYNC: 1;   // -HSYNC
        unsigned VSYNC: 1;   // -VSYNC
        unsigned DE: 1;      // -DE
        unsigned PC: 1;      // -PC
    } polarity;
    int width;               // Amplada
    int height;              // Alçada
    LTDCInterruptFunction isrFunction;
    void *isrParams;
} LTDCSettings;


// Identificados de les capes
#define HAL_LTDC_LAYER_0          ((LTDCLayerNum) 0)
#define HAL_LTDC_LAYER_1          ((LTDCLayerNum) 1)


// Format de pixel
#define HAL_LTDC_FORMAT_RGB888    ((LTDCPixelFormat) 0)
#define HAL_LTDC_FORMAT_RGB565    ((LTDCPixelFormat) 1)
#define HAL_LTDC_FORMAT_L8        ((LTDCPixelFormat) 2)


void halLTDCInitialize(const LTDCSettings *settings);
void halLTDCDeinitialize();

void halLTDCSetBackgroundColor(uint32_t rgb);

void halLTDCLayerSetWindow(LTDCLayerNum layerNum, int x, int y, int width, int height);
void halLTDCLayerSetDefaultColor(LTDCLayerNum layerNum, uint32_t argb);
void halLTDCLayerSetKeyColor(LTDCLayerNum layerNum, uint32_t rgb);
void halLTDCLayerDisableKeyColor(LTDCLayerNum layerNum);
void halLTDCLayerSetFrameFormat(LTDCLayerNum layerNum, LTDCPixelFormat pixelFormat, int lineWidth, int linePitch, int numLines);
void halLTDCLayerSetFrameBuffer(LTDCLayerNum layerNum, void *buffer);
void halLTDCLayerUpdate(LTDCLayerNum layerNum);

int halLTDCGetPixelOffset(LTDCLayerNum layerNum, int x, int y);
uint8_t halLTDCGetPixelBytes(LTDCPixelFormat pixelFormat);

#define halLTDCEnable()      __set_bit_msk(LTDC->GCR, LTDC_GCR_LTDCEN)
#define halLTDCDisable()     __clear_bit_msk(LTDC->GCR, LTDC_GCR_LTDCEN)


void halLTDCSetInterruptFunction(LTDCInterruptFunction function, void *params);
void halLTDCInterruptHandler();

void halLTDCEnableInterrupts();
void halLTDCDisableInterrupts();

bool halLTDCGetInterruptFlag(uint32_t event);
void halLTDCClearInterruptFlag(uint32_t events);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halLTDC__
