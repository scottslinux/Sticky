# Use g++ unless CXX is provided from environment/CLI.
CXX ?= g++
# Final executable name.
TARGET := myProject

# Source and object file discovery in this folder.
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

# Optional raylib compile/link flags (can be overridden externally).
RAYLIB_CFLAGS ?=
RAYLIB_LIBS ?= -lraylib -lm -lpthread -ldl -lrt -lX11

# Default compile settings: C++17, debug build, and warnings.
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra
# Preprocessor flags (includes/defines).
CPPFLAGS += $(RAYLIB_CFLAGS)
# Libraries passed at link time.
LDLIBS += $(RAYLIB_LIBS)

# These targets are commands, not real files.
.PHONY: all build rebuild clean run help

# Default target: clean, then build.
all: rebuild

# Build only (no forced clean).
build: $(TARGET)

# Full rebuild path.
rebuild: clean build

# Link object files into the final executable.
# Automatic variable: $@ = target name (myProject).
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDLIBS)

# Compile each .cpp into a matching .o file.
# Automatic variables: $< = first prerequisite (.cpp), $@ = output (.o).
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Build and run the app.
run: build
	./$(TARGET)

# Show available make commands.
help:
	@echo "Available targets:"
	@echo "  make        - Clean then build (default)"
	@echo "  make build  - Build only"
	@echo "  make rebuild- Clean then build"
	@echo "  make run    - Build then run ./$(TARGET)"
	@echo "  make clean  - Remove object files and executable"
	@echo "  make help   - Show this help message"

# Remove generated build artifacts.
clean:
	rm -f $(OBJ) $(TARGET)

