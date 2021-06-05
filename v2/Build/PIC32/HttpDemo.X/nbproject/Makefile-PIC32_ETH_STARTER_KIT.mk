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
ifeq "$(wildcard nbproject/Makefile-local-PIC32_ETH_STARTER_KIT.mk)" "nbproject/Makefile-local-PIC32_ETH_STARTER_KIT.mk"
include nbproject/Makefile-local-PIC32_ETH_STARTER_KIT.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_ETH_STARTER_KIT
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp ../../../Demo/HttpDemo/Source/appApplication.cpp ../../../Demo/HttpDemo/Source/appLedService.cpp ../../../Demo/HttpDemo/Source/appMain.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Source/System/eosDebug.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/619230300/appInitialize.o ${OBJECTDIR}/_ext/1768032414/appApplication.o ${OBJECTDIR}/_ext/1768032414/appLedService.o ${OBJECTDIR}/_ext/1768032414/appMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/1315484212/eosDebug.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/619230300/appInitialize.o.d ${OBJECTDIR}/_ext/1768032414/appApplication.o.d ${OBJECTDIR}/_ext/1768032414/appLedService.o.d ${OBJECTDIR}/_ext/1768032414/appMain.o.d ${OBJECTDIR}/_ext/346134360/halSYS.o.d ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d ${OBJECTDIR}/_ext/1315484212/eosString.o.d ${OBJECTDIR}/_ext/1315484212/eosDebug.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/619230300/appInitialize.o ${OBJECTDIR}/_ext/1768032414/appApplication.o ${OBJECTDIR}/_ext/1768032414/appLedService.o ${OBJECTDIR}/_ext/1768032414/appMain.o ${OBJECTDIR}/_ext/346134360/halSYS.o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ${OBJECTDIR}/_ext/1315484212/eosString.o ${OBJECTDIR}/_ext/1315484212/eosDebug.o

