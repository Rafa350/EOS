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
ifeq "$(wildcard nbproject/Makefile-local-PIC32MX_ESK.mk)" "nbproject/Makefile-local-PIC32MX_ESK.mk"
include nbproject/Makefile-local-PIC32MX_ESK.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32MX_ESK
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Main.c ../Config.c ../rtos_hooks.c ../DisplayService.c ../MnuMain.c ../../Source/Services/Forms/eosForms.c ../../Source/Services/Forms/eosFormsMenus.c ../../Source/Services/eosDigOutput.c ../../Source/Services/eosDigInput.c ../../Source/Services/eosI2CMaster.c ../../Source/Services/eosI2CMasterISRWrapper.S ../../Source/Services/eosTimer.c ../../Source/Services/eosAppLoop.c ../../Source/System/eosKernel.c ../../Source/System/eosHeap.c ../../Source/System/eosInterrupt.c ../../Source/System/eosQueue.c ../../Source/System/eosSemaphore.c ../../Source/System/eosPool.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c ../../Source/System/eosApplication.cpp ../../Source/System/eosTask.c ../../Source/System/eosProcess.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/DisplayService.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/241869326/eosForms.o ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o ${OBJECTDIR}/_ext/474813902/eosTimer.o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o ${OBJECTDIR}/_ext/1479454979/eosQueue.o ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o ${OBJECTDIR}/_ext/1479454979/eosPool.o ${OBJECTDIR}/_ext/1501210797/heap_4.o ${OBJECTDIR}/_ext/1208317312/port.o ${OBJECTDIR}/_ext/1208317312/port_asm.o ${OBJECTDIR}/_ext/565814006/list.o ${OBJECTDIR}/_ext/565814006/queue.o ${OBJECTDIR}/_ext/565814006/tasks.o ${OBJECTDIR}/_ext/565814006/timers.o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ${OBJECTDIR}/_ext/1479454979/eosTask.o ${OBJECTDIR}/_ext/1479454979/eosProcess.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/1472/DisplayService.o.d ${OBJECTDIR}/_ext/1472/MnuMain.o.d ${OBJECTDIR}/_ext/241869326/eosForms.o.d ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d ${OBJECTDIR}/_ext/474813902/eosTimer.o.d ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d ${OBJECTDIR}/_ext/1479454979/eosKernel.o.d ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d ${OBJECTDIR}/_ext/1479454979/eosQueue.o.d ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d ${OBJECTDIR}/_ext/1479454979/eosPool.o.d ${OBJECTDIR}/_ext/1501210797/heap_4.o.d ${OBJECTDIR}/_ext/1208317312/port.o.d ${OBJECTDIR}/_ext/1208317312/port_asm.o.d ${OBJECTDIR}/_ext/565814006/list.o.d ${OBJECTDIR}/_ext/565814006/queue.o.d ${OBJECTDIR}/_ext/565814006/tasks.o.d ${OBJECTDIR}/_ext/565814006/timers.o.d ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d ${OBJECTDIR}/_ext/1479454979/eosTask.o.d ${OBJECTDIR}/_ext/1479454979/eosProcess.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/DisplayService.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/241869326/eosForms.o ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o ${OBJECTDIR}/_ext/474813902/eosTimer.o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o ${OBJECTDIR}/_ext/1479454979/eosQueue.o ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o ${OBJECTDIR}/_ext/1479454979/eosPool.o ${OBJECTDIR}/_ext/1501210797/heap_4.o ${OBJECTDIR}/_ext/1208317312/port.o ${OBJECTDIR}/_ext/1208317312/port_asm.o ${OBJECTDIR}/_ext/565814006/list.o ${OBJECTDIR}/_ext/565814006/queue.o ${OBJECTDIR}/_ext/565814006/tasks.o ${OBJECTDIR}/_ext/565814006/timers.o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ${OBJECTDIR}/_ext/1479454979/eosTask.o ${OBJECTDIR}/_ext/1479454979/eosProcess.o

