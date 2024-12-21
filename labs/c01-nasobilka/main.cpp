#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "main.hpp"

MultiplicationTable::MultiplicationTable() : from_(1), to_(10) {}

void MultiplicationTable::setRange(int from, int to) {
    from_ = from;
    to_ = to;
}

void MultiplicationTable::addNumber(int number) {
    numbers_.push_back(number);
}

void MultiplicationTable::print() const {
    for (int number : numbers_) {
        for (int i = from_; i <= to_; ++i) {
            std::cout << i << " * " << number << " = " 
                     << (i * number) << std::endl;
        }
        std::cout << std::endl;
    }
}

void printUsage() {
    std::cout << "Usage: nasobilka [-f from] [-t to] numbers...\n";
    std::cout << "  -f from: starting number (default: 1)\n";
    std::cout << "  -t to: ending number (default: 10)\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    MultiplicationTable table;

    int from = 1;
    int to   = 10;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-f" && i + 1 < argc) {
            try {
                from = std::stoi(argv[++i]);
            } catch (const std::exception&) {
                std::cerr << "Invalid 'from' value\n";
                return 1;
            }
        }
        else if (arg == "-t" && i + 1 < argc) {
            try {
                to = std::stoi(argv[++i]);
            } catch (const std::exception&) {
                std::cerr << "Invalid 'to' value\n";
                return 1;
            }
        }
        else {
            try {
                table.addNumber(std::stoi(arg));
            } catch (const std::exception&) {
                std::cerr << "Invalid number: " << arg << "\n";
                return 1;
            }
        }
    }

    table.setRange(from, to);

    table.print();
    return 0;
}