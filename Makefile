# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Project name (the name of the executable)
TARGET = myprogram

# Source files and object files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean
