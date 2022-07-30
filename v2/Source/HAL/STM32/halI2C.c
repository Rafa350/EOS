#include "HAL/hal.h"
#include "HAL/STM32/halI2C.h"
#include "HAL/STM32/halSYS.h"
#if defined(STM32F4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx.h"
#include "stm32f7xx_hal_i2c.h"
#else
#error Hardware no soportado
#endif


// I2C TIMING Register define when I2C clock source is SYSCLK
// I2C TIMING is calculated from APB1 source clock = 50 MHz
// Due to the big MOFSET capacity for adapting the camera level the rising time is very large (>1us)
// 0x40912732 takes in account the big rising and aims a clock of 100khz
#ifndef DISCOVERY_I2Cx_TIMING
#define DISCOVERY_I2Cx_TIMING     ((uint32_t)0x40912732)
#endif


#define __VERIFY_CHANNEL(channel) eosAssert((channel >= HAL_I2C_CHANNEL_1) && (channel <= HAL_I2C_CHANNEL_4))
#define __VERIFY_DEVICE(device)   eosAssert(IS_I2C_ALL_INSTANCE(device))
#define __VERIFY_HANDLER(handler) eosAssert(handler != NULL)


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: Identificador del dispositiu.
/// \return   El dispositiu.
///
static inline I2C_TypeDef* getDevice(
	halI2CChannel channel) {

	__VERIFY_CHANNEL(channel);

	static I2C_TypeDef* const devices[] = {
		I2C1,
		I2C2,
		I2C3,
		I2C4,
	};

	return devices[channel];
}


/// ----------------------------------------------------------------------
/// \brief    Activa el modul I2C.
/// \param    device: El dispositiu.
///
static void enableDeviceClock(
	I2C_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {
		case I2C1_BASE:
            __set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
			break;

		case I2C2_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_I2C2EN);
			break;

		case I2C3_BASE:
            __set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);
			break;

		case I2C4_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_I2C4EN);
			break;
	}

	__DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu
