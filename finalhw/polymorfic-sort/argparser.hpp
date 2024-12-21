#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <optional>
#include <vector>
#include "types.hpp"

class ArgParser
{
public:
    ArgParser() = delete;
    ArgParser(size_t argc, char *argv[]);

    /// @brief If argument with flag `name` was parsed, returns its value.
    ///        If not, return std::nullopt.
    /// @param name name of flag
    std::optional<std::string> get_flag_value(const std::string& name);

    std::vector<Column> get_columns();

private:
    /// @brief Map flag to value.
    std::map<std::string, std::string> arguments_;
    
    /// @brief Vector of columns for sorting. From the most to the least priority.
    std::vector<Column> columns_;

    void process_column(const std::string& arg);

    void process_flag(size_t i, size_t argc, char *argv[]);
};

#endif // ARGPARSER_HPP