CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = stack

SRCS = Stack.cpp TestStack.cpp
OBJS = $(SRCS:.cpp=.o)

run: clean $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
