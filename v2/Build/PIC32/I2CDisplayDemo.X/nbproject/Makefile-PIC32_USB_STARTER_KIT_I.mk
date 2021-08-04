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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/I2CDisplayDemo/Source/appMain.cpp ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp ../../../Source/HAL/PIC32/halI2C.c ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosService.cpp ../../../Source/Services/eosI2CMasterService.cpp ../../../Source/Services/eosTerminalService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosPoolAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1139265468/appInitialize.o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ${OBJECTDIR}/_ext/1013783234/appMain.o ${OBJECTDIR}/_ext/1013783234/appApplication.o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ${OBJECTDIR}/_ext/1013783234/appLedService.o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ${OBJECTDIR}/_ext/346134360/halI2C.o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1139265468/appInitialize.o.d ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d ${OBJECTDIR}/_ext/1013783234/appMain.o.d ${OBJECTDIR}/_ext/1013783234/appApplication.o.d ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d ${OBJECTDIR}/_ext/1013783234/appLedService.o.d ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d ${OBJECTDIR}/_ext/346134360/halI2C.o.d ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/690033423/list.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1139265468/appInitialize.o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ${OBJECTDIR}/_ext/1013783234/appMain.o ${OBJECTDIR}/_ext/1013783234/appApplication.o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ${OBJECTDIR}/_ext/1013783234/appLedService.o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ${OBJECTDIR}/_ext/346134360/halI2C.o ${OBJECTDIR}/_ext/346134360/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/timers.o

# Source Files
SOURCEFILES=../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/I2CDisplayDemo/Source/appMain.cpp ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp ../../../Source/HAL/PIC32/halI2C.c ../../../Source/HAL/PIC32/halI2CInterruptWrapper.S ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosService.cpp ../../../Source/Services/eosI2CMasterService.cpp ../../../Source/Services/eosTerminalService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Core/eosPoolAllocator.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/timers.c



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
${OBJECTDIR}/_ext/1139265468/appInitialize.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d3e78b9bf296509804610fd5b760cef41c47b073 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInitialize.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1139265468/appInterrupts.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8518edddc8fac89a31484b14a086ff86660ea71d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appMain.o: ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/35d029018eb202810e5a2f6fe46e3d24ea188ef0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appMain.o.d" -o ${OBJECTDIR}/_ext/1013783234/appMain.o ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appApplication.o: ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/88434fc929e78d92bc0a2b687ff86eab42df8f8b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appApplication.o.d" -o ${OBJECTDIR}/_ext/1013783234/appApplication.o ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appDisplayService.o: ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ed35d54076f108b9aee9dce07b36d16b57eee634 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appLedService.o: ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c0a5acdadfa171738c738d02147f1778de6d94d5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appLedService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appLedService.o ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o: ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b71d8fdbf4a6696d60d1785f06bb8c5f4cb7f079 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o: ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e8cc0f78e1e729b7535abddddd9f5454a12886ba .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/754d173ff4e8baa9e14a80ef8ec206455141fffa .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/88dc2f6e2d4d1ce362d9790be77ec638aa5eb959 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o: ../../../Source/Services/eosI2CMasterService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/397a4b4b15419b87550473b361ec43521ffb58af .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ../../../Source/Services/eosI2CMasterService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTerminalService.o: ../../../Source/Services/eosTerminalService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/aea0a865871a5174a6b90633e1dd12dbf1f5ff6d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ../../../Source/Services/eosTerminalService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/50bd2b81190358bc8fdf020450378b3ead92b24e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o: ../../../Source/System/Core/eosPoolAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ecfe202ba415126b815e03ae5840df2138071bdc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ../../../Source/System/Core/eosPoolAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a6ab743105f4a7eedd59291643949de34d3b9661 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b2d6305e86eb57f8f0b0929adc36c37418b00661 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/790344d74b4a4966692121ce32dd5ec645f63fba .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ca76ee8c3f3735f18ebb94e7845b19a361a58fa .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9769be201fc0513f1f17034001fcd46eb0d8769 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/16dd888a5f1291a32b858e65cbbc128cbf638fe5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1a61b22b47eb10fbc589ac613f23d468a4b8ee6e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1139265468/appInitialize.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/860e9a7e8910a5aa978c3e7a3a4b5be1373e29d1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInitialize.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1139265468/appInterrupts.o: ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f3167c365443000a74ea2758d734034ccfcc7f5d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1139265468" 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1139265468/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1139265468/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1139265468/appInterrupts.o ../../../Demo/I2CDisplayDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appMain.o: ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/20cbad81a481aceb0d01f7ec5fa0a08b3052aeb4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appMain.o.d" -o ${OBJECTDIR}/_ext/1013783234/appMain.o ../../../Demo/I2CDisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appApplication.o: ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/58a2219d0fb2d30aab2bf2726163f091e055f6cc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appApplication.o.d" -o ${OBJECTDIR}/_ext/1013783234/appApplication.o ../../../Demo/I2CDisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appDisplayService.o: ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/39b9c166a5acf1a1d4081a9d300f91c4c57f36ed .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appDisplayService.o ../../../Demo/I2CDisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1013783234/appLedService.o: ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3047bcd8fb89f48898d6e74cff1390f608802fcc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1013783234" 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1013783234/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1013783234/appLedService.o.d" -o ${OBJECTDIR}/_ext/1013783234/appLedService.o ../../../Demo/I2CDisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o: ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d114cff9618afeb4b6164bfe172848a353266b33 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxDisplay.o ../../../Source/Controllers/SmartDisplay/eosGfxDisplay.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o: ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c0002da497df21848fdb9921a089f6151f68525b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1714805334" 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d 
	@${RM} ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o.d" -o ${OBJECTDIR}/_ext/1714805334/eosGfxCommandBuilder.o ../../../Source/Controllers/SmartDisplay/eosGfxCommandBuilder.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/70d9e64b7ac681ac293b27aac08aaf7f21640e78 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5f5cb6110b97721a1eb605e2a7d6c052a27cdfe6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o: ../../../Source/Services/eosI2CMasterService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9e02a56f9954600992aa8984ff9aedd58d814829 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMasterService.o ../../../Source/Services/eosI2CMasterService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTerminalService.o: ../../../Source/Services/eosTerminalService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b4a8b35b84f2b08dc2584411cd85af3b07394627 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTerminalService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTerminalService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTerminalService.o ../../../Source/Services/eosTerminalService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c1789e9b53b8b1eb82847baf53af8206cab76393 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o: ../../../Source/System/Core/eosPoolAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8d93e74f31970cfcb0f7841ebc9f3ae4b6a75751 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPoolAllocator.o ../../../Source/System/Core/eosPoolAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bab8cb22a6bf9678e47d903119c07e29923cf156 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e8dbe5a28e107920a8bceec6040303a6986171a1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/864ce98bcec37ff12ac5a3245697c48b72701029 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a9627d2644d0cfb11fa86098119419e3d8beb46 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8f865713593da898d7fa64a64266085661d22e5e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7a7062a047bf4bfc2df607178421764e64b5ca56 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/316ba1d550ccf548feecbd34abf82cf350e51968 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/I2CDisplayDemo/Include" -I"../../../Demo/I2CDisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../../MD-DSP04" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -std=c++17 -mdfp="${DFP_DIR}"  
	
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
