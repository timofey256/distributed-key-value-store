CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

SRCS = main.cpp argparser.cpp tablesorter.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = polymorficsort

HEADERS = argparser.hpp types.hpp tablesorter.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean