#include "Dictionary.h"
#include <stdexcept>
#include <format>

void Dictionary::add(std::string word, std::string translation) {
	if (dictionary_.find(word) == dictionary_.end()){
		std::set<std::string> new_set;
		dictionary_.insert({ word, new_set });
	}
	
	dictionary_[word].insert(translation);
}

void Dictionary::remove(std::string word, std::string translation) {
	if (dictionary_.find(word) != dictionary_.end()) {
		auto it = dictionary_[word].find(translation);
		dictionary_[word].erase(it);
	}
}

void Dictionary::remove(std::string word) {
	auto it = dictionary_.find(word);
	if (it != dictionary_.end()) {
		dictionary_.erase(it);
	}
}

std::set<std::string> Dictionary::find(std::string word) {
	if (dictionary_.find(word) != dictionary_.end()) {
		return dictionary_[word];
	}

	throw std::invalid_argument(std::format("Word {} not found in the dictionary.", word));
}
