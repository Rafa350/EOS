#include "eos.h"
#include "Controllers/Usb/eosUSB.h"
#include "Controllers/Usb/STM32/usbd.h"
#include "HAL/halGPIO.h"
#include "HAL/halUSB.h"



using namespace eos;

#ifdef USE_USB_HOST0
extern HCD_HandleTypeDef hhcd_FS;
#endif
#ifdef USE_USB_HOST1
extern HCD_HandleTypeDef hhcd_HS;
#endif

#ifdef USE_USB_DEVICE0
extern PCD_HandleTypeDef hpcd_FS;
#endif
#ifdef USE_USB_DEVICE1
extern PCD_HandleTypeDef hpcd_HS;
#endif


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param port: Identificador del port USB
///
UsbBase::UsbBase(
	USBPort port):

	port(port) {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el port USB
///
void UsbBase::initialize() {

	onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins, les interrupcions, etc.
///
void UsbBase::onInitialize() {

#if defined(USE_USB_DEVICE0) || defined(USE_USB_HOST0)
	static GPIOInitializePinInfo fsInitInfo[] = {
		{ USB_USB0_DP_PORT,
		  USB_USB0_DP_PIN,
		  HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH,
		  USB_USB0_DP_AF },

		{ USB_USB0_DM_PORT,
		  USB_USB0_DM_PIN,
		  HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH,
		  USB_USB0_DM_AF },

		{ USB_USB0_ID_PORT,
		  USB_USB0_ID_PIN,
		  HAL_GPIO_MODE_ALT_OD | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH,
		  USB_USB0_ID_AF },

		{ USB_USB0_VBUS_PORT,
		  USB_USB0_VBUS_PIN,
		  HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH,
		  USB_USB0_VBUS_AF },

#ifdef USB_USB0_VBUSEN_PIN
		{ USB_USB0_VBUSEN_PORT,
		  USB_USB0_VBUSEN_PIN,
		  HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH | HAL_GPIO_INIT_CLR,
		  USB_USB0_VBUSEN_AF },
#endif
	};
#endif

#if defined(USE_USB_DEVICE1) || defined(USE_USB_HOST1)
	static GPIOInitializePinInfo hsInitInfo[] = {

	};
#endif

	switch (port) {
		case HAL_USB_PORT_FS:
#if defined(USE_USB_DEVICE0) || defined(USE_USB_HOST0)
			halGPIOInitializePins(fsInitInfo, sizeof(fsInitInfo) / sizeof(fsInitInfo[0]));
			__HAL_RCC_USB_OTG_FS_CLK_ENABLE();
			HAL_NVIC_SetPriority(OTG_FS_IRQn, USB_NVIC_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
#endif
			break;

		case HAL_USB_PORT_HS:
#if defined(USE_USB_DEVICE1) || defined(USE_USB_HOST1)
			halGPIOInitializePins(hsInitInfo, sizeof(hsInitInfo) / sizeof(hsInitInfo[0]));
			__HAL_RCC_USB_OTG_HS_CLK_ENABLE();
			HAL_NVIC_SetPriority(OTG_HS_IRQn, USB_NVIC_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
#endif
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Control d'interrupcio del USB0 (FS)
///
#if defined(USE_USB_DEVICE0) || defined(USE_USB_HOST0)
void OTG_FS_IRQHandler(void) {
#ifdef USE_USB_HOST0
	HAL_HCD_IRQHandler(&hhcd_FS);
#endif

#ifdef USE_USB_DEVICE0
	HAL_PCD_IRQHandler(&hpcd_FS);
#endif
}
#endif


/// ----------------------------------------------------------------------
/// \brief Control d'interrupcio del USB1 (HS)
///
#if defined(USE_USB_DEVIDE1) || defined(USE_USB_HOST1)
void OTG_HS_IRQHandler(void) {
#ifdef USE_USB_HOST1
	HAL_HCD_IRQHandler(&hhcd_HS);
#endif

#ifdef USE_USB_DEVICE1
	HAL_PCD_IRQHandler(&hpcd_HS);
#endif
}
#endif
