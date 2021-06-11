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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DisplayDemo/Source/appMain.cpp ../../../Demo/DisplayDemo/Source/appApplication.cpp ../../../Demo/DisplayDemo/Source/appLedService.cpp ../../../Demo/DisplayDemo/Source/appDisplayService.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Circle.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/481076924/appInitialize.o ${OBJECTDIR}/_ext/480300606/appMain.o ${OBJECTDIR}/_ext/480300606/appApplication.o ${OBJECTDIR}/_ext/480300606/appLedService.o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ${OBJECTDIR}/_ext/212539067/FontTable.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/481076924/appInitialize.o.d ${OBJECTDIR}/_ext/480300606/appMain.o.d ${OBJECTDIR}/_ext/480300606/appApplication.o.d ${OBJECTDIR}/_ext/480300606/appLedService.o.d ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/346134360/halTMR.o.d ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d ${OBJECTDIR}/_ext/346134360/halGPIO.o.d ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d ${OBJECTDIR}/_ext/539928147/osalTask.o.d ${OBJECTDIR}/_ext/539928147/osalHeap.o.d ${OBJECTDIR}/_ext/539928147/osalKernel.o.d ${OBJECTDIR}/_ext/863068963/eosService.o.d ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d ${OBJECTDIR}/_ext/1127873614/main.o.d ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d ${OBJECTDIR}/_ext/1935080774/eosTask.o.d ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d ${OBJECTDIR}/_ext/212539067/FontTable.o.d ${OBJECTDIR}/_ext/1486223398/eosColor.o.d ${OBJECTDIR}/_ext/1486223398/eosFont.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d ${OBJECTDIR}/_ext/1486223398/eosRect.o.d ${OBJECTDIR}/_ext/1486223398/eosSize.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/1199125522/heap_4.o.d ${OBJECTDIR}/_ext/1871038939/port.o.d ${OBJECTDIR}/_ext/1871038939/port_asm.o.d ${OBJECTDIR}/_ext/690033423/tasks.o.d ${OBJECTDIR}/_ext/690033423/timers.o.d ${OBJECTDIR}/_ext/690033423/queue.o.d ${OBJECTDIR}/_ext/690033423/list.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/481076924/appInitialize.o ${OBJECTDIR}/_ext/480300606/appMain.o ${OBJECTDIR}/_ext/480300606/appApplication.o ${OBJECTDIR}/_ext/480300606/appLedService.o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/346134360/halTMR.o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ${OBJECTDIR}/_ext/346134360/halGPIO.o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ${OBJECTDIR}/_ext/539928147/osalTask.o ${OBJECTDIR}/_ext/539928147/osalHeap.o ${OBJECTDIR}/_ext/539928147/osalKernel.o ${OBJECTDIR}/_ext/863068963/eosService.o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ${OBJECTDIR}/_ext/1127873614/main.o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ${OBJECTDIR}/_ext/1935080774/eosTask.o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ${OBJECTDIR}/_ext/212539067/FontTable.o ${OBJECTDIR}/_ext/1486223398/eosColor.o ${OBJECTDIR}/_ext/1486223398/eosFont.o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ${OBJECTDIR}/_ext/1486223398/eosRect.o ${OBJECTDIR}/_ext/1486223398/eosSize.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/1199125522/heap_4.o ${OBJECTDIR}/_ext/1871038939/port.o ${OBJECTDIR}/_ext/1871038939/port_asm.o ${OBJECTDIR}/_ext/690033423/tasks.o ${OBJECTDIR}/_ext/690033423/timers.o ${OBJECTDIR}/_ext/690033423/queue.o ${OBJECTDIR}/_ext/690033423/list.o

