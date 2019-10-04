#ifndef __STM32_halLTDC__
#define __STM32_halLTDC__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t LTDCLayerNum;
typedef uint8_t LTDCPixelFormat;

typedef struct {
    uint16_t HSYNC;
    uint16_t VSYNC;
    uint16_t HBP;
    uint16_t HFP;
    uint16_t VBP;
    uint16_t VFP;
    struct {                      // Polaritat
        unsigned HSYNC: 1;        //     Polaritat HSYNC
        unsigned VSYNC: 1;        //     Polaritat VSYNC
        unsigned DE: 1;           //     Polaritat DE
        unsigned PC: 1;           //     Polaritat PC
    } polarity;
    uint16_t width;               // Amplada
    uint16_t height;              // Alçada
    struct {                      // Color de fons
        uint8_t R;                //     Component R
        uint8_t G;                //     Component G
        uint8_t B;                //     Component B
    } backgroundColor;
} LTDCInitializeInfo;

typedef struct {
    uint16_t x;                   // Posicio X
    uint16_t y;                   // Posicio Y
	uint16_t width;               // Amplada
	uint16_t height;              // Alçada
    LTDCPixelFormat pixelFormat;  // Format de pixel
    struct {                      // Color per defecte
        uint8_t A;
        uint8_t R;
        uint8_t G;
        uint8_t B;
    } defaultColor;
    struct {                      // Color per croma
        uint8_t R;
        uint8_t G;
        uint8_t B;
    } keyColor;
    uint8_t constantAlpha;
} LTDCInitializeLayerInfo;


// Identificados de les capes
#define HAL_LTDC_LAYER_0          ((LTDCLayerNum) 0)
#define HAL_LTDC_LAYER_1          ((LTDCLayerNum) 1)


// Format de pixel
#define HAL_LTDC_FORMAT_RGB888    ((LTDCPixelFormat) 0)
#define HAL_LTDC_FORMAT_RGB565    ((LTDCPixelFormat) 1)
#define HAL_LTDC_FORMAT_L8        ((LTDCPixelFormat) 2)


void halLTDCInitialize(const LTDCInitializeInfo *pInfo);
void halLTDCInitializeLayer(LTDCLayerNum layerNum, const LTDCInitializeLayerInfo *pInfo);

void halLTDCSetFrameAddress(LTDCLayerNum layerNum, int frameAddr);
uint8_t halLTDCGetPixelSize(LTDCPixelFormat pixelFormat);

#define halLTDCEnable()      LTDC->GCR |= LTDC_GCR_LTDCEN
#define halLTDCDisable()     LTDC->GCR &= ~LTDC_GCR_LTDCEN


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halLTDC__
