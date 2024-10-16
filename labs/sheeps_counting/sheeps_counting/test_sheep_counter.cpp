#include "sheeps_counting.cpp"
#include <string>
#include <fstream>
#include <cassert>
#include <cstdio>

struct TestCase {
	std::string filepath;
	int expected_num_of_characters;
	int expected_num_of_words;
	int expected_num_of_sentences;
};

void print_equals_error(const std::string& what, 
						const std::string& filepath, 
						int expected, 
						int actual) {
	printf("ERROR: wrong number of %s for %s. Expected: %d, Actual: %d\n\n", what.c_str(), filepath.c_str(), expected, actual);
}

void run_test_case(const TestCase& testcase) {
	SheepCounter counter;
	std::ifstream f;
	f.open(testcase.filepath);
	if (f.good())
		counter.count(f);

	if (counter.number_of_characters != testcase.expected_num_of_characters)
		print_equals_error("characters", testcase.filepath, testcase.expected_num_of_characters, counter.number_of_characters);

	if (counter.number_of_words != testcase.expected_num_of_words)
		print_equals_error("words", testcase.filepath, testcase.expected_num_of_words, counter.number_of_words);

	if (counter.number_of_sentences != testcase.expected_num_of_sentences)
		print_equals_error("sentences", testcase.filepath, testcase.expected_num_of_sentences, counter.number_of_sentences);
}

void test() {
	std::string small_filepath = "small.txt";
	std::string big_filepath = "big.txt";
	std::string test1 = "test1.txt";
	TestCase small(small_filepath, 13, 2, 1);
	TestCase big(big_filepath, 14 * 5 + 13, 2 * 6, 6);
	TestCase test1(test1, 3, 3, 1);

	run_test_case(small);
	run_test_case(big);
}

int main() {
	test();
}