#pragma once


#include "eos.h"
#include "usbb_def.h"


namespace eos {
	
	class USBDeviceClass;
	
	class USBDevice {
		private:
			USBD_HandleTypeDef _hDevice;
		public:
			void initialize();
			void registerClass(USBDeviceClass *cls);
			void start();
	}
}

