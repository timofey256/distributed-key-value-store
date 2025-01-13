#include <mutex>
#include "storage.hpp"

void Storage::put(const std::string& key, const std::string& value) {
    std::unique_lock lock(mutex_);  // Exclusive lock for writing
    data_[key] = value;
}

std::optional<std::string> Storage::get(const std::string& key) {
    std::shared_lock lock(mutex_);  // Shared lock for reading
    auto it = data_.find(key);
    if (it != data_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool Storage::remove(const std::string& key) {
    std::unique_lock lock(mutex_);
    return data_.erase(key) > 0;
}

bool Storage::exists(const std::string& key) {
    std::shared_lock lock(mutex_);
    return data_.find(key) != data_.end();
}

size_t Storage::count() const {
    std::shared_lock lock(mutex_);
    return data_.size();
}

void Storage::clear() {
    std::unique_lock lock(mutex_);
    data_.clear();
}

std::vector<std::string> Storage::getAllKeys() {
    std::shared_lock lock(mutex_);
    std::vector<std::string> keys;
    keys.reserve(data_.size());
    for (const auto& pair : data_) {
        keys.push_back(pair.first);
    }
    return keys;
}