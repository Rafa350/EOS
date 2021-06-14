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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o.d ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d ${OBJECTDIR}/_ext/2104168611/AppMain.o.d ${OBJECTDIR}/_ext/2104168611/appApplication.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halCN.o.d ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalMutex.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/618460187/heap_4.o.d ${OBJECTDIR}/_ext/152460360/port.o.d ${OBJECTDIR}/_ext/152460360/port_asm.o.d ${OBJECTDIR}/_ext/1745914046/list.o.d ${OBJECTDIR}/_ext/1745914046/queue.o.d ${OBJECTDIR}/_ext/1745914046/tasks.o.d ${OBJECTDIR}/_ext/1745914046/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o

# Source Files
SOURCEFILES=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c



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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d8e4ae62abbd89116d9f5b73adb5393449755af2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/804f8ec139e499cca950fe0264673b1e65bf9c16 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ce19f2a8f609ed7be3045632de69213a308c1629 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c627d30b2816e9ee8f4c0dfab118b886e1f84bc3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ff174e54ecd36c354c8d917455e036b291ee8d75 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1f0da5e723d6341096687ef501e72aea03a8175e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dfebd16a3050ac9e93001661b9c4397cc00e7cb9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7841ab2ec26b388d5d22f1c20bdf8d18e0c34760 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fbd6f5187dda62d8ecb7e7201f99d0f6c0804c55 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/69f53b051cc5e434eb493f1e34d2b3ab528684b4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9216eb36ace92ef319c2d2ae25433992dd05ed80 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/519ebd4e2961b26549ae2de537266cc1b0667e36 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bf0c38192a09af651b4ffc4199ba170838d4f1ad .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/412445c94445d10b0d4a3a8c5f630fba409ace4a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/59e9d784da6170769ec3681774e19121ff55a1f5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/aab3026dcc4e2fba93419a8573c3fdfa387a461f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fbf6df4fd5e7059638fd815d27c8eeee75c63eeb .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/465e912924b170151fbcb19ee039848b67a0df80 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2e54179e0a60711a41cc89a21d09fd2dbcaa019a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b5c0e7ab23c43ae2c3e9014a6c0ee79d33d28b08 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/39ccce266ab50c84d64439271d00b80b0dae957a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9d14d30dadba12548acd53c672956247c9988cd4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3ebc067fd303505eed52e9a5f8965d3821a3e381 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3a7c916a374ee9d25460775ec55f61feb945e525 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4d1da0e53709adfa267f45e4a72c40cc762f9f82 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/18ce369cd4740b8a3d5be346d60ba776bf66972 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8e07b4b9394698105aa8dda8d88f05049b2fcd66 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4825bbc3bcd36da426496c5be6514f3b3de45eb8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/58a9e876709205136e28984c25053f4a854421f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/84a0134cb4a774ac66f77a77c9d2835535cb3d6d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6eb834378f8b501c2aa0bf6d9a628f69e30b10aa .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6c58d3915cffc70b9c84bb7f273e97eb46531ed8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e82d21f0f78657666c8c4c8a8b4138f81bf8a18 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1070ba332b202dbe573fb73b6fc69221c064f5b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/99671649fffb0bb808f8e686dd754ad7186499a8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e3bceb7424be87e3ab446d918909eb8f6527d9fd .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ebbb8e11df259f24d5d4d8e9e2b7341c04fb97dd .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e9853820f318760d1e3924b98dbb9a488794a6f1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2f3cb1f34cbc638c632bb1e03c6ca93b6f57bad9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c610e0b274b3d61d80695a96c44684d1b678a5da .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b9b14fa1febac6d75ed1a4f87e427febd4c9316e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/128aa7e0f2c826ba23d7740a9d77323384cc9b53 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/53913ff9e5f7d4f1bf5f981f98b4415e1c53d1b0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/285f77770ea8d288de16b5c2b9219a1a7fcdd72b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1ce5647c43eddcc8a386d7cf52cb3c643c98ff8e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e1330768e7746e1b900e07b977fa82076a59126f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/571bb8ff95b109c2e4fdb546ff53f28d66aed256 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8eacccb1dda72e8e9a75828306217bf5d0c8a766 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f5d15c34942298f5eeb1f02e7b77d85484a8943f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3b1558c69827eb924f3c2fc46fc907e51de9a29e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8a20299306ebefb665e8e2670fe2ac28a9e6f226 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3ec7278faa0091cb6a00038128338a2f412e1288 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/28a8a6bde9135ca83f4c7f107f739b1c965a096c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a910d907ad9ba378236ab2be2510167df265ec3f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/61495aa945c634a9a5d450d6219992aaca9a2492 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b3a69e29f4f7a75aeaf79bae7e2716a0ac2ed2fc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/992e8dde5e7e2ea988b5cf31f3d6873772003f24 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d2f6adb8c8e5b827aba89e21218e50cc60632a4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/20e18f07f674cae2a5c527f312b2ad3be7224a00 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ee59029275b8ec14a9c77ff4ab1ad224043ecf3a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2a66b28f5c98e7c80e2aae2b1e20f2aa3c244b30 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a1334424c3a8fa2c386db5b1bfd65b1425a03542 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2513fa2df44f528382bc68acbdf8e023b6be9632 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bbb70eba77d054c9130b7941c0bb0d33807090df .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fc5380de84ce549a339c6af8799eb0b4a30907e7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3da224fa7b50400bf29060ea50b785d402690653 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fc6eed16db755cd9172f88cb088338b241087e8c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/93a1bb55f798935a22035d45564d41f524bd51d4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ccaedeac582e2c062ff2c37a92b450ba24ddc699 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e48349c12d95b1aededfd903d04b54f5d80430e6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/47af99eaba47c31a82cad2dce5c1cfaaaa424c51 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1a652546232a8ef8413e8bb63c84ce5999fb812e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c395aaf28b90599dcecb46aea7f04661ccbfffdc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/aa278a7e7c420ad3a63f223b062c3f25a9e1a1b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4973cf0fcbce53503cf018c3a4a5b953bc8bedf1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8a893e0f9ed9aef56412a92f21d63ce2b997d599 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/81d4eb12ab5e348504cf45c1ea4cb0e7eb1fa3f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bce8940a2c090d7ed49fb7726502c115b9b6528f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a4bdf44a2cd7c045232edeb9884e5e82300cadd3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a7d6c8475dc669cca21eada2ed597e9a7732015e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/919f7d0f628a4e27113d739dc6e54466e3049617 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8c00a282e3c3ec9ae02de11117ab699cfa98ad0a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9e74dfd10f739f294f855c5cd3bf161001cb0d9c .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/39eed08fa89d5d8307daf9f14bbdd4c653575c58 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c1170d7e45bc954fd62920587713295de32eaae .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d6d5eed2f4d9810dd1306d3580010dc92d82e377 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DxUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
