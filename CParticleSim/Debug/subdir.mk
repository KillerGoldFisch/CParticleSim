################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CParticleSim.cpp \
../OpenGL_Helper.cpp \
../Particle.cpp \
../ParticleSnapshot.cpp \
../ParticleSystem.cpp \
../stdafx.cpp 

OBJS += \
./CParticleSim.o \
./OpenGL_Helper.o \
./Particle.o \
./ParticleSnapshot.o \
./ParticleSystem.o \
./stdafx.o 

CPP_DEPS += \
./CParticleSim.d \
./OpenGL_Helper.d \
./Particle.d \
./ParticleSnapshot.d \
./ParticleSystem.d \
./stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