/// \brief    device: El dispositiu.
/// \brief    handle: Handler HAL (Provisional).
/// \param    options: Opcions d'inicialitzacio.
///
static void setupDevice(
	I2C_TypeDef* device,
	I2C_HandleTypeDef* handle,
	halI2COptions options) {

	eosAssert(handle != NULL);
	__VERIFY_DEVICE(device);

	// TODO : Fer-ho be.
	/*RCC_PeriphCLKInitTypeDef pclkInit;
    pclkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C3;
	pclkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_SYSCLK;
	HAL_RCCEx_PeriphCLKConfig(&pclkInit);
	*/

	handle->Instance = device;
	handle->Init.Timing           = DISCOVERY_I2Cx_TIMING;
    handle->Init.OwnAddress1      = 0;
    handle->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    handle->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    handle->Init.OwnAddress2      = 0;
    handle->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    handle->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

	HAL_I2C_Init(handle);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un modul I2C.
/// \param    data: Buffer de dades.
/// \param    info: Els parametres d'inicialitzacio.
/// \param    handler: El handler del modul.
/// \return   El resultat de l'operacio.
///
halI2CResult halI2CMasterInitialize(
	halI2CData *data,
	const halI2CMasterInitializeInfo* info,
	halI2CHandler *handler) {

	eosAssert(data != NULL);
	eosAssert(info != NULL);

	I2C_TypeDef *device = getDevice(info->channel);

	enableDeviceClock(device);

	setupDevice(device, &data->handle, info->options);

	halI2CHandler h = data;
	h->device = device;

	if (__check_bit_msk(info->options, HAL_I2C_INT_ENABLE)) {
		h->isrFunction = info->isrFunction;
		h->isrParams = info->isrParams;
	}
	else {
		h->isrFunction = NULL;
		h->isrParams = NULL;
	}

    halI2CEnable(h);

    *handler = h;

    return HAL_I2C_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    handler: Handler del dispositiu.
/// \param    El resultast de l'operacio
///
halI2CResult halI2CDeinitialize(
	halI2CHandler handler) {

	__VERIFY_HANDLER(handler);

	halI2CDisable(handler);

	return HAL_I2C_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu.
/// \param    handler: Handler del dispositiu.
/// \return   El resultat de l'operacio.
///
halI2CResult halI2CEnable(
	halI2CHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__set_bit_msk(handler->device->CR1, I2C_CR1_PE);

	return HAL_I2C_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu.
/// \param    handler: Handler del dispositiu.
/// \return   El resultat de l'operacio.
///
halI2CResult halI2CDisable(
	halI2CHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__clear_bit_msk(handler->device->CR1, I2C_CR1_PE);

	return HAL_I2C_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Transmeteix una sequencia de bytes.
/// \param    handler: Handler del dispositiu.
/// \param    addr: Adressa.
/// \param    data: Bloc de dades transmetre.
/// \param    size: Tamany del bloc en bytes.
/// \param    blockTime: Temps maxim de bloqueig.
/// \param    El resultat de l'operacio.
///
halI2CResult halI2CMasterSend(
	halI2CHandler handler,
	uint8_t addr,
	const void *data,
	int size,
	unsigned blockTime) {

	__VERIFY_HANDLER(handler);

	if (HAL_I2C_Master_Transmit(&handler->handle, addr, (uint8_t*)data, size, blockTime) == HAL_OK)
		return HAL_I2C_OK;
	else
		return HAL_I2C_ERR;
}


/// ----------------------------------------------------------------------
/// \brief    Transmeteix una sequencia de bytes.
/// \param    handler: Handler del dispositiu.
/// \param    addr: Adressa.
/// \param    data: Bloc de dades transmetre.
/// \param    size: Tamany del bloc en bytes.
/// \param    blockTime: Temps maxim de bloqueig.
/// \result   El resultat de l'operacio
///
/*
halI2CResult __halI2CMasterSend(
	halI2CHandler handler,
	uint8_t addr,
	const void *data,
	int size,
	unsigned blockTime) {

	unsigned tickstart = HAL_GetTick();

	// Espera el flag BUSY del registre ISR
	//
	while (handler->device->ISR & I2C_ISR_BUSY != 0) {
		if (((HAL_GetTick() - tickstart) > blockTime) || (blockTime == 0))
			return HAL_I2C_ERR_TIMEOUT;
	}

	uint32_t temp;

	// Configura el registre CR2 (Control Register 2)
	//
	temp = handler->device->CR2;
	temp &= ~(I2C_CR2_SADD | I2C_CR2_ADD10 | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	temp |= (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD_Msk;
	temp |= (size << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk;
	temp |= 0x80000000 | I2C_CR2_START;
	temp |= I2C_CR2_AUTOEND;
	handler->device->CR2 = temp;

	uint8_t *p = (uint8_t*) data;

	while (size-- > 0) {

		handler->device->TXDR = *p++;

		// Espera el flag TXIS del registre ISR
		//
		while (handler->device->ISR & I2C_ISR_TXIS == 0) {

			if (handler->device->ISR & I2C_ISR_NACKF)

			if (((HAL_GetTick() - tickstart) > blockTime) || (blockTime == 0))
				return HAL_I2C_ERR_TIMEOUT;
		}
	}
}
*/


/// ----------------------------------------------------------------------
/// \brief    Reb una sequencia de bytes.
/// \param    handler: Handler.
/// \param    addr: Adressa.
/// \param    data: Buffer de recepcio.
/// \param    size: Tamany del buffer de recepcio en bytes.
/// \param    blockParam: Temps maxim de bloqueig.
/// \return   El resultat de l'operacio.
///
halI2CResult halI2CMasterReceive(
	halI2CHandler handler,
	uint8_t addr,
	void *data,
	int size,
	unsigned blockTime) {

	__VERIFY_HANDLER(handler);

	if (HAL_I2C_Master_Receive(&handler->handle, addr, data, size, blockTime) == HAL_OK)
		return HAL_I2C_OK;
	else
		return HAL_I2C_ERR;
}
