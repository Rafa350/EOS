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
ifeq "$(wildcard nbproject/Makefile-local-PIC32MX_USK.mk)" "nbproject/Makefile-local-PIC32MX_USK.mk"
include nbproject/Makefile-local-PIC32MX_USK.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32MX_USK
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
SOURCEFILES_QUOTED_IF_SPACED=../Config.c ../rtos_hooks.c ../MnuMain.c ../Main.cpp ../fsmMachine.cpp ../fsmStates.cpp ../appMainForm.cpp ../../Source/Controllers/eosDisplayController.cpp ../../Source/HAL/halGPIO.c ../../Source/HAL/halSYS.c ../../Source/HAL/halI2C.c ../../Source/HAL/halI2CInterruptWrapper.S ../../Source/Services/Forms/eosSelector.cpp ../../Source/Services/Forms/eosFormsDisplay.cpp ../../Source/Services/Forms/eosForm.cpp ../../Source/Services/Forms/eosFormsService.cpp ../../Source/Services/Forms/eosNumericEditorForm.cpp ../../Source/Services/Forms/eosOptionEditorForm.cpp ../../Source/Services/Forms/eosMenuForm.cpp ../../Source/Services/Forms/eosKeyboard.cpp ../../Source/Services/Fsm/eosStateMachine.cpp ../../Source/Services/Fsm/eosState.cpp ../../Source/Services/Fsm/eosFSM.cpp ../../Source/Services/eosAppLoop.cpp ../../Source/Services/eosDigOutput.cpp ../../Source/Services/eosDigInput.cpp ../../Source/Services/eosI2CMaster.cpp ../../Source/System/Collections/eosList.cpp ../../Source/System/Collections/eosQueue.cpp ../../Source/System/Collections/eosStack.cpp ../../Source/System/Collections/eosListImpl.cpp ../../Source/System/Core/eosGlobalAlloc.cpp ../../Source/System/Core/eosHeap.cpp ../../Source/System/Core/eosInterrupt.c ../../Source/System/Core/eosPool.cpp ../../Source/System/Core/eosTask.cpp ../../Source/System/Core/eosSemaphore.cpp ../../Source/System/Core/eosTimer.cpp ../../Source/System/Core/eosErrorHandler.cpp ../../Source/System/Core/eosString.cpp ../../Source/System/eosApplication.cpp ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/fsmMachine.o ${OBJECTDIR}/_ext/1472/fsmStates.o ${OBJECTDIR}/_ext/1472/appMainForm.o ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o ${OBJECTDIR}/_ext/313532353/halGPIO.o ${OBJECTDIR}/_ext/313532353/halSYS.o ${OBJECTDIR}/_ext/313532353/halI2C.o ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/241869326/eosSelector.o ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o ${OBJECTDIR}/_ext/241869326/eosForm.o ${OBJECTDIR}/_ext/241869326/eosFormsService.o ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o ${OBJECTDIR}/_ext/241869326/eosMenuForm.o ${OBJECTDIR}/_ext/241869326/eosKeyboard.o ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o ${OBJECTDIR}/_ext/1627065405/eosState.o ${OBJECTDIR}/_ext/1627065405/eosFSM.o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ${OBJECTDIR}/_ext/566062697/eosList.o ${OBJECTDIR}/_ext/566062697/eosQueue.o ${OBJECTDIR}/_ext/566062697/eosStack.o ${OBJECTDIR}/_ext/566062697/eosListImpl.o ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1507005109/eosHeap.o ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o ${OBJECTDIR}/_ext/1507005109/eosPool.o ${OBJECTDIR}/_ext/1507005109/eosTask.o ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o ${OBJECTDIR}/_ext/1507005109/eosTimer.o ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o ${OBJECTDIR}/_ext/1507005109/eosString.o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ${OBJECTDIR}/_ext/1504962773/heap_4.o ${OBJECTDIR}/_ext/1136849752/port.o ${OBJECTDIR}/_ext/1136849752/port_asm.o ${OBJECTDIR}/_ext/2118413774/list.o ${OBJECTDIR}/_ext/2118413774/queue.o ${OBJECTDIR}/_ext/2118413774/timers.o ${OBJECTDIR}/_ext/2118413774/tasks.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/1472/MnuMain.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/fsmMachine.o.d ${OBJECTDIR}/_ext/1472/fsmStates.o.d ${OBJECTDIR}/_ext/1472/appMainForm.o.d ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d ${OBJECTDIR}/_ext/313532353/halGPIO.o.d ${OBJECTDIR}/_ext/313532353/halSYS.o.d ${OBJECTDIR}/_ext/313532353/halI2C.o.d ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d ${OBJECTDIR}/_ext/241869326/eosSelector.o.d ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d ${OBJECTDIR}/_ext/241869326/eosForm.o.d ${OBJECTDIR}/_ext/241869326/eosFormsService.o.d ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d ${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d ${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d ${OBJECTDIR}/_ext/1627065405/eosState.o.d ${OBJECTDIR}/_ext/1627065405/eosFSM.o.d ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d ${OBJECTDIR}/_ext/566062697/eosList.o.d ${OBJECTDIR}/_ext/566062697/eosQueue.o.d ${OBJECTDIR}/_ext/566062697/eosStack.o.d ${OBJECTDIR}/_ext/566062697/eosListImpl.o.d ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1507005109/eosHeap.o.d ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d ${OBJECTDIR}/_ext/1507005109/eosPool.o.d ${OBJECTDIR}/_ext/1507005109/eosTask.o.d ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d ${OBJECTDIR}/_ext/1507005109/eosTimer.o.d ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1507005109/eosString.o.d ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d ${OBJECTDIR}/_ext/1504962773/heap_4.o.d ${OBJECTDIR}/_ext/1136849752/port.o.d ${OBJECTDIR}/_ext/1136849752/port_asm.o.d ${OBJECTDIR}/_ext/2118413774/list.o.d ${OBJECTDIR}/_ext/2118413774/queue.o.d ${OBJECTDIR}/_ext/2118413774/timers.o.d ${OBJECTDIR}/_ext/2118413774/tasks.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/fsmMachine.o ${OBJECTDIR}/_ext/1472/fsmStates.o ${OBJECTDIR}/_ext/1472/appMainForm.o ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o ${OBJECTDIR}/_ext/313532353/halGPIO.o ${OBJECTDIR}/_ext/313532353/halSYS.o ${OBJECTDIR}/_ext/313532353/halI2C.o ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/241869326/eosSelector.o ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o ${OBJECTDIR}/_ext/241869326/eosForm.o ${OBJECTDIR}/_ext/241869326/eosFormsService.o ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o ${OBJECTDIR}/_ext/241869326/eosMenuForm.o ${OBJECTDIR}/_ext/241869326/eosKeyboard.o ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o ${OBJECTDIR}/_ext/1627065405/eosState.o ${OBJECTDIR}/_ext/1627065405/eosFSM.o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ${OBJECTDIR}/_ext/566062697/eosList.o ${OBJECTDIR}/_ext/566062697/eosQueue.o ${OBJECTDIR}/_ext/566062697/eosStack.o ${OBJECTDIR}/_ext/566062697/eosListImpl.o ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1507005109/eosHeap.o ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o ${OBJECTDIR}/_ext/1507005109/eosPool.o ${OBJECTDIR}/_ext/1507005109/eosTask.o ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o ${OBJECTDIR}/_ext/1507005109/eosTimer.o ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o ${OBJECTDIR}/_ext/1507005109/eosString.o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ${OBJECTDIR}/_ext/1504962773/heap_4.o ${OBJECTDIR}/_ext/1136849752/port.o ${OBJECTDIR}/_ext/1136849752/port_asm.o ${OBJECTDIR}/_ext/2118413774/list.o ${OBJECTDIR}/_ext/2118413774/queue.o ${OBJECTDIR}/_ext/2118413774/timers.o ${OBJECTDIR}/_ext/2118413774/tasks.o

# Source Files
SOURCEFILES=../Config.c ../rtos_hooks.c ../MnuMain.c ../Main.cpp ../fsmMachine.cpp ../fsmStates.cpp ../appMainForm.cpp ../../Source/Controllers/eosDisplayController.cpp ../../Source/HAL/halGPIO.c ../../Source/HAL/halSYS.c ../../Source/HAL/halI2C.c ../../Source/HAL/halI2CInterruptWrapper.S ../../Source/Services/Forms/eosSelector.cpp ../../Source/Services/Forms/eosFormsDisplay.cpp ../../Source/Services/Forms/eosForm.cpp ../../Source/Services/Forms/eosFormsService.cpp ../../Source/Services/Forms/eosNumericEditorForm.cpp ../../Source/Services/Forms/eosOptionEditorForm.cpp ../../Source/Services/Forms/eosMenuForm.cpp ../../Source/Services/Forms/eosKeyboard.cpp ../../Source/Services/Fsm/eosStateMachine.cpp ../../Source/Services/Fsm/eosState.cpp ../../Source/Services/Fsm/eosFSM.cpp ../../Source/Services/eosAppLoop.cpp ../../Source/Services/eosDigOutput.cpp ../../Source/Services/eosDigInput.cpp ../../Source/Services/eosI2CMaster.cpp ../../Source/System/Collections/eosList.cpp ../../Source/System/Collections/eosQueue.cpp ../../Source/System/Collections/eosStack.cpp ../../Source/System/Collections/eosListImpl.cpp ../../Source/System/Core/eosGlobalAlloc.cpp ../../Source/System/Core/eosHeap.cpp ../../Source/System/Core/eosInterrupt.c ../../Source/System/Core/eosPool.cpp ../../Source/System/Core/eosTask.cpp ../../Source/System/Core/eosSemaphore.cpp ../../Source/System/Core/eosTimer.cpp ../../Source/System/Core/eosErrorHandler.cpp ../../Source/System/Core/eosString.cpp ../../Source/System/eosApplication.cpp ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c


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
	${MAKE}  -f nbproject/Makefile-PIC32MX_USK.mk dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o: ../../Source/HAL/halI2CInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o ../../Source/HAL/halI2CInterruptWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
${OBJECTDIR}/_ext/1136849752/port_asm.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1136849752" 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o.ok ${OBJECTDIR}/_ext/1136849752/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1136849752/port_asm.o.d" "${OBJECTDIR}/_ext/1136849752/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1136849752/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1136849752/port_asm.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1136849752/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
else
${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o: ../../Source/HAL/halI2CInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o ../../Source/HAL/halI2CInterruptWrapper.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/313532353/halI2CInterruptWrapper.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1136849752/port_asm.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1136849752" 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port_asm.o.ok ${OBJECTDIR}/_ext/1136849752/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1136849752/port_asm.o.d" "${OBJECTDIR}/_ext/1136849752/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1136849752/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1136849752/port_asm.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1136849752/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c   
	
${OBJECTDIR}/_ext/313532353/halGPIO.o: ../../Source/HAL/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halGPIO.o.d" -o ${OBJECTDIR}/_ext/313532353/halGPIO.o ../../Source/HAL/halGPIO.c   
	
${OBJECTDIR}/_ext/313532353/halSYS.o: ../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halSYS.o.d" -o ${OBJECTDIR}/_ext/313532353/halSYS.o ../../Source/HAL/halSYS.c   
	
${OBJECTDIR}/_ext/313532353/halI2C.o: ../../Source/HAL/halI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halI2C.o.d" -o ${OBJECTDIR}/_ext/313532353/halI2C.o ../../Source/HAL/halI2C.c   
	
${OBJECTDIR}/_ext/1507005109/eosInterrupt.o: ../../Source/System/Core/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o ../../Source/System/Core/eosInterrupt.c   
	
${OBJECTDIR}/_ext/1504962773/heap_4.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1504962773" 
	@${RM} ${OBJECTDIR}/_ext/1504962773/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1504962773/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1504962773/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1504962773/heap_4.o.d" -o ${OBJECTDIR}/_ext/1504962773/heap_4.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1136849752/port.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1136849752" 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1136849752/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1136849752/port.o.d" -o ${OBJECTDIR}/_ext/1136849752/port.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/2118413774/list.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/list.o.d" -o ${OBJECTDIR}/_ext/2118413774/list.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/2118413774/queue.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/queue.o.d" -o ${OBJECTDIR}/_ext/2118413774/queue.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/2118413774/timers.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/timers.o.d" -o ${OBJECTDIR}/_ext/2118413774/timers.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/2118413774/tasks.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/tasks.o.d" -o ${OBJECTDIR}/_ext/2118413774/tasks.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c   
	
else
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c   
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c   
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c   
	
${OBJECTDIR}/_ext/313532353/halGPIO.o: ../../Source/HAL/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halGPIO.o.d" -o ${OBJECTDIR}/_ext/313532353/halGPIO.o ../../Source/HAL/halGPIO.c   
	
${OBJECTDIR}/_ext/313532353/halSYS.o: ../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halSYS.o.d" -o ${OBJECTDIR}/_ext/313532353/halSYS.o ../../Source/HAL/halSYS.c   
	
${OBJECTDIR}/_ext/313532353/halI2C.o: ../../Source/HAL/halI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/313532353" 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/313532353/halI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/313532353/halI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/313532353/halI2C.o.d" -o ${OBJECTDIR}/_ext/313532353/halI2C.o ../../Source/HAL/halI2C.c   
	
${OBJECTDIR}/_ext/1507005109/eosInterrupt.o: ../../Source/System/Core/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosInterrupt.o ../../Source/System/Core/eosInterrupt.c   
	
${OBJECTDIR}/_ext/1504962773/heap_4.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1504962773" 
	@${RM} ${OBJECTDIR}/_ext/1504962773/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1504962773/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1504962773/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1504962773/heap_4.o.d" -o ${OBJECTDIR}/_ext/1504962773/heap_4.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c   
	
${OBJECTDIR}/_ext/1136849752/port.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1136849752" 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1136849752/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1136849752/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1136849752/port.o.d" -o ${OBJECTDIR}/_ext/1136849752/port.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/2118413774/list.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/list.o.d" -o ${OBJECTDIR}/_ext/2118413774/list.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/2118413774/queue.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/queue.o.d" -o ${OBJECTDIR}/_ext/2118413774/queue.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/2118413774/timers.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/timers.o.d" -o ${OBJECTDIR}/_ext/2118413774/timers.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/2118413774/tasks.o: ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118413774" 
	@${RM} ${OBJECTDIR}/_ext/2118413774/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118413774/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118413774/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -DHARDWARE_PIC32MX_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/2118413774/tasks.o.d" -o ${OBJECTDIR}/_ext/2118413774/tasks.o ../../../../../../../../../microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/tasks.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp  
	
${OBJECTDIR}/_ext/1472/fsmMachine.o: ../fsmMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fsmMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/fsmMachine.o.d" -o ${OBJECTDIR}/_ext/1472/fsmMachine.o ../fsmMachine.cpp  
	
${OBJECTDIR}/_ext/1472/fsmStates.o: ../fsmStates.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmStates.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmStates.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fsmStates.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/fsmStates.o.d" -o ${OBJECTDIR}/_ext/1472/fsmStates.o ../fsmStates.cpp  
	
${OBJECTDIR}/_ext/1472/appMainForm.o: ../appMainForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appMainForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/appMainForm.o.d" -o ${OBJECTDIR}/_ext/1472/appMainForm.o ../appMainForm.cpp  
	
${OBJECTDIR}/_ext/1640630781/eosDisplayController.o: ../../Source/Controllers/eosDisplayController.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1640630781" 
	@${RM} ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d" -o ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o ../../Source/Controllers/eosDisplayController.cpp  
	
${OBJECTDIR}/_ext/241869326/eosSelector.o: ../../Source/Services/Forms/eosSelector.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosSelector.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosSelector.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosSelector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosSelector.o.d" -o ${OBJECTDIR}/_ext/241869326/eosSelector.o ../../Source/Services/Forms/eosSelector.cpp  
	
${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o: ../../Source/Services/Forms/eosFormsDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o ../../Source/Services/Forms/eosFormsDisplay.cpp  
	
${OBJECTDIR}/_ext/241869326/eosForm.o: ../../Source/Services/Forms/eosForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosForm.o ../../Source/Services/Forms/eosForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosFormsService.o: ../../Source/Services/Forms/eosFormsService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsService.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsService.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsService.o ../../Source/Services/Forms/eosFormsService.cpp  
	
${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o: ../../Source/Services/Forms/eosNumericEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o ../../Source/Services/Forms/eosNumericEditorForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o: ../../Source/Services/Forms/eosOptionEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o ../../Source/Services/Forms/eosOptionEditorForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosMenuForm.o: ../../Source/Services/Forms/eosMenuForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosMenuForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosMenuForm.o ../../Source/Services/Forms/eosMenuForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosKeyboard.o: ../../Source/Services/Forms/eosKeyboard.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d" -o ${OBJECTDIR}/_ext/241869326/eosKeyboard.o ../../Source/Services/Forms/eosKeyboard.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosStateMachine.o: ../../Source/Services/Fsm/eosStateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o ../../Source/Services/Fsm/eosStateMachine.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosState.o: ../../Source/Services/Fsm/eosState.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosState.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosState.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosState.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosState.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosState.o ../../Source/Services/Fsm/eosState.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosFSM.o: ../../Source/Services/Fsm/eosFSM.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosFSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosFSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosFSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosFSM.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosFSM.o ../../Source/Services/Fsm/eosFSM.cpp  
	
${OBJECTDIR}/_ext/474813902/eosAppLoop.o: ../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ../../Source/Services/eosAppLoop.cpp  
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.cpp  
	
${OBJECTDIR}/_ext/474813902/eosDigInput.o: ../../Source/Services/eosDigInput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ../../Source/Services/eosDigInput.cpp  
	
${OBJECTDIR}/_ext/474813902/eosI2CMaster.o: ../../Source/Services/eosI2CMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ../../Source/Services/eosI2CMaster.cpp  
	
${OBJECTDIR}/_ext/566062697/eosList.o: ../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosList.o.d" -o ${OBJECTDIR}/_ext/566062697/eosList.o ../../Source/System/Collections/eosList.cpp  
	
${OBJECTDIR}/_ext/566062697/eosQueue.o: ../../Source/System/Collections/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosQueue.o.d" -o ${OBJECTDIR}/_ext/566062697/eosQueue.o ../../Source/System/Collections/eosQueue.cpp  
	
${OBJECTDIR}/_ext/566062697/eosStack.o: ../../Source/System/Collections/eosStack.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosStack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosStack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosStack.o.d" -o ${OBJECTDIR}/_ext/566062697/eosStack.o ../../Source/System/Collections/eosStack.cpp  
	
${OBJECTDIR}/_ext/566062697/eosListImpl.o: ../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/566062697/eosListImpl.o ../../Source/System/Collections/eosListImpl.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o: ../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o ../../Source/System/Core/eosGlobalAlloc.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosHeap.o: ../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosHeap.o ../../Source/System/Core/eosHeap.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosPool.o: ../../Source/System/Core/eosPool.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosPool.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosPool.o ../../Source/System/Core/eosPool.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosTask.o: ../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosTask.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosTask.o ../../Source/System/Core/eosTask.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosSemaphore.o: ../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o ../../Source/System/Core/eosSemaphore.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosTimer.o: ../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosTimer.o ../../Source/System/Core/eosTimer.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o: ../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o ../../Source/System/Core/eosErrorHandler.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosString.o: ../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosString.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosString.o ../../Source/System/Core/eosString.cpp  
	
${OBJECTDIR}/_ext/1479454979/eosApplication.o: ../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ../../Source/System/eosApplication.cpp  
	
else
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp  
	
${OBJECTDIR}/_ext/1472/fsmMachine.o: ../fsmMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fsmMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/fsmMachine.o.d" -o ${OBJECTDIR}/_ext/1472/fsmMachine.o ../fsmMachine.cpp  
	
${OBJECTDIR}/_ext/1472/fsmStates.o: ../fsmStates.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmStates.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fsmStates.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fsmStates.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/fsmStates.o.d" -o ${OBJECTDIR}/_ext/1472/fsmStates.o ../fsmStates.cpp  
	
${OBJECTDIR}/_ext/1472/appMainForm.o: ../appMainForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appMainForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1472/appMainForm.o.d" -o ${OBJECTDIR}/_ext/1472/appMainForm.o ../appMainForm.cpp  
	
${OBJECTDIR}/_ext/1640630781/eosDisplayController.o: ../../Source/Controllers/eosDisplayController.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1640630781" 
	@${RM} ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1640630781/eosDisplayController.o.d" -o ${OBJECTDIR}/_ext/1640630781/eosDisplayController.o ../../Source/Controllers/eosDisplayController.cpp  
	
${OBJECTDIR}/_ext/241869326/eosSelector.o: ../../Source/Services/Forms/eosSelector.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosSelector.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosSelector.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosSelector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosSelector.o.d" -o ${OBJECTDIR}/_ext/241869326/eosSelector.o ../../Source/Services/Forms/eosSelector.cpp  
	
${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o: ../../Source/Services/Forms/eosFormsDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsDisplay.o ../../Source/Services/Forms/eosFormsDisplay.cpp  
	
${OBJECTDIR}/_ext/241869326/eosForm.o: ../../Source/Services/Forms/eosForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosForm.o ../../Source/Services/Forms/eosForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosFormsService.o: ../../Source/Services/Forms/eosFormsService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsService.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosFormsService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosFormsService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosFormsService.o.d" -o ${OBJECTDIR}/_ext/241869326/eosFormsService.o ../../Source/Services/Forms/eosFormsService.cpp  
	
${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o: ../../Source/Services/Forms/eosNumericEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosNumericEditorForm.o ../../Source/Services/Forms/eosNumericEditorForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o: ../../Source/Services/Forms/eosOptionEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosOptionEditorForm.o ../../Source/Services/Forms/eosOptionEditorForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosMenuForm.o: ../../Source/Services/Forms/eosMenuForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosMenuForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosMenuForm.o.d" -o ${OBJECTDIR}/_ext/241869326/eosMenuForm.o ../../Source/Services/Forms/eosMenuForm.cpp  
	
${OBJECTDIR}/_ext/241869326/eosKeyboard.o: ../../Source/Services/Forms/eosKeyboard.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/241869326" 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/241869326/eosKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/241869326/eosKeyboard.o.d" -o ${OBJECTDIR}/_ext/241869326/eosKeyboard.o ../../Source/Services/Forms/eosKeyboard.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosStateMachine.o: ../../Source/Services/Fsm/eosStateMachine.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosStateMachine.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosStateMachine.o ../../Source/Services/Fsm/eosStateMachine.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosState.o: ../../Source/Services/Fsm/eosState.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosState.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosState.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosState.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosState.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosState.o ../../Source/Services/Fsm/eosState.cpp  
	
${OBJECTDIR}/_ext/1627065405/eosFSM.o: ../../Source/Services/Fsm/eosFSM.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1627065405" 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosFSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1627065405/eosFSM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1627065405/eosFSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1627065405/eosFSM.o.d" -o ${OBJECTDIR}/_ext/1627065405/eosFSM.o ../../Source/Services/Fsm/eosFSM.cpp  
	
${OBJECTDIR}/_ext/474813902/eosAppLoop.o: ../../Source/Services/eosAppLoop.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosAppLoop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosAppLoop.o.d" -o ${OBJECTDIR}/_ext/474813902/eosAppLoop.o ../../Source/Services/eosAppLoop.cpp  
	
${OBJECTDIR}/_ext/474813902/eosDigOutput.o: ../../Source/Services/eosDigOutput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigOutput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigOutput.o ../../Source/Services/eosDigOutput.cpp  
	
${OBJECTDIR}/_ext/474813902/eosDigInput.o: ../../Source/Services/eosDigInput.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosDigInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosDigInput.o.d" -o ${OBJECTDIR}/_ext/474813902/eosDigInput.o ../../Source/Services/eosDigInput.cpp  
	
${OBJECTDIR}/_ext/474813902/eosI2CMaster.o: ../../Source/Services/eosI2CMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474813902" 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/474813902/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/474813902/eosI2CMaster.o ../../Source/Services/eosI2CMaster.cpp  
	
${OBJECTDIR}/_ext/566062697/eosList.o: ../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosList.o.d" -o ${OBJECTDIR}/_ext/566062697/eosList.o ../../Source/System/Collections/eosList.cpp  
	
${OBJECTDIR}/_ext/566062697/eosQueue.o: ../../Source/System/Collections/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosQueue.o.d" -o ${OBJECTDIR}/_ext/566062697/eosQueue.o ../../Source/System/Collections/eosQueue.cpp  
	
${OBJECTDIR}/_ext/566062697/eosStack.o: ../../Source/System/Collections/eosStack.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosStack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosStack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosStack.o.d" -o ${OBJECTDIR}/_ext/566062697/eosStack.o ../../Source/System/Collections/eosStack.cpp  
	
${OBJECTDIR}/_ext/566062697/eosListImpl.o: ../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/566062697" 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/566062697/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/566062697/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/566062697/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/566062697/eosListImpl.o ../../Source/System/Collections/eosListImpl.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o: ../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosGlobalAlloc.o ../../Source/System/Core/eosGlobalAlloc.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosHeap.o: ../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosHeap.o ../../Source/System/Core/eosHeap.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosPool.o: ../../Source/System/Core/eosPool.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosPool.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosPool.o ../../Source/System/Core/eosPool.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosTask.o: ../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosTask.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosTask.o ../../Source/System/Core/eosTask.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosSemaphore.o: ../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosSemaphore.o ../../Source/System/Core/eosSemaphore.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosTimer.o: ../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosTimer.o ../../Source/System/Core/eosTimer.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o: ../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosErrorHandler.o ../../Source/System/Core/eosErrorHandler.cpp  
	
${OBJECTDIR}/_ext/1507005109/eosString.o: ../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1507005109" 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1507005109/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1507005109/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1507005109/eosString.o.d" -o ${OBJECTDIR}/_ext/1507005109/eosString.o ../../Source/System/Core/eosString.cpp  
	
${OBJECTDIR}/_ext/1479454979/eosApplication.o: ../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1479454979" 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1479454979/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-rtti -fexceptions -fno-check-new -fenforce-eh-specs -DHARDWARE_PIC32_USK -I"../" -I"../../Include" -I"C:/microchip/harmony/v1_06_01/framework" -I"C:/microchip/harmony/v1_06_01/third_party/rtos/FreeRTOS/Source/Include" -I"C:/microchip/harmony/v1_006_01/third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/1479454979/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1479454979/eosApplication.o ../../Source/System/eosApplication.cpp  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  c:/microchip/harmony/v1_06_01/bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    c:\microchip\harmony\v1_06_01\bin\framework\peripheral\PIC32MX795F512L_peripherals.a          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=0,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  c:/microchip/harmony/v1_06_01/bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    c:\microchip\harmony\v1_06_01\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32MX_USK
	${RM} -r dist/PIC32MX_USK

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
