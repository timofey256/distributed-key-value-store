#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <vector>

class MultiplicationTable {
private:
    int from_;
    int to_;
    std::vector<int> numbers_;

public:
    MultiplicationTable();
    void setRange(int from, int to);
    void addNumber(int number);
    void print() const;
};

void printUsage();

#endif // MAIN_HPP