# Source Files
SOURCEFILES=../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp ../../../Demo/HttpDemo/Source/appApplication.cpp ../../../Demo/HttpDemo/Source/appLedService.cpp ../../../Demo/HttpDemo/Source/appMain.cpp ../../../Source/HAL/PIC32/halSYS.c ../../../Source/System/eosApplication.cpp ../../../Source/System/eosString.cpp ../../../Source/System/eosDebug.cpp



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
	${MAKE}  -f nbproject/Makefile-PIC32_ETH_STARTER_KIT.mk dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX775F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_ETH_STARTER_KIT/fd557ad7e660fe4804049265dd41c5ef504ec60b .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -mno-float -fno-common -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/346134360/halSYS.o: ../../../Source/HAL/PIC32/halSYS.c  .generated_files/flags/PIC32_ETH_STARTER_KIT/45b27f833f5ec1c4ddc56c86c3ae552e93ce4796 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/346134360" 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o.d 
	@${RM} ${OBJECTDIR}/_ext/346134360/halSYS.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -mno-float -fno-common -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/346134360/halSYS.o.d" -o ${OBJECTDIR}/_ext/346134360/halSYS.o ../../../Source/HAL/PIC32/halSYS.c    -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/619230300/appInitialize.o: ../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/8b2c8ab6fb55a91c973a04b76d54179b3d75e452 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/619230300" 
	@${RM} ${OBJECTDIR}/_ext/619230300/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/619230300/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/619230300/appInitialize.o.d" -o ${OBJECTDIR}/_ext/619230300/appInitialize.o ../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appApplication.o: ../../../Demo/HttpDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/1a686445834b45dd0fabdab8e88ecb2e8fb506f9 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appApplication.o.d" -o ${OBJECTDIR}/_ext/1768032414/appApplication.o ../../../Demo/HttpDemo/Source/appApplication.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appLedService.o: ../../../Demo/HttpDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/80c8558fed7bee03c1d29bb7c57473b35f72d458 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appLedService.o.d" -o ${OBJECTDIR}/_ext/1768032414/appLedService.o ../../../Demo/HttpDemo/Source/appLedService.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appMain.o: ../../../Demo/HttpDemo/Source/appMain.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/b7718b46ff144333e68167497544beefe4976fe3 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appMain.o.d" -o ${OBJECTDIR}/_ext/1768032414/appMain.o ../../../Demo/HttpDemo/Source/appMain.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/6a0dc108660f0a7ddca559d29278649d70a922a .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/e9beb69629748d230aac79b1d8059f949c176f4b .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosDebug.o: ../../../Source/System/eosDebug.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/a969715dafd89f194a7eb33a17ed501887b7ac78 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosDebug.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosDebug.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosDebug.o ../../../Source/System/eosDebug.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/619230300/appInitialize.o: ../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/ca1ec0b3c48f489a885bc2450f80fb8c919269d7 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/619230300" 
	@${RM} ${OBJECTDIR}/_ext/619230300/appInitialize.o.d 
	@${RM} ${OBJECTDIR}/_ext/619230300/appInitialize.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/619230300/appInitialize.o.d" -o ${OBJECTDIR}/_ext/619230300/appInitialize.o ../../../Demo/HttpDemo/Source/PIC32/appInitialize.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appApplication.o: ../../../Demo/HttpDemo/Source/appApplication.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/8a3d160808f3900b6afc00eb41d320dae9c06346 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appApplication.o.d" -o ${OBJECTDIR}/_ext/1768032414/appApplication.o ../../../Demo/HttpDemo/Source/appApplication.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appLedService.o: ../../../Demo/HttpDemo/Source/appLedService.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/90a9cb558ae8b653fe049d1a9a27bf83574807dd .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appLedService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appLedService.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appLedService.o.d" -o ${OBJECTDIR}/_ext/1768032414/appLedService.o ../../../Demo/HttpDemo/Source/appLedService.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1768032414/appMain.o: ../../../Demo/HttpDemo/Source/appMain.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/c5fd491e381c34f59618e8b50550029d85235cae .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1768032414" 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1768032414/appMain.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1768032414/appMain.o.d" -o ${OBJECTDIR}/_ext/1768032414/appMain.o ../../../Demo/HttpDemo/Source/appMain.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosApplication.o: ../../../Source/System/eosApplication.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/651789ee96461413f1096996badd6c08c4b00255 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosApplication.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosApplication.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosApplication.o ../../../Source/System/eosApplication.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosString.o: ../../../Source/System/eosString.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/1808ff9b2870bc521566330c7e705d798a508cbf .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosString.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosString.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosString.o ../../../Source/System/eosString.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1315484212/eosDebug.o: ../../../Source/System/eosDebug.cpp  .generated_files/flags/PIC32_ETH_STARTER_KIT/1a7de2f33a6ceeef127f20a0fd28bcb927d7f001 .generated_files/flags/PIC32_ETH_STARTER_KIT/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1315484212" 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1315484212/eosDebug.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../Include" -I"../../../Demo/HTTPDemo/Include" -I"../../../Demo/HTTPDemo/Include/PIC32" -I"../../../Library/PIC32/FreeRTOS/Source/Include" -I"../../../Library/PIC32/Harmony/Framework" -I"../../../Library/PIC32/LwIP/Src/Include" -I"../../../Library/PIC32/LwIP/Src/System" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -mno-float -DHARDWARE_PIC32_ETH_STARTER_KIT -I"../../../Demo/HttpServer/Include" -I"../../../Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1315484212/eosDebug.o.d" -o ${OBJECTDIR}/_ext/1315484212/eosDebug.o ../../../Source/System/eosDebug.cpp   -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -msoft-float -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_ETH_STARTER_KIT=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/HttpDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_ETH_STARTER_KIT
	${RM} -r dist/PIC32_ETH_STARTER_KIT

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
