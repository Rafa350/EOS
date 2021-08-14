#ifndef __STM32_halLTDC__
#define __STM32_halLTDC__


// HAL includes
//
#include "HAL/hal.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t halLTDCLayerNum;
typedef uint8_t halLTDCPixelFormat;

typedef struct __halLDTCData* halLTDCHandler;

typedef void (*halLTDCInterruptFunction)(void* params, uint32_t event);

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
    halLTDCInterruptFunction isrFunction;
    void *isrParams;
} halLTDCSettings;


// Identificados de les capes
#define HAL_LTDC_LAYER_0          ((halLTDCLayerNum) 0)
#define HAL_LTDC_LAYER_1          ((halLTDCLayerNum) 1)


// Format de pixel
#define HAL_LTDC_FORMAT_RGB888    ((halLTDCPixelFormat) 0)
#define HAL_LTDC_FORMAT_RGB565    ((halLTDCPixelFormat) 1)
#define HAL_LTDC_FORMAT_L8        ((halLTDCPixelFormat) 2)


void halLTDCInitialize(const halLTDCSettings *settings);
void halLTDCDeinitialize();

void halLTDCSetBackgroundColor(uint32_t rgb);

void halLTDCLayerSetWindow(halLTDCLayerNum layerNum, int x, int y, int width, int height);
void halLTDCLayerSetDefaultColor(halLTDCLayerNum layerNum, uint32_t argb);
void halLTDCLayerSetKeyColor(halLTDCLayerNum layerNum, uint32_t rgb);
void halLTDCLayerDisableKeyColor(halLTDCLayerNum layerNum);
void halLTDCLayerSetFrameFormat(halLTDCLayerNum layerNum, halLTDCPixelFormat pixelFormat, int lineWidth, int linePitch, int numLines);
void halLTDCLayerSetFrameBuffer(halLTDCLayerNum layerNum, void *buffer);
void halLTDCLayerUpdate(halLTDCLayerNum layerNum);

int halLTDCGetPixelOffset(halLTDCLayerNum layerNum, int x, int y);
uint8_t halLTDCGetPixelBytes(halLTDCPixelFormat pixelFormat);

#define halLTDCEnable()      __set_bit_msk(LTDC->GCR, LTDC_GCR_LTDCEN)
#define halLTDCDisable()     __clear_bit_msk(LTDC->GCR, LTDC_GCR_LTDCEN)


void halLTDCSetInterruptFunction(halLTDCInterruptFunction function, void* params);
void halLTDCInterruptHandler();

void halLTDCEnableInterrupts();
void halLTDCDisableInterrupts();

bool halLTDCGetInterruptFlag(uint32_t event);
void halLTDCClearInterruptFlag(uint32_t events);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halLTDC__
