#include "types.hpp"

IntCell::IntCell(std::string stringVal) : AbstractCell(stringVal.empty()) {
    if (!stringVal.empty())
        value_ = std::stoi(stringVal);
    else
        value_ = std::numeric_limits<int>::max(); // For sorting purposes we want empty cells to be at the end.
}

bool IntCell::operator>(const AbstractCell& other) const {
    const IntCell* intOther = dynamic_cast<const IntCell*>(&other);
    if (!intOther)
        throw std::invalid_argument("Cannot compare IntCell with different cell type");
    return value_ > intOther->value_;
}

std::string IntCell::to_string() const {
    if (is_empty_)
        return "";
    return std::to_string(value_);
}

StringCell::StringCell(std::string stringVal) : 
    AbstractCell(stringVal.empty()),
    value_(std::move(stringVal)) { }

bool StringCell::operator>(const AbstractCell& other) const {
    const StringCell* strOther = dynamic_cast<const StringCell*>(&other);
    if (!strOther)
            throw std::invalid_argument("Cannot compare StringCell with different cell type");
    return value_ > strOther->value_;
}

std::string StringCell::to_string() const {
    return value_;
}