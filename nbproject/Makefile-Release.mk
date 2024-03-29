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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GPIO.o \
	${OBJECTDIR}/axiopcjsonclient.o \
	${OBJECTDIR}/device.o \
	${OBJECTDIR}/easylogging++.o \
	${OBJECTDIR}/function.o \
	${OBJECTDIR}/simpleclient.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libaxiclient.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libaxiclient.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libaxiclient.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/GPIO.o: GPIO.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/GPIO.o GPIO.cpp

${OBJECTDIR}/axiopcjsonclient.o: axiopcjsonclient.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/axiopcjsonclient.o axiopcjsonclient.cpp

${OBJECTDIR}/device.o: device.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/device.o device.cpp

${OBJECTDIR}/easylogging++.o: easylogging++.cc
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/easylogging++.o easylogging++.cc

${OBJECTDIR}/function.o: function.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/function.o function.cpp

${OBJECTDIR}/simpleclient.o: simpleclient.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/simpleclient.o simpleclient.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
