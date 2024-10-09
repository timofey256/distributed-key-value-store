#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

/// Character is anything that can be stored in char.
/// Word      is anything that is separated by whitespace (' ', '\t', '\n', '\r' or whatever for which cctype.isspace(char) emits `true`)
/// Sentence  is anything that is separated by a sentence-delimiter ('.', '!', '?') AND a whitespace (or end of stream).

class SheepCounter {
private:
    int __was_last_whitespace = false;
    int __was_last_sentence_separator = false;

    std::vector<char> __sentence_separators = { '.', '!', '?' };

    bool is_sentence_separator(const char& c) {
        return std::find(__sentence_separators.begin(), __sentence_separators.end(), c) != __sentence_separators.end();
    }

    void process(const char& c) {
        ++number_of_characters;

        if (isspace(c) && !__was_last_whitespace)
            ++number_of_words;

        if (isspace(c) && __was_last_sentence_separator)
            ++number_of_sentences;

        __was_last_sentence_separator = is_sentence_separator(c);
        __was_last_whitespace = isspace(c);
    }
public:
    int number_of_sentences = 0;
    int number_of_words = 0;
    int number_of_characters = 0;

    void count(std::istream& s) {
        char c;
        for (;;) {
            c = s.get();
            if (s.fail())
                return;
            process(c);
        }
        
        if (!__was_last_whitespace) {   // we should regard end of stream as whitespace or sentence separator.
            ++number_of_words;
            ++number_of_sentences;
        }
    }
};

