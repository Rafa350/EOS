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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DisplayDemo/Source/appMain.cpp ../../../Demo/DisplayDemo/Source/appApplication.cpp ../../../Demo/DisplayDemo/Source/appLedService.cpp ../../../Demo/DisplayDemo/Source/appDisplayService.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosString.cpp ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Circle.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/eosApplication.cpp ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/481076924/appInitialize.o ${OBJECTDIR}/_ext/480300606/appMain.o ${OBJECTDIR}/_ext/480300606/appApplication.o ${OBJECTDIR}/_ext/480300606/appLedService.o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosString.o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/212539067/FontTable.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/481076924/appInitialize.o.d ${OBJECTDIR}/_ext/480300606/appMain.o.d ${OBJECTDIR}/_ext/480300606/appApplication.o.d ${OBJECTDIR}/_ext/480300606/appLedService.o.d ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosList.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/1935080774/eosString.o.d ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d ${OBJECTDIR}/_ext/1486223398/eosColor.o.d ${OBJECTDIR}/_ext/1486223398/eosFont.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d ${OBJECTDIR}/_ext/1486223398/eosRect.o.d ${OBJECTDIR}/_ext/1486223398/eosSize.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/list.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d ${OBJECTDIR}/_ext/212539067/FontTable.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/481076924/appInitialize.o ${OBJECTDIR}/_ext/480300606/appMain.o ${OBJECTDIR}/_ext/480300606/appApplication.o ${OBJECTDIR}/_ext/480300606/appLedService.o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosList.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/1935080774/eosString.o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/212539067/FontTable.o

# Source Files
SOURCEFILES=../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DisplayDemo/Source/appMain.cpp ../../../Demo/DisplayDemo/Source/appApplication.cpp ../../../Demo/DisplayDemo/Source/appLedService.cpp ../../../Demo/DisplayDemo/Source/appDisplayService.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosList.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Core/eosString.cpp ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Circle.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/eosApplication.cpp ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp


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
	${MAKE}  -f nbproject/Makefile-PINGUINO.mk dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halSYS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/690033423/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c    -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appLedService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosString.o: ../../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosString.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosString.o ../../../Source/System/Core/eosString.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/FontTable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appLedService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127873614/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1156436454/eosList.o: ../../../Source/System/Collections/eosList.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1156436454/eosList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosList.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosList.o ../../../Source/System/Collections/eosList.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1935080774/eosString.o: ../../../Source/System/Core/eosString.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosString.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1935080774/eosString.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosString.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosString.o ../../../Source/System/Core/eosString.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/212539067/FontTable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -fdata-sections -mno-float -O1 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp   -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX440F256H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX440F256H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX440F256H_peripherals.a      -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
