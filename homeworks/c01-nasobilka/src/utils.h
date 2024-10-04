#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Tries to cast a given string to int. If not successful, throws std::invalid_argument with custom message.
 * @param str String to cast
 * @param msg Error message
 */
int customStoi(const std::string& str, const char* msg);

#endif // UTILS_H