#include "argparser.hpp"

ArgParser::ArgParser(size_t argc, char* argv[]) {
    for (size_t i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            process_flag(i, argc, argv);
        }
        else {
            process_column(arg);
        }
    }
}

void ArgParser::process_flag(size_t i, size_t argc, char* argv[]) {
    std::string arg = argv[i];
    if (arg.size() == 1)
        throw std::invalid_argument("Invalid commandline arguments: separated '-'.");

    if (arg.size() == 2) {
        if (i+1 == argc)
            throw std::invalid_argument("Invalid commandline arguments: you did not specify value.");

        auto value = argv[i + 1];
        arguments_[arg] = value;
    }
    else if (arg.size() > 2) {
        auto name = arg.substr(0, 1);
        auto value = arg.substr(2);
        
        arguments_[name] = value;
    }
}

std::optional<ColumnType> charToColumnType(char c) {
    switch(c) {
        case 'N': return ColumnType::NUMBER;
        case 'S': return ColumnType::STRING;
        default: return std::nullopt;
    }
}

void ArgParser::process_column(const std::string& arg) {
    auto type = arg[0];
    size_t idx;
    try {
        idx = std::stoi(arg.substr(1));
    }
    catch(const std::exception& e) {
        throw std::invalid_argument("Couldn't parse index of column " + arg);
    }
    auto typeOpt = charToColumnType(type);

    if (typeOpt == std::nullopt)
        throw std::invalid_argument("Couldn't parse type of column " + arg);

    auto column = Column(typeOpt.value(), idx);
    columns_.push_back(column);
}

std::optional<std::string> ArgParser::get_flag_value(const std::string& name) {
    auto it = arguments_.find(name);
    
    if (it != arguments_.end()) {
        return it->second;
    }
    
    return std::nullopt;
}

std::vector<Column> ArgParser::get_columns() {
    return columns_;
}