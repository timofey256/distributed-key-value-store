#include <iostream> 
#include <string>
#include <fstream>
#include <exception>
#include <optional>
#include <algorithm>
#include <vector>
#include "argparser.hpp"
#include "tablesorter.hpp"

void print_usage() {
    std::cout << "usage: polysort [-i in] [-o out] [-s separator] { type colnum }" << std::endl;
    std::cout << "\t-i: vstupní soubor (default: stdin)" << std::endl;
    std::cout << "\t-o: výstupní soubor (default: stdout)" << std::endl;
    std::cout << "\t-s: separator (default: ' ')" << std::endl;
    std::cout << "\ttype: S - string, N - numeric, ..." << std::endl;
    std::cout << "\tcolumn: číslo logického sloupce (počítáno od 1)" << std::endl;
}

std::ifstream open_input_file(const std::string& filepath) {
    auto file = std::ifstream(filepath);
    if (!file.good()) {
        throw std::invalid_argument("error: Couldn't open input file " + filepath);
    }
    return file;
}

std::ofstream open_output_file(const std::string& filepath) {
    auto file = std::ofstream(filepath);
    if (!file.good()) {
        throw std::invalid_argument("error: Couldn't open output file " + filepath);
    }
    return file;
}

void run(int argc, char* argv[]) {
    ArgParser argParser(argc, argv);
    std::string separator = " ";
    
    std::optional<std::ifstream> input_file;
    std::optional<std::ofstream> output_file;
    
    std::istream* input = &std::cin;
    if (auto fileOpt = argParser.get_flag_value("-i")) {
        input_file.emplace(open_input_file(fileOpt.value()));
        input = &input_file.value();
    }
    
    std::ostream* output = &std::cout;
    if (auto fileOpt = argParser.get_flag_value("-o")) {
        output_file.emplace(open_output_file(fileOpt.value()));
        output = &output_file.value();
    }
    
    if (auto separatorOption = argParser.get_flag_value("-s")) {
        separator = separatorOption.value();
    }
    
    auto cols = argParser.get_columns();
    TableSorter tableSorter(separator[0], cols);
    tableSorter.parse(*input);
    tableSorter.sort();
    tableSorter.print(*output);

    // Input and output files are destoyed here at the end, so i don't do this explicitly.
}

int main(int argc, char* argv[]) {
    try {
        run(argc, argv);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}