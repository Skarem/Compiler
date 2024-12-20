# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -pedantic \
            -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast \
		    -Wcast-align -Wunused -Woverloaded-virtual -Wnull-dereference \
		    -Wdouble-promotion -Wformat=2 -O2

# Default target
TARGET = build/compiler_driver
all: $(TARGET)

# Build target (linking the executable)
$(TARGET): build/compiler_driver.o build/lexer.o | build
	@echo "Linking executable..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) build/compiler_driver.o build/lexer.o

# Compile source files into objects
build/compiler_driver.o: src/compiler_driver.cpp inc/lexer.hpp | build
	@echo "Compiling compiler_driver.cpp..."
	$(CXX) $(CXXFLAGS) -c src/compiler_driver.cpp -o build/compiler_driver.o

build/lexer.o: src/lexer.cpp inc/lexer.hpp inc/tokens.hpp
	@echo "Compiling lexer.cpp"
	$(CXX) $(CXXFLAGS) -c src/lexer.cpp -o build/lexer.o

# Create build directory
build:
	@echo "Creating build directory..."
	@mkdir -p build

# Clean target
clean:
	@echo "Cleaning up..."
	rm -rf build

# Phony targets
.PHONY: all clean