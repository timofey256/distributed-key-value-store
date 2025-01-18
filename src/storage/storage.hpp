#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <optional>
#include <vector>
#include <shared_mutex>
#include <unordered_map>
#include <stdexcept>

class Storage {
public:
    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    bool remove(const std::string& key);
    
    bool exists(const std::string& key);
    size_t count() const;
    void clear();

    std::vector<std::string> getAllKeys();

private:
    mutable std::shared_mutex mutex_;  // mutable because we need to lock in const methods
    std::unordered_map<std::string, std::string> data_;
};

class StorageError : public std::runtime_error {
public:
    explicit StorageError(const std::string& msg) : std::runtime_error(msg) {}
};

class KeyNotFoundError : public StorageError {
public:
    explicit KeyNotFoundError(const std::string& key) 
        : StorageError("Key not found: " + key), key_(key) {}
    const std::string& key() const { return key_; }
private:
    std::string key_;
};

#endif