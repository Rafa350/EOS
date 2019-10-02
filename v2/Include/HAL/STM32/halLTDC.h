#ifndef __STM32_halLTDC__
#define __STM32_halLTDC__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t LTDCLayerNum;
typedef uint32_t LTDCOptions;

typedef struct {
    uint16_t HSYNC;
    uint16_t VSYNC;
    uint16_t HBP;
    uint16_t HFP;
    uint16_t VBP;
    uint16_t VFP;
    LTDCOptions options;
    uint16_t width;               // Amplada
    uint16_t height;              // Alçada
    uint32_t backgroundColor;     // Color de fons RGB888
} LTDCInitializeInfo;

typedef struct {
	uint16_t width;               // Amplada
	uint16_t height;              // Alçada
    uint32_t defaultColor;        // Color per defecte ARGB8888
    uint32_t keyColor;            // Color per croma RGB000
} LTDCInitializeLayerInfo;


#define HAL_LTDC_LAYER_0          ((LTDCLayerNum) 0)
#define HAL_LTDC_LAYER_1          ((LTDCLayerNum) 1)


// Polaritat del senyal HSYNC
#define HAL_LTDC_HSPOL_pos        0u
#define HAL_LTDC_HSPOL_bits       0b1u
#define HAL_LTDC_HSPOL_mask       (HAL_LTDC_HSPOL_bits << HAL_LTDC_HSPOL_pos)

#define HAL_LTDC_HSPOL_LOW        (0u << HAL_LTDC_HSPOL_pos)
#define HAL_LTDC_HSPOL_HIGH       (1u << HAL_LTDC_HSPOL_pos)

// Polaritat del senyal VSYNC
#define HAL_LTDC_VSPOL_pos        1u
#define HAL_LTDC_VSPOL_bits       0b1u
#define HAL_LTDC_VSPOL_mask       (HAL_LTDC_VSPOL_bits << HAL_LTDC_HSPOL_pos)

#define HAL_LTDC_VSPOL_LOW        (0u << HAL_LTDC_VSPOL_pos)
#define HAL_LTDC_VSPOL_HIGH       (1u << HAL_LTDC_VSPOL_pos)

// Polaritat del senyal DE
#define HAL_LTDC_DEPOL_pos        2u
#define HAL_LTDC_DEPOL_bits       0b1u
#define HAL_LTDC_DEPOL_mask       (HAL_LTDC_DEPOL_bits << HAL_LTDC_DEPOL_pos)

#define HAL_LTDC_DEPOL_LOW        (0u << HAL_LTDC_DEPOL_pos)
#define HAL_LTDC_DEPOL_HIGH       (1u << HAL_LTDC_DEPOL_pos)

// Polaritat del senyal PC
#define HAL_LTDC_PCPOL_pos        3u
#define HAL_LTDC_PCPOL_bits       0b1u
#define HAL_LTDC_PCPOL_mask       (HAL_LTDC_PCPOL_bits << HAL_LTDC_PCPOL_pos)

#define HAL_LTDC_PCPOL_LOW        (0u << HAL_LTDC_PCPOL_pos)
#define HAL_LTDC_PCPOL_HIGH       (1u << HAL_LTDC_PCPOL_pos)

// Format de pixel
#define HAL_LTDC_FORMAT_pos       4u
#define HAL_LTDC_FORMAT_bits      0b11
#define HAL_LTDC_FORMAT_mask      (HAL_LTDC_FORMAT_bits << HAL_LTDC_FORMAT_pos)


void halLTDCInitialize(const LTDCInitializeInfo *pInfo);
void halLTDCInitializeLayer(LTDCLayerNum layerNum, const LTDCInitializeLayerInfo *pInfo);

void halLTDCSetFrameAddress(LTDCLayerNum layerNum, int frameAddr);

#define halLTDCEnable()      LTDC->GCR |= LTDC_GCR_LTDCEN
#define halLTDCDisable()     LTDC->GCR &= ~LTDC_GCR_LTDCEN


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halLTDC__
