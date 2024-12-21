#include "tablesorter.hpp"

auto makeComparator(const std::vector<size_t>& columnIndices) {
    return [&columnIndices](const std::vector<ValueCell*>& row1, const std::vector<ValueCell*>& row2) {
        for (size_t colIndex : columnIndices) {
            if (*row1[colIndex] > *row2[colIndex]) return false;
            if (*row2[colIndex] > *row1[colIndex]) return true;
        }
        return false;
    };
}

std::vector<std::string> splitLine(const std::string& line, char separator) {
    std::vector<std::string> result;
    std::string field;
    std::istringstream stream(line);
    
    while (std::getline(stream, field, separator)) {
        result.push_back(field);
    }
    
    return result;
}

ColumnType TableSorter::get_column_type(size_t idx) {
    if (definedColumnTypes_.find(idx) != definedColumnTypes_.end())
        return definedColumnTypes_[idx];

    return ColumnType::STRING; // As per assignment, if type was not specified, it's string.
}

void TableSorter::parse(std::istream &input) {
    table_.clear();
    std::string line;
    size_t expectedColumns = 0;

    while (std::getline(input, line)) {
        std::vector<ValueCell> row;
        auto rawStringCells = splitLine(line, separator_);

        if (expectedColumns == 0) {
            expectedColumns = rawStringCells.size();
        } else if (rawStringCells.size() != expectedColumns) {
            throw std::runtime_error("Inconsistent number of columns at line: " + line);
        }

        std::string field;
        size_t idx = 0;
        while (std::getline(input, field, separator_)) {
            auto type = get_column_type(idx);
            
            switch (type) {
                case ColumnType::STRING:
                    row.emplace_back(make_unique<IntCell>(field));
                    break;
                case ColumnType::NUMBER:
                    row.emplace_back(make_unique<StringCell>(field));
                    break;
                default:
                    throw std::invalid_argument("Could not identify type of cell");
                    break;
            }

            ++idx;
        }

        table_.push_back(row);
    }
}

void TableSorter::sort() {
    std::vector<size_t> output(columns_.size());

    std::transform(columns_.begin(), columns_.end(), output.begin(),
        [](const Column& x) {
            return x.idx;
        });

    std::sort(table_.begin(), table_.end(), makeComparator(output));
}

void TableSorter::print(std::ostream &output) {

}