#ifndef TABLE_SORTER_HPP
#define TABLE_SORTER_HPP

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
#include <sstream>
#include "types.hpp"

/**
 * @brief Class responsible for parsing, sorting and outputting tabular data.
 */
class TableSorter {
public:
    TableSorter(char separator,
                const std::vector<Column>& columns) : 
                separator_(separator),
                columns_(columns) 
    {
        std::transform(columns.begin(), columns.end(), 
            std::inserter(definedColumnTypes_, definedColumnTypes_.begin()),
            [](const Column& item) {
                return std::make_pair(item.idx, item.type);
            });
    }

    /**
     * @brief Parses the input stream into an internal table representation
     * @param input Input stream containing the table data
     * @throw std::runtime_error if the input format is invalid or inconsistent
     */
    void parse(std::istream &input);

    /**
     * @brief Sorts the table based on the columns specified in the constructor
     */
    void sort();

    /**
     * @brief Outputs the sorted table to the specified stream
     * @param output Stream where the sorted table should be written
     */
    void print(std::ostream &output);

private:
    char separator_;                              ///< Field separator character
    size_t number_of_columns_;                    ///< Number of columns in the table
    std::vector<Column> columns_;                 ///< Columns to sort by, in priority order
    std::vector<std::vector<ValueCell>> table_;   ///< Internal table representation
    std::map<size_t, ColumnType> definedColumnTypes_;  ///< Maps column indices to their types

    /**
     * @brief Determines the type of a column
     * @param idx Zero-based index of the column
     * @return ColumnType for the specified column (STRING if not explicitly defined)
     */
    ColumnType get_column_type(size_t idx);

    /**
     * @brief Validates the internal state of the TableSorter
     * @throw std::runtime_error if validation fails
     */
    void validate_state();

    /**
     * @brief Splits a line into fields using the specified separator
     * @param line The input line to split
     * @param separator Character to use as field delimiter
     * @return Vector of strings containing the split fields
     * @note If the line ends with a separator, an empty field is added
     */
    std::vector<std::string> split_line(const std::string &line, char separator);
};

#endif // TABLE_SORTER_HPP