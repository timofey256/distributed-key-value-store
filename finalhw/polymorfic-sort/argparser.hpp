#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <optional>
#include <vector>
#include "types.hpp"

/**
 * @brief Class for parsing and managing command-line arguments
 * 
 * ArgParser handles two types of arguments:
 * 1. Flags: Arguments starting with '-' followed by their values (e.g., -i input.txt)
 * 2. Column definitions: Arguments defining column types and indices (e.g., N1 for numeric column 1)
 */
class ArgParser
{
public:
    ArgParser() = delete;   // We don't need the default ctor.

    /**
     * @brief Constructs ArgParser and processes command line arguments
     * @param argc Number of command line arguments
     * @param argv Array of command line argument strings
     * @throw std::invalid_argument if arguments are malformed
     */
    ArgParser(size_t argc, char *argv[]);

    /**
     * @brief If argument with flag `name` was parsed, returns its value.
     * If not, return std::nullopt.
     * @param name name of flag
     * @return Optional containing the flag's value if present, empty optional otherwise
     */
    std::optional<std::string> get_flag_value(const std::string& name);

    const std::vector<Column>& get_columns() const;

private:
    std::map<std::string, std::string> arguments_;  ///< Maps flags to their values
    std::vector<Column> columns_;  ///< Stores column definitions in priority order

    /**
     * @brief Processes a column definition argument
     * @param arg String containing the column definition (e.g., "N1", "S2")
     * @throw std::invalid_argument if the column definition is invalid
     */
    void process_column(const std::string& arg);

    /**
     * @brief Processes a flag argument and its value
     * @param i Current argument index
     * @param argc Total number of arguments
     * @param argv Array of argument strings
     * @throw std::invalid_argument if the flag format is invalid
     */
    void process_flag(size_t i, size_t argc, char *argv[]);

    /**
     * @brief Validates a column index
     * @param idx Column index to validate
     * @throw std::invalid_argument if the index is invalid
     */
    void validate_column(size_t idx);
};

#endif // ARGPARSER_HPP