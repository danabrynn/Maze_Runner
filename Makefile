# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Define the target executable
TARGET = my_program

# Define source and object files
SRCS = main.cpp maze.cpp
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependency rules
main.o: maze.h
maze.o: maze.h

# Rule to clean up the directory
clean:
	rm -f $(OBJS) $(TARGET)