#include <string>
#include <stdexcept>
#include "utils.h"

int customStoi(const std::string& str, const char* msg) {
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        throw std::invalid_argument(msg);
    }
}