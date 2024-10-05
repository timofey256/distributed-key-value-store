#include <iostream>
#include <string>
#include <stdexcept>
#include <optional>
#include "utils.hpp"


std::optional<int> tryStoi(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        return {};
    }
}

void print_error(std::string msg) {
    std::cout << "ERROR: " << msg << std::endl;
}

void print_warning(std::string msg) {
    std::cout << "WARNING: " << msg << std::endl;
}

