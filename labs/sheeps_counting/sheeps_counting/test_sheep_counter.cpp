#include <string>
#include <fstream>
#include <cassert>
#include <cstdio>
#include "sheeps_counting.cpp"

struct TestCase {
	std::string filepath;
	int expected_num_of_characters;
	int expected_num_of_words;
	int expected_num_of_numbers;
	int expected_num_of_sentences;
	int expected_num_of_lines;
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

	if (counter.number_of_lines != testcase.expected_num_of_lines)
		print_equals_error("lines", testcase.filepath, testcase.expected_num_of_lines, counter.number_of_lines);

	if (counter.number_of_numbers != testcase.expected_num_of_numbers)
		print_equals_error("numbers", testcase.filepath, testcase.expected_num_of_numbers, counter.number_of_numbers);
}

void test() {
	std::vector<std::string> test_fp = 
		{
			"data/test1.txt", 
			"data/test2.txt", 
			"data/test3.txt", 
			"data/test4.txt",
			"data/test5.txt", 
			"data/test6.txt" 
		};
	

	TestCase test1(test_fp[0], 5, 3, 0, 1, 3);
	TestCase test2(test_fp[1], 39, 5, 3, 2, 1);
	TestCase test3(test_fp[2], 73, 13, 2, 2, 1);
	TestCase test4(test_fp[3], 100, 16, 3, 3, 5);
	TestCase test5(test_fp[4], 13, 2, 0, 1, 1);
	TestCase test6(test_fp[5], 14 * 5 + 13, 2 * 6, 0, 6, 6);

	std::vector<TestCase> testcases = {test1, test2, test3, test4, test5, test6};
	
	for (auto&& testcase : testcases) 
		run_test_case(testcase);
}


// // Uncomment the below and comment `main()` in sheeps_counting.cpp to run tests.

// int main() {
// 	test();
// 	return 0;
// }