CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pedantic

TARGET = matrix

SRCS = Matrix.cpp TestMatrix.cpp
OBJS = $(SRCS:.cpp=.o)

run: clean $(TARGET)
	./$(TARGET)

valgrind: clean $(TARGET)
	valgrind ./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp Matrix.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
