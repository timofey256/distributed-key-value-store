#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstddef>
#include <memory>
#include <limits>
#include <iostream>

/**
 * @brief Enumerates the possible types of columns in the table
 */
enum ColumnType {
    NUMBER,
    STRING  
};

struct Column {
    ColumnType type;  
    size_t idx;
};

/**
 * @brief Abstract base class representing a cell in the table
 * 
 * Provides interface for comparison and string conversion operations
 * that must be implemented by concrete cell types.
 */
class AbstractCell {
protected:
    const bool is_empty_;

public:
    explicit AbstractCell(bool empty) : is_empty_(empty) {}

    virtual ~AbstractCell() = default;

    /**
     * @brief Compares this cell with another cell
     * @param other The cell to compare with
     * @return true if this cell's value is greater than the other's
     */
    virtual bool operator>(const AbstractCell &other) const = 0;

    /**
     * @brief Converts the cell's value to a string representation. Should be empty string for empty cells.
     * @return String representation of the cell's value
     */
    virtual std::string to_string() const = 0;
};

using ValueCell = std::unique_ptr<AbstractCell>;

class IntCell : public AbstractCell {
private:
    int value_;
public:
    /**
     * @brief Constructs an IntCell from a string value
     * @param stringVal String representation of the integer
     * @note Empty strings are treated as maximum integer value
     */
    IntCell(std::string stringVal);

    bool operator>(const AbstractCell& other) const override;
    std::string to_string() const override;
};

class StringCell : public AbstractCell {
private:
    std::string value_; 
public:
    /**
     * @brief Constructs a StringCell from a string value
     * @param stringVal The string to store
     */
    StringCell(std::string stringVal);

    bool operator>(const AbstractCell& other) const override;
    std::string to_string() const override;
};

#endif // TYPES_HPP