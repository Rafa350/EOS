#include "hal/halUSBDevice.h"


#ifdef USB_USE_FS
extern PCD_HandleTypeDef hpcd_FS;
#endif
#ifdef USB_USE_HS
extern PCD_HandleTypeDef hpcd_HS;
#endif
#endif


/// ----------------------------------------------------------------------
/// \brief FS IRQ Handler
///
#ifdef USB_USE_FS
void OTG_FS_IRQHandler(void) {
	
	HAL_PCD_IRQHandler(&hpcd_FS);
}
#endif


/// ----------------------------------------------------------------------
/// \brief HS IRQ Handler
///
#ifdef USB_USE_HS
void OTG_HS_IRQHandler(void) {
	
	HAL_PCD_IRQHandler(&hpcd_HS);
}
#endif