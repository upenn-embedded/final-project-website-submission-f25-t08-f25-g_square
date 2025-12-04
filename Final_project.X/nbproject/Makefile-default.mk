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
FINAL_IMAGE=${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../Final_project.X/LCD_GFX.c ../Final_project.X/ST7735.c ../Final_project.X/imu.c ../Final_project.X/main.c ../Final_project.X/pca9685.c ../Final_project.X/uart.c ../Final_project.X/voice_control.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/427673803/LCD_GFX.o ${OBJECTDIR}/_ext/427673803/ST7735.o ${OBJECTDIR}/_ext/427673803/imu.o ${OBJECTDIR}/_ext/427673803/main.o ${OBJECTDIR}/_ext/427673803/pca9685.o ${OBJECTDIR}/_ext/427673803/uart.o ${OBJECTDIR}/_ext/427673803/voice_control.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d ${OBJECTDIR}/_ext/427673803/ST7735.o.d ${OBJECTDIR}/_ext/427673803/imu.o.d ${OBJECTDIR}/_ext/427673803/main.o.d ${OBJECTDIR}/_ext/427673803/pca9685.o.d ${OBJECTDIR}/_ext/427673803/uart.o.d ${OBJECTDIR}/_ext/427673803/voice_control.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/427673803/LCD_GFX.o ${OBJECTDIR}/_ext/427673803/ST7735.o ${OBJECTDIR}/_ext/427673803/imu.o ${OBJECTDIR}/_ext/427673803/main.o ${OBJECTDIR}/_ext/427673803/pca9685.o ${OBJECTDIR}/_ext/427673803/uart.o ${OBJECTDIR}/_ext/427673803/voice_control.o

# Source Files
SOURCEFILES=../Final_project.X/LCD_GFX.c ../Final_project.X/ST7735.c ../Final_project.X/imu.c ../Final_project.X/main.c ../Final_project.X/pca9685.c ../Final_project.X/uart.c ../Final_project.X/voice_control.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/427673803/LCD_GFX.o: ../Final_project.X/LCD_GFX.c  .generated_files/flags/default/95d102d567ca7a665a5a3e6f4bdade192d01f2a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/427673803/LCD_GFX.o -o ${OBJECTDIR}/_ext/427673803/LCD_GFX.o ../Final_project.X/LCD_GFX.c 
	
${OBJECTDIR}/_ext/427673803/ST7735.o: ../Final_project.X/ST7735.c  .generated_files/flags/default/122d0cd039f24cfc3a08ebc4395e8a929b48cf9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/ST7735.o.d" -MT "${OBJECTDIR}/_ext/427673803/ST7735.o.d" -MT ${OBJECTDIR}/_ext/427673803/ST7735.o -o ${OBJECTDIR}/_ext/427673803/ST7735.o ../Final_project.X/ST7735.c 
	
${OBJECTDIR}/_ext/427673803/imu.o: ../Final_project.X/imu.c  .generated_files/flags/default/c6627e2ef5903ee7db68fb5c06d34869a77abc0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/imu.o.d" -MT "${OBJECTDIR}/_ext/427673803/imu.o.d" -MT ${OBJECTDIR}/_ext/427673803/imu.o -o ${OBJECTDIR}/_ext/427673803/imu.o ../Final_project.X/imu.c 
	
${OBJECTDIR}/_ext/427673803/main.o: ../Final_project.X/main.c  .generated_files/flags/default/49fc0b2d6499d70728c2c50554aa5ebc6455725e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/main.o.d" -MT "${OBJECTDIR}/_ext/427673803/main.o.d" -MT ${OBJECTDIR}/_ext/427673803/main.o -o ${OBJECTDIR}/_ext/427673803/main.o ../Final_project.X/main.c 
	
${OBJECTDIR}/_ext/427673803/pca9685.o: ../Final_project.X/pca9685.c  .generated_files/flags/default/e7e0e0a31b3fc3c7016140be64cc3c4e2215cb76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/pca9685.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/pca9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/pca9685.o.d" -MT "${OBJECTDIR}/_ext/427673803/pca9685.o.d" -MT ${OBJECTDIR}/_ext/427673803/pca9685.o -o ${OBJECTDIR}/_ext/427673803/pca9685.o ../Final_project.X/pca9685.c 
	
${OBJECTDIR}/_ext/427673803/uart.o: ../Final_project.X/uart.c  .generated_files/flags/default/e7344f77f8b4d33d6c430eadaabddc1e7931e9ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/uart.o.d" -MT "${OBJECTDIR}/_ext/427673803/uart.o.d" -MT ${OBJECTDIR}/_ext/427673803/uart.o -o ${OBJECTDIR}/_ext/427673803/uart.o ../Final_project.X/uart.c 
	
${OBJECTDIR}/_ext/427673803/voice_control.o: ../Final_project.X/voice_control.c  .generated_files/flags/default/32adc502db976bd257a8f49fae2416bafe309d43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/voice_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/voice_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/voice_control.o.d" -MT "${OBJECTDIR}/_ext/427673803/voice_control.o.d" -MT ${OBJECTDIR}/_ext/427673803/voice_control.o -o ${OBJECTDIR}/_ext/427673803/voice_control.o ../Final_project.X/voice_control.c 
	
else
${OBJECTDIR}/_ext/427673803/LCD_GFX.o: ../Final_project.X/LCD_GFX.c  .generated_files/flags/default/eaa5eaa7a0b821f91042b458d9f9f9590beeac09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/427673803/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/427673803/LCD_GFX.o -o ${OBJECTDIR}/_ext/427673803/LCD_GFX.o ../Final_project.X/LCD_GFX.c 
	
${OBJECTDIR}/_ext/427673803/ST7735.o: ../Final_project.X/ST7735.c  .generated_files/flags/default/39f32119023b4d8bf102481d7df38957eb217884 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/ST7735.o.d" -MT "${OBJECTDIR}/_ext/427673803/ST7735.o.d" -MT ${OBJECTDIR}/_ext/427673803/ST7735.o -o ${OBJECTDIR}/_ext/427673803/ST7735.o ../Final_project.X/ST7735.c 
	
${OBJECTDIR}/_ext/427673803/imu.o: ../Final_project.X/imu.c  .generated_files/flags/default/1fd76aea57946fb0e04ee8b89c7b0955f263604 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/imu.o.d" -MT "${OBJECTDIR}/_ext/427673803/imu.o.d" -MT ${OBJECTDIR}/_ext/427673803/imu.o -o ${OBJECTDIR}/_ext/427673803/imu.o ../Final_project.X/imu.c 
	
${OBJECTDIR}/_ext/427673803/main.o: ../Final_project.X/main.c  .generated_files/flags/default/7d138885a7064c7d980e50509cb77591e914210f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/main.o.d" -MT "${OBJECTDIR}/_ext/427673803/main.o.d" -MT ${OBJECTDIR}/_ext/427673803/main.o -o ${OBJECTDIR}/_ext/427673803/main.o ../Final_project.X/main.c 
	
${OBJECTDIR}/_ext/427673803/pca9685.o: ../Final_project.X/pca9685.c  .generated_files/flags/default/eeec99d8cd6fff2f22858cb673c3f02f158974c1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/pca9685.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/pca9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/pca9685.o.d" -MT "${OBJECTDIR}/_ext/427673803/pca9685.o.d" -MT ${OBJECTDIR}/_ext/427673803/pca9685.o -o ${OBJECTDIR}/_ext/427673803/pca9685.o ../Final_project.X/pca9685.c 
	
${OBJECTDIR}/_ext/427673803/uart.o: ../Final_project.X/uart.c  .generated_files/flags/default/ddeb214707fbdbe8dbb2eb4987a9fdde47c7c7f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/uart.o.d" -MT "${OBJECTDIR}/_ext/427673803/uart.o.d" -MT ${OBJECTDIR}/_ext/427673803/uart.o -o ${OBJECTDIR}/_ext/427673803/uart.o ../Final_project.X/uart.c 
	
${OBJECTDIR}/_ext/427673803/voice_control.o: ../Final_project.X/voice_control.c  .generated_files/flags/default/ac9c972fe169deba41a9651699c0a117962bd2d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/427673803" 
	@${RM} ${OBJECTDIR}/_ext/427673803/voice_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/427673803/voice_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/427673803/voice_control.o.d" -MT "${OBJECTDIR}/_ext/427673803/voice_control.o.d" -MT ${OBJECTDIR}/_ext/427673803/voice_control.o -o ${OBJECTDIR}/_ext/427673803/voice_control.o ../Final_project.X/voice_control.c 
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Final_project.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Final_project.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/Final_project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/Final_project.X.${IMAGE_TYPE}.hex"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
