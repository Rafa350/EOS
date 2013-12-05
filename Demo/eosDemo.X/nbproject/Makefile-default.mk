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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
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
SOURCEFILES_QUOTED_IF_SPACED=../../Source/SysMain.c ../Config.c ../Main.c ../../Source/Ports/InpPorts.c ../../Source/Ports/OutPorts.c ../outPortsDriver.asm

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1787047461/SysMain.p1 ${OBJECTDIR}/_ext/1472/Config.p1 ${OBJECTDIR}/_ext/1472/Main.p1 ${OBJECTDIR}/_ext/648081730/InpPorts.p1 ${OBJECTDIR}/_ext/648081730/OutPorts.p1 ${OBJECTDIR}/_ext/1472/outPortsDriver.obj
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1787047461/SysMain.p1.d ${OBJECTDIR}/_ext/1472/Config.p1.d ${OBJECTDIR}/_ext/1472/Main.p1.d ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1787047461/SysMain.p1 ${OBJECTDIR}/_ext/1472/Config.p1 ${OBJECTDIR}/_ext/1472/Main.p1 ${OBJECTDIR}/_ext/648081730/InpPorts.p1 ${OBJECTDIR}/_ext/648081730/OutPorts.p1 ${OBJECTDIR}/_ext/1472/outPortsDriver.obj

# Source Files
SOURCEFILES=../../Source/SysMain.c ../Config.c ../Main.c ../../Source/Ports/InpPorts.c ../../Source/Ports/OutPorts.c ../outPortsDriver.asm


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1787047461/SysMain.p1: ../../Source/SysMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/SysMain.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1787047461/SysMain.p1  ../../Source/SysMain.c 
	@-${MV} ${OBJECTDIR}/_ext/1787047461/SysMain.d ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Config.p1: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1472/Config.p1  ../Config.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Config.d ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/648081730/InpPorts.p1: ../../Source/Ports/InpPorts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/648081730 
	@${RM} ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/648081730/InpPorts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/648081730/InpPorts.p1  ../../Source/Ports/InpPorts.c 
	@-${MV} ${OBJECTDIR}/_ext/648081730/InpPorts.d ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/648081730/OutPorts.p1: ../../Source/Ports/OutPorts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/648081730 
	@${RM} ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/648081730/OutPorts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/648081730/OutPorts.p1  ../../Source/Ports/OutPorts.c 
	@-${MV} ${OBJECTDIR}/_ext/648081730/OutPorts.d ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1787047461/SysMain.p1: ../../Source/SysMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/SysMain.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1787047461/SysMain.p1  ../../Source/SysMain.c 
	@-${MV} ${OBJECTDIR}/_ext/1787047461/SysMain.d ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1787047461/SysMain.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Config.p1: ../Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Config.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1472/Config.p1  ../Config.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Config.d ${OBJECTDIR}/_ext/1472/Config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/648081730/InpPorts.p1: ../../Source/Ports/InpPorts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/648081730 
	@${RM} ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/648081730/InpPorts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/648081730/InpPorts.p1  ../../Source/Ports/InpPorts.c 
	@-${MV} ${OBJECTDIR}/_ext/648081730/InpPorts.d ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/648081730/InpPorts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/648081730/OutPorts.p1: ../../Source/Ports/OutPorts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/648081730 
	@${RM} ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/648081730/OutPorts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"    -o${OBJECTDIR}/_ext/648081730/OutPorts.p1  ../../Source/Ports/OutPorts.c 
	@-${MV} ${OBJECTDIR}/_ext/648081730/OutPorts.d ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/648081730/OutPorts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/outPortsDriver.obj: ../outPortsDriver.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1472/outPortsDriver.obj  ../outPortsDriver.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/outPortsDriver.d ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1472/outPortsDriver.obj: ../outPortsDriver.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d 
	@${RM} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj 
	${MP_CC} -C $(MP_EXTRA_AS_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1472/outPortsDriver.obj  ../outPortsDriver.asm 
	@-${MV} ${OBJECTDIR}/_ext/1472/outPortsDriver.d ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/outPortsDriver.obj.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"        -odist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -DHARDWARE_CPU04B -P -N255 -I"../" -I"../../Include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"     -odist/${CND_CONF}/${IMAGE_TYPE}/eosDemo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