# Source Files
SOURCEFILES=../Main.c ../Config.c ../rtos_hooks.c ../DisplayService.c ../MnuMain.c ../../Source/Services/Forms/eosForms.c ../../Source/Services/Forms/eosFormsMenus.c ../../Source/Services/eosDigOutput.c ../../Source/Services/eosDigInput.c ../../Source/Services/eosI2CMaster.c ../../Source/Services/eosI2CMasterISRWrapper.S ../../Source/Services/eosTimer.c ../../Source/Services/eosAppLoop.c ../../Source/System/eosKernel.c ../../Source/System/eosHeap.c ../../Source/System/eosInterrupt.c ../../Source/System/eosQueue.c ../../Source/System/eosSemaphore.c ../../Source/System/eosPool.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c ../../Source/System/eosApplication.cpp ../../Source/System/eosTask.c ../../Source/System/eosProcess.cpp


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
	${MAKE}  -f nbproject/Makefile-PIC32MX_ESK.mk dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o: ../../Source/Services/eosI2CMasterISRWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.ok ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d" "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d"  -o ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o ../../Source/Services/eosI2CMasterISRWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1208317312/port_asm.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.ok ${OBJECTDIR}/_ext/1208317312/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port_asm.o.d" "${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1208317312/port_asm.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o: ../../Source/Services/eosI2CMasterISRWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.ok ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d" "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.d"  -o ${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o ../../Source/Services/eosI2CMasterISRWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/474813902/eosI2CMasterISRWrapper.o.asm.d",--gdwarf-2,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1208317312/port_asm.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port_asm.o.ok ${OBJECTDIR}/_ext/1208317312/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port_asm.o.d" "${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1208317312/port_asm.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1208317312/port_asm.o.asm.d",--gdwarf-2,-I"../" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c   
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1472/DisplayService.o: ../DisplayService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/DisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/DisplayService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/DisplayService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/DisplayService.o.d" -o ${OBJECTDIR}/_ext/1472/DisplayService.o ../DisplayService.c   
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c   
	
${OBJECTDIR}/_ext/241869326/eosForms.o: ../../Source/Services/Forms/eosForms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForms.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForms.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosForms.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosForms.o.d" -o ${OBJECTDIR}/_ext/241869326/eosForms.o ../../Source/Services/Forms/eosForms.c   
	
${OBJECTDIR}/_ext/241869326/eosFormsMenus.o: ../../Source/Services/Forms/eosFormsMenus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o ../../Source/Services/Forms/eosFormsMenus.c   
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.c   
	
${OBJECTDIR}/_ext/474813902/eosDigInput.o: ../../Source/Services/eosDigInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ../../Source/Services/eosDigInput.c   
	
${OBJECTDIR}/_ext/474813902/eosI2CMaster.o: ../../Source/Services/eosI2CMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ../../Source/Services/eosI2CMaster.c   
	
${OBJECTDIR}/_ext/474813902/eosTimer.o: ../../Source/Services/eosTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTimer.o.d" -o ${OBJECTDIR}/_ext/474813902/eosTimer.o ../../Source/Services/eosTimer.c   
	
${OBJECTDIR}/_ext/474813902/eosAppLoop.o: ../../Source/Services/eosAppLoop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ../../Source/Services/eosAppLoop.c   
	
${OBJECTDIR}/_ext/1479454979/eosKernel.o: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ../../Source/System/eosKernel.c   
	
${OBJECTDIR}/_ext/1479454979/eosHeap.o: ../../Source/System/eosHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ../../Source/System/eosHeap.c   
	
${OBJECTDIR}/_ext/1479454979/eosInterrupt.o: ../../Source/System/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o ../../Source/System/eosInterrupt.c   
	
${OBJECTDIR}/_ext/1479454979/eosQueue.o: ../../Source/System/eosQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosQueue.o ../../Source/System/eosQueue.c   
	
${OBJECTDIR}/_ext/1479454979/eosSemaphore.o: ../../Source/System/eosSemaphore.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o ../../Source/System/eosSemaphore.c   
	
${OBJECTDIR}/_ext/1479454979/eosPool.o: ../../Source/System/eosPool.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosPool.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosPool.o ../../Source/System/eosPool.c   
	
${OBJECTDIR}/_ext/1501210797/heap_4.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1501210797" 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" -o ${OBJECTDIR}/_ext/1501210797/heap_4.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1208317312/port.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port.o.d" -o ${OBJECTDIR}/_ext/1208317312/port.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/565814006/list.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/list.o.d" -o ${OBJECTDIR}/_ext/565814006/list.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/565814006/queue.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/queue.o.d" -o ${OBJECTDIR}/_ext/565814006/queue.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/565814006/tasks.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/tasks.o.d" -o ${OBJECTDIR}/_ext/565814006/tasks.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/565814006/timers.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/timers.o.d" -o ${OBJECTDIR}/_ext/565814006/timers.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1479454979/eosTask.o: ../../Source/System/eosTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosTask.o ../../Source/System/eosTask.c   
	
else
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.c   
	
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1472/DisplayService.o: ../DisplayService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/DisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/DisplayService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/DisplayService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/DisplayService.o.d" -o ${OBJECTDIR}/_ext/1472/DisplayService.o ../DisplayService.c   
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c   
	
${OBJECTDIR}/_ext/241869326/eosForms.o: ../../Source/Services/Forms/eosForms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForms.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForms.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosForms.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosForms.o.d" -o ${OBJECTDIR}/_ext/241869326/eosForms.o ../../Source/Services/Forms/eosForms.c   
	
${OBJECTDIR}/_ext/241869326/eosFormsMenus.o: ../../Source/Services/Forms/eosFormsMenus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsMenus.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsMenus.o ../../Source/Services/Forms/eosFormsMenus.c   
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.c   
	
${OBJECTDIR}/_ext/474813902/eosDigInput.o: ../../Source/Services/eosDigInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ../../Source/Services/eosDigInput.c   
	
${OBJECTDIR}/_ext/474813902/eosI2CMaster.o: ../../Source/Services/eosI2CMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ../../Source/Services/eosI2CMaster.c   
	
${OBJECTDIR}/_ext/474813902/eosTimer.o: ../../Source/Services/eosTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosTimer.o.d" -o ${OBJECTDIR}/_ext/474813902/eosTimer.o ../../Source/Services/eosTimer.c   
	
${OBJECTDIR}/_ext/474813902/eosAppLoop.o: ../../Source/Services/eosAppLoop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ../../Source/Services/eosAppLoop.c   
	
${OBJECTDIR}/_ext/1479454979/eosKernel.o: ../../Source/System/eosKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosKernel.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosKernel.o ../../Source/System/eosKernel.c   
	
${OBJECTDIR}/_ext/1479454979/eosHeap.o: ../../Source/System/eosHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosHeap.o ../../Source/System/eosHeap.c   
	
${OBJECTDIR}/_ext/1479454979/eosInterrupt.o: ../../Source/System/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosInterrupt.o ../../Source/System/eosInterrupt.c   
	
${OBJECTDIR}/_ext/1479454979/eosQueue.o: ../../Source/System/eosQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosQueue.o ../../Source/System/eosQueue.c   
	
${OBJECTDIR}/_ext/1479454979/eosSemaphore.o: ../../Source/System/eosSemaphore.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosSemaphore.o ../../Source/System/eosSemaphore.c   
	
${OBJECTDIR}/_ext/1479454979/eosPool.o: ../../Source/System/eosPool.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosPool.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosPool.o ../../Source/System/eosPool.c   
	
${OBJECTDIR}/_ext/1501210797/heap_4.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1501210797" 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1501210797/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1501210797/heap_4.o.d" -o ${OBJECTDIR}/_ext/1501210797/heap_4.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1208317312/port.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1208317312" 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1208317312/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1208317312/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1208317312/port.o.d" -o ${OBJECTDIR}/_ext/1208317312/port.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/565814006/list.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/list.o.d" -o ${OBJECTDIR}/_ext/565814006/list.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/565814006/queue.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/queue.o.d" -o ${OBJECTDIR}/_ext/565814006/queue.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/565814006/tasks.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/tasks.o.d" -o ${OBJECTDIR}/_ext/565814006/tasks.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/565814006/timers.o: C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/565814006" 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/565814006/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/565814006/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/565814006/timers.o.d" -o ${OBJECTDIR}/_ext/565814006/timers.o C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1479454979/eosTask.o: ../../Source/System/eosTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/framework" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosTask.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosTask.o ../../Source/System/eosTask.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1479454979/eosApplication.o: ../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ../../Source/System/eosApplication.cpp  
	
${OBJECTDIR}/_ext/1479454979/eosProcess.o: ../../Source/System/eosProcess.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosProcess.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosProcess.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosProcess.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosProcess.o ../../Source/System/eosProcess.cpp  
	
else
${OBJECTDIR}/_ext/1479454979/eosApplication.o: ../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ../../Source/System/eosApplication.cpp  
	
${OBJECTDIR}/_ext/1479454979/eosProcess.o: ../../Source/System/eosProcess.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosProcess.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosProcess.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosProcess.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_05/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosProcess.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosProcess.o ../../Source/System/eosProcess.cpp  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:/microchip/harmony/v1_05/bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v1_05\bin\framework\peripheral\PIC32MX795F512L_peripherals.a       -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  C:/microchip/harmony/v1_05/bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    C:\microchip\harmony\v1_05\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32MX_ESK
	${RM} -r dist/PIC32MX_ESK

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
