#ifndef __STM32_halDMA2D__
#define __STM32_halDMA2D__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

// Format de color de la destinacio
#define HAL_DMA2D_DFMT_POS        0u
#define HAL_DMA2D_DFMT_BITS       0b111u
#define HAL_DMA2D_DFMT_MASK       (HAL_DMA2D_DFMT_BITS << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_ARGB8888   (0u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_RGB888     (1u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_RGB565     (2u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_A8         (3u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_L8         (4u << HAL_DMA2D_DFMT_POS)

// Format de color del origen
#define HAL_DMA2D_SFMT_POS        3u
#define HAL_DMA2D_SFMT_BITS       0b111u
#define HAL_DMA2D_SFMT_MASK       (HAL_DMA2D_SFMT_BITS << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_ARGB8888   (0u << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_RGB888     (1u << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_RGB565     (2u << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_A8         (3u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_SFMT_L8         (4u << HAL_DMA2D_DFMT_POS)

// Us de les interrupcions
#define HAL_DMA2D_INT_POS         6u
#define HAL_DMA2D_INT_BITS        0b1u
#define HAL_DMA2D_INT_MASK        (HAL_DMS2D_INT_BITS << HAL_DMA2D_INT_POS)
#define HAL_DMA2D_INT_DISABLE     (0u << HAL_DMA2D_INT_POS)
#define HAL_DMA2D_INT_ENABLE      (1u << HAL_DMA2D_INT_POS)

typedef uint32_t DMA2DOptions;


void halDMA2DInitialize(void);

void halDMA2DConfigureCLUT();

void halDMA2DStartFill(int addr, int width, int height, int pitch,
		DMA2DOptions options, uint32_t color);
void halDMA2DStartCopy(int addr, int width, int height, int pitch,
		DMA2DOptions options, int sAddr, int dx, int dy, int sPitch);

bool halDMA2DWaitForFinish(void);

#ifdef	__cplusplus
}
#endif


#endif // __STM32_halDMA2D__