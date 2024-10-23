#include <iostream>
#include <map>
#include <string>

using uint = unsigned int;

class MySomeSortOfDictionary {
private:
    std::map<std::string, uint> frequency_;

public:
    void append(const std::string& str) {
        if (frequency_.find(str) == frequency_.end())
            frequency_.insert({ str, 1 });
        else
            ++frequency_[str];
    }

    void append(char* argv[], int argn) {
        for (int i = 0; i < argn; i++) {
            append(argv[i]);
        }
    }

    void append(std::istream& s) {
        std::string str(std::istreambuf_iterator<char>(s), {}); // https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
        append(str);
    }

    std::map<std::string, uint> get_frequency_map() {
        return frequency_;
    }
};

template<typename T, typename U>
void print_map(std::map<T, U> map) {
    for (auto const& el : map) {
        std::cout << el.first << " : " << el.second << std::endl;
    }
}

int main(int argc, char* argv[])
{
    MySomeSortOfDictionary d;
    d.append("hello");
    d.append("hello");
    d.append("hello");
    d.append("hello2");
    d.append("hello2");
    d.append(argv, argc);

    print_map(d.get_frequency_map());
}
