#include <iostream> 
#include <string>
#include <fstream>
#include <exception>
#include <optional>
#include <algorithm>
#include <vector>
#include "argparser.hpp"

void print_usage() {
    std::cout << "usage: polysort [-i in] [-o out] [-s separator] { type colnum }" << std::endl;
    std::cout << "\t-i: vstupní soubor (default: stdin)" << std::endl;
    std::cout << "\t-o: výstupní soubor (default: stdout)" << std::endl;
    std::cout << "\t-s: separator (default: ' ')" << std::endl;
    std::cout << "\ttype: S - string, N - numeric, ..." << std::endl;
    std::cout << "\tcolumn: číslo logického sloupce (počítáno od 1)" << std::endl;
}

std::ifstream* open_input_file(const std::string& filepath) {
    auto* file = new std::ifstream(filepath);
    if (!file->good()) {
        delete file;
        throw std::invalid_argument("Couldn't open input file " + filepath);
    }
    return file;
}

std::ofstream* open_output_file(const std::string& filepath) {
    auto* file = new std::ofstream(filepath);
    if (!file->good()) {
        delete file;
        throw std::invalid_argument("Couldn't open output file " + filepath);
    }
    return file;
}

void run(int argc, char* argv[]) {
    ArgParser argParser(argc, argv);

    // Default values
    std::string separator = " ";
    std::istream* input = &std::cin;
    std::ostream* output = &std::cout;
    
    if (auto fileOpt = argParser.get_flag_value("-i")) {
        input = open_input_file(fileOpt.value());
    }
    
    if (auto fileOpt = argParser.get_flag_value("-o")) {
        output = open_output_file(fileOpt.value());
    }
    
    if (auto separatorOption = argParser.get_flag_value("-s")) {
        separator = separatorOption.value();
    }

    auto cols = argParser.get_columns();

    std::for_each(cols.begin(), cols.end(), 
        [](const Column& col) {
            std::cout << col.type << " " << col.idx << "\n";
        });
    std::cout << std::endl;
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