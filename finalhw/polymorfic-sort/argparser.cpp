#include "argparser.hpp"

ArgParser::ArgParser(size_t argc, char* argv[]) {
    for (size_t i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            process_flag(i, argc, argv);

            // if the current word was flag, then the next had to be value
            // and we already parsed it, so we should skip it.
            if (arg.size() == 2) 
                ++i;
        }
        else {
            process_column(arg);
        }
    }
}

void ArgParser::process_flag(size_t i, size_t argc, char* argv[]) {
    std::string arg = argv[i];
    size_t flag_length = 2; // "-i" or "-o" ...
    if (arg.size() < flag_length)
        throw std::invalid_argument("error: Invalid commandline arguments: separated '-'.");

    if (arg.size() == flag_length) {
        if (i+1 == argc)
            throw std::invalid_argument("error: Invalid commandline arguments: you did not specify value.");

        auto value = argv[i + 1];
        arguments_[arg] = value;
    }
    else if (arg.size() > flag_length) {
        auto name = arg.substr(0, flag_length);
        auto value = arg.substr(flag_length);
        
        arguments_[name] = value;
    }
}

std::optional<ColumnType> char_to_column_type(char c) {
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
        throw std::invalid_argument("error: Couldn't parse index of column " + arg);
    }
    auto typeOpt = char_to_column_type(type);

    if (typeOpt == std::nullopt)
        throw std::invalid_argument("error: Couldn't parse type of column " + arg);

    validate_column(idx);
    idx -= 1; // For user columns are 1-based but I want to keep it 0-based inside implementation.
    auto column = Column(typeOpt.value(), idx);
    columns_.push_back(column);
}

void ArgParser::validate_column(size_t idx) {
    if (idx <= 0)
        throw std::invalid_argument("error: Column indices are 1-based.");
}

std::optional<std::string> ArgParser::get_flag_value(const std::string& name) {
    auto it = arguments_.find(name);
    
    if (it != arguments_.end()) {
        return it->second;
    }
    
    return std::nullopt;
}

const std::vector<Column>& ArgParser::get_columns() const {
    return columns_;
}