#include "hal/halUSB.h"
#include "hal/halGPIO.h"


#if defined(USE_USB_USB0) && defined(USB_USB0_HOST)
static USBH_HandleTypeDef hUSBHost_FS;
#endif
#if defined(USE_USB_USB1) && defined(USB_USB1_HOST)
static USBH_HandleTypeDef hUSBHost_HS;
#endif


#if defined(USE_USB_USB0) && defined(USB_USB0_HOST)
extern PCD_HandleTypeDef hpcd_FS;
#endif
#if defined(USE_USB_USB1) && defined(USB_USB1_HOST)
extern PCD_HandleTypeDef hpcd_HS;
#endif

#if defined(USE_USB_USB0) && defined(USB_USB0_DEVICE)
extern HCD_HandleTypeDef hhcd_FS;
#endif
#if defined(USE_USB_USB1) && defined(USB_USB1_DEVICE)
extern HCD_HandleTypeDef hhcd_HS;
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador USB
///
void hslUSBInitialize(void) {
   
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

    
#ifdef USE_USB_USB0    
    static const GPIOInitializePinInfo usb0Info[] = {
        { USB_USB0_DP_PORT,     USB_USB0_DP_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_DP_AF },
        { USB_USB0_DM_PORT,     USB_USB0_DM_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_DM_AF },
        { USB_USB0_ID_PORT,     USB_USB0_ID_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_ID_AF },
        { USB_USB0_VBUS_PORT,   USB_USB0_VBUS_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_VBUS_AF },
        { USB_USB0_VBUSEN_PORT, USB_USB0_VBUSEN_PIN, 
            HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPED_HIGH, USB_USB1_VBUSEN_AF },
    };

    // Configura els pins
    halGPIOInitializePins(usb0Info, sizeof(usb0Info) / sizeof(usb0Info[0]));

    // Activa el CLK del modul
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    
    // Configura les interrupcions
    HAL_NVIC_SetPriority(OTG_FS_IRQn, USB_NVIC_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);           
#endif    
    
#ifdef USE_USB_USB1    
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

    // Configura els pins
    halGPIOInitializePins(usb1Info, sizeof(usb1Info) / sizeof(usb1Info[0]));

    // Activa el CLK del modul
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    
    // Configura les interrupcions
    HAL_NVIC_SetPriority(OTG_HS_IRQn, USB_NVIC_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
#endif    

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza un port USB HOST
/// \param info: Parametres de configuracio.
///
void halUSBHostInitialize(
    const USBInitializeInfo *info) {
    
    switch (info->port) {
        
#ifdef USB_USE_USB0      
        case HAL_USB_PORT_0:
            USBH_Init(&hUSBHost_FS, USBH_ProcessCallback, USB_ID_FS);
            USBH_Start(&hUSBHost_FS);
            break;
#endif            
    
#ifdef USB_USE_USB1
        case HAL_USB_PORT_1:
            USBH_Init(&hUSBHost_HS, USBH_ProcessCallback, USB_ID_HS);
            USBH_Start(&hUSBHost_HS);
            break;       
#endif        
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa la maquina d'estats del controlador USB
///
void halUSBProcess() {
    
    USBH_Process();
}



/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio USB-FS
///
#ifdef USE_USB_USB0
void OTG_FS_IRQHandler(void) {
#ifdef USB_USB0_HOST
	HAL_HCD_IRQHandler(&hhcd_FS);
#endif
	
#ifdef USB_USB0_DEVICE
	HAL_PCD_IRQHandler(&hpcd_FS);
#endif
}
#endif


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio USB-HS
///
#ifdef USE_USB_USB1
void OTG_HS_IRQHandler(void) {
#ifdef USB_USB1_HOST
	HAL_HCD_IRQHandler(&hhcd_HS);
#endif
	
#ifdef USB_USB1_DEVICE
	HAL_PCD_IRQHandler(&hpcd_HS);
#endif
}
#endif
