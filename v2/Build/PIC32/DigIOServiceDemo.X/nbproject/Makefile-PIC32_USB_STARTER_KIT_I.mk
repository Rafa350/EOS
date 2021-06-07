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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o.d ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d ${OBJECTDIR}/_ext/2104168611/AppMain.o.d ${OBJECTDIR}/_ext/2104168611/appApplication.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halCN.o.d ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halINT.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTimer.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalQueue.o.d ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d ${OBJECTDIR}/_ext/539928147/osalMutex.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/618460187/heap_4.o.d ${OBJECTDIR}/_ext/152460360/port.o.d ${OBJECTDIR}/_ext/152460360/port_asm.o.d ${OBJECTDIR}/_ext/1745914046/list.o.d ${OBJECTDIR}/_ext/1745914046/queue.o.d ${OBJECTDIR}/_ext/1745914046/tasks.o.d ${OBJECTDIR}/_ext/1745914046/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1052343273/appInitialize.o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ${OBJECTDIR}/_ext/2104168611/AppMain.o ${OBJECTDIR}/_ext/2104168611/appApplication.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halINT.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTimer.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalQueue.o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ${OBJECTDIR}/_ext/539928147/osalMutex.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/618460187/heap_4.o ${OBJECTDIR}/_ext/152460360/port.o ${OBJECTDIR}/_ext/152460360/port_asm.o ${OBJECTDIR}/_ext/1745914046/list.o ${OBJECTDIR}/_ext/1745914046/queue.o ${OBJECTDIR}/_ext/1745914046/tasks.o ${OBJECTDIR}/_ext/1745914046/timers.o

