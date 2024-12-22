#include "tablesorter.hpp"

// Add an anonymous namespace to prevent `make_comparator` from being visible on the outside, as it's an implementation detail
namespace {  
    auto make_comparator(const std::vector<size_t>& columnIndices) {
        return [&columnIndices](const std::vector<ValueCell>& row1, 
                            const std::vector<ValueCell>& row2) {
            for (size_t colIndex : columnIndices) {
                if (*row1[colIndex] > *row2[colIndex]) return false;
                if (*row2[colIndex] > *row1[colIndex]) return true;
            }
            return false;
        };
    }
}

std::vector<std::string> TableSorter::split_line(const std::string& line, char separator) {
    // Implementation discussion:
    // this approach involves several string copies that could be optimized,
    // but i've prioritized code clarity over performance since this isn't a bottleneck.  
    std::vector<std::string> result;
    std::string field;
    std::istringstream stream(line);
    
    while (std::getline(stream, field, separator)) {
        result.push_back(field);
    }

    // if the line ends with a separator, add an empty field.
    if (!line.empty() && line.back() == separator) {
        result.push_back("");
    }
    
    return result;
}

ColumnType TableSorter::get_column_type(size_t idx) {
    if (definedColumnTypes_.find(idx) != definedColumnTypes_.end())
        return definedColumnTypes_[idx];

    return ColumnType::STRING; // According to the assignment, if type was not specified, it's string.
}

void TableSorter::validate_state() {
    auto is_greated_than_number_of_columns = [this](Column column) {
        return column.idx > number_of_columns_-1;
    };

    auto it = std::find_if(columns_.begin(), columns_.end(), is_greated_than_number_of_columns);
    if (it != columns_.end())
        throw std::runtime_error("error: You specified a column index that is greater than number of columns.");
}

void TableSorter::parse(std::istream &input) {
    table_.clear();
    number_of_columns_ = 0;

    std::string line;
    while (std::getline(input, line)) {
        std::vector<ValueCell> row;
        auto rawStringCells = split_line(line, separator_);

        if (number_of_columns_ == 0) {
            number_of_columns_ = rawStringCells.size();
        } else if (rawStringCells.size() != number_of_columns_) {
            throw std::runtime_error("error: Inconsistent number of columns at line: " + line);
        }

        for (size_t idx = 0; idx < rawStringCells.size(); ++idx) {
            auto field = rawStringCells[idx];
            auto type = get_column_type(idx);

            switch (type) {
                case ColumnType::NUMBER:
                    row.emplace_back(make_unique<IntCell>(field));
                    break;
                case ColumnType::STRING:
                    row.emplace_back(make_unique<StringCell>(field));
                    break;
                default:
                    throw std::invalid_argument("error: Could not identify type of cell");
                    break;
            }
        }

        table_.push_back(std::move(row));
    }

    validate_state();
}

void TableSorter::sort() {
    std::vector<size_t> columnPriorities(columns_.size());

    std::transform(columns_.begin(), columns_.end(), columnPriorities.begin(),
        [](const Column& x) {
            return x.idx;
        });

    std::sort(table_.begin(), table_.end(), make_comparator(columnPriorities));
}

void TableSorter::print(std::ostream &output) {
    for (const auto& row : table_) {
        size_t length = row.size();
        for (size_t idx = 0; idx < length; ++idx) {
            auto& cell = row[idx];
            output << cell->to_string();
            if (idx != length-1)
                output << separator_;
        }
        output << '\n';
    }
}