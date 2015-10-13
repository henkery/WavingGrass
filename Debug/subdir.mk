################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../GameObject.cpp \
../Grass.cpp \
../Main.cpp \
../Mesh.cpp \
../NormalCalculators.cpp \
../ObjectLoader.cpp \
../Player.cpp \
../Tile.cpp \
../Vector3F.cpp \
../shader.cpp 

C_SRCS += \
../stb_image.c 

OBJS += \
./Camera.o \
./GameObject.o \
./Grass.o \
./Main.o \
./Mesh.o \
./NormalCalculators.o \
./ObjectLoader.o \
./Player.o \
./Tile.o \
./Vector3F.o \
./shader.o \
./stb_image.o 

C_DEPS += \
./stb_image.d 

CPP_DEPS += \
./Camera.d \
./GameObject.d \
./Grass.d \
./Main.d \
./Mesh.d \
./NormalCalculators.d \
./ObjectLoader.d \
./Player.d \
./Tile.d \
./Vector3F.d \
./shader.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