# Source Files
SOURCEFILES=../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halINT.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTimer.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalQueue.c ../../../Source/OSAL/FreeRTOS/osalSemaphore.c ../../../Source/OSAL/FreeRTOS/osalMutex.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/Services/eosDigInputService.cpp ../../../Source/Services/eosDigOutputService.cpp ../../../Source/Services/eosTimerService.cpp ../../../Source/Services/eosDispatchService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/eosApplication.cpp ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c



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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ab0b2b806f7f07b004a92aa98f3258e2754deb0b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1088970da402a729f66fabcc61f040331b04a1b2 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cd793dc32d713b8a8ee6a65417d8e6215e2b9bb7 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/99d5400d9d0f18615a6a57eb57ccc94eca775b06 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/dea8b8385d211c32b68f4e211f17c95e28ad2dc5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/152460360/port_asm.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8b40b7eb4179dc8d676d2f26afa4334dfa994b10 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/152460360/port_asm.o.ok ${OBJECTDIR}/_ext/152460360/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/152460360/port_asm.o.d"  -o ${OBJECTDIR}/_ext/152460360/port_asm.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/152460360/port_asm.o.d" "${OBJECTDIR}/_ext/152460360/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6f0c48b0ddeb38d3fd2e353cbb19d4fdd11499 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7ecf5eb1170d083a6313334713787c73870d7b0a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2076cee6221e77bfcf74f1f5616178afa67d0e53 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/43c786c304b4b973ac6d59c2c15dd73cda94ad25 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2c265a189c54b4781d9735eece59d83732628ac0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/58036c5032a0032ff7efebdeed3129b46d9d4bdf .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f62429da6143281bb8c735fc3487501e90da56ea .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e4381168251131959ee3f93976942e370f7ccbde .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/869fb79303aed00244ca95180b1c601f6fcf5d3a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2222b8c27da7914df64b70fe27abbf3e41c20c3d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e9312d335c93f2920ccfcc2c10f63eb0872b7157 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/287a1782a449bd1f571b6164120308cfe165042 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5893712641d6bdf004d36d4141ff714ddab4cf3b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cd3e33e6496dd2562fc195f6f80cb8f210c5205b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9ea6d2a826de60706c92e2e8fef415ffc7e09d3f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8fdcd1c0ce49f5247b299714318a23385cf7abed .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/c943c2da8e25393b5bf64e3db1ca236a2f942f1a .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ce85812e9d794ad3ed5d5e6f8c614b547f69f5dd .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a1fa9a65a610f9cb4529f4f6383382636f40f825 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e665f727f599c014795299739e074ade06ccf6da .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cc038b1f08ff11cc4310dcf360fb0fd215bbc7c6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/241511c28c0821e672c197f8715fe984d001ffa5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a3db1ba20baf593e226ba1d6ea6644faab871e9b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halINT.o: ../../../Source/HAL/PIC32/halINT.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d1af1abdaeed4efa2097732feddb63e1bd77e9ca .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halINT.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halINT.o.d" -o ${OBJECTDIR}/_ext/346134360/halINT.o ../../../Source/HAL/PIC32/halINT.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ab8607810e13d09b81626e7c535afbac6dea2bdb .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTimer.o: ../../../Source/OSAL/FreeRTOS/osalTimer.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/aef4fcbd4f39aef53614756f909c59c31bfcccd0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTimer.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTimer.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTimer.o ../../../Source/OSAL/FreeRTOS/osalTimer.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ce5be7785a4cd88295924844ab667cf1a451b4f8 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d12c552f99a818a146728b360bdf5e1713b3f2cf .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b737aa79bde62fcb8f717412c5dd07fee3f38db9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalQueue.o: ../../../Source/OSAL/FreeRTOS/osalQueue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2e61cf43aa3aa8c84c63769a71e56728e0eb3db5 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalQueue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalQueue.o.d" -o ${OBJECTDIR}/_ext/539928147/osalQueue.o ../../../Source/OSAL/FreeRTOS/osalQueue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalSemaphore.o: ../../../Source/OSAL/FreeRTOS/osalSemaphore.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3a3b0cc7d51d9670f5c2d630068cd704728e873f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalSemaphore.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalSemaphore.o.d" -o ${OBJECTDIR}/_ext/539928147/osalSemaphore.o ../../../Source/OSAL/FreeRTOS/osalSemaphore.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalMutex.o: ../../../Source/OSAL/FreeRTOS/osalMutex.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/39c6426ffd8745cde7fbd52ac2f17f0e2d2eff5e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalMutex.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalMutex.o.d" -o ${OBJECTDIR}/_ext/539928147/osalMutex.o ../../../Source/OSAL/FreeRTOS/osalMutex.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/618460187/heap_4.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3347908aca28f8c78213cda00101997c81c7a842 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/618460187" 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/618460187/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/618460187/heap_4.o.d" -o ${OBJECTDIR}/_ext/618460187/heap_4.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/152460360/port.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/92ea0f20a94c5cf4d797b1ba6084fbe0653b956f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/152460360" 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/152460360/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/152460360/port.o.d" -o ${OBJECTDIR}/_ext/152460360/port.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/list.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/eda399c6a9fa53c88ab2bc939c96a5000232ca2f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/list.o.d" -o ${OBJECTDIR}/_ext/1745914046/list.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/queue.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8f003588471b93edb883740010f3b9d9d318c2dc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/queue.o.d" -o ${OBJECTDIR}/_ext/1745914046/queue.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/tasks.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/3ad051ab7ebf6a4ff3101ad7818ab7cfa20b974f .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/tasks.o.d" -o ${OBJECTDIR}/_ext/1745914046/tasks.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745914046/timers.o: ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c  .generated_files/flags/PIC32_USB_STARTER_KIT_I/18255668188804c72f856fa5d211d286bc219f80 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1745914046" 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745914046/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MP -MMD -MF "${OBJECTDIR}/_ext/1745914046/timers.o.d" -o ${OBJECTDIR}/_ext/1745914046/timers.o ../../../Library/PIC32/Harmony/third_party/rtos/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2deb22e703837dbd3f6d0a7942126e9255425bbd .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a72bf7779cabc60af0311737e753e1a1ca72e35d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8ec969cab9ab8c5483a4e2aea19a56d65ce87c52 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5e9bdabc3597602dc893d264a7205a113f681100 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f7a525ccc77f16f8afd7c1755b67efbd286163a3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e902df0824d24363ff1e2f2827f4e7e43dcad8ba .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cdd255a0c6956574e658f9de3f17c83637ac96ac .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8c8359046a1c0e3249fbd5fca8341306bd6c123e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cf221fa6f73b0441204fd4fc842698d85a4f193e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a24b21134977de3457f60d4d18088aba4fa99ab0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/17615dd00d3e7cb8d8eaf91314eb85fad75bf461 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6ced9c96ce4eae7dafc717ed593dd53151f7cc87 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/4824e017cd5c0bc9b2602c4dbddc2accc878c278 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/fdedfc3ccc7785900919a4ebff1e9d2a3db450f3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/2b230636b3b09212804dad45e48aede09b7173a0 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/427433ae6ff88596adf6a56be2566a122b9745d4 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e836333f19dd5625a8b848999bc80f9c707de719 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/754fd1197dd09428806f31ba3b474b12e2eb1ca9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/cd19b2c38beadcdfaa2454030fbf5e53a5dcb375 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/a4843ed95bc92af53a268f36029ce2439d84adb1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1052343273/appInitialize.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/d1319419eefa58c34315c71b33d7dbd3fc814600 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInitialize.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInitialize.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1052343273/appInterrupts.o: ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/135e3c3eb52d6364c851c0e7dd58bb0ecec6a7d1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1052343273" 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1052343273/appInterrupts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1052343273/appInterrupts.o.d" -o ${OBJECTDIR}/_ext/1052343273/appInterrupts.o ../../../Demo/DigIOServiceDemo/Source/PIC32/appInterrupts.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/AppMain.o: ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/395dd3d0eabf77bde091f5d283387726ae2f2b19 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/AppMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/AppMain.o.d" -o ${OBJECTDIR}/_ext/2104168611/AppMain.o ../../../Demo/DigIOServiceDemo/Source/AppMain.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2104168611/appApplication.o: ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/6ea7fbc27cea4be868f9212a1b27d1f80586900d .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2104168611" 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/2104168611/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/2104168611/appApplication.o.d" -o ${OBJECTDIR}/_ext/2104168611/appApplication.o ../../../Demo/DigIOServiceDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/91f30fc290b253e4a6a6f4b5b2ee57bca38494de .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/b85d682da7cd1632da5f085bb1832ca0bef7ebf9 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigInputService.o: ../../../Source/Services/eosDigInputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/7daf4bc343dfd0c85316d09662113e0dbbfbe55e .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInputService.o ../../../Source/Services/eosDigInputService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDigOutputService.o: ../../../Source/Services/eosDigOutputService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/34339b899a95f515e64a3414eea4619fd4bcd9c6 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutputService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutputService.o ../../../Source/Services/eosDigOutputService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosTimerService.o: ../../../Source/Services/eosTimerService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f3f725080fae7a043cbd8e6e3dda6c8f63e232b1 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosTimerService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosTimerService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosTimerService.o ../../../Source/Services/eosTimerService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosDispatchService.o: ../../../Source/Services/eosDispatchService.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f4946dcf17d0d63fda4c956ad4f7982b08876cce .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDispatchService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDispatchService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDispatchService.o ../../../Source/Services/eosDispatchService.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/e2a244384997d862cf1e7c8f38eb76111dba7aee .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/f0020b1bcf0a6b3d416a806ab85a9c7d0d072c45 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/1cab8d695062f914473334cea03e9370297903f3 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/8ca98def45443f6da2fdb010ebd34f2284a0035 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/bbe640d9f806dd4796f4514308917e82f7c6ea64 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/9f56efe035e4ebdde9c6135a6cddd93051d8e294 .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/ec206df10d743a8a9f8867b41e0d5d9830d7a0dc .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/16bd69297c98b3637437f7a7a22d4c827c99027b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5522069b9e1b436297bcf7888a1065a497891cda .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_USB_STARTER_KIT_I/5b1ba0f750b11f007b30466b539eb2471d9d466b .generated_files/flags/PIC32_USB_STARTER_KIT_I/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServiceDemo/Include" -I"../../../Demo/DigIOServiceDemo/Include/PIC32" -I"../../../Include" -I"../../../Source" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -DUSE_STD_STRINGS -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a     -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServiceDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX460F512L_peripherals.a     -relaxed-math -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
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
