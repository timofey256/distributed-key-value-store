CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++23
SRCS = main.cpp argparser.cpp tablesorter.cpp types.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = polymorficsort
HEADERS = argparser.hpp types.hpp tablesorter.hpp

CONCAT_OUTPUT = all_cpp_files.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Concatenation target that combines all source and header files
concatenate: $(SRCS) $(HEADERS)
	echo "// Combined C++ Files" > $(CONCAT_OUTPUT)
	date +"// Generated on %Y-%m-%d %H:%M:%S" >> $(CONCAT_OUTPUT)
	echo "" >> $(CONCAT_OUTPUT)
	for file in $(HEADERS); do \
		echo "// Begin $$file" >> $(CONCAT_OUTPUT); \
		cat $$file >> $(CONCAT_OUTPUT); \
		echo -e "\n// End $$file\n" >> $(CONCAT_OUTPUT); \
	done
	for file in $(SRCS); do \
		echo "// Begin $$file" >> $(CONCAT_OUTPUT); \
		cat $$file >> $(CONCAT_OUTPUT); \
		echo -e "\n// End $$file\n" >> $(CONCAT_OUTPUT); \
	done
	echo "Concatenation complete. Output saved to $(CONCAT_OUTPUT)"

clean:
	rm -f $(OBJS) $(TARGET) $(CONCAT_OUTPUT)

try:
	make all
	./polymorficsort -s# -i input.txt S3

.PHONY: all clean concatenate