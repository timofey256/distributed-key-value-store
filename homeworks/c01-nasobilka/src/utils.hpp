#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>

/**
 * @brief Result type. Something like F# has.
 */
template<typename T, typename E>
class Result {
    // If you ask why at all do I need this: 
    // I don't want to use exceptions, status codes, or anything like that for logic flow.
    // A bit of an overkill for this homework, of course. 
    // Also: ChatGPT helped me with templates.
public:
    Result(T value);
    Result(E error);
    
    bool is_success() const;
    bool is_error() const;
    
    T& value();
    E& error();

private:
    std::optional<T> value_;
    std::optional<E> error_;
};

template<typename T, typename E>
Result<T, E>::Result(T value) : value_(std::move(value)), error_{} {}

template<typename T, typename E>
Result<T, E>::Result(E error) : value_{}, error_(std::move(error)) {}

template<typename T, typename E>
bool Result<T, E>::is_success() const { return value_.has_value(); }

template<typename T, typename E>
bool Result<T, E>::is_error() const { return error_.has_value(); }

template<typename T, typename E>
T& Result<T, E>::value() { return value_.value(); }

template<typename T, typename E>
E& Result<T, E>::error() { return error_.value(); }

/**
 * @brief Tries to cast a given string to std::option<int>. If successful, return a value. If not, returns {}.
 * @param str String to cast
 */
std::optional<int> tryStoi(const std::string& str);

/**
 * @brief Prints warning.
 * @param msg Warning message.
 */
void print_warning(std::string msg);

/**
 * @brief Prints error.
 * @param msg Warning message.
 */
void print_error(std::string msg);

#endif // UTILS_H