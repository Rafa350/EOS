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
ifeq "$(wildcard nbproject/Makefile-local-PINGUINO.mk)" "nbproject/Makefile-local-PINGUINO.mk"
include nbproject/Makefile-local-PINGUINO.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PINGUINO
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Config.c ../rtos_hooks.c ../MnuMain.c ../Main.cpp ../appMainForm.cpp ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/eosFont.cpp ../../../Source/HAL/halSYS.c ../../../Source/HAL/halI2C.c ../../../Source/HAL/halI2CInterruptWrapper.S ../../../Source/Services/Forms/eosFormsDisplay.cpp ../../../Source/Services/Forms/eosForm.cpp ../../../Source/Services/Forms/eosFormsService.cpp ../../../Source/Services/Forms/eosNumericEditorForm.cpp ../../../Source/Services/Forms/eosOptionEditorForm.cpp ../../../Source/Services/Forms/eosMenuForm.cpp ../../../Source/Services/eosI2CMaster.cpp ../../../Source/Services/eosKeyboard.cpp ../../../Source/Services/eosSelector.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosStack.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosInterrupt.c ../../../Source/System/Core/eosPool.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosString.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/appMainForm.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/771906982/Consolas8pt.o ${OBJECTDIR}/_ext/771906982/Consolas10pt.o ${OBJECTDIR}/_ext/771906982/Consolas12pt.o ${OBJECTDIR}/_ext/771906982/Consolas14pt.o ${OBJECTDIR}/_ext/771906982/Consolas18pt.o ${OBJECTDIR}/_ext/771906982/Consolas24pt.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/2094700795/eosFont.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/55825582/halI2C.o ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o ${OBJECTDIR}/_ext/1286103517/eosForm.o ${OBJECTDIR}/_ext/1286103517/eosFormsService.o ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o ${OBJECTDIR}/_ext/863068963/eosKeyboard.o ${OBJECTDIR}/_ext/863068963/eosSelector.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosStack.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o ${OBJECTDIR}/_ext/1935080774/eosPool.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosString.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/696550819/heap_4.o ${OBJECTDIR}/_ext/1298945782/port.o ${OBJECTDIR}/_ext/1298945782/port_asm.o ${OBJECTDIR}/_ext/2129976512/list.o ${OBJECTDIR}/_ext/2129976512/queue.o ${OBJECTDIR}/_ext/2129976512/tasks.o ${OBJECTDIR}/_ext/2129976512/timers.o ${OBJECTDIR}/_ext/466955231/eosILI9341io.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/Config.o.d ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d ${OBJECTDIR}/_ext/1472/MnuMain.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1472/appMainForm.o.d ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d ${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d ${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d ${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d ${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d ${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d ${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d ${OBJECTDIR}/_ext/2094700795/eosFont.o.d ${OBJECTDIR}/_ext/55825582/halSYS.o.d ${OBJECTDIR}/_ext/55825582/halI2C.o.d ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d ${OBJECTDIR}/_ext/1286103517/eosForm.o.d ${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d ${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d ${OBJECTDIR}/_ext/863068963/eosSelector.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1156436454/eosStack.o.d ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d ${OBJECTDIR}/_ext/1935080774/eosPool.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosString.o.d ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/696550819/heap_4.o.d ${OBJECTDIR}/_ext/1298945782/port.o.d ${OBJECTDIR}/_ext/1298945782/port_asm.o.d ${OBJECTDIR}/_ext/2129976512/list.o.d ${OBJECTDIR}/_ext/2129976512/queue.o.d ${OBJECTDIR}/_ext/2129976512/tasks.o.d ${OBJECTDIR}/_ext/2129976512/timers.o.d ${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/Config.o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ${OBJECTDIR}/_ext/1472/MnuMain.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1472/appMainForm.o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ${OBJECTDIR}/_ext/771906982/Consolas8pt.o ${OBJECTDIR}/_ext/771906982/Consolas10pt.o ${OBJECTDIR}/_ext/771906982/Consolas12pt.o ${OBJECTDIR}/_ext/771906982/Consolas14pt.o ${OBJECTDIR}/_ext/771906982/Consolas18pt.o ${OBJECTDIR}/_ext/771906982/Consolas24pt.o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ${OBJECTDIR}/_ext/2094700795/eosFont.o ${OBJECTDIR}/_ext/55825582/halSYS.o ${OBJECTDIR}/_ext/55825582/halI2C.o ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o ${OBJECTDIR}/_ext/1286103517/eosForm.o ${OBJECTDIR}/_ext/1286103517/eosFormsService.o ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o ${OBJECTDIR}/_ext/863068963/eosKeyboard.o ${OBJECTDIR}/_ext/863068963/eosSelector.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1156436454/eosStack.o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o ${OBJECTDIR}/_ext/1935080774/eosPool.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosString.o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/696550819/heap_4.o ${OBJECTDIR}/_ext/1298945782/port.o ${OBJECTDIR}/_ext/1298945782/port_asm.o ${OBJECTDIR}/_ext/2129976512/list.o ${OBJECTDIR}/_ext/2129976512/queue.o ${OBJECTDIR}/_ext/2129976512/tasks.o ${OBJECTDIR}/_ext/2129976512/timers.o ${OBJECTDIR}/_ext/466955231/eosILI9341io.o

# Source Files
SOURCEFILES=../Config.c ../rtos_hooks.c ../MnuMain.c ../Main.cpp ../appMainForm.cpp ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp ../../../Source/Controllers/Display/eosDisplay.cpp ../../../Source/Controllers/Display/eosFont.cpp ../../../Source/HAL/halSYS.c ../../../Source/HAL/halI2C.c ../../../Source/HAL/halI2CInterruptWrapper.S ../../../Source/Services/Forms/eosFormsDisplay.cpp ../../../Source/Services/Forms/eosForm.cpp ../../../Source/Services/Forms/eosFormsService.cpp ../../../Source/Services/Forms/eosNumericEditorForm.cpp ../../../Source/Services/Forms/eosOptionEditorForm.cpp ../../../Source/Services/Forms/eosMenuForm.cpp ../../../Source/Services/eosI2CMaster.cpp ../../../Source/Services/eosKeyboard.cpp ../../../Source/Services/eosSelector.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Collections/eosStack.cpp ../../../Source/System/Collections/eosListImpl.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosHeap.cpp ../../../Source/System/Core/eosInterrupt.c ../../../Source/System/Core/eosPool.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosSemaphore.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosString.cpp ../../../Source/System/Core/eosTimer.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/eosApplication.cpp ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp


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
	${MAKE}  -f nbproject/Makefile-PINGUINO.mk dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F256H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o: ../../../Source/HAL/halI2CInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o ../../../Source/HAL/halI2CInterruptWrapper.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1298945782/port_asm.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.ok ${OBJECTDIR}/_ext/1298945782/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port_asm.o.d" "${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1298945782/port_asm.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o: ../../../Source/HAL/halI2CInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.ok ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d" "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o ../../../Source/HAL/halI2CInterruptWrapper.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/55825582/halI2CInterruptWrapper.o.asm.d",--gdwarf-2 -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1298945782/port_asm.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port_asm.o.ok ${OBJECTDIR}/_ext/1298945782/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port_asm.o.d" "${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1298945782/port_asm.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1298945782/port_asm.o.asm.d",--gdwarf-2 -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halI2C.o: ../../../Source/HAL/halI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halI2C.o.d" -o ${OBJECTDIR}/_ext/55825582/halI2C.o ../../../Source/HAL/halI2C.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosInterrupt.o: ../../../Source/System/Core/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o ../../../Source/System/Core/eosInterrupt.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/696550819/heap_4.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/696550819" 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/696550819/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/696550819/heap_4.o.d" -o ${OBJECTDIR}/_ext/696550819/heap_4.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1298945782/port.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port.o.d" -o ${OBJECTDIR}/_ext/1298945782/port.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/list.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/list.o.d" -o ${OBJECTDIR}/_ext/2129976512/list.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/queue.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/queue.o.d" -o ${OBJECTDIR}/_ext/2129976512/queue.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/tasks.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/tasks.o.d" -o ${OBJECTDIR}/_ext/2129976512/tasks.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/timers.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/timers.o.d" -o ${OBJECTDIR}/_ext/2129976512/timers.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/Config.o: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Config.o.d" -o ${OBJECTDIR}/_ext/1472/Config.o ../Config.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rtos_hooks.o: ../rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/rtos_hooks.o ../rtos_hooks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/MnuMain.o: ../MnuMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MnuMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MnuMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/MnuMain.o.d" -o ${OBJECTDIR}/_ext/1472/MnuMain.o ../MnuMain.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halSYS.o: ../../../Source/HAL/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halSYS.o.d" -o ${OBJECTDIR}/_ext/55825582/halSYS.o ../../../Source/HAL/halSYS.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/55825582/halI2C.o: ../../../Source/HAL/halI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/55825582" 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/55825582/halI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55825582/halI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/55825582/halI2C.o.d" -o ${OBJECTDIR}/_ext/55825582/halI2C.o ../../../Source/HAL/halI2C.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosInterrupt.o: ../../../Source/System/Core/eosInterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosInterrupt.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosInterrupt.o ../../../Source/System/Core/eosInterrupt.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/696550819/heap_4.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/696550819" 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/696550819/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/696550819/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/696550819/heap_4.o.d" -o ${OBJECTDIR}/_ext/696550819/heap_4.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1298945782/port.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1298945782" 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1298945782/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1298945782/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1298945782/port.o.d" -o ${OBJECTDIR}/_ext/1298945782/port.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/list.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/list.o.d" -o ${OBJECTDIR}/_ext/2129976512/list.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/list.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/queue.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/queue.o.d" -o ${OBJECTDIR}/_ext/2129976512/queue.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/queue.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/tasks.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/tasks.o.d" -o ${OBJECTDIR}/_ext/2129976512/tasks.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/tasks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2129976512/timers.o: ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2129976512" 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2129976512/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2129976512/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2129976512/timers.o.d" -o ${OBJECTDIR}/_ext/2129976512/timers.o ../../../../../../../../../../microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/timers.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/appMainForm.o: ../appMainForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appMainForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/appMainForm.o.d" -o ${OBJECTDIR}/_ext/1472/appMainForm.o ../appMainForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas8pt.o: ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas8pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas8pt.o ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas10pt.o: ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas10pt.o ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas12pt.o: ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas12pt.o ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas14pt.o: ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas14pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas14pt.o ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas18pt.o: ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas18pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas18pt.o ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas24pt.o: ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas24pt.o ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosFont.o: ../../../Source/Controllers/Display/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosFont.o ../../../Source/Controllers/Display/eosFont.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o: ../../../Source/Services/Forms/eosFormsDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o ../../../Source/Services/Forms/eosFormsDisplay.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosForm.o: ../../../Source/Services/Forms/eosForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosForm.o ../../../Source/Services/Forms/eosForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosFormsService.o: ../../../Source/Services/Forms/eosFormsService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosFormsService.o ../../../Source/Services/Forms/eosFormsService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o: ../../../Source/Services/Forms/eosNumericEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o ../../../Source/Services/Forms/eosNumericEditorForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o: ../../../Source/Services/Forms/eosOptionEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o ../../../Source/Services/Forms/eosOptionEditorForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosMenuForm.o: ../../../Source/Services/Forms/eosMenuForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o ../../../Source/Services/Forms/eosMenuForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosI2CMaster.o: ../../../Source/Services/eosI2CMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o ../../../Source/Services/eosI2CMaster.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosKeyboard.o: ../../../Source/Services/eosKeyboard.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d" -o ${OBJECTDIR}/_ext/863068963/eosKeyboard.o ../../../Source/Services/eosKeyboard.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosSelector.o: ../../../Source/Services/eosSelector.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosSelector.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosSelector.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosSelector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosSelector.o.d" -o ${OBJECTDIR}/_ext/863068963/eosSelector.o ../../../Source/Services/eosSelector.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosStack.o: ../../../Source/System/Collections/eosStack.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosStack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosStack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosStack.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosStack.o ../../../Source/System/Collections/eosStack.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosPool.o: ../../../Source/System/Core/eosPool.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPool.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPool.o ../../../Source/System/Core/eosPool.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosString.o: ../../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosString.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosString.o ../../../Source/System/Core/eosString.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341io.o: ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341io.o ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/Main.o: ../Main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d" -o ${OBJECTDIR}/_ext/1472/Main.o ../Main.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/appMainForm.o: ../appMainForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appMainForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appMainForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1472/appMainForm.o.d" -o ${OBJECTDIR}/_ext/1472/appMainForm.o ../appMainForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341.o ../../../Source/Controllers/Display/Drivers/eosILI9341.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas8pt.o: ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas8pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas8pt.o ../../../Source/Controllers/Display/Fonts/Consolas8pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas10pt.o: ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas10pt.o ../../../Source/Controllers/Display/Fonts/Consolas10pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas12pt.o: ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas12pt.o ../../../Source/Controllers/Display/Fonts/Consolas12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas14pt.o: ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas14pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas14pt.o ../../../Source/Controllers/Display/Fonts/Consolas14pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas18pt.o: ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas18pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas18pt.o ../../../Source/Controllers/Display/Fonts/Consolas18pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/771906982/Consolas24pt.o: ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/771906982" 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/771906982/Consolas24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/771906982/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/771906982/Consolas24pt.o ../../../Source/Controllers/Display/Fonts/Consolas24pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosDisplay.o: ../../../Source/Controllers/Display/eosDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosDisplay.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosDisplay.o ../../../Source/Controllers/Display/eosDisplay.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2094700795/eosFont.o: ../../../Source/Controllers/Display/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2094700795" 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/2094700795/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/2094700795/eosFont.o.d" -o ${OBJECTDIR}/_ext/2094700795/eosFont.o ../../../Source/Controllers/Display/eosFont.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o: ../../../Source/Services/Forms/eosFormsDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosFormsDisplay.o ../../../Source/Services/Forms/eosFormsDisplay.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosForm.o: ../../../Source/Services/Forms/eosForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosForm.o ../../../Source/Services/Forms/eosForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosFormsService.o: ../../../Source/Services/Forms/eosFormsService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosFormsService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosFormsService.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosFormsService.o ../../../Source/Services/Forms/eosFormsService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o: ../../../Source/Services/Forms/eosNumericEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosNumericEditorForm.o ../../../Source/Services/Forms/eosNumericEditorForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o: ../../../Source/Services/Forms/eosOptionEditorForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosOptionEditorForm.o ../../../Source/Services/Forms/eosOptionEditorForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1286103517/eosMenuForm.o: ../../../Source/Services/Forms/eosMenuForm.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1286103517" 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1286103517/eosMenuForm.o.d" -o ${OBJECTDIR}/_ext/1286103517/eosMenuForm.o ../../../Source/Services/Forms/eosMenuForm.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosI2CMaster.o: ../../../Source/Services/eosI2CMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosI2CMaster.o.d" -o ${OBJECTDIR}/_ext/863068963/eosI2CMaster.o ../../../Source/Services/eosI2CMaster.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosKeyboard.o: ../../../Source/Services/eosKeyboard.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosKeyboard.o.d" -o ${OBJECTDIR}/_ext/863068963/eosKeyboard.o ../../../Source/Services/eosKeyboard.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosSelector.o: ../../../Source/Services/eosSelector.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosSelector.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosSelector.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosSelector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/863068963/eosSelector.o.d" -o ${OBJECTDIR}/_ext/863068963/eosSelector.o ../../../Source/Services/eosSelector.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosStack.o: ../../../Source/System/Collections/eosStack.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosStack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosStack.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosStack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosStack.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosStack.o ../../../Source/System/Collections/eosStack.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosListImpl.o: ../../../Source/System/Collections/eosListImpl.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosListImpl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosListImpl.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosListImpl.o ../../../Source/System/Collections/eosListImpl.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeap.o: ../../../Source/System/Core/eosHeap.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeap.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeap.o ../../../Source/System/Core/eosHeap.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosPool.o: ../../../Source/System/Core/eosPool.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPool.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosPool.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosPool.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosPool.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosPool.o ../../../Source/System/Core/eosPool.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosSemaphore.o: ../../../Source/System/Core/eosSemaphore.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosSemaphore.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosSemaphore.o ../../../Source/System/Core/eosSemaphore.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosString.o: ../../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosString.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosString.o ../../../Source/System/Core/eosString.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTimer.o: ../../../Source/System/Core/eosTimer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTimer.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTimer.o ../../../Source/System/Core/eosTimer.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/466955231/eosILI9341io.o: ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/466955231" 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d 
	@${RM} ${OBJECTDIR}/_ext/466955231/eosILI9341io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../../Include" -I"C:/microchip/Harmony/v1_07_01/framework" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/include" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable" -I"C:/microchip/FreeRTOS/FreeRTOSv9.0.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_PINGUINO -MMD -MF "${OBJECTDIR}/_ext/466955231/eosILI9341io.o.d" -o ${OBJECTDIR}/_ext/466955231/eosILI9341io.o ../../../Source/Controllers/Display/Drivers/eosILI9341io.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/Harmony/v1_07_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\Harmony\v1_07_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../../../../microchip/Harmony/v1_07_01/bin/framework/peripheral/PIC32MX440F256H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\..\..\..\microchip\Harmony\v1_07_01\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FormsDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PINGUINO
	${RM} -r dist/PINGUINO

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
