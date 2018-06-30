#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk)" "nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk"
include nbproject/Makefile-local-PIC32_USB_STARTER_KIT_I.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_USB_STARTER_KIT_I
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/USBDemo/PIC32/Main.cpp ../../../Demo/USBDemo/AppMain.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halUSBDevice.c ../../../Source/HAL/PIC32/halUSBDeviceCDC.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalMemory.c ../../../Source/Services/Usb/Microchip/system_init.c ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp ../../../Source/Services/Usb/eosUsbDevice.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/Services/eosService.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1389438628/Main.o ${OBJECTDIR}/_ext/1355038806/AppMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halUSBDevice.o ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalMemory.o ${OBJECTDIR}/_ext/1705198617/system_init.o ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/212497336/tasks.o ${OBJECTDIR}/_ext/212497336/queue.o ${OBJECTDIR}/_ext/212497336/timers.o ${OBJECTDIR}/_ext/1804092654/port.o ${OBJECTDIR}/_ext/1804092654/port_asm.o ${OBJECTDIR}/_ext/1321749915/heap_4.o ${OBJECTDIR}/_ext/212497336/list.o ${OBJECTDIR}/_ext/440510736/drv_usbfs.o ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o ${OBJECTDIR}/_ext/2125418608/osal_freertos.o ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o ${OBJECTDIR}/_ext/969108643/usb_device.o ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1389438628/Main.o.d ${OBJECTDIR}/_ext/1355038806/AppMain.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalMemory.o.d ${OBJECTDIR}/_ext/1705198617/system_init.o.d ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/212497336/tasks.o.d ${OBJECTDIR}/_ext/212497336/queue.o.d ${OBJECTDIR}/_ext/212497336/timers.o.d ${OBJECTDIR}/_ext/1804092654/port.o.d ${OBJECTDIR}/_ext/1804092654/port_asm.o.d ${OBJECTDIR}/_ext/1321749915/heap_4.o.d ${OBJECTDIR}/_ext/212497336/list.o.d ${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d ${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d ${OBJECTDIR}/_ext/969108643/usb_device.o.d ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1389438628/Main.o ${OBJECTDIR}/_ext/1355038806/AppMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halUSBDevice.o ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalMemory.o ${OBJECTDIR}/_ext/1705198617/system_init.o ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/212497336/tasks.o ${OBJECTDIR}/_ext/212497336/queue.o ${OBJECTDIR}/_ext/212497336/timers.o ${OBJECTDIR}/_ext/1804092654/port.o ${OBJECTDIR}/_ext/1804092654/port_asm.o ${OBJECTDIR}/_ext/1321749915/heap_4.o ${OBJECTDIR}/_ext/212497336/list.o ${OBJECTDIR}/_ext/440510736/drv_usbfs.o ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o ${OBJECTDIR}/_ext/2125418608/osal_freertos.o ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o ${OBJECTDIR}/_ext/969108643/usb_device.o ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o

# Source Files
SOURCEFILES=../../../Demo/USBDemo/PIC32/Main.cpp ../../../Demo/USBDemo/AppMain.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halUSBDevice.c ../../../Source/HAL/PIC32/halUSBDeviceCDC.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalMemory.c ../../../Source/Services/Usb/Microchip/system_init.c ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp ../../../Source/Services/Usb/eosUsbDevice.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/Services/eosService.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1804092654/port_asm.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1804092654" 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o.ok ${OBJECTDIR}/_ext/1804092654/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1804092654/port_asm.o.d" "${OBJECTDIR}/_ext/1804092654/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -DSKDEPIC32PlatformTool=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1804092654/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1804092654/port_asm.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1804092654/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=SKDEPIC32PlatformTool=1 -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/1804092654/port_asm.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1804092654" 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port_asm.o.ok ${OBJECTDIR}/_ext/1804092654/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1804092654/port_asm.o.d" "${OBJECTDIR}/_ext/1804092654/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1804092654/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1804092654/port_asm.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1804092654/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halUSBDevice.o: ../../../Source/HAL/PIC32/halUSBDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d" -o ${OBJECTDIR}/_ext/346134360/halUSBDevice.o ../../../Source/HAL/PIC32/halUSBDevice.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o: ../../../Source/HAL/PIC32/halUSBDeviceCDC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d" -o ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o ../../../Source/HAL/PIC32/halUSBDeviceCDC.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalMemory.o: ../../../Source/OSAL/FreeRTOS/osalMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMemory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalMemory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMemory.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMemory.o ../../../Source/OSAL/FreeRTOS/osalMemory.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1705198617/system_init.o: ../../../Source/Services/Usb/Microchip/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1705198617" 
	@${RM} ${OBJECTDIR}/_ext/1705198617/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705198617/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705198617/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1705198617/system_init.o.d" -o ${OBJECTDIR}/_ext/1705198617/system_init.o ../../../Source/Services/Usb/Microchip/system_init.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/tasks.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/tasks.o.d" -o ${OBJECTDIR}/_ext/212497336/tasks.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/queue.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/queue.o.d" -o ${OBJECTDIR}/_ext/212497336/queue.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/timers.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/timers.o.d" -o ${OBJECTDIR}/_ext/212497336/timers.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1804092654/port.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1804092654" 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1804092654/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1804092654/port.o.d" -o ${OBJECTDIR}/_ext/1804092654/port.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1321749915/heap_4.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1321749915" 
	@${RM} ${OBJECTDIR}/_ext/1321749915/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321749915/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321749915/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1321749915/heap_4.o.d" -o ${OBJECTDIR}/_ext/1321749915/heap_4.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/list.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/list.o.d" -o ${OBJECTDIR}/_ext/212497336/list.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/440510736/drv_usbfs.o: C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/440510736" 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/440510736/drv_usbfs.o C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o: C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/440510736" 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/2125418608/osal_freertos.o: ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2125418608" 
	@${RM} ${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125418608/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/2125418608/osal_freertos.o ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o: C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1135707888" 
	@${RM} ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device_cdc.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halUSBDevice.o: ../../../Source/HAL/PIC32/halUSBDevice.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halUSBDevice.o.d" -o ${OBJECTDIR}/_ext/346134360/halUSBDevice.o ../../../Source/HAL/PIC32/halUSBDevice.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o: ../../../Source/HAL/PIC32/halUSBDeviceCDC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o.d" -o ${OBJECTDIR}/_ext/346134360/halUSBDeviceCDC.o ../../../Source/HAL/PIC32/halUSBDeviceCDC.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalMemory.o: ../../../Source/OSAL/FreeRTOS/osalMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMemory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalMemory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMemory.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMemory.o ../../../Source/OSAL/FreeRTOS/osalMemory.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1705198617/system_init.o: ../../../Source/Services/Usb/Microchip/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1705198617" 
	@${RM} ${OBJECTDIR}/_ext/1705198617/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1705198617/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1705198617/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1705198617/system_init.o.d" -o ${OBJECTDIR}/_ext/1705198617/system_init.o ../../../Source/Services/Usb/Microchip/system_init.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/tasks.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/tasks.o.d" -o ${OBJECTDIR}/_ext/212497336/tasks.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/queue.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/queue.o.d" -o ${OBJECTDIR}/_ext/212497336/queue.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/timers.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/timers.o.d" -o ${OBJECTDIR}/_ext/212497336/timers.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1804092654/port.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1804092654" 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1804092654/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1804092654/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1804092654/port.o.d" -o ${OBJECTDIR}/_ext/1804092654/port.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1321749915/heap_4.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1321749915" 
	@${RM} ${OBJECTDIR}/_ext/1321749915/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1321749915/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1321749915/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1321749915/heap_4.o.d" -o ${OBJECTDIR}/_ext/1321749915/heap_4.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/212497336/list.o: C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212497336" 
	@${RM} ${OBJECTDIR}/_ext/212497336/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/212497336/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212497336/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/212497336/list.o.d" -o ${OBJECTDIR}/_ext/212497336/list.o C:\Library\Microchip\Harmony\v2_05_01\third_party\rtos\FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/440510736/drv_usbfs.o: C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/440510736" 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/440510736/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/440510736/drv_usbfs.o C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o: C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/440510736" 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/440510736/drv_usbfs_device.o C:\Library\Microchip\Harmony\v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/2125418608/osal_freertos.o: ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2125418608" 
	@${RM} ${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/2125418608/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/2125418608/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/2125418608/osal_freertos.o ../../../../../../../../../../Library/Microchip/Harmony/v2_05_01/framework/osal/src/osal_freertos.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o: C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1135707888" 
	@${RM} ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1135707888/sys_int_pic32.o C:\Library\Microchip\Harmony\v2_05_01/framework/system/int/src/sys_int_pic32.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device_cdc.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device_cdc.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o: C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/969108643" 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DOSAL_USE_RTOS -MMD -MF "${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/969108643/usb_device_cdc_acm.o C:\Library\Microchip\Harmony\v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1389438628/Main.o: ../../../Demo/USBDemo/PIC32/Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1389438628" 
	@${RM} ${OBJECTDIR}/_ext/1389438628/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1389438628/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1389438628/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1389438628/Main.o.d" -o ${OBJECTDIR}/_ext/1389438628/Main.o ../../../Demo/USBDemo/PIC32/Main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1355038806/AppMain.o: ../../../Demo/USBDemo/AppMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1355038806" 
	@${RM} ${OBJECTDIR}/_ext/1355038806/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1355038806/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1355038806/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1355038806/AppMain.o.d" -o ${OBJECTDIR}/_ext/1355038806/AppMain.o ../../../Demo/USBDemo/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o: ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o: ../../../Source/Services/Usb/eosUsbDevice.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o ../../../Source/Services/Usb/eosUsbDevice.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1389438628/Main.o: ../../../Demo/USBDemo/PIC32/Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1389438628" 
	@${RM} ${OBJECTDIR}/_ext/1389438628/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1389438628/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1389438628/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1389438628/Main.o.d" -o ${OBJECTDIR}/_ext/1389438628/Main.o ../../../Demo/USBDemo/PIC32/Main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1355038806/AppMain.o: ../../../Demo/USBDemo/AppMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1355038806" 
	@${RM} ${OBJECTDIR}/_ext/1355038806/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1355038806/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1355038806/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1355038806/AppMain.o.d" -o ${OBJECTDIR}/_ext/1355038806/AppMain.o ../../../Demo/USBDemo/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o: ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbDeviceCDC.o ../../../Source/Services/Usb/eosUsbDeviceCDC.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o: ../../../Source/Services/Usb/eosUsbDevice.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2012494728" 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d 
	@${RM} ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o.d" -o ${OBJECTDIR}/_ext/2012494728/eosUsbDevice.o ../../../Source/Services/Usb/eosUsbDevice.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/USBDemo" -I"../../../Demo/USBDemo/PIC32" -I"../../../Include" -I"C:/Library/Microchip/Harmony/v2_05_01/framework" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/include" -I"C:/Library/Microchip/Harmony/v2_05_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:\\Library\\Microchip\\Harmony\\v2_05_01/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSKDEPIC32PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\Library\Microchip\Harmony\v2_05_01\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=SKDEPIC32PlatformTool=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=1024,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:\\Library\\Microchip\\Harmony\\v2_05_01/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\Library\Microchip\Harmony\v2_05_01\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=1024,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/USBDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_USB_STARTER_KIT_I
	${RM} -r dist/PIC32_USB_STARTER_KIT_I

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
