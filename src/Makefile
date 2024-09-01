# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -Wall -Wextra -std=c++14

# Define the target executable
TARGET = maisy

# Define source and object files
SRCS = main.cpp maze.cpp consolegame.cpp disjointset.cpp mazesolver.cpp
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
main.o: consolegame.h
maze.o: maze.h disjointset.h
consolegame.o: consolegame.h maze.h mazesolver.h
disjointset.o: disjointset.h
mazesolver.cpp: mazesolver.h maze.h

# Rule to clean up the directory
clean:
	rm -f $(OBJS) $(TARGET)