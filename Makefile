CC = g++
ESSENTIAL_FLAGS = -I include/ -L lib/
RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(wildcard src/*.cpp)
	$(CC) $^ $(ESSENTIAL_FLAGS) $(RAYLIB_FLAGS) -o tower-defense

test-mvc: src/ControllerInterface.cpp src/Core.cpp tests/test_MVC.cpp
	$(CC) $^ -I include/ -o test-mvc

clean:
	rm -f $(EXECUTABLE)