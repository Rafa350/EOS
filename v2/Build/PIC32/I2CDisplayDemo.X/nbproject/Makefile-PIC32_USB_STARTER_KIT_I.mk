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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/I2CDisplayDemo/Source/appMain.cpp ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp ../../../Source/HAL/PIC32/halI2C.c ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosService.cpp ../../../Source/Services/eosI2CMasterService.cpp ../../../Source/Services/eosTerminalService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosPoolAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1139265468/appInitialize.o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ${OBJECTDIR}/_ext/1013783234/appMain.o ${OBJECTDIR}/_ext/1013783234/appApplication.o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ${OBJECTDIR}/_ext/1013783234/appLedService.o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ${OBJECTDIR}/_ext/346134360/halI2C.o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1139265468/appInitialize.o.d ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d ${OBJECTDIR}/_ext/1013783234/appMain.o.d ${OBJECTDIR}/_ext/1013783234/appApplication.o.d ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d ${OBJECTDIR}/_ext/1013783234/appLedService.o.d ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d ${OBJECTDIR}/_ext/346134360/halI2C.o.d ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/690033423/list.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1139265468/appInitialize.o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ${OBJECTDIR}/_ext/1013783234/appMain.o ${OBJECTDIR}/_ext/1013783234/appApplication.o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ${OBJECTDIR}/_ext/1013783234/appLedService.o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ${OBJECTDIR}/_ext/346134360/halI2C.o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o

