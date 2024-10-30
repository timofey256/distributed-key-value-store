#pragma once

#include <string>
#include <map>
#include <set>

class Dictionary
{
private:
	std::map<std::string, std::set<std::string>> dictionary_;

public:
	/// <summary>
	/// Adds word with its translation to the dictionary.
	/// </summary>
	/// <param name="word">Word</param>
	/// <param name="translation">Word's translation to add</param>
	void add(std::string word, std::string translation);

	/// <summary>
	/// Removes a specific translation of a word. If translation is not there, does nothing.
	/// </summary>
	/// <param name="word">Word</param>
	/// <param name="translation">Word's translation to remove</param>
	void remove(std::string word, std::string translation);

	/// <summary>
	/// Removes word from the dictionary together with all its translations.
	/// </summary>
	/// <param name="word"></param>
	void remove(std::string word);

	/// <summary>
	/// Returns all translations of a word. If word is not in the dictionary, throws std::invalud_argument.
	/// </summary>
	/// <param name="word"></param>
	/// <returns></returns>
	std::set<std::string> find(std::string word);
};

