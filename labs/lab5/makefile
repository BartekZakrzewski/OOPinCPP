CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pedantic

TARGET = poly
TARGETFUNCTIONS = polyfunctions

TESTFILE = TestPoly.cpp
TESTFILEFUNCTIONS = TestPolyWithFunctionTemplate.cpp

SRCS = Poly.cpp $(TESTFILE)
SRCSFUNCTIONS = Poly.cpp $(TESTFILEFUNCTIONS)
OBJS = $(SRCS:.cpp=.o)
OBJSFUNCTIONS = $(SRCSFUNCTIONS:.cpp=.o)

.PHONY: all run runfunctions diff clean cleanfunctions cleanall

all: $(TARGET) $(TARGETFUNCTIONS)

run: $(TARGET)
	./$(TARGET)

runfunctions: $(TARGETFUNCTIONS)
	./$(TARGETFUNCTIONS)

$(TARGET).txt: $(TARGET)
	./$(TARGET) > $@

$(TARGETFUNCTIONS).txt: $(TARGETFUNCTIONS)
	./$(TARGETFUNCTIONS) > $@

diff: $(TARGET).txt $(TARGETFUNCTIONS).txt
	diff $(TARGET).txt $(TARGETFUNCTIONS).txt && echo "Outputs are identical"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGETFUNCTIONS): $(OBJSFUNCTIONS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp Poly.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).txt

cleanfunctions:
	rm -f $(OBJSFUNCTIONS) $(TARGETFUNCTIONS) $(TARGETFUNCTIONS).txt

cleanall:
	rm -f $(OBJS) $(OBJSFUNCTIONS) $(TARGET) $(TARGETFUNCTIONS) $(TARGET).txt $(TARGETFUNCTIONS).txt