# Source Files
SOURCEFILES=../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/I2CDisplayDemo/Source/appMain.cpp ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp ../../../Source/HAL/PIC32/halI2C.c ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosService.cpp ../../../Source/Services/eosI2CMasterService.cpp ../../../Source/Services/eosTerminalService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosPoolAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c



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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o: ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f0a9f67b53c1b6dcdfcd0d43e508e84eefbb2f07 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -msoft-float -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/19b7361b2df3f67591fe53b44f5f43e0e0f33284 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -msoft-float -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o: ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/14c168113f2557f5cdd93ff619c1f9b0d8f35473 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -msoft-float -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/47b84c9a65da85dd47b1c39961969623b6c4e62c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -msoft-float -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halI2C.o: ../../../Source/HAL/PIC32/halI2C.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7c4847ae89ae948880c284eb7e717e012a3f5679 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2C.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halI2C.o.d" -o ${OBJECTDIR}/_ext/346134360/halI2C.o ../../../Source/HAL/PIC32/halI2C.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a2a8f9ef47a53751e59fb15b7f25236570c9c510 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bc74c3ac842bb88cd43f6ef04337e28f87c4ab5d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/93ef06181816e7d7bbd5bc16de7c330585da3145 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ec7d9f8e740922aa74730ef04633c4f38f8d10a1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d79a6bc0b6a66105ad24f49e8c0f3ccbac490710 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4c19b1cb6fe20e6084096227462caf24a1a21012 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/381f1ac4f29eef753b59f1331b654e96d4ee81ba .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9e3ed7c1e9f45ee99043e956f11a0443e85abb96 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/48d66d328bd7c1bbc0b0b89e0585b4d4aaff3d2d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/907ca6a7d56cc1a9d52b846ca0b2e224e8aa0154 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cb5cbcd07cca1f74831bfb4ab69dd940f554ab51 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/60202bf69fb76bbab4752431fae974d4810032a5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/358681110990d81030a4cd5db6fd1531e6f9c091 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5308e7ae7e733dec277ffc30d748323fbd580653 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9853f344eb406c8b7237012640a1a8cced93390e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halI2C.o: ../../../Source/HAL/PIC32/halI2C.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f5f6758d7f7d77b6296b9044c1ea5ec9bd10408 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halI2C.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halI2C.o.d" -o ${OBJECTDIR}/_ext/346134360/halI2C.o ../../../Source/HAL/PIC32/halI2C.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/169f9745c5b0d1ee51575bb2ac217f675705e4e7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6e58ac3f7b60b940c27f52ac105b6ba1f6e0dfca .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b049a13045a8d6ebd3dccbf05bc0eb764a6a2209 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/416263e96e5837f97eb84f1a21292a71ef57cc8e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/132705611869608a173bb32c33093fee68f556ff .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/93db98fa1274927ff0a606d2f9b9d02324254751 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/50669b8b95d5095479122ac488b2c75470b8f878 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/796a5bb3f5c1f2560ea1209cc27bb9f4febf6feb .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2709fded31c9be60725ddf91bbe25e8c1b0bb6c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/113eb64f7ff6c812b69dea30aa68ced8ba9968a8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1e420ed7cbc2411657703e8eb8d48fb541f7d4c8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/98a6be51219c2a1ae90046a245eb4be0152f1f5c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/61f6f0b417c5443599f58fd029570b335ca993b7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e166e057a018189dafda9c57f344c61cb415e31b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1cb8c9aeccb89b929ab73870c29a1afad006dfaa .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -msoft-float -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1139265468/appInitialize.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/69a3fdbd76d3188cd1a6c668b3cd12e7dbfaae4b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInitialize.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1139265468/appInterrupts.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/849fc2cb06d38010f42bae7e7c6cf38b4ad07899 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appMain.o: ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ad57f6c4b676f1feaffc7299082b7077c948163f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appMain.o.d" -o ${OBJECTDIR}/_ext/1013783234/appMain.o ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appApplication.o: ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/afd008ae0f4de3fa768ef546f6bfe642fd01ab31 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appApplication.o.d" -o ${OBJECTDIR}/_ext/1013783234/appApplication.o ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appDisplayService.o: ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/74a01589c4a2ae814dfd50a6365fb571f1469bbc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appLedService.o: ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fc749c36d0acb3de98e39a3cf8ff221c0900d831 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appLedService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appLedService.o ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o: ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/80708317311e0f0b1daefb8758551313ba76e6d5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o: ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1bf7d6d8dd6f6e4ba21e68fb881d6fa8faf4f320 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/316b5da453b5449fae33303f876d77c9c4338abc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/60076807451ba0c52de5b36877b375c8064d56d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o: ../../../Source/Services/eosI2CMasterService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8ad3ab377d3bac4192940a4f7551a42a75e6c6f8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ../../../Source/Services/eosI2CMasterService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTerminalService.o: ../../../Source/Services/eosTerminalService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2a3c2d0aef2653811f6eaf16733ff053e6f564c3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ../../../Source/Services/eosTerminalService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d3a8abf188627811c0dfca507ba777189d1850e1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/abbdb92b24dc9a31ed7a797c95475e6275b811b5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o: ../../../Source/System/Core/eosPoolAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b0801af14c383693a3e76b643d996a2ff96c30b3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ../../../Source/System/Core/eosPoolAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e65d52e43365baa75f4604c1839e81cfc429c79f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/89f53d39e569feca24401f7b656b855b196bdb87 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/24224c743bec8a14a4674c4e1f05180d2c2e147b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6640d806ac9ac2fa9ebfc2b2e04bbd5470d51f70 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6018a1a30fea701b7dddb93a48274fb533b376cf .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/16b3743b9babebf6c12720f4c704d3ebce93d892 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b9a5062b90fe950da14657c9b55cbbe27c63b868 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1139265468/appInitialize.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c306dc6d0ed3881b72818e1006dd97934ba5014b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInitialize.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1139265468/appInterrupts.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9ecf480f2059eb38ff7bbf34bb66ae23eb847a3f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appMain.o: ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5e667906002967be6e9b10d18597423132de79e6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appMain.o.d" -o ${OBJECTDIR}/_ext/1013783234/appMain.o ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appApplication.o: ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fd4374991f35b482a3fc5e0782d241c4454075d5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appApplication.o.d" -o ${OBJECTDIR}/_ext/1013783234/appApplication.o ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appDisplayService.o: ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1138df23fba284cde0f08865b3085927191d5b0e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appLedService.o: ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/757e54bb339cea6ee71a095d9f34d10133774530 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appLedService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appLedService.o ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o: ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d6de4e91813e38d881c8dcd5c53fd464c86edb2b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o: ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6980e73a196ae4acfabeb94d20a3096911526f05 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7b0cd4dd8e616f536cd43df5368f476d1669cd43 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/947f14e67f32af2647ce24765dee02dfdc8c360f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o: ../../../Source/Services/eosI2CMasterService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/af93e74c9a9cebdd1f0cb65b6536f858e26639a7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ../../../Source/Services/eosI2CMasterService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTerminalService.o: ../../../Source/Services/eosTerminalService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cc3b5de25a5bee3d38d50b7ecb47e94350e1b96d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ../../../Source/Services/eosTerminalService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b9d9d4d394212e88a91e2171f9ec3d963b3eb036 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3e25f67fe526ff1347cbed8f042a11cdd65e9000 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o: ../../../Source/System/Core/eosPoolAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/82489f5f13275b57912bf4b1697b3fc63ea7f6f3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ../../../Source/System/Core/eosPoolAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/67be179e821af79ef16d73db42c50411037c4b4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3e2675ba97582fbd162286a650f3b62bcf13575f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a6b81bf3ebe9dc197e180f63d7a7da5909ab412 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/245c172c85a0a06f8110a8d50394c67092dac1f1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/de959647f25d133fdfe7e11c3c4cad46858e72c2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/965427edc392c7281567c6f9232ebab99ceaa854 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/991f548fdc66e68e8822c7227e48a6896b39572e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a     -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a     -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/I2CDisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
