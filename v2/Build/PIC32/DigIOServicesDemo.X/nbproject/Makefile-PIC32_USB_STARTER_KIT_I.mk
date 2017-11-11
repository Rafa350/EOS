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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DigIOServicesDemo/PIC32/Main.cpp ../../../Demo/DigIOServicesDemo/AppMain.cpp ../../../Demo/DigIOServicesDemo/rtos_hooks.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/Services/eosDigOutput.cpp ../../../Source/Services/eosDigInput.cpp ../../../Source/Services/eosExtInterrupt.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Source/OSAL/osalThread.c ../../../Source/OSAL/osalMemory.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/477420410/Main.o ${OBJECTDIR}/_ext/616935668/AppMain.o ${OBJECTDIR}/_ext/616935668/rtos_hooks.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/863068963/eosDigOutput.o ${OBJECTDIR}/_ext/863068963/eosDigInput.o ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1545219271/tasks.o ${OBJECTDIR}/_ext/1545219271/queue.o ${OBJECTDIR}/_ext/1545219271/list.o ${OBJECTDIR}/_ext/1545219271/timers.o ${OBJECTDIR}/_ext/1204364548/heap_4.o ${OBJECTDIR}/_ext/1683326351/port.o ${OBJECTDIR}/_ext/1683326351/port_asm.o ${OBJECTDIR}/_ext/1730818612/osalThread.o ${OBJECTDIR}/_ext/1730818612/osalMemory.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/477420410/Main.o.d ${OBJECTDIR}/_ext/616935668/AppMain.o.d ${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halCN.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d ${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d ${OBJECTDIR}/_ext/863068963/eosDigInput.o.d ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1545219271/tasks.o.d ${OBJECTDIR}/_ext/1545219271/queue.o.d ${OBJECTDIR}/_ext/1545219271/list.o.d ${OBJECTDIR}/_ext/1545219271/timers.o.d ${OBJECTDIR}/_ext/1204364548/heap_4.o.d ${OBJECTDIR}/_ext/1683326351/port.o.d ${OBJECTDIR}/_ext/1683326351/port_asm.o.d ${OBJECTDIR}/_ext/1730818612/osalThread.o.d ${OBJECTDIR}/_ext/1730818612/osalMemory.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/477420410/Main.o ${OBJECTDIR}/_ext/616935668/AppMain.o ${OBJECTDIR}/_ext/616935668/rtos_hooks.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halCN.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ${OBJECTDIR}/_ext/863068963/eosDigOutput.o ${OBJECTDIR}/_ext/863068963/eosDigInput.o ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1545219271/tasks.o ${OBJECTDIR}/_ext/1545219271/queue.o ${OBJECTDIR}/_ext/1545219271/list.o ${OBJECTDIR}/_ext/1545219271/timers.o ${OBJECTDIR}/_ext/1204364548/heap_4.o ${OBJECTDIR}/_ext/1683326351/port.o ${OBJECTDIR}/_ext/1683326351/port_asm.o ${OBJECTDIR}/_ext/1730818612/osalThread.o ${OBJECTDIR}/_ext/1730818612/osalMemory.o

# Source Files
SOURCEFILES=../../../Demo/DigIOServicesDemo/PIC32/Main.cpp ../../../Demo/DigIOServicesDemo/AppMain.cpp ../../../Demo/DigIOServicesDemo/rtos_hooks.c ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halCNInterruptWrapper.S ../../../Source/HAL/PIC32/halCN.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoop.cpp ../../../Source/Services/eosDigOutput.cpp ../../../Source/Services/eosDigInput.cpp ../../../Source/Services/eosExtInterrupt.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Source/OSAL/osalThread.c ../../../Source/OSAL/osalMemory.c


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
	${MAKE}  -f nbproject/Makefile-PIC32_USB_STARTER_KIT_I.mk dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -DSKDEPIC32PlatformTool=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=SKDEPIC32PlatformTool=1 -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1683326351/port_asm.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.ok ${OBJECTDIR}/_ext/1683326351/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port_asm.o.d" "${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -DSKDEPIC32PlatformTool=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1683326351/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1683326351/port_asm.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=SKDEPIC32PlatformTool=1 -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o: ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o ../../../Source/HAL/PIC32/halCNInterruptWrapper.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halCNInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1683326351/port_asm.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port_asm.o.ok ${OBJECTDIR}/_ext/1683326351/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port_asm.o.d" "${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1683326351/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1683326351/port_asm.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1683326351/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/616935668/rtos_hooks.o: ../../../Demo/DigIOServicesDemo/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616935668" 
	@${RM} ${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/616935668/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/616935668/rtos_hooks.o ../../../Demo/DigIOServicesDemo/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/tasks.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/tasks.o.d" -o ${OBJECTDIR}/_ext/1545219271/tasks.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/queue.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/queue.o.d" -o ${OBJECTDIR}/_ext/1545219271/queue.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/list.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/list.o.d" -o ${OBJECTDIR}/_ext/1545219271/list.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/timers.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/timers.o.d" -o ${OBJECTDIR}/_ext/1545219271/timers.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1204364548/heap_4.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1204364548" 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" -o ${OBJECTDIR}/_ext/1204364548/heap_4.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1683326351/port.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1683326351/port.o.d" -o ${OBJECTDIR}/_ext/1683326351/port.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1730818612/osalThread.o: ../../../Source/OSAL/osalThread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalThread.o ../../../Source/OSAL/osalThread.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1730818612/osalMemory.o: ../../../Source/OSAL/osalMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalMemory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalMemory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalMemory.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalMemory.o ../../../Source/OSAL/osalMemory.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/616935668/rtos_hooks.o: ../../../Demo/DigIOServicesDemo/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616935668" 
	@${RM} ${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/616935668/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/616935668/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/616935668/rtos_hooks.o ../../../Demo/DigIOServicesDemo/rtos_hooks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/346134360/halCN.o: ../../../Source/HAL/PIC32/halCN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halCN.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halCN.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/346134360/halCN.o.d" -o ${OBJECTDIR}/_ext/346134360/halCN.o ../../../Source/HAL/PIC32/halCN.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/tasks.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/tasks.o.d" -o ${OBJECTDIR}/_ext/1545219271/tasks.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/tasks.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/queue.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/queue.o.d" -o ${OBJECTDIR}/_ext/1545219271/queue.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/queue.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/list.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/list.o.d" -o ${OBJECTDIR}/_ext/1545219271/list.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/list.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1545219271/timers.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1545219271" 
	@${RM} ${OBJECTDIR}/_ext/1545219271/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1545219271/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1545219271/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1545219271/timers.o.d" -o ${OBJECTDIR}/_ext/1545219271/timers.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/timers.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1204364548/heap_4.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1204364548" 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1204364548/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1204364548/heap_4.o.d" -o ${OBJECTDIR}/_ext/1204364548/heap_4.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MemMang/heap_4.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1683326351/port.o: ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1683326351" 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1683326351/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1683326351/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1683326351/port.o.d" -o ${OBJECTDIR}/_ext/1683326351/port.o ../../../../../../../../../../Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1730818612/osalThread.o: ../../../Source/OSAL/osalThread.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalThread.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalThread.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalThread.o ../../../Source/OSAL/osalThread.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1730818612/osalMemory.o: ../../../Source/OSAL/osalMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1730818612" 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1730818612/osalMemory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1730818612/osalMemory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1730818612/osalMemory.o.d" -o ${OBJECTDIR}/_ext/1730818612/osalMemory.o ../../../Source/OSAL/osalMemory.c    -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/477420410/Main.o: ../../../Demo/DigIOServicesDemo/PIC32/Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/477420410" 
	@${RM} ${OBJECTDIR}/_ext/477420410/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/477420410/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/477420410/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/477420410/Main.o.d" -o ${OBJECTDIR}/_ext/477420410/Main.o ../../../Demo/DigIOServicesDemo/PIC32/Main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/616935668/AppMain.o: ../../../Demo/DigIOServicesDemo/AppMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616935668" 
	@${RM} ${OBJECTDIR}/_ext/616935668/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/616935668/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616935668/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/616935668/AppMain.o.d" -o ${OBJECTDIR}/_ext/616935668/AppMain.o ../../../Demo/DigIOServicesDemo/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosDigOutput.o: ../../../Source/Services/eosDigOutput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutput.o ../../../Source/Services/eosDigOutput.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosDigInput.o: ../../../Source/Services/eosDigInput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInput.o ../../../Source/Services/eosDigInput.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o: ../../../Source/Services/eosExtInterrupt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d" -o ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o ../../../Source/Services/eosExtInterrupt.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/477420410/Main.o: ../../../Demo/DigIOServicesDemo/PIC32/Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/477420410" 
	@${RM} ${OBJECTDIR}/_ext/477420410/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/477420410/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/477420410/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/477420410/Main.o.d" -o ${OBJECTDIR}/_ext/477420410/Main.o ../../../Demo/DigIOServicesDemo/PIC32/Main.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/616935668/AppMain.o: ../../../Demo/DigIOServicesDemo/AppMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/616935668" 
	@${RM} ${OBJECTDIR}/_ext/616935668/AppMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/616935668/AppMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/616935668/AppMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/616935668/AppMain.o.d" -o ${OBJECTDIR}/_ext/616935668/AppMain.o ../../../Demo/DigIOServicesDemo/AppMain.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoop.o: ../../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoop.o ../../../Source/Services/eosAppLoop.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosDigOutput.o: ../../../Source/Services/eosDigOutput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigOutput.o ../../../Source/Services/eosDigOutput.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosDigInput.o: ../../../Source/Services/eosDigInput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/863068963/eosDigInput.o ../../../Source/Services/eosDigInput.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o: ../../../Source/Services/eosExtInterrupt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o.d" -o ${OBJECTDIR}/_ext/863068963/eosExtInterrupt.o ../../../Source/Services/eosExtInterrupt.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DigIOServicesDemo" -I"../../../Demo/DigIOServicesDemo/PIC32" -I"../../../Include" -I"c:/Library/Microchip/Harmony/v1.9/framework" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/include" -I"c:/Library/Microchip/FreeRTOS/v9.0.0/Source/portable/MPLAB/PIC32MX" -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -mno-float -funroll-loops -fomit-frame-pointer -DHARDWARE_PIC32_USB_STARTER_KIT_I -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../Library/Microchip/Harmony/v1.9/bin/framework/peripheral/PIC32MX460F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSKDEPIC32PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\Library\Microchip\Harmony\v1.9\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=SKDEPIC32PlatformTool=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../Library/Microchip/Harmony/v1.9/bin/framework/peripheral/PIC32MX460F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\Library\Microchip\Harmony\v1.9\bin\framework\peripheral\PIC32MX460F512L_peripherals.a      -DXPRJ_PIC32_USB_STARTER_KIT_I=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DigIOServicesDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
