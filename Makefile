ESSENTIAL_FLAGS = -I include/ -L lib/
RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(wildcard src/*.cpp)
	g++ $^ obj/flecs.o $(ESSENTIAL_FLAGS) $(RAYLIB_FLAGS) -std=c++0x -o tower-defense -lWs2_32

flecs: $(obj/flecs.c)
	g++ $^ -I include -std=gnu99 -c -o obj/flecs.o -lWs2_32

test-mvc: src/ControllerInterface.cpp src/Core.cpp tests/test_MVC.cpp
	g++ $^ -I include/ -o test-mvc

test-flecs: tests/test_flecs.cpp
	g++ tests/test_flecs.cpp obj/flecs.o -I include/ -o test-flecs -std=c++0x -lWs2_32

clean:
	rm -f $(EXECUTABLE)