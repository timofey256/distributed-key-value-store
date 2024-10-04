#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include "utils.h"

constexpr const char* COULDNT_PARSE_INTEGER_MESSAGE = "ERROR: Passed arguments are incorrect: couldn't parse a passed argument.";
constexpr const char* NO_VALUE_AFTER_FLAG_MESSAGE = "ERROR: Passed arguments are incorrect: no value after flag.";
constexpr const char* NO_ARGUMENTS_MESSAGE = "ERROR: No arguments are passed.";

class Multiplier {
public:
    Multiplier(std::optional<int> from, std::optional<int> to) {
        constexpr int default_from = 1;
        constexpr int default_to   = 10;

        _from = from.has_value() ? from.value() : default_from;
        _to = to.has_value() ? to.value() : default_to;
    }

    void display_multiply_table(int multiplier) {
        for (int curr = _from; curr <= _to; curr++) {
            std::cout << curr << " * " << multiplier << " = " << curr*multiplier << std::endl;
        }
    }

    void display_multiply_table(std::vector<int> multipliers) {
        for (auto&& m : multipliers) {
            display_multiply_table(m);
        }
    }

private:
    int _from;
    int _to;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    if (argc == 0) {
        throw std::invalid_argument(NO_ARGUMENTS_MESSAGE);
    }

    std::optional<int> from = {};
    std::optional<int> to = {};
    std::vector<int> values;

    for (int i = 1; i < argc; i++) { // start from 1, because first argument is the name of the project
        if (args[i] == "-f") {
            if (i + 1 >= argc) {
                throw std::invalid_argument(NO_VALUE_AFTER_FLAG_MESSAGE);
            }
            from = customStoi(args[i + 1], COULDNT_PARSE_INTEGER_MESSAGE);
            i++;
        } 
        else if (args[i] == "-t") {
            if (i + 1 >= argc) {
                throw std::invalid_argument(NO_VALUE_AFTER_FLAG_MESSAGE);
            }
            to = customStoi(args[i + 1], COULDNT_PARSE_INTEGER_MESSAGE);
            i++;
        }
        else {
            values.push_back(std::stoi(args[i]));
        }
    }

    Multiplier multiplier(from, to);
    multiplier.display_multiply_table(values);
}