#ifndef __STM32_halDMA2D__
#define __STM32_halDMA2D__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


// Format de color de la destinacio
#define HAL_DMA2D_DFMT_pos        0u
#define HAL_DMA2D_DFMT_bits       0b111u
#define HAL_DMA2D_DFMT_mask       (HAL_DMA2D_DFMT_bits << HAL_DMA2D_DFMT_pos)

#define HAL_DMA2D_DFMT_ARGB8888   (0u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_DFMT_RGB888     (1u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_DFMT_RGB565     (2u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_DFMT_A8         (3u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_DFMT_L8         (4u << HAL_DMA2D_DFMT_pos)

// Format de color del origen
#define HAL_DMA2D_SFMT_pos        3u
#define HAL_DMA2D_SFMT_bits       0b111u
#define HAL_DMA2D_SFMT_mask       (HAL_DMA2D_SFMT_bits << HAL_DMA2D_SFMT_pos)

#define HAL_DMA2D_SFMT_ARGB8888   (0u << HAL_DMA2D_SFMT_pos)
#define HAL_DMA2D_SFMT_RGB888     (1u << HAL_DMA2D_SFMT_pos)
#define HAL_DMA2D_SFMT_RGB565     (2u << HAL_DMA2D_SFMT_pos)
#define HAL_DMA2D_SFMT_A8         (3u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_SFMT_L8         (4u << HAL_DMA2D_DFMT_pos)
#define HAL_DMA2D_SFMT_NOCHANGE   (7u << HAL_DMA2D_DFMT_pos)

// Us de les interrupcions
#define HAL_DMA2D_INT_pos         6u
#define HAL_DMA2D_INT_bits        0b1u

#define HAL_DMA2D_INT_mask        (HAL_DMS2D_INT_bits << HAL_DMA2D_INT_pos)
#define HAL_DMA2D_INT_DISABLE     (0u << HAL_DMA2D_INT_POS)
#define HAL_DMA2D_INT_ENABLE      (1u << HAL_DMA2D_INT_POS)

typedef uint32_t DMA2DOptions;


void halDMA2DInitialize();
void halDMA2DDeinitialize();

void halDMA2DConfigureCLUT();

void halDMA2DStartFill(void* dst, int width, int height, int offset, DMA2DOptions options, uint32_t color);
void halDMA2DStartCopy(void* dst, int width, int height, int offset, DMA2DOptions options, void* src, int srcOffset);
bool halDMA2DWaitForFinish();

void halDMA2DInterruptHandler();


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halDMA2D__
