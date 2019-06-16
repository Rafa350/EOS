#ifndef __STM32_halDMA2D__
#define __STM32_halDMA2D__


#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

// Format de color de la destinacio
#define HAL_DMA2D_DFMT_POS        0u
#define HAL_DMA2D_DFMT_BITS       0b11u
#define HAL_DMA2D_DFMT_MASK       (HAL_DMA2D_DFMT_BITS << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_ARGB8888   (0u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_RGB888     (1u << HAL_DMA2D_DFMT_POS)
#define HAL_DMA2D_DFMT_RGB565     (2u << HAL_DMA2D_DFMT_POS)

// Format de color del origen
#define HAL_DMA2D_SFMT_POS        2u
#define HAL_DMA2D_SFMT_BITS       0b11u
#define HAL_DMA2D_SFMT_MASK       (HAL_DMA2D_SFMT_BITS << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_ARGB8888   (0u << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_RGB888     (1u << HAL_DMA2D_SFMT_POS)
#define HAL_DMA2D_SFMT_RGB565     (2u << HAL_DMA2D_SFMT_POS)

typedef uint32_t DMA2DOptions;


void halDMA2DInitialize(void);
bool halDMA2DWaitForFinish(void);

void halDMA2DFill(int addr, int width, int height, int pitch, DMA2DOptions options, uint32_t color);
void halDMA2DCopy(int addr,	int width, int height, int pitch, DMA2DOptions options, int sAddr, int dx, int dy, int sPitch);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halDMA2D__
