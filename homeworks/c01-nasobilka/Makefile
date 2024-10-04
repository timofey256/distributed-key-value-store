CXX = g++

CXXFLAGS = -std=c++23 -Wall

SRC = src/main.cpp src/utils.cpp

TARGET = MyExecutable

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -I src -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)