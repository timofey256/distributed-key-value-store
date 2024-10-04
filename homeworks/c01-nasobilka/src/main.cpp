#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include "utils.hpp"

class Multiplier {
public:
    Multiplier(std::optional<int> from = {}, std::optional<int> to = {}) {
        constexpr int default_from = 1;
        constexpr int default_to   = 10;
        
        if (from > to) {
            print_warning("You have set `from` larger than `to`, your table won't output anything.");
        }

        _from = from.value_or(default_from);
        _to = to.value_or(default_to);
    }

    void display_multiply_table(int multiplier) const {
        for (int curr = _from; curr <= _to; curr++) {
            std::cout << curr << " * " << multiplier << " = " << curr*multiplier << std::endl;
        }
    }

    void display_multiply_table(const std::vector<int>& multipliers) const {
        for (const auto& m : multipliers) {
            display_multiply_table(m);
            std::cout << '\n';
        }
    }

private:
    int _from;
    int _to;
};

struct ParsedArguments {
    std::optional<int> from;
    std::optional<int> to;
    std::vector<int> values;
};

Result<ParsedArguments, std::string> try_parse_arguments(int argc, char** args) {
    std::string failed_to_parse_int = "Passed arguments are incorrect: couldn't parse a passed argument.";
    std::string no_value_after_flag = "Passed arguments are incorrect: no value after flag.";

    if (argc == 1) {
        print_warning("You didn't pass any arguments.");
    }

    ParsedArguments parsed{{}, {}, {}};

    for (int i = 1; i < argc; i++) { // start from 1, because first argument is the name of the project
        if ((std::string(args[i]) == "-f") || (std::string(args[i]) == "-t")) {
            if (i + 1 >= argc) {
                return Result<ParsedArguments, std::string>(no_value_after_flag);
            }

            auto result = tryStoi(args[i + 1]);
            if (!result.has_value()) {
                return Result<ParsedArguments, std::string>(failed_to_parse_int);
            }

            (std::string(args[i]) == "-f" ? parsed.from : parsed.to) = result.value();
            i++;
        }
        else {
            std::cout << args[i] << std::endl;
            auto result = tryStoi(args[i]);
            if (!result.has_value()) {
                return Result<ParsedArguments, std::string>(failed_to_parse_int);
            }
            parsed.values.push_back(result.value());
        }
    }

    return Result<ParsedArguments, std::string>(parsed);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    Result<ParsedArguments, std::string> result = try_parse_arguments(argc, argv);
    
    if (result.is_error()) {
        print_error(result.error());
        return 1;
    }

    Multiplier multiplier(result.value().from, result.value().to);
    multiplier.display_multiply_table(result.value().values);
}