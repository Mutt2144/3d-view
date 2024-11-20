COMPILER=g++
MAIN=src/main.cpp
GWM=src/GWM/*.cpp src/GWM/keyboard/*.cpp src/GWM/texture/*.cpp
BUILD=build/3d-program
LIBS=-lSDL2_image -lSDL2 -lGL -lGLU -lglut

all:
	clear
	$(COMPILER) $(MAIN) $(GWM) $(LIBS) -o $(BUILD)