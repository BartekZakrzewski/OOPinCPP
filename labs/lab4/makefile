CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pedantic

TARGET = complex

SRCS = Complex.cpp TestComplex.cpp
OBJS = $(SRCS:.cpp=.o)

run: clean $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
