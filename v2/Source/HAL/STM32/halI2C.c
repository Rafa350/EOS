#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halI2C.h"
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


static I2C_HandleTypeDef i2cHandler[HAL_I2C_ID_MAX];


/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge del modul I2C.
/// \param    module: identificador del modul.
///
static void EnableClock(
	I2CModule module) {

	switch (module) {
		case HAL_I2C_I2C1:
            //RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
            __HAL_RCC_I2C1_CLK_ENABLE();
			break;

		case HAL_I2C_I2C2:
            //RCC->APB1ENR |=  RCC_APB1ENR_I2C2EN;
			__HAL_RCC_I2C2_CLK_ENABLE();
			break;

		case HAL_I2C_I2C3:
            //RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
			__HAL_RCC_I2C3_CLK_ENABLE();
			break;

		case HAL_I2C_I2C4:
            //RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
			__HAL_RCC_I2C4_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el handler del modul I2C
/// \param    module: Identificador del modul.
/// \return   El handler.
///
static I2C_HandleTypeDef *GetHandler(
	I2CModule module) {

	return &i2cHandler[module];
}


/// ----------------------------------------------------------------------
/// \brief    Configura els parametres d'inicialitzacio del handler.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler.
///
static I2C_HandleTypeDef *PrepareHandler(
	const I2CMasterInitializeInfo *info) {

	EnableClock(info->module);

	static I2C_TypeDef * const instances[HAL_I2C_ID_MAX] = {
		I2C1,
		I2C2,
		I2C3,
		I2C4
	};

	I2C_HandleTypeDef *handler = GetHandler(info->module);
	handler->Instance = instances[info->module];

	handler->Init.Timing           = DISCOVERY_I2Cx_TIMING;
    handler->Init.OwnAddress1      = 0;
    handler->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    handler->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    handler->Init.OwnAddress2      = 0;
    handler->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    handler->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul.
/// \param    handler: El handler del modul.
//
static void InitializeModule(
	I2C_HandleTypeDef *handler) {

	HAL_I2C_Init(handler);
	__HAL_I2C_ENABLE(handler);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul.
/// \param    handler: El handler del modul.
///
static void DeinitializeModule(
	I2C_HandleTypeDef *handler) {

	__HAL_I2C_DISABLE(handler);
	HAL_I2C_DeInit(handler);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un modul I2C
/// \param    info: Els parametres d'inicialitzacio.
///
void halI2CMasterInitialize(
	const I2CMasterInitializeInfo *info) {

	EnableClock(info->module);

	I2C_HandleTypeDef *handler = PrepareHandler(info);
	InitializeModule(handler);
}


void halI2CShutdown(
	I2CModule module) {

	DeinitializeModule(GetHandler(module));
}


void halI2CMasterReadMultiple(
	uint8_t id,
	uint8_t addr,
	uint16_t reg,
	uint16_t memAddress,
	uint8_t *buffer,
	uint16_t length) {

	I2C_HandleTypeDef *handler = GetHandler(id);
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(handler, addr, (uint16_t)reg, memAddress, buffer, length, 1000);

	// Check the communication status
	if(status != HAL_OK) {
		// I2C error occurred
		//I2Cx_Error(handler, addr);
	}
}


void halI2CMasterWriteMultiple(
	uint8_t id,
	uint8_t addr,
	uint16_t reg,
	uint16_t memAddress,
	uint8_t *buffer,
	uint16_t length) {

	I2C_HandleTypeDef *handler = GetHandler(id);

	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(handler, addr, (uint16_t)reg, memAddress, buffer, length, 1000);

	// Check the communication status
	if (status != HAL_OK) {
		// Re-Initiaize the I2C Bus
		//I2Cx_Error(handler, addr);
	}
}
