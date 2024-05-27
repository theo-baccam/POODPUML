CC = g++
ESSENTIAL_FLAGS = -I include/ -L lib/
RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

EXECUTABLE = tower-defense
all: $(wildcard src/*.cpp)
	$(CC) $^ $(ESSENTIAL_FLAGS) $(RAYLIB_FLAGS) -o $(EXECUTABLE)
clean:
	rm -f $(EXECUTABLE)