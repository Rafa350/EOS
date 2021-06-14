#ifndef __PIC32_halSPI__
#define __PIC32_halSPI__

#ifdef	__cplusplus
extern "C" {
#endif


// Identificador dels canals
#define HAL_SPI_CHANNEL_1         0
#ifdef _SPI2
#define HAL_SPI_CHANNEL_2         1
#endif
#ifdef _SPI3
#define HAL_SPI_CHANNEL_3         2
#endif
#ifdef _SPI4
#define HAL_SPI_CHANNEL_4         3
#endif
#ifdef _SPI5
#define HAL_SPI_CHANNEL_5         4
#endif
#define HAL_SPI_CHANNEL_NONE      0xFFFFFFFF


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halSPI__

