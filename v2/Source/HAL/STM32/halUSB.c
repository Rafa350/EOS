#include "hal/halUSB.h"
#include "hal/halGPIO.h"


//#define USB_USE_FS
#define USB_USE_HS
//#define USB_USE_HS_PHY


static void InitializeClock() {
   
#if defined(STM32F7xx)
	RCC_PeriphCLKInitTypeDef clkInit;
	
	// Select PLLSAI output as USB clock source 
    //
	clkInit.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
	clkInit.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
	clkInit.PLLSAI.PLLSAIN = 192;
	clkInit.PLLSAI.PLLSAIQ = 4; 
	clkInit.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
	
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el port USB
/// \param info: Parametres de configuracio.
///
void halUSBInitialize(
    const USBInitializeInfp *info) {
    
    static const GPIOInitializePinInfo usb1Info[] = {
        { USB_USB1_DP_PORT,     USB_USB1_DP_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_DP_AF },
        { USB_USB1_DM_PORT,     USB_USB1_DM_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_DM_AF },
        { USB_USB1_ID_PORT,     USB_USB1_ID_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_ID_AF },
        { USB_USB1_VBUS_PORT,   USB_USB1_VBUS_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_VBUS_AF },
        { USB_USB1_VBUSEN_PORT, USB_USB1_VBUSEN_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_VBUSEN_AF },
    };
    
    switch (info->port) {
        
#ifdef USB_USE_FS        
        case HAL_USB_PORT_0:
        
            // Configura els pins
            //halGPIOInitializePins(usb0Info, sizeof(usb0Info) / sizeof(usb0Info[0]));

            // Activa el CLK del modul
            __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
            
            // Configura les interrupcions
            HAL_NVIC_SetPriority(OTG_FS_IRQn, USB_NVIC_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(OTG_FS_IRQn);           
            break;
#endif            
    
#if defined(USB_USE_HS) || defined(USB_USE_HS_PHY)
        case HAL_USB_PORT_1:

            // Configura els pins
            halGPIOInitializePins(usb1Info, sizeof(usb1Info) / sizeof(usb1Info[0]));

            // Activa el CLK del modul
            __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
            
            // Configura les interrupcions
            HAL_NVIC_SetPriority(OTG_HS_IRQn, USB_NVIC_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
            break;       
#endif        
    }
}

