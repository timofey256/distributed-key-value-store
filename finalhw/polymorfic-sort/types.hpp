#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstddef>
#include <memory>

enum ColumnType {
    NUMBER,
    STRING
};

struct Column {
    ColumnType type;
    size_t idx;
};

class AbstractCell {
public:
    virtual ~AbstractCell() = default;
    virtual bool operator>(const AbstractCell& other) const = 0;
};

using ValueCell = std::unique_ptr<AbstractCell>;

class IntCell : public AbstractCell {
    int value;
public:
    IntCell(std::string stringVal) {
        value = std::stoi(stringVal);
    }

    bool operator>(const AbstractCell& other) const override {
        const IntCell& intOther = dynamic_cast<const IntCell&>(other);
        return value > intOther.value;
    }
};

class StringCell : public AbstractCell {
    std::string value;
public:
    StringCell(std::string stringVal) {
        value = std::stoi(stringVal);
    }

    bool operator>(const AbstractCell& other) const override {
        const StringCell& strOther = dynamic_cast<const StringCell&>(other);
        return value > strOther.value;
    }
};

#endif // TYPES_HPP