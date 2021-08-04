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
	I2CChannel channel) {

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
	I2COptions options) {

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
///
I2CHandler halI2CMasterInitialize(
	I2CData* data,
	const I2CMasterInitializeInfo* info) {

	eosAssert(data != NULL);
	eosAssert(info != NULL);

	I2C_TypeDef* device = getDevice(info->channel);

	enableDeviceClock(device);

	setupDevice(device, &data->handle, info->options);

	I2CHandler handler = data;
	handler->device = device;

	if (__check_bit_msk(info->options, HAL_I2C_INT_ENABLE)) {
		handler->isrFunction = info->isrFunction;
		handler->isrParams = info->isrParams;
	}
	else {
		handler->isrFunction = NULL;
		handler->isrParams = NULL;
	}

    halI2CEnable(handler);

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    handler: Handler del dispositiu.
///
void halI2CDeinitialize(
	I2CHandler handler) {

	__VERIFY_HANDLER(handler);

	halI2CDisable(handler);
}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu.
/// \param    handler: Handler del dispositiu.
///
void halI2CEnable(
	I2CHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__set_bit_msk(handler->device->CR1, I2C_CR1_PE);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu.
/// \param    handler: Handler del dispositiu.
///
void halI2CDisable(
	I2CHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	__clear_bit_msk(handler->device->CR1, I2C_CR1_PE);
}


void halI2CMasterReadMultiple(
	I2CHandler handler,
	uint8_t addr,
	uint16_t reg,
	uint16_t memAddress,
	uint8_t* buffer,
	uint16_t length) {

	__VERIFY_HANDLER(handler);

	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&handler->handle, addr, (uint16_t)reg, memAddress, buffer, length, 1000);

	// Check the communication status
	if(status != HAL_OK) {
		HAL_I2C_DeInit(&handler->handle);
		HAL_I2C_Init(&handler->handle);
	}
}


void halI2CMasterWriteMultiple(
	I2CHandler handler,
	uint8_t addr,
	uint16_t reg,
	uint16_t memAddress,
	const uint8_t* buffer,
	uint16_t length) {

	__VERIFY_HANDLER(handler);

	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&handler->handle, addr, (uint16_t)reg, memAddress, (uint8_t*)buffer, length, 1000);

	// Check the communication status
	if (status != HAL_OK) {
		HAL_I2C_DeInit(&handler->handle);
		HAL_I2C_Init(&handler->handle);
	}
}
