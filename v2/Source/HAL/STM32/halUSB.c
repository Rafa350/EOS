#include "hal/halUSB.h"
#include "hal/halGPIO.h"


#define USB_USE_FS
//#define USB_USE_HS
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
    
    GPIOInitializePortInfo portInfo;
    
    switch (info->id) {
        
#ifdef USB_USE_FS        
        case HAL_USB_PORT_FS:
        
            // Configura els pins DM, DP i VBUS
            portInfo.Port = HAL_GPIO_PORT_A;
            portInfo.Mask = HAL_GPIO_POS_9 | HAL_GPIO_POS_11 | HAL_GPIO_POS_12;
            portInfo.Options = HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_HIGH;
            portInfo.Alt = HAL_GPIO_AF10_OGT_FS;
            halGPIOInitializePorts(&portInfo, 1);

            // Configura el pin ID
            portInfo.Port = HAL_GPIO_PORT_A;
            portInfo.Mask = HAL_GPIO_POS_10;
            portInfo.Options = HAL_GPIO_MODE_ALT_OD | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH;
            portInfo.Alt = HAL_GPIO_AF10_OGT_FS;
            halGPIOInitializePorts(&portInfo, 1);

            // Activa el CLK del modul
            __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
            
            // Configura les interrupcions
            HAL_NVIC_SetPriority(OTG_FS_IRQn, USB_NVIC_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(OTG_FS_IRQn);           
            break;
#endif            
    
#if defined(USB_USE_HS) || defined(USB_USE_HS_PHY)
        case HAL_USB_PORT_HS:

            // Configura els pins DB, DP, VBUS i ID
            portInfo.Port = HAL_GPIO_PORT_B;
            portInfo.Mask = HAL_GPIO_POS_12 | HAL_GPIO_POS_13 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15;
            portInfo.Options = HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_HIGH;
            portInfo.Alt = HAL_GPIO_AF10_OGT_HS;
            halGPIOInitializePorts(&portInfo, 1);

            // Activa el CLK del modul
            __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
            
            // Configura les interrupcions
            HAL_NVIC_SetPriority(OTG_HS_IRQn, USB_NVIC_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
            break;       
#endif        
    }
}