# Source Files
SOURCEFILES=../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp ../../../Demo/DisplayDemo/Source/appMain.cpp ../../../Demo/DisplayDemo/Source/appApplication.cpp ../../../Demo/DisplayDemo/Source/appLedService.cpp ../../../Demo/DisplayDemo/Source/appDisplayService.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/HAL/PIC32/halTMR.c ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S ../../../Source/HAL/PIC32/halGPIO.c ../../../Source/OSAL/FreeRTOS/rtos_hooks.c ../../../Source/OSAL/FreeRTOS/osalTask.c ../../../Source/OSAL/FreeRTOS/osalHeap.c ../../../Source/OSAL/FreeRTOS/osalKernel.c ../../../Source/Services/eosService.cpp ../../../Source/Services/eosAppLoopService.cpp ../../../Source/StartUp/PIC32/main.cpp ../../../Source/System/Collections/eosContainer.cpp ../../../Source/System/Core/eosTask.cpp ../../../Source/System/Core/eosGlobalAlloc.cpp ../../../Source/System/Core/eosQueue.cpp ../../../Source/System/Core/eosHeapAllocator.cpp ../../../Source/System/Core/eosErrorHandler.cpp ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp ../../../Source/System/Graphics/Fonts/FontTable.cpp ../../../Source/System/Graphics/eosColor.cpp ../../../Source/System/Graphics/eosFont.cpp ../../../Source/System/Graphics/eosGraphics.cpp ../../../Source/System/Graphics/eosGraphics_Circle.cpp ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp ../../../Source/System/Graphics/eosGraphics_Line.cpp ../../../Source/System/Graphics/eosPoint.cpp ../../../Source/System/Graphics/eosRect.cpp ../../../Source/System/Graphics/eosSize.cpp ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp ../../../Source/System/Graphics/eosTransformation.cpp ../../../Source/System/Graphics/eosGraphics_Text.cpp ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../Library/PIC32/FreeRTOS/Source/tasks.c ../../../Library/PIC32/FreeRTOS/Source/timers.c ../../../Library/PIC32/FreeRTOS/Source/queue.c ../../../Library/PIC32/FreeRTOS/Source/list.c



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
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PINGUINO/c8d29bbb13e174489ff2a3e8eabfc45c105013c6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PINGUINO/80047a5a032b34f293453d51836042d777d4fda2 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o: ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S  .generated_files/flags/PINGUINO/39e1a57c2089885ef6d11422a18c156468b1b193 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.ok ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d"  -o ${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o ../../../Source/HAL/PIC32/halTMRInterruptWrapper.S -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d",--gdwarf-2 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.d" "${OBJECTDIR}/_ext/346134360/halTMRInterruptWrapper.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1871038939/port_asm.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  .generated_files/flags/PINGUINO/27df14fd58c1ba55ac5a89ea6fb9a3a2292af401 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port_asm.o.ok ${OBJECTDIR}/_ext/1871038939/port_asm.o.err 
	${MP_CPPC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -DHARDWARE_CUSTOM -MMD -MF "${OBJECTDIR}/_ext/1871038939/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1871038939/port_asm.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d",--gdwarf-2 -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1871038939/port_asm.o.d" "${OBJECTDIR}/_ext/1871038939/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PINGUINO/fff7afa559ffccf5aaea4c87314f22fdef96ce3b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PINGUINO/edb6a99da0b1910adb1e19eaf72638865dda65c4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PINGUINO/c17606d3b79bd333622c7013e9b4c400d33ad227 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PINGUINO/acf2e180602963a16c7e6d037a9f0bc30435a302 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PINGUINO/c57426bd03ef607a500152f4f90e1e992cd4b74 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PINGUINO/38ebc10e66244c99e8b0b327d5abdfae98729d26 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PINGUINO/5ce50d45983e717323488608409f3ff31ec32d5f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PINGUINO/9ec07f86628d9c88ca658beaf44e10435271406d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PINGUINO/422d619569773a1568b177ce4e4de0f7e367d768 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PINGUINO/47e53654b3a540fe4fd5d5e3c8a35e254840a55f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PINGUINO/b0553c572588b6cf0589ddc8f526736b38bc79d4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PINGUINO/8f18fd0ce9ebc2d37228a0761a5dd4d730a5ba6a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PINGUINO/437e64bf44441e7d317eca2e2280353c95bdba3b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PINGUINO/3eff27510e97aefca94b007d3d41b0f8bc63f89e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PINGUINO/922681b95ace9f693071bd43dd9ca3b6f2448a42 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PINGUINO/14db20a99fa318cd13080a06a6426d6ab1aa101b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PINGUINO/1b4f2af0007c9871efe1e8a623c20f1818fa2686 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PINGUINO/682ced2947236bc21fcdaeb1e0d0e1eb1694b281 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PINGUINO/60696349eeb4dd9443d0c78c8837b64cbef9e2ad .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PINGUINO/c865e869bb07c12296664eb601b78672b0526ea0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PINGUINO/a98fcf8dde4b073992af75e26e6092a79f73abae .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PINGUINO/5408bc647fbf779407eadeb0619997cce7bd0ac6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PINGUINO/cdefb104781b3d343c6ba2045276116b349a5f4b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PINGUINO/74311296b9144925726ccd9a7730220420d513ee .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PINGUINO/ee07e1339cc9e3802e50bbfcb16afdf1382c8958 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PINGUINO/4fd666cdf597befdee738ae0d6569b948007d9f4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PINGUINO/a84c1780d8d1c9211732f055cb03c6a454b187a4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  .generated_files/flags/PINGUINO/9203108b6fa39cbcc753359bb0b62c0523264c9c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  .generated_files/flags/PINGUINO/244a819138818e6ceb32de9c1ec148e7f64c78dc .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  .generated_files/flags/PINGUINO/22aee820cc066b9f69f0e7f6d9255eb15e7e11a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PINGUINO/27534b0c7bf54e7bad3b82444a99b382b5196a81 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  .generated_files/flags/PINGUINO/1d6d5140e02684c7a7be5e56668b0599dbd7fe57 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  .generated_files/flags/PINGUINO/43ee36a9ba8721b2d219a3e16c4622f211fdd762 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  .generated_files/flags/PINGUINO/4bcf62e540b202a58b43bf53f48d4bdf35fda91b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  .generated_files/flags/PINGUINO/c68ef62f38fdf7b3a5cc4353eb515e25dd84f408 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PINGUINO/40017d6843dfb2ad8245119ac58e15d5eca89a4c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PINGUINO/90ed8b145d6ef9564a852ed226037c5b3afbf720 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PINGUINO/d4910d6295b6eeface3c765389c95d0cd99274be .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PINGUINO/fbb26379fd23e742a19a507fa84ea70de7189927 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PINGUINO/7713f5635f76f4c05796cd84ebfa731908c56129 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PINGUINO/f6897c85f732c74d9a1c7e6c8f3d668af8e6a3b2 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PINGUINO/2d647b1b57ff8f8cec86037f95170e9f18be9cb0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PINGUINO/3b3ad090190f318e7858a57805ba6dcd10c0b17c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PINGUINO/9df3acc1c44d97016e639a5d7d5c7d3d0a8f07aa .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  .generated_files/flags/PINGUINO/7271990c874769506d3f0bd6f1ab780d55cc6327 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  .generated_files/flags/PINGUINO/7e4461ee3bb437ba0ef37bfa19ceca60d4b94b1 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  .generated_files/flags/PINGUINO/f29b93288d581025e21f1742732cf492b35dec2e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  .generated_files/flags/PINGUINO/23ebe3f68bb1d25dd60462432bb2260d5784bc94 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  .generated_files/flags/PINGUINO/acbafc85b99a6bc1e12a1f2d00f501e250de7afe .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  .generated_files/flags/PINGUINO/51b2b2cb53621a80bb4836d48cb5b97237242b5 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  .generated_files/flags/PINGUINO/d3cc48ac02d8fc3ec397e0af59692e44e7ca0971 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PINGUINO/60cceec273a1a6ea3cf8fe3075dbb8a156219533 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PINGUINO/41ee73ff18613dc0068c7e45909a7a04cde8894d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PINGUINO/74d3950802b7d1266594cef2b01347e2db08b451 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PINGUINO/592f1d26c1f333aad88d5f13c743e3608643a32e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  .generated_files/flags/PINGUINO/8a55ae306f20e5109edc360259ce3d938847fd81 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PINGUINO/3b6bc5167e36d74dc0d2539984ba39949786fd28 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PINGUINO/5a508a92e9650b2f153721ab4b140693f2f475f8 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PINGUINO/cdf5fcb70131e2530fddb224b2c12e17b82595b2 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PINGUINO/4214bd5672204356d3923819c39264ad8aa941b9 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PINGUINO/2ad84ed1aca3c8f9d8416679c78d1366c6a378ca .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PINGUINO/9a6fa31695baa42419976cda0023625f9aca5d65 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PINGUINO/19b1e2f628840e02080160907937aaa12ab6d16b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PINGUINO/740d25eeb4874b858abe435299a9ce1c42d7e13 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PINGUINO/7d05366cff7c11b6d146698aea93525490dfc499 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PINGUINO/aaf9b91783bdfe660f2e9f19e84bd93b76be1b7a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PINGUINO/e73de395cb63573d7ab8f6b910558e6dd8c07a7d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  .generated_files/flags/PINGUINO/ab3841ee8d1f2f6359f2c491a4961f8a086143ad .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  .generated_files/flags/PINGUINO/7de6f6b707e917236814e59c0df7f70161b8c42e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  .generated_files/flags/PINGUINO/ab59ea560232575233a1b33a14bd2fc5f726e01e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PINGUINO/c3d34c3fc6fb9a71c3c550d7485e799f8fec09e0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  .generated_files/flags/PINGUINO/18aa5986f262592b455e58fac32a1c0523ee3688 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  .generated_files/flags/PINGUINO/5a93b0bdf17e22b55e618c9dc50ea9bcf1e3ff43 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  .generated_files/flags/PINGUINO/16d8f6566bd4cd83113e70a016b0d6619d4fc75f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  .generated_files/flags/PINGUINO/860522c6ba76296dfd4298c1f12acb87ca1e7887 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PINGUINO/ad15ae6174acab2347d94c7173e25163802f1d95 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PINGUINO/549a19d7d12d22d32fac2dc25f346845fae9bfbf .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PINGUINO/d0085dba482327008518bc546a187ebada652fc0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PINGUINO/79c4d365611cf460ba1822ee37c2731fc120e119 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PINGUINO/812e31ff5df208f2e719ff07ddda5d3cd20d3b1d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PINGUINO/e7e8e4484e602f8ee339d1c4c07e23c48604a0c0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PINGUINO/67df050deab5fd7fdc1d432acac1b83d83aa061 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PINGUINO/2ac3034923d6b1fd4f25c952fe41a64e40080597 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PINGUINO/dd3ba7150b6ce5bcf9bdff508657e4f440a68c64 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  .generated_files/flags/PINGUINO/bdd701f3b5ad69a29c107e71a36163e421d72e17 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  .generated_files/flags/PINGUINO/36b17ca10771f6116bf758f8b295e43899763b31 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  .generated_files/flags/PINGUINO/dae9ad41e2a103e2150db8677403b03cd775a235 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  .generated_files/flags/PINGUINO/cac217a47c1f7b947c9b5e4fbd48a1129fe76dec .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  .generated_files/flags/PINGUINO/5fc24af1cfceed10fcfb0067bcd9efcb81bc8eef .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  .generated_files/flags/PINGUINO/4efd89dbc0ecbc8fe0b07452ee70ef4098808242 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  .generated_files/flags/PINGUINO/e15688bfcb5acd2f0782b4907743c498c36bad5 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PINGUINO/c19707fa352e48fc1370835e1e969bda1839efeb .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PINGUINO/7b81892af3b4b6d2eb478dc01840fb1f2650aebc .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PINGUINO/a24044ce00d9bd57d176ff8ef141e0dd6633d990 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PINGUINO/395f10ebece193574592dbfced5220ec4816f1d9 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  .generated_files/flags/PINGUINO/3ed9c53d0681d2eba7716be17eb8082213de5892 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PINGUINO/a0e60b688ccc3a7c2779b5c2f4a61e344a23b3ea .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PINGUINO/196f99b51dbd5fedfde05e25222c7251749173af .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PINGUINO/e986e0051ac3b20a6c51c266f432da1e4f9138b8 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PINGUINO/fface2e34b4ee94ba2da19124a3f345869b0e144 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PINGUINO/a1a8735a63e8c94d84b7fa9630553e1e9ae83666 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PINGUINO/79411d40d8f46a330b7e38b575b5020327a02949 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PINGUINO/5399b25e168d2141b6c17693798fb73d5524033b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PINGUINO/5b4a677c6103ef325821f4c39e7be2dd5f577bf0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PINGUINO/be799464685467a2b1a07ba52e1b96a536c5ebb9 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PINGUINO/d6ad481bd7fbe37e0c96fcbcdee07585a70827ac .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX440F256H_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX440F256H_peripherals.a     -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../Library/PIC32/Harmony/bin/framework/peripheral/PIC32MX440F256H_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/DisplayDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\Library\PIC32\Harmony\bin\framework\peripheral\PIC32MX440F256H_peripherals.a     -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2048,--defsym=_min_stack_size=2048,--no-check-sections,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml,--allow-multiple-definition -mdfp="${DFP_DIR}"
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
