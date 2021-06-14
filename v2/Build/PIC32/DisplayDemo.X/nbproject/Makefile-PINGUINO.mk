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
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PINGUINO/f574f5b706fe36d0acf3b6781f9425ec14af3e5 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PINGUINO/978794c58b86e1505495e1ba31861ea3092a9f5f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PINGUINO/36a2da7aeacd011dfae3d43c96a64a1aa4750997 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PINGUINO/1c844213397ccc766ad4c7af2dbffdbfb91f92d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PINGUINO/d65ee4d22cbd0169ca96ca438954cd38db6289d .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PINGUINO/dcc399a605e8be8cd706fe2d7ff6b48578113a1f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PINGUINO/b92b66c23b79c96ecb5397b0ad5b51ca70371bff .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PINGUINO/c341dc337bfacf35f2b275b7bcf26fd962396883 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PINGUINO/d571c398e385ce2d57a08786b553951dc0684128 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PINGUINO/38a682977af5c7224f43b0848c0b21ed83ce464a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PINGUINO/c35a0698d207c6271a82c7e92bb0f8ff21d9e820 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PINGUINO/683940fee6430927acc46bb4e3893cf69b2eee09 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PINGUINO/fbb596e113d24e62f87af618c5a259cbee83abe1 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PINGUINO/91fea40227dd0c8c6492dd7621a3dd4498d335e6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halTMR.o: ../../../Source/HAL/PIC32/halTMR.c  .generated_files/flags/PINGUINO/951ff43fe464d958119c2ec6f9a7ce5df6f676b4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halTMR.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halTMR.o.d" -o ${OBJECTDIR}/_ext/346134360/halTMR.o ../../../Source/HAL/PIC32/halTMR.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/346134360/halGPIO.o: ../../../Source/HAL/PIC32/halGPIO.c  .generated_files/flags/PINGUINO/6d1b21eb54ccc480876e83aad6f3ff5b2349a7ad .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halGPIO.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halGPIO.o.d" -o ${OBJECTDIR}/_ext/346134360/halGPIO.o ../../../Source/HAL/PIC32/halGPIO.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/rtos_hooks.o: ../../../Source/OSAL/FreeRTOS/rtos_hooks.c  .generated_files/flags/PINGUINO/6b7e489f65b0030169b53bb1f91dd49b34d010fa .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/rtos_hooks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/539928147/rtos_hooks.o ../../../Source/OSAL/FreeRTOS/rtos_hooks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalTask.o: ../../../Source/OSAL/FreeRTOS/osalTask.c  .generated_files/flags/PINGUINO/59143c145c6d8addb7d0f047a70a7fcf5cc31c07 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalTask.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalTask.o.d" -o ${OBJECTDIR}/_ext/539928147/osalTask.o ../../../Source/OSAL/FreeRTOS/osalTask.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalHeap.o: ../../../Source/OSAL/FreeRTOS/osalHeap.c  .generated_files/flags/PINGUINO/b70d0d49fee24294b3f3562e19f56b2cab2885f8 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalHeap.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalHeap.o.d" -o ${OBJECTDIR}/_ext/539928147/osalHeap.o ../../../Source/OSAL/FreeRTOS/osalHeap.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/539928147/osalKernel.o: ../../../Source/OSAL/FreeRTOS/osalKernel.c  .generated_files/flags/PINGUINO/17570aeb43081d77e2c9b46ba38972f604a968c0 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/539928147" 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/539928147/osalKernel.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/539928147/osalKernel.o.d" -o ${OBJECTDIR}/_ext/539928147/osalKernel.o ../../../Source/OSAL/FreeRTOS/osalKernel.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1199125522/heap_4.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c  .generated_files/flags/PINGUINO/5512d099983690b76cb1200ac72ae9e4e79b850a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1199125522" 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1199125522/heap_4.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1199125522/heap_4.o.d" -o ${OBJECTDIR}/_ext/1199125522/heap_4.o ../../../Library/PIC32/FreeRTOS/Source/portable/MemMang/heap_4.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1871038939/port.o: ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  .generated_files/flags/PINGUINO/e748b4379ecf891ec7d84cc9019263c889a974c6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1871038939" 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1871038939/port.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1871038939/port.o.d" -o ${OBJECTDIR}/_ext/1871038939/port.o ../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/tasks.o: ../../../Library/PIC32/FreeRTOS/Source/tasks.c  .generated_files/flags/PINGUINO/7818e2e52fe1522ee50d4c506f8af0a18f8cac1a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/tasks.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/tasks.o.d" -o ${OBJECTDIR}/_ext/690033423/tasks.o ../../../Library/PIC32/FreeRTOS/Source/tasks.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/timers.o: ../../../Library/PIC32/FreeRTOS/Source/timers.c  .generated_files/flags/PINGUINO/95b464c8babc7906e54075b4a78bea0a7dd2afac .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/timers.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/timers.o.d" -o ${OBJECTDIR}/_ext/690033423/timers.o ../../../Library/PIC32/FreeRTOS/Source/timers.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/queue.o: ../../../Library/PIC32/FreeRTOS/Source/queue.c  .generated_files/flags/PINGUINO/92b1324e936e90c1bad3587b31ed40f4739c5a4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/queue.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/queue.o.d" -o ${OBJECTDIR}/_ext/690033423/queue.o ../../../Library/PIC32/FreeRTOS/Source/queue.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/690033423/list.o: ../../../Library/PIC32/FreeRTOS/Source/list.c  .generated_files/flags/PINGUINO/3fc519f1a733353adae187d502261495895b97eb .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/690033423" 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/690033423/list.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -fno-common -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/690033423/list.o.d" -o ${OBJECTDIR}/_ext/690033423/list.o ../../../Library/PIC32/FreeRTOS/Source/list.c   -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PINGUINO/4e6b313021e9b20cd3e452b9eb3eced10b777afb .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  .generated_files/flags/PINGUINO/1d5ed1b6a70650f85262201e0cfe0100016455f3 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  .generated_files/flags/PINGUINO/7d3bae2ab97f38a47c6260940f45c6c3c5c694d1 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  .generated_files/flags/PINGUINO/d256413cc9cfabe2da29baa6ab765baddf3bc6c9 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PINGUINO/85cdf4826f3068dbf4f3e07dc6faeae5ff38f7ef .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  .generated_files/flags/PINGUINO/357d40cb7ee0c15ee96cbca72be78b512e4eff74 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  .generated_files/flags/PINGUINO/85adfb0e38e5aa630813595b77fd35bd53e86a44 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  .generated_files/flags/PINGUINO/ff7039aebaf2954b4a9d3c33ef897cac5794eb91 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  .generated_files/flags/PINGUINO/d2ae6bab73f1d1b3e0942f389df1fa5bec9c30aa .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PINGUINO/683b2cea45524e8249eb7408c0f51d862da76bf4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PINGUINO/915f33f3ba2f25b814fd3fa3b3f1a3135f9c65de .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PINGUINO/66749d808625691069b08181da872335f6212498 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PINGUINO/b0057639ea73a4a27404d3e8eabae3872562555b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PINGUINO/28bcafe98788de855767431f9d72f1cedc618120 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PINGUINO/90ebd7189e22719cda4937f2547b3ed3a839e363 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PINGUINO/727adebab3cbe3eea5306cbdfe94f39d482784a3 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PINGUINO/f353a457862bc688c6e48bcd1cf9ab0c16030058 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PINGUINO/7903056139caaa722b6d252548d041bf5f91ee49 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  .generated_files/flags/PINGUINO/fc286273ca5a3de75c65569b85264409db8593c9 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  .generated_files/flags/PINGUINO/7bcd0f9097ae224174638f141f5c13e56190d189 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  .generated_files/flags/PINGUINO/20c9c7c8a0a08720f133e26dc5afac3e163cbd29 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  .generated_files/flags/PINGUINO/52807984d6b6765c3e0b76218a5d3df0481f9589 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  .generated_files/flags/PINGUINO/10ca17bc3352fb1684de53091f0fa12cf341f375 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  .generated_files/flags/PINGUINO/a839e8e0f0f56b02cc613c4cab362e9b0aa82624 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  .generated_files/flags/PINGUINO/3db8eb04ff63abc7ad751b5f06c5e177935a7bcd .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PINGUINO/b5b88897271c0a513dcffe1940dd0967cb280f7b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PINGUINO/47035d4b9756a4190eebf97e103a5634ef7124b4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PINGUINO/8d8bb6fd8c8eccf2915298ae767bbccbff54b814 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PINGUINO/4c836b50d7fc9733d98df953dee086134af51af4 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  .generated_files/flags/PINGUINO/4758fde2f3d13a7bf1d72d5fc16f34f3f83b177f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PINGUINO/7484c506cd61c7dbc59986bd5d64045f8b6aa0ff .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PINGUINO/fa51faddd02a60fdf2765b5ed135c7b683b5de2c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PINGUINO/40b3cd18a48255f85fe9d4cbbb41a62563fab18 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PINGUINO/e3bc198b1ce2321e0d34e0a03f35eaf1352358c7 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PINGUINO/22af5928890c8a7d12785d9ed9679dc18118ebc6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PINGUINO/e9c934bf3986d3cdecd3fa69c7f292820df0b5a7 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PINGUINO/83d4c2b71a67d095e8932636152f307cbcff88a6 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PINGUINO/6fdb80bb995cb8c9b8c156d7e2b504f4117b3a34 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PINGUINO/8df049e3dd34b8affbeac6ff72877da92195ef1c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PINGUINO/eaa0216e6b13eb83ede9124c83f5e2d48dd25afb .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/481076924/appInitialize.o: ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PINGUINO/855448533bdb829fc4f3d5585359548d97e706c1 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/481076924" 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/481076924/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/481076924/appInitialize.o.d" -o ${OBJECTDIR}/_ext/481076924/appInitialize.o ../../../Demo/DisplayDemo/Source/PIC32/appInitialize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appMain.o: ../../../Demo/DisplayDemo/Source/appMain.cpp  .generated_files/flags/PINGUINO/a97a9b3a98f148eb3dba4b407df1c55fd1639634 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appMain.o.d" -o ${OBJECTDIR}/_ext/480300606/appMain.o ../../../Demo/DisplayDemo/Source/appMain.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appApplication.o: ../../../Demo/DisplayDemo/Source/appApplication.cpp  .generated_files/flags/PINGUINO/f1d8ab893cfeb3d6a2336cfbc555ae3554c7fe31 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appApplication.o.d" -o ${OBJECTDIR}/_ext/480300606/appApplication.o ../../../Demo/DisplayDemo/Source/appApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appLedService.o: ../../../Demo/DisplayDemo/Source/appLedService.cpp  .generated_files/flags/PINGUINO/942f16bd83b2e056bbe8f7953758f5f154e38374 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appLedService.o.d" -o ${OBJECTDIR}/_ext/480300606/appLedService.o ../../../Demo/DisplayDemo/Source/appLedService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/480300606/appDisplayService.o: ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  .generated_files/flags/PINGUINO/dd4f043cfdb4f843112ac6bc99f923eeeb71ce9e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/480300606" 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o.d 
	@${RM} ${OBJECTDIR}/_ext/480300606/appDisplayService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/480300606/appDisplayService.o.d" -o ${OBJECTDIR}/_ext/480300606/appDisplayService.o ../../../Demo/DisplayDemo/Source/appDisplayService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  .generated_files/flags/PINGUINO/b205718d9143a5675582467ca8c28dd82a1addeb .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  .generated_files/flags/PINGUINO/b18b257fdacabc57b73865f20d59c3bd6eddaf6b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PIO8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PIO8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  .generated_files/flags/PINGUINO/72331f9fd2b11578d6e4029ec7116f8f18e03196 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_PMP8.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_PMP8.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o: ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  .generated_files/flags/PINGUINO/b6975f367de1b52b22bd23683d509494485efe52 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1867057233" 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o.d" -o ${OBJECTDIR}/_ext/1867057233/eosILI9341_SIO.o ../../../Source/Controllers/Display/Drivers/ILI9341/eosILI9341_SIO.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosService.o: ../../../Source/Services/eosService.cpp  .generated_files/flags/PINGUINO/de073cd7b9cd9f52d9bd4fdd6f101a5a3718499b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosService.o ../../../Source/Services/eosService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/863068963/eosAppLoopService.o: ../../../Source/Services/eosAppLoopService.cpp  .generated_files/flags/PINGUINO/7735910587e9fe3adfd17584ba191da73938997 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/863068963" 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d 
	@${RM} ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/863068963/eosAppLoopService.o.d" -o ${OBJECTDIR}/_ext/863068963/eosAppLoopService.o ../../../Source/Services/eosAppLoopService.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1127873614/main.o: ../../../Source/StartUp/PIC32/main.cpp  .generated_files/flags/PINGUINO/9bcb761b41b16d67ca1b1a78d47b2d571ed5d7d8 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1127873614" 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127873614/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1127873614/main.o.d" -o ${OBJECTDIR}/_ext/1127873614/main.o ../../../Source/StartUp/PIC32/main.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1156436454/eosContainer.o: ../../../Source/System/Collections/eosContainer.cpp  .generated_files/flags/PINGUINO/3e9a5c68db86d9bca20ef1dc293a33348a612907 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1156436454" 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1156436454/eosContainer.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1156436454/eosContainer.o.d" -o ${OBJECTDIR}/_ext/1156436454/eosContainer.o ../../../Source/System/Collections/eosContainer.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosTask.o: ../../../Source/System/Core/eosTask.cpp  .generated_files/flags/PINGUINO/5709c9b0be994bd2e53e8960b7b08a2cd4c8039 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosTask.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosTask.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosTask.o ../../../Source/System/Core/eosTask.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o: ../../../Source/System/Core/eosGlobalAlloc.cpp  .generated_files/flags/PINGUINO/b490f55cecd24a16d2157f45ff95722f2189f655 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosGlobalAlloc.o ../../../Source/System/Core/eosGlobalAlloc.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosQueue.o: ../../../Source/System/Core/eosQueue.cpp  .generated_files/flags/PINGUINO/72054f6b9c3aeae7377ef349e0a96137d8e655f7 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosQueue.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosQueue.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosQueue.o ../../../Source/System/Core/eosQueue.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o: ../../../Source/System/Core/eosHeapAllocator.cpp  .generated_files/flags/PINGUINO/eff747c70891db2aa99501e6674c5d3f23fb5898 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosHeapAllocator.o ../../../Source/System/Core/eosHeapAllocator.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o: ../../../Source/System/Core/eosErrorHandler.cpp  .generated_files/flags/PINGUINO/f1f36f63c1530e29a0f0982a1ed5e6e60305db8e .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1935080774" 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o.d" -o ${OBJECTDIR}/_ext/1935080774/eosErrorHandler.o ../../../Source/System/Core/eosErrorHandler.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas8pt.o: ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  .generated_files/flags/PINGUINO/7279bfe5820dc614381b0448974922fa4a112b32 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas8pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas8pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas8pt.o ../../../Source/System/Graphics/Fonts/Consolas8pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas10pt.o: ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  .generated_files/flags/PINGUINO/c6b2b3af1dcd24de11adf747e74b99d04641c36f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas10pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas10pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas10pt.o ../../../Source/System/Graphics/Fonts/Consolas10pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas12pt.o: ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  .generated_files/flags/PINGUINO/42327318f532188c960934704aa27a6893b41e43 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas12pt.o ../../../Source/System/Graphics/Fonts/Consolas12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas14pt.o: ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  .generated_files/flags/PINGUINO/b203362acb0ae967202eed9d052a99ed0a8baecc .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas14pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas14pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas14pt.o ../../../Source/System/Graphics/Fonts/Consolas14pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas18pt.o: ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  .generated_files/flags/PINGUINO/d0d35a3dc78bb3aee29b285dec4d1482d1959af3 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas18pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas18pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas18pt.o ../../../Source/System/Graphics/Fonts/Consolas18pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Consolas24pt.o: ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  .generated_files/flags/PINGUINO/10575af906e41147350656562b884152df979594 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Consolas24pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Consolas24pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Consolas24pt.o ../../../Source/System/Graphics/Fonts/Consolas24pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/Tahoma12pt.o: ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  .generated_files/flags/PINGUINO/e5c8dd5a272333041d1dbb664a497eb08a35a233 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/Tahoma12pt.o.d" -o ${OBJECTDIR}/_ext/212539067/Tahoma12pt.o ../../../Source/System/Graphics/Fonts/Tahoma12pt.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/212539067/FontTable.o: ../../../Source/System/Graphics/Fonts/FontTable.cpp  .generated_files/flags/PINGUINO/d6eff20b6405a597bbbcdb5600fdc6fda8aa93b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/212539067" 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o.d 
	@${RM} ${OBJECTDIR}/_ext/212539067/FontTable.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/212539067/FontTable.o.d" -o ${OBJECTDIR}/_ext/212539067/FontTable.o ../../../Source/System/Graphics/Fonts/FontTable.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosColor.o: ../../../Source/System/Graphics/eosColor.cpp  .generated_files/flags/PINGUINO/2ccf449ea62f3e67580a9280bc77c7b825f5056 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosColor.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosColor.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosColor.o ../../../Source/System/Graphics/eosColor.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosFont.o: ../../../Source/System/Graphics/eosFont.cpp  .generated_files/flags/PINGUINO/76aef77579567c0b239158da6c979974fa2e7af7 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosFont.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosFont.o ../../../Source/System/Graphics/eosFont.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics.o: ../../../Source/System/Graphics/eosGraphics.cpp  .generated_files/flags/PINGUINO/959d7d050a13b3269b0b7d04ec6227dfba107d3c .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics.o ../../../Source/System/Graphics/eosGraphics.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o: ../../../Source/System/Graphics/eosGraphics_Circle.cpp  .generated_files/flags/PINGUINO/c1da6cb0a40bdf5e38fc8ddf8b755601761e10e7 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Circle.o ../../../Source/System/Graphics/eosGraphics_Circle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o: ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  .generated_files/flags/PINGUINO/5d831a9be47831af16a4f7590e80581f56851ddd .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Rectangle.o ../../../Source/System/Graphics/eosGraphics_Rectangle.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o: ../../../Source/System/Graphics/eosGraphics_Line.cpp  .generated_files/flags/PINGUINO/87192c864904a8d0efa5ae7ef07c17d8af0e23d2 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Line.o ../../../Source/System/Graphics/eosGraphics_Line.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosPoint.o: ../../../Source/System/Graphics/eosPoint.cpp  .generated_files/flags/PINGUINO/d312f9d29c6977dab7f3e9f24a2203c01866e42a .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosPoint.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosPoint.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosPoint.o ../../../Source/System/Graphics/eosPoint.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosRect.o: ../../../Source/System/Graphics/eosRect.cpp  .generated_files/flags/PINGUINO/9f619f99202eb9ba20cd2302d58e8ee002f63f55 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosRect.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosRect.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosRect.o ../../../Source/System/Graphics/eosRect.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosSize.o: ../../../Source/System/Graphics/eosSize.cpp  .generated_files/flags/PINGUINO/71cf73bea89024e71013943be1d07f0682b44a7b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosSize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosSize.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosSize.o ../../../Source/System/Graphics/eosSize.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o: ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  .generated_files/flags/PINGUINO/738f47342364ad41526cd2af09767b547746c024 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Ellipse.o ../../../Source/System/Graphics/eosGraphics_Ellipse.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosTransformation.o: ../../../Source/System/Graphics/eosTransformation.cpp  .generated_files/flags/PINGUINO/3461ca1aeefe0754c5d8b91d61ee18e3f306c773 .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosTransformation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosTransformation.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosTransformation.o ../../../Source/System/Graphics/eosTransformation.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o: ../../../Source/System/Graphics/eosGraphics_Text.cpp  .generated_files/flags/PINGUINO/770aee6b07337536abead0af18be76c41a1cd9ad .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1486223398" 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o.d" -o ${OBJECTDIR}/_ext/1486223398/eosGraphics_Text.o ../../../Source/System/Graphics/eosGraphics_Text.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PINGUINO/85cb509c7e9a5c6097fece9d904de5734dfdc84f .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PINGUINO/eb14ff14ea45bc12c40733deb6c2171b0258344b .generated_files/flags/PINGUINO/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Demo/DisplayDemo/Include" -I"../../../Demo/DisplayDemo/Include/PIC32" -I"../../../Include" -I"../../../Library/PIC32/Harmony/framework" -I"../../../Library/PIC32/FreeRTOS/Source/include" -I"../../../Library/PIC32/FreeRTOS/Source/portable/MPLAB/PIC32MX" -fno-rtti -fno-exceptions -fno-check-new -fno-enforce-eh-specs -ffunction-sections -mno-float -O2 -funroll-loops -fomit-frame-pointer -DHARDWARE_CUSTOM -DHARDWARE_CUSTOM_PINGUINO -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp  -relaxed-math -DXPRJ_PINGUINO=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
