#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW_QT-Windows
CND_CONF=ApplicationMode
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/FunctionGrid.o \
	${OBJECTDIR}/src/Animator.o \
	${OBJECTDIR}/src/logger.o \
	${OBJECTDIR}/src/SurfaceFactory.o \
	${OBJECTDIR}/src/ScreenSaverMain.o \
	${OBJECTDIR}/src/SurfaceGrid.o \
	${OBJECTDIR}/src/ParametricSurfacesDemo.o \
	${OBJECTDIR}/src/ColorRamp.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Lsdk/lib -lopengl32 -lglu32 -lglaux -llwtk -lrender2d -lrender3d -lLMath

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-ApplicationMode.mk dist/ApplicationMode/screensaver.exe

dist/ApplicationMode/screensaver.exe: ${OBJECTFILES}
	${MKDIR} -p dist/ApplicationMode
	${LINK.cc} -mwindows -mwin32 -o ${CND_DISTDIR}/${CND_CONF}/screensaver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/FunctionGrid.o: src/FunctionGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FunctionGrid.o src/FunctionGrid.cpp

${OBJECTDIR}/src/Animator.o: src/Animator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Animator.o src/Animator.cpp

${OBJECTDIR}/src/logger.o: src/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/logger.o src/logger.cpp

${OBJECTDIR}/src/SurfaceFactory.o: src/SurfaceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SurfaceFactory.o src/SurfaceFactory.cpp

${OBJECTDIR}/src/ScreenSaverMain.o: src/ScreenSaverMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ScreenSaverMain.o src/ScreenSaverMain.cpp

${OBJECTDIR}/src/SurfaceGrid.o: src/SurfaceGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SurfaceGrid.o src/SurfaceGrid.cpp

${OBJECTDIR}/src/ParametricSurfacesDemo.o: src/ParametricSurfacesDemo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ParametricSurfacesDemo.o src/ParametricSurfacesDemo.cpp

${OBJECTDIR}/src/ColorRamp.o: src/ColorRamp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Isrc/include -Isdk/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ColorRamp.o src/ColorRamp.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/ApplicationMode
	${RM} dist/ApplicationMode/screensaver.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
