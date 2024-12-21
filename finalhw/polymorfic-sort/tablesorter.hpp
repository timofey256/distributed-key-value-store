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

class TableSorter {
public:
    TableSorter(char separator,
                std::vector<Column> columns) : 
                separator_(separator),
                columns_(columns) 
    {
        std::transform(columns.begin(), columns.end(), 
            std::inserter(definedColumnTypes_, definedColumnTypes_.begin()),
            [](const Column& item) {
                return std::make_pair(item.idx, item.type);
            });
    }

    void parse(std::istream &input);

    void sort();

    void print(std::ostream &output);

private:
    char separator_;
    std::vector<Column> columns_;
    std::vector<std::vector<ValueCell>> table_;
    std::map<size_t, ColumnType> definedColumnTypes_;

    ColumnType get_column_type(size_t idx);
};

#endif // TABLE_SORTER_HPP