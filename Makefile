# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS =  -lSDL2_image -lm -Wall -Wextra -Wpedantic -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wredundant-decls -Winline -Wunreachable-code -Wconversion -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor -Wctor-dtor-privacy -Wdelete-non-virtual-dtor -Wnull-dereference

# Linker Flags
#LDFLAGS = -lncurses
# Default Source and Target (can be overridden)
SRC = main.cpp
TARGET = main

# Build and Run Target
all: $(TARGET)


# Build Target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean up build files
.PHONY: clean
clean:
	rm -f $(TARGET)